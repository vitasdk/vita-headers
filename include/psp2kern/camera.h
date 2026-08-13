/**
 * \kernelgroup{SceCamera}
 * \usage{psp2kern/camera.h,SceCameraForDriver_stub}
 */

#ifndef _PSP2KERN_CAMERA_H_
#define _PSP2KERN_CAMERA_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceCameraIsActive(SceUID pid, SceUInt32 *puiStatus);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_CAMERA_H_ */
