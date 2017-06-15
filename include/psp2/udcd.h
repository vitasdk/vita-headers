/**
 * \usergroup{SceUdcd}
 * \usage{psp2/udcd.h,SceUdcd_stub}
 */


#ifndef _PSP2_UDCD_H_
#define _PSP2_UDCD_H_

#ifdef __cplusplus
extern "C" {
#endif

/** USB Status */
typedef enum SceUdcdStatus {
	SCE_UDCD_STATUS_CONNECTION_NEW          = 0x0001,
	SCE_UDCD_STATUS_CONNECTION_ESTABLISHED  = 0x0002,
	SCE_UDCD_STATUS_CONNECTION_SUSPENDED    = 0x0004,
	SCE_UDCD_STATUS_CABLE_DISCONNECTED      = 0x0010,
	SCE_UDCD_STATUS_CABLE_CONNECTED         = 0x0020,
	SCE_UDCD_STATUS_DEACTIVATED             = 0x0100,
	SCE_UDCD_STATUS_ACTIVATED               = 0x0200,
	SCE_UDCD_STATUS_IS_CHARGING             = 0x0400,
	SCE_UDCD_STATUS_USE_USB_CHARGING        = 0x0800,
	SCE_UDCD_STATUS_UNKNOWN_1000            = 0x1000,
	SCE_UDCD_STATUS_UNKNOWN_2000            = 0x2000
} SceUdcdStatus;

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
