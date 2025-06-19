/*
 * Copyright (c) 2025 Dapeng Feng
 * All rights reserved.
 */

fn main() -> miette::Result<()> {
    cxx_build::bridge("src/lib.rs").std("c++17");

    println!("cargo:rerun-if-changed=src/lib.rs");
    Ok(())
}
