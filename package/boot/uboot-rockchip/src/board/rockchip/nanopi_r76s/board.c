// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2025 FriendlyElec Computer Tech. Co., Ltd.
 * (http://www.friendlyelec.com)
 */

#include <common.h>
#include <dm.h>
#include <asm/arch-rockchip/periph.h>
#include <power/regulator.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_MISC_INIT_R
int misc_init_r(void)
{
	const u32 cpuid_offset = 0x7;
	const u32 cpuid_length = 0x10;
	u8 cpuid[cpuid_length];
	int ret;

	memset(cpuid, 0, cpuid_length);
	ret = rockchip_cpuid_from_efuse(cpuid_offset, cpuid_length, cpuid);
	if (ret)
		return ret;

	ret = rockchip_cpuid_set(cpuid, cpuid_length);
	if (ret)
		return ret;

	return ret;
}
#endif

int board_early_init_f(void)
{
	return 0;
}


#include <usb.h>