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

# NanoPi R76S RK3576
define U-Boot/nanopi-r76s-rk3576
  $(U-Boot/Default)
  BUILD_SUBTARGET:=armv8
  NAME:=NanoPi R76S (RK3576)
  BUILD_DEVICES:= \
    friendlyarm_nanopi-r76s
endef

UBOOT_TARGETS := \
  nanopi-r76s-rk3576

UBOOT_CONFIGURE_VARS += USE_PRIVATE_LIBGCC=yes

define Build/Prepare
	$(call Build/Prepare/Default)
	# 拷贝增量文件到构建目录
	$(if $(wildcard $(CURDIR)/src),$(CP) -a $(CURDIR)/src/* $(PKG_BUILD_DIR)/)
endef

# 基于nanopi-m5创建nanopi-r76s的defconfig
define Build/Configure
	# 复制nanopi-m5配置作为基础（如果存在）
	if [ -f $(PKG_BUILD_DIR)/configs/nanopi_m5_defconfig ]; then \
		$(CP) $(PKG_BUILD_DIR)/configs/nanopi_m5_defconfig $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		$(SED) 's/nanopi-m5/nanopi-r76s/g' $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		$(SED) 's/TARGET_NANOPI_M5/TARGET_NANOPI_R76S/g' $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		$(SED) 's/rk3576-nanopi-m5/rk3576-nanopi-r76s/g' $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		$(SED) '/ANDROID/d' $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		$(SED) '/AVB/d' $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_FASTBOOT is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_USB_FUNCTION_FASTBOOT is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_CMD_FASTBOOT is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_CMD_ROCKUSB is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_CMD_USB_MASS_STORAGE is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_USB_DWC3 is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_USB_DWC3_GADGET is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_USB_DWC3_GENERIC is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_USB_STORAGE is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_USB_GADGET is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_USB_XHCI_DWC3 is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		$(SED) '/OPTEE/d' $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_DM_VIDEO is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_DISPLAY is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "# CONFIG_DRM_ROCKCHIP is not set" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "CONFIG_DM_ETH=y" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "CONFIG_DM_ETH_PHY=y" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig && \
		echo "CONFIG_GMAC_ROCKCHIP=y" >> $(PKG_BUILD_DIR)/configs/nanopi-r76s-rk3576_defconfig; \
	fi
	$(call Build/Configure/U-Boot)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	# 尝试复制不同可能的U-Boot输出文件
	if [ -f $(PKG_BUILD_DIR)/u-boot-rockchip.bin ]; then \
		$(CP) $(PKG_BUILD_DIR)/u-boot-rockchip.bin $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot-rockchip.bin; \
	elif [ -f $(PKG_BUILD_DIR)/u-boot-dtb.img ]; then \
		$(CP) $(PKG_BUILD_DIR)/u-boot-dtb.img $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot-rockchip.bin; \
	elif [ -f $(PKG_BUILD_DIR)/u-boot.img ]; then \
		$(CP) $(PKG_BUILD_DIR)/u-boot.img $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot-rockchip.bin; \
	elif [ -f $(PKG_BUILD_DIR)/u-boot.bin ]; then \
		$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot-rockchip.bin; \
	else \
		echo "Error: No U-Boot binary found"; \
		exit 1; \
	fi
endef

define Package/u-boot/install/default
endef

$(eval $(call BuildPackage/U-Boot))
