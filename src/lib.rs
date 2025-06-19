/*
 * Copyright (c) 2025 Dapeng Feng
 * All rights reserved.
 */

mod blobstore;
use blobstore::*;

#[cxx::bridge(namespace = "org::blobstore")]
pub mod ffi {
    // Shared structs with fields visible to both languages.
    struct BlobMetadata {
        size: usize,
        tags: Vec<String>,
    }

    pub struct MultiBuf {
        pub chunks: Vec<u8>,
        pub lens: Vec<usize>,
        pub pos: usize,
        pub len_pos: usize,
    }

    // Rust types and signatures exposed to C++.
    extern "Rust" {
        fn next_chunk(buf: &mut MultiBuf) -> &[u8];
    }
}
