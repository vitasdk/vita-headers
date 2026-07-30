/**
 * \kernelgroup{SceTouch}
 * \usage{psp2common/touch.h}
 */

#ifndef _PSP2COMMON_TOUCH_H_
#define _PSP2COMMON_TOUCH_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceTouchDeviceInfo {
	SceUInt16 vendorID;       //!< Vendor ID.
	SceUInt16 firmwareRev;    //!< Firmware revision.
	SceUInt16 configRev;      //!< Configuration revision.
	SceUInt8 hwVersion;       //!< Hardware version.
	SceUInt8 vendorInfo;      //!< Vendor-specific byte; not interpreted by observed FW 3.60 consumers.
	SceUInt8 reserved[4];     //!< Reserved. Set to zero on FW 3.60.
} SceTouchDeviceInfo;
VITASDK_BUILD_ASSERT_EQ(0xC, SceTouchDeviceInfo); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_TOUCH_H_ */
