/**
 * \usergroup{SceUsbd}
 * \usage{psp2kern/usbd.h,-lSceUsbdForDriver_stub}
 */

/**
 * \file
 * \brief Header file which defines USB driver kernel related variables and functions
 *
 * Copyright (C) 2017 vitasdk developers
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_USBD_H_
#define _PSP2_KERNEL_USBD_H_

#include <psp2kern/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_USBD_ERROR_ACCESS 0x80240003
#define SCE_USBD_ERROR_BUSY 0x80240006
#define SCE_USBD_ERROR_FATAL 0x802400ff
#define SCE_USBD_ERROR_INTERRUPTED 0x8024000a
#define SCE_USBD_ERROR_INVALID_ARG 0x80240002
#define SCE_USBD_ERROR_IO 0x80240001
#define SCE_USBD_ERROR_NO_DEVICE 0x80240004
#define SCE_USBD_ERROR_NO_MEM 0x8024000b
#define SCE_USBD_ERROR_NOT_FOUND 0x80240005
#define SCE_USBD_ERROR_NOT_SUPPORTED 0x8024000c
#define SCE_USBD_ERROR_OVERFLOW 0x80240008
#define SCE_USBD_ERROR_PIPE 0x80240009
#define SCE_USBD_ERROR_TIMEOUT 0x80240007

typedef struct SceUsbdDeviceInfo {
	unsigned int unk0;
	unsigned int unk1;
	unsigned int unk2;
} SceUsbdDeviceInfo; /* size = 0xC */

typedef struct SceUsbdDeviceAddress {
	unsigned int unk0;
	unsigned short unk1;
} SceUsbdDeviceAddress; /* size = 0x6 */

typedef struct SceUsbdDriver {
	const char *name;
	int (*func_unk0)(int);
	int (*func_unk1)(int);
	int (*func_unk2)(int);
	SceUsbdDriver *next;
} SceUsbdDriver; /* size = 0x14 */

int ksceUsbdRegisterDriver(SceUsbdDriver *driver);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_USBD_H_ */
