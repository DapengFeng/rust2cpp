# rust2cpp

A demonstration project showcasing seamless interoperability between Rust and C++ using [cxx](https://cxx.rs/) and [Corrosion](https://corrosion-rs.github.io/corrosion/). This project implements a toy blobstore system where Rust provides high-performance data processing functions that are consumed by a C++ application.

## 🚀 Features

- **Rust-C++ FFI**: Safe and efficient interoperability using the `cxx` crate
- **Modern Build System**: CMake with Corrosion for seamless Rust integration
- **Cross-Language Data Structures**: Shared structs and types between Rust and C++
- **Memory Safety**: Zero-copy data sharing where possible
- **Link Time Optimization**: Optional LTO support for maximum performance

## 📁 Project Structure

```
rust2cpp/
├── src/
│   ├── lib.rs          # Rust FFI bridge definition
│   ├── blobstore.rs    # Rust implementation
│   ├── main.cpp        # C++ application entry point
│   └── blobstore.cpp   # C++ blobstore client implementation
├── include/
│   └── blobstore.hpp   # C++ header with class definitions
├── Cargo.toml          # Rust package configuration
├── CMakeLists.txt      # CMake build configuration
└── build.rs            # Rust build script
```

## 🛠️ Building the Project

### Prerequisites

- **Rust**: Install from [rustup.rs](https://rustup.rs/)
- **CMake**: Version 3.21 or higher
- **C++ Compiler**: Supporting C++17 (GCC, Clang, or MSVC)
- **Ninja**: Build system (optional but recommended)

### Build Steps

1. **Clone the repository**:
   ```bash
   git clone https://github.com/DapengFeng/rust2cpp.git
   cd rust2cpp
   ```

2. **Configure with CMake**:
   ```bash
   cmake -B build -G Ninja
   ```

3. **Build the project**:
   ```bash
   cmake --build build
   ```

4. **Run the example**:
   ```bash
   ./build/rust2cpp
   ```

### Build Options

- **Shared Libraries**: Use `-DBUILD_SHARED_LIBS=ON` (default)
- **Link Time Optimization**: Use `-DENABLE_LIO=ON` (default, requires LTO support)

## 🎯 How It Works

The project demonstrates a blobstore system with the following architecture:

### Rust Side (`src/lib.rs`, `src/blobstore.rs`)

- Defines the FFI bridge using `#[cxx::bridge]`
- Implements `next_chunk()` function for processing multi-buffer data
- Exports shared data structures like `MultiBuf` and `BlobMetadata`

### C++ Side (`src/blobstore.cpp`, `include/blobstore.hpp`)

- Implements `BlobstoreClient` class with methods:
  - `put()`: Upload data using Rust's chunk processing
  - `tag()`: Add metadata tags to blobs
  - `metadata()`: Retrieve blob information
- Uses Rust functions seamlessly through generated bindings

### Example Usage

```cpp
auto client = org::blobstore::new_blobstore_client();
auto chunks = rust::Vec<uint8_t> {'H','e','l','l','o',',',' ','w','o','r','l','d','!'};
auto buf = org::blobstore::MultiBuf{
    .chunks = std::move(chunks),
    .lens = {7, 6},
    .pos = 0,
    .len_pos = 0
};

auto blobid = client->put(buf);           // Uses Rust's next_chunk()
client->tag(blobid, "greeting");         // Add metadata
auto metadata = client->metadata(blobid); // Retrieve info
```

## 🔧 Technical Details

### Dependencies

**Rust**:
- `cxx` - Safe FFI bindings
- `cxx-build` - Build-time code generation
- `miette` - Error handling in build scripts

**C++**:
- Standard library containers (`std::vector`, `std::unordered_map`)
- Memory management (`std::unique_ptr`, `std::shared_ptr`)

### Build Integration

- **Corrosion**: Integrates Rust builds into CMake
- **cxxbridge**: Generates C++ headers from Rust bridge definitions
- **Static Linking**: Rust code compiled as static library
- **Profile**: Release builds with full optimizations

## 📊 Performance Features

- **Zero-Copy**: Data structures shared without copying where possible
- **Link Time Optimization**: Cross-language LTO when supported
- **Release Profile**: Aggressive optimizations (`opt-level = 3`, `lto = true`)
- **Static Linking**: Eliminates runtime dependencies

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Ensure code passes linting (cpplint configuration included)
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🔗 Related Projects

- [cxx](https://github.com/dtolnay/cxx) - Safe FFI between Rust and C++
- [Corrosion](https://github.com/corrosion-rs/corrosion) - CMake integration for Rust

---

*Copyright (c) 2025 Dapeng Feng. All rights reserved.*
