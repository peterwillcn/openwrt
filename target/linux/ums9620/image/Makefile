# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

# The kernel artifact this target produces is not an Image the bootloader can
# take: LK branches to a fixed address, so the Image is wrapped (see
# wrap-image.py) before it is written into a boot slot.
define Build/lk-image
	python3 $(CURDIR)/wrap-image.py $< $@
endef

define Device/Default
	PROFILES := Default
	KERNEL := kernel-bin
	KERNEL_NAME := Image
	DEVICE_DTS :=
	# LK loads the wrapped image at 0x80080000 and the stub branches to
	# 0x80200000; nothing has to be placed by the image builder itself.
	KERNEL_LOADADDR := 0x80080000
endef

define Device/zte_f50
	DEVICE_VENDOR := ZTE
	DEVICE_MODEL := F50
	DEVICE_ALT0_VENDOR := ZTE
	DEVICE_ALT0_MODEL := MU300
	DEVICE_PACKAGES := kmod-zte-card-holder-det
	# No DTS: the device tree comes from the stock vendor_boot partition, which
	# LK merges with the dtbo and passes to the kernel. A device tree in the
	# kernel image is not used and one of our own was rejected (mu300-linux
	# upstream/README.md).
	IMAGES := Image.lk
	IMAGE/Image.lk := lk-image
	SUPPORTED_DEVICES := zte,f50 zte,mu300
endef
TARGET_DEVICES += zte_f50

$(eval $(call BuildImage))
