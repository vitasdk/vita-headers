/**
 * \kernelgroup{SceUdcd}
 * \usage{psp2common/udcd.h}
 */


#ifndef _PSP2COMMON_UDCD_H_
#define _PSP2COMMON_UDCD_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


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

typedef enum SceUdcdStatusDriver {
	SCE_UDCD_STATUS_DRIVER_STARTED         = 0x01,
	SCE_UDCD_STATUS_DRIVER_REGISTERED      = 0x02
} SceUdcdStatusDriver;

typedef struct SceUdcdDeviceInfo {
	unsigned char info[64];
} SceUdcdDeviceInfo;
VITASDK_BUILD_ASSERT_EQ(0x40, SceUdcdDeviceInfo);

typedef struct SceUdcdWaitParam {
	int unk_00;
	int status;
	int unk_08;
	int unk_0C;
	int unk_10;
	const char *driverName;
} SceUdcdWaitParam;
VITASDK_BUILD_ASSERT_EQ(0x18, SceUdcdWaitParam);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_UDCD_H_ */
