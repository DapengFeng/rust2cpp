/*
 * Copyright (c) 2025 Dapeng Feng
 * All rights reserved.
 */

#include <iostream>

#include "blobstore.hpp"  // NOLINT

int main(int argc, char const *argv[]) {
  auto client = org::blobstore::new_blobstore_client();
  auto chunks = rust::Vec<uint8_t>{
      'H', 'e', 'l', 'l', 'o', ',', ' ',
      'w', 'o', 'r', 'l', 'd', '!'};  // Create a vector of byte vectors
  auto buf = org::blobstore::MultiBuf{
      .chunks = std::move(chunks), .lens = {7, 6},
           .pos = 0, .len_pos = 0
  };
  auto blobid = client->put(buf);
  std::cout << "blobid: " << blobid << std::endl;

  client->tag(blobid, "greeting");
  auto metadata = client->metadata(blobid);
  std::cout << "tags: = [\"";
  for (const auto &tag : metadata.tags) std::cout << tag;
  std::cout << "\"]" << std::endl;
  return 0;
}
