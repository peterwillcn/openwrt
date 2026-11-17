# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk

BOARD:=ums9620
BOARDNAME:=Unisoc UMS9620 (T760)
FEATURES:=ext4 fpu gpio rootfs-part rtc targz usb usbgadget
SUBTARGETS:=generic

KERNEL_PATCHVER:=6.18

define Target/Description
	Build firmware for devices based on the Unisoc UMS9620 (T760)
	SoC, such as the ZTE F50 / MU300 5G pocket router.

	The device boots through Android's boot chain: the kernel and the
	initramfs go into an Android boot image written to a boot slot and
	the root filesystem lives on the free area of the internal eMMC.
	There is no U-Boot, no partition table to write and no sysupgrade:
	see README in this directory.
endef

include $(INCLUDE_DIR)/target.mk

DEFAULT_PACKAGES += block-mount e2fsprogs f2fs-tools

$(eval $(call BuildTarget))
