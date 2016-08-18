/**
 * \file
 * \brief Header file which defines processes related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2/kernel/threadmgr.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_HIGH	= 32,
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_DEFAULT	= 96,
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_LOW		= 159
};

enum {
	SCE_KERNEL_PROCESS_PRIORITY_USER_HIGH		= 64,
	SCE_KERNEL_PROCESS_PRIORITY_USER_DEFAULT	= 96,
	SCE_KERNEL_PROCESS_PRIORITY_USER_LOW		= 127
};

enum {
	/** Cancel all timers */
	SCE_KERNEL_POWER_TICK_DEFAULT				= 0,
	/** Cancel automatic suspension timer */
	SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND	= 1,
	/** Cancel OLED-off timer */
	SCE_KERNEL_POWER_TICK_DISABLE_OLED_OFF		= 4,
	/** Cancel OLED dimming timer */
	SCE_KERNEL_POWER_TICK_DISABLE_OLED_DIMMING	= 6
};

/***
 * Exit current Process with specified return code
 *
 * @param[in] res - Exit code to return
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as FrameBuf pointer, output is blacked out.
*/
int sceKernelExitProcess(int res);

/***
 * Cancel specified idle timers to prevent entering in power save processing.
 *
 * @param[in] type - One of ::KernelPowerTickType
 *
 * @return 0
*/
int sceKernelPowerTick(int type);

/***
 * Get the process time of the current process.
 *
 * @param[out] type - Pointer to a ::SceKernelSysClock structure which will receive the process time.
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetProcessTime(SceKernelSysClock *pSysClock);

/***
 * Get the lower 32 bits part of process time of the current process.
 *
 * @return process time of the current process
*/
SceUInt32 sceKernelGetProcessTimeLow(void);

/***
 * Get the process time of the current process.
 *
 * @return process time of the current process
*/
SceUInt64 sceKernelGetProcessTimeWide(void);

/***
 * Get the process ID of the current process.
 *
 * @return process ID of the current process
*/
SceUID sceKernelGetProcessId(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */
