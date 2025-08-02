#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_VERSION:=2017.09
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/friendlyarm/uboot-rockchip
PKG_SOURCE_VERSION:=nanopi5-v2017.09
PKG_MIRROR_HASH:=skip

PKG_MAINTAINER:=Claude AI <claude@anthropic.com>

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=rockchip
  UENV:=default
  HIDDEN:=1
endef

define U-Boot/nanopi-r76s-rk3576
  $(U-Boot/Default)
  BUILD_SUBTARGET:=armv8
  NAME:=NanoPi R76S RK3576 using M5 config
  BUILD_DEVICES:= \
    friendlyarm_nanopi-r76s
  UBOOT_CONFIG:=nanopi_m5
endef

UBOOT_TARGETS := \
  nanopi-r76s-rk3576

UBOOT_CONFIGURE_VARS += USE_PRIVATE_LIBGCC=yes

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) $(PKG_BUILD_DIR)/configs/nanopi_m5_defconfig $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/u-boot-dtb.bin $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot-rockchip.bin
endef

define Package/u-boot/install/default
endef

$(eval $(call BuildPackage/U-Boot))
