/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2017 Fuzhou Rockchip Electronics Co.Ltd
 *
 * Rockchip USB download function support
 */

#ifndef _ROCKUSB_H_
#define _ROCKUSB_H_

#include <blk.h>
#include <linux/usb/composite.h>

#define ROCKUSB_VERSION		"0.1"

enum rkusb_command {
	K_FW_TEST_UNIT_READY	= 0x00,
	K_FW_READ_FLASH_ID	= 0x01,
	K_FW_SET_DEVICE_ID	= 0x02,
	K_FW_TEST_BAD_BLOCK	= 0x03,
	K_FW_READ_10		= 0x04,
	K_FW_WRITE_10		= 0x05,
	K_FW_ERASE_10		= 0x06,
	K_FW_WRITE_SPARE	= 0x07,
	K_FW_READ_SPARE		= 0x08,

	K_FW_ERASE_10_FORCE	= 0x0b,
	K_FW_GET_VERSION	= 0x0c,

	K_FW_LBA_READ_10	= 0x14,
	K_FW_LBA_WRITE_10	= 0x15,
	K_FW_ERASE_SYS_DISK	= 0x16,
	K_FW_SDRAM_READ_10	= 0x17,
	K_FW_SDRAM_WRITE_10	= 0x18,
	K_FW_SDRAM_EXECUTE	= 0x19,
	K_FW_READ_FLASH_INFO	= 0x1A,
	K_FW_GET_CHIP_VER	= 0x1B,
	K_FW_LOW_FORMAT		= 0x1C,
	K_FW_SET_RESET_FLAG	= 0x1E,
	K_FW_SPI_READ_10	= 0x21,
	K_FW_SPI_WRITE_10	= 0x22,

	K_FW_SESSION		= 0x30,
	K_FW_RESET		= 0xff,
};

#define CBW_DIRECTION_OUT		0x00
#define CBW_DIRECTION_IN		0x80

struct cmd_dispatch_info {
	enum rkusb_command cmd;
	/* call back function to handle rockusb command */
	void (*cb)(struct usb_ep *ep, struct usb_request *req);
};

/* Bulk-only data structures */

/* Command Block Wrapper */
struct fsg_bulk_cb_wrap {
	__le32	signature;		/* Contains 'USBC' */
	u32	tag;			/* Unique per command id */
	__le32	data_transfer_length;	/* Size of the data */
	u8	flags;			/* Direction in bit 7 */
	u8	lun;			/* LUN (normally 0) */
	u8	length;			/* Of the CDB, <= MAX_COMMAND_SIZE */
	u8	CDB[16];		/* Command Data Block */
};

#define USB_BULK_CB_WRAP_LEN	31
#define USB_BULK_CB_SIG		0x43425355	/* Spells out USBC */
#define USB_BULK_IN_FLAG	0x80

/* Command Status Wrapper */
struct bulk_cs_wrap {
	__le32	signature;		/* Should = 'USBS' */
	u32	tag;			/* Same as original command */
	__le32	residue;		/* Amount not transferred */
	u8	status;			/* See below */
};

#define USB_BULK_CS_WRAP_LEN	13
#define USB_BULK_CS_SIG		0x53425355	/* Spells out 'USBS' */
#define USB_STATUS_PASS		0
#define USB_STATUS_FAIL		1
#define USB_STATUS_PHASE_ERROR	2

#define CSW_GOOD		0x00
#define CSW_FAILED		0x01
#define CSW_PHASE_ERROR		0x02

int rockusb_add(struct usb_configuration *c);

#ifdef CONFIG_CMD_ROCKUSB
#define IS_RKUSB_UMS_DNL(name)	(!strncmp((name), "rkusb_ums_dnl", 13))

int rkusb_do_check_parity(struct fsg_common *common);
void rkusb_force_to_usb2(bool enable);
bool rkusb_force_usb2_enabled(void);
void rkusb_switch_to_usb3_enable(bool enable);
bool rkusb_switch_usb3_enabled(void);
bool rkusb_usb3_capable(void);

#else
#define IS_RKUSB_UMS_DNL(name)	0

struct fsg_buffhd;
struct fsg_dev;
struct fsg_common;
struct fsg_config;

static inline int rkusb_cmd_process(struct fsg_common *common,
				    struct fsg_buffhd *bh, int *reply)
{
	return -EPERM;
}

static inline int rkusb_do_check_parity(struct fsg_common *common)
{
	return -EOPNOTSUPP;
}

static inline void rkusb_force_to_usb2(bool enable)
{
}

static inline bool rkusb_force_usb2_enabled(void)
{
	return false;
}

static inline void rkusb_switch_to_usb3_enable(bool enable)
{
}

static inline bool rkusb_switch_usb3_enabled(void)
{
	return false;
}

static inline bool rkusb_usb3_capable(void)
{
	return false;
}

#endif /* CONFIG_CMD_ROCKUSB */

#endif /* _ROCKUSB_H_ */