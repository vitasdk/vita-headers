/**
 * \usergroup{SceUdcd}
 * \usage{psp2/udcd.h,SceUdcd_stub}
 */


#ifndef _PSP2_UDCD_H_
#define _PSP2_UDCD_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/udcd.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceUdcdDeviceState {
	int unk_00;
	int state;
	int cable;
	int connection;
	int use_usb_charging;
	int unk_14;
} SceUdcdDeviceState;
VITASDK_BUILD_ASSERT_EQ(0x18, SceUdcdDeviceState);

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
 * Get state of a specific USB driver
 *
 * @param driverName - name of USB driver to get status from
 *
 * @return SCE_UDCD_STATUS_DRIVER_STARTED if the driver has been started, SCE_UDCD_STATUS_DRIVER_REGISTERED if it is stopped
 */
int sceUdcdGetDrvState(const char *driverName);

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
 * @param[in] timeout - Timeout
 *
 * @return 0 on success, < 0 on error.
*/
int sceUdcdWaitState(SceUdcdWaitParam *waitParam, unsigned int timeout);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_UDCD_H_ */
