cmake_minimum_required(VERSION 3.21)

project(
    rust2cpp
    VERSION 0.3.0
    LANGUAGES C CXX
    DESCRIPTION "Exposed Rust library for C++"
)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(ENABLE_LIO "Enable cross language linking time optimization" ON)
if(ENABLE_LIO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported OUTPUT error)
    if(ipo_supported)
        message(STATUS "Link Time Optimization (LTO) is enabled")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        # corrosion_add_target_rustflags(rust2cpp_rust "-Clto" "--verbose")
    else()
        message(
            WARNING
            "Link Time Optimization (LTO) is not supported: ${error}"
        )
    endif()
endif()

include(FetchContent)
FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
    GIT_TAG v0.5.2
)
FetchContent_MakeAvailable(Corrosion)

corrosion_import_crate(MANIFEST_PATH Cargo.toml PROFILE release)

corrosion_add_cxxbridge(rust2cpp_abi CRATE rust2cpp_rust MANIFEST_PATH src FILES lib.rs)

add_library(${PROJECT_NAME}_lib src/blobstore.cpp)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC rust2cpp_abi)
target_include_directories(
    ${PROJECT_NAME}_lib
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)
