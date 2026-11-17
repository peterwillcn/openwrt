# SPDX-License-Identifier: GPL-2.0-only
#
# The UMS9620 drivers that config-6.18 builds as modules. Everything the board
# needs to boot, to reach the eMMC, USB and PCIe is built in (see config-6.18);
# what is here binds to parts of the vendor device tree that only exist on some
# of the boards, so it is a module.

define KernelPackage/zte-card-holder-det
  SUBMENU := Other modules
  TITLE := ZTE SIM card tray detection
  KCONFIG := CONFIG_ZTE_CARD_HOLDER_DET
  FILES := $(LINUX_DIR)/drivers/misc/zte_card_holder_det.ko
  AUTOLOAD := $(call AutoProbe,zte_card_holder_det)
endef

define KernelPackage/zte-card-holder-det/description
  /sys/zcard_det/zcard_det: whether the SIM tray is in, from the card slot's
  detect line, as the ZTE 5.4 kernel reports it.
endef

$(eval $(call KernelPackage,zte-card-holder-det))


define KernelPackage/typec-ump9620
  SUBMENU := USB Support
  TITLE := Unisoc UMP9620 USB Type-C port controller
  KCONFIG := CONFIG_TYPEC_UMP9620 CONFIG_TYPEC
  FILES := $(LINUX_DIR)/drivers/usb/typec/tcpm/ump9620-tcpc.ko
  AUTOLOAD := $(call AutoProbe,ump9620-tcpc)
  DEPENDS := +kmod-usb-typec
endef

define KernelPackage/typec-ump9620/description
  The UMP9620 PMIC's Type-C port controller (mainline tcpm driver), on the
  boards whose device tree describes it. Not used on the F50, which is powered
  over USB-C but does not negotiate power delivery.
endef

$(eval $(call KernelPackage,typec-ump9620))


define KernelPackage/typec-sc27xx
  SUBMENU := USB Support
  TITLE := Unisoc PMIC (SC27XX/UMP9620) Type-C detection
  KCONFIG := CONFIG_TYPEC_SC27XX CONFIG_TYPEC
  FILES := $(LINUX_DIR)/drivers/usb/typec/sc27xx_typec.ko
  AUTOLOAD := $(call AutoProbe,sc27xx_typec)
  DEPENDS := +kmod-usb-typec +kmod-mfd-sc27xx-pmic
endef

define KernelPackage/typec-sc27xx/description
  The PMIC's Type-C attach/detach block as a Type-C port with extcon, as the
  Unisoc 5.4 kernel's sc27xx_typec (no power delivery). The port's own driver
  from the 5.4 tree; only one of the two Type-C drivers binds on a board.
endef

$(eval $(call KernelPackage,typec-sc27xx))


define KernelPackage/sprd-bc1p2
  SUBMENU := USB Support
  TITLE := Unisoc PMIC BC1.2 charger detection
  KCONFIG := CONFIG_SPRD_BC1P2
  FILES := $(LINUX_DIR)/drivers/usb/phy/sprd-bc1p2.ko
  AUTOLOAD := $(call AutoProbe,sprd-bc1p2)
  DEPENDS := +kmod-mfd-sc27xx-pmic
endef

define KernelPackage/sprd-bc1p2/description
  The PMIC's BC1.2 charger-port detection result, as the Unisoc 5.4 kernel's
  sprd_bc1p2. Used to tell the kind of charger on the boards with a battery.
endef

$(eval $(call KernelPackage,sprd-bc1p2))


define KernelPackage/sprd-top-dvfs
  SUBMENU := Other modules
  TITLE := Unisoc top-level DVFS set-up
  KCONFIG := CONFIG_SPRD_TOP_DVFS_DEVFREQ
  FILES := $(LINUX_DIR)/drivers/devfreq/sprd-top-dvfs.ko
  AUTOLOAD := $(call AutoProbe,sprd-top-dvfs)
endef

define KernelPackage/sprd-top-dvfs/description
  Enables the top DVFS module and the DCDCs' DVFS a sprd,topdvfs-dev node
  describes. Binds nothing on these boards (the DDR and modem DVFS talk to the
  co-processors over SIPC), as on 5.4.
endef

$(eval $(call KernelPackage,sprd-top-dvfs))
