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

typedef struct SceKernelMotionDeviceInfo {
	uint16_t BarkleyFwVersion;
	uint16_t BarkleyHwInfo;
} SceKernelMotionDeviceInfo;

int ksceMotionDevGetDeviceInfo(SceKernelMotionDeviceInfo *pInfo);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_MOTION_DEV_H_ */
