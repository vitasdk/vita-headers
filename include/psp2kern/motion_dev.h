/**
 * \kernelgroup{SceMotionDev}
 * \usage{psp2kern/motion_dev.h,SceMotionDevForDriver_stub}
 */

#ifndef _PSP2KERN_MOTION_DEV_H_
#define _PSP2KERN_MOTION_DEV_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Cached motion-controller identity record.
 *
 * FW 3.60 always writes the complete 0x2C-byte record. The first four bytes
 * have the same meaning in both device-information response formats. The
 * remaining bytes come directly from the controller response. Their layout
 * depends on the response format; this API does not interpret them.
 */
typedef struct SceKernelMotionDeviceInfo {
	SceUInt16 barkley_firmware_version; //!< Barkley motion-controller firmware version.
	SceUInt16 barkley_hardware_info; //!< Barkley hardware information.
	SceUInt8 controller_info[0x28]; //!< Controller-specific device-information response data.
} SceKernelMotionDeviceInfo;
VITASDK_BUILD_ASSERT_EQ(0x2C, SceKernelMotionDeviceInfo); // size is from FW 3.60

/**
 * Get the cached motion-controller identity record.
 *
 * MotionDev holds its state spinlock with CPU interrupts suspended while
 * copying the output. On error, \a info is not modified.
 *
 * @param[out] info - Receives the complete identity record; must not be NULL.
 *
 * @return 0 on success, 0x80360001 if \a info is NULL, 0x80360004 while
 *         MotionDev is in a state that does not expose device information, or
 *         0x80360006 when its cached device-information record is unavailable.
 */
int ksceMotionDevGetDeviceInfo(SceKernelMotionDeviceInfo *info);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_MOTION_DEV_H_ */
