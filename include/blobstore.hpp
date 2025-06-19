/*
 * Copyright (c) 2025 Dapeng Feng
 * All rights reserved.
 */

#pragma once
#include <memory>

#include "rust/cxx.h"
#include "rust2cpp_abi/lib.h"

namespace org {
namespace blobstore {

struct MultiBuf;
struct BlobMetadata;

class BlobstoreClient {
 public:
  BlobstoreClient();
  uint64_t put(MultiBuf &buf) const;  // NOLINT
  void tag(uint64_t blobid, rust::Str tag) const;
  BlobMetadata metadata(uint64_t blobid) const;

 private:
  class impl;
  std::shared_ptr<impl> impl;
};

std::unique_ptr<BlobstoreClient> new_blobstore_client();

}  // namespace blobstore
}  // namespace org
