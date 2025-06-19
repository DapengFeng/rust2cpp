/*
 * Copyright (c) 2025 Dapeng Feng
 * All rights reserved.
 */

use crate::ffi::MultiBuf;

pub fn next_chunk(buf: &mut MultiBuf) -> &[u8] {
  let next_len = buf.lens.get(buf.len_pos).unwrap_or(&0);
  let next = buf.chunks.get(buf.pos..(buf.pos + next_len));
  buf.pos += next_len;
  buf.len_pos += 1;
  next.unwrap_or(&[])
}
