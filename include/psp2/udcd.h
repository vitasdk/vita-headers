/**
 * \usergroup{SceUdcd}
 * \usage{psp2/udcd.h,-lSceUdcd_stub}
 */

/**
 * \file
 * \brief Header file which defines USB Device Controller Driver related variables and functions
 *
 * Copyright (C) 2017 vitasdk developers
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_UDCD_H_
#define _PSP2_UDCD_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * USB Status
 */
#define SCE_UDCD_STATUS_CONNECTION_NEW		0x0001
#define SCE_UDCD_STATUS_CONNECTION_ESTABLISHED	0x0002
#define SCE_UDCD_STATUS_CONNECTION_SUSPENDED	0x0004
#define SCE_UDCD_STATUS_CABLE_DISCONNECTED	0x0010
#define SCE_UDCD_STATUS_CABLE_CONNECTED		0x0020
#define SCE_UDCD_STATUS_DEACTIVATED		0x0100
#define SCE_UDCD_STATUS_ACTIVATED		0x0200
#define SCE_UDCD_STATUS_IS_CHARGING		0x0400
#define SCE_UDCD_STATUS_USE_USB_CHARGING	0x0800
#define SCE_UDCD_STATUS_UNKNOWN_1000		0x1000
#define SCE_UDCD_STATUS_UNKNOWN_2000		0x2000

typedef struct {
	uint8_t info[64];
} SceUdcdDeviceInfo;

typedef struct {
	int unk_00;
	int unk_04;
	int unk_08;
	int unk_0C;
	int unk_10;
	const char *driverName;
} SceUdcdWaitParam;

typedef struct {
	int unk_00;
	int state;
	int cable;
	int connection;
	int use_usb_charging;
	int unk_14;
} SceUdcdDeviceState;

/**
 * Get device state
 *
 * @param[out] state - Device state
 *
 * @return 0 on success, < 0 on error.
*/
int sceUdcdGetDeviceState(SceUdcdDeviceState *state);

/**
 * Get device information
 *
 * @param[out] devInfo - Device information
 *
 * @return 0 on success, < 0 on error.
*/
int sceUdcdGetDeviceInfo(SceUdcdDeviceInfo *devInfo);

/**
 * Register callback
 *
 * @param[in] cbid - Callback UID
 * @param[in] state - State
 *
 * @return 0 on success, < 0 on error.
*/
int sceUdcdRegisterCallback(SceUID cbid, int state);

/**
 * Unregister callback
 *
 * @param[in] cbid - Callback UID
 *
 * @return 0 on success, < 0 on error.
*/
int sceUdcdUnregisterCallback(SceUID cbid);

/**
 * Wait for state
 *
 * @param[in] waitParam - Wait parameter
 * @param[in] state - State
 *
 * @return 0 on success, < 0 on error.
*/
int sceUdcdWaitState(SceUdcdWaitParam *waitParam, int state);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_UDCD_H_ */
