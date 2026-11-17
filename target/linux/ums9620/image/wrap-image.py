#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-only
"""Wrap an arm64 Image into the layout the Unisoc LK bootloader on the UMS9620 expects.

LK always copies the kernel to 0x80080000 and branches there (the "text_offset"
of pre-5.8 kernels, 0x80000, which is also what its boot header check accepts).
A kernel since 5.8 has text_offset 0 and must be placed on a 2 MiB boundary, so a
bare Image loaded at 0x80080000 is rejected or dies at once.

This prepends a stub that carries a valid arm64 Image header whose first
instruction branches 0x180000 bytes forward: 0x80080000 + 0x180000 = 0x80200000,
where the first 2 MiB boundary inside a 2 MiB-aligned region above the load
address falls, and where the real Image is. x0 (the DTB pointer) is passed
through untouched. The device tree is not part of this image: LK merges the
vendor dtbo and passes the result in vendor_boot, which is why the target has no
device tree of its own.

Proven on the device by mu300-linux (upstream/wrap-image.py, its FINDINGS 31);
this is the same layout, kept here so the target does not depend on that
checkout to produce a bootable kernel.

usage: wrap-image.py <Image> <Image.lk>
"""
import struct
import sys

GAP = 0x180000          # 0x80080000 (where LK branches) + GAP = 0x80200000 (2 MiB aligned)
ARM64_IMAGE_MAGIC = b'ARMd'
IMAGE_HEADER_SIZE = 64


def main(src, dst):
    img = open(src, 'rb').read()
    if img[56:60] != ARM64_IMAGE_MAGIC:
        sys.exit('%s: not an arm64 Image (no ARMd magic at offset 56)' % src)
    text_offset, image_size, flags = struct.unpack_from('<QQQ', img, 8)

    branch = 0x14000000 | (GAP // 4)        # b #GAP (imm26, in instructions)
    header = struct.pack('<IIQQQQQQ', branch, 0, 0x80000, GAP + image_size, flags, 0, 0, 0)
    header += ARM64_IMAGE_MAGIC + struct.pack('<I', 0)
    assert len(header) == IMAGE_HEADER_SIZE, len(header)

    stub = header + b'\0' * (GAP - IMAGE_HEADER_SIZE)
    with open(dst, 'wb') as f:
        f.write(stub)
        f.write(img)

    print('%s: stub %#x + Image %#x (image_size %#x, text_offset was %#x)'
          % (dst, GAP, len(img), image_size, text_offset))


if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    main(sys.argv[1], sys.argv[2])
