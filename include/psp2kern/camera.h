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

/** Camera-active bits returned by ::ksceCameraIsActive. */
typedef enum SceCameraActiveStatusFlag {
	SCE_CAMERA_ACTIVE_STATUS_FRONT = 0x1, //!< The process owns an active front-camera stream.
	SCE_CAMERA_ACTIVE_STATUS_BACK  = 0x2  //!< The process owns an active back-camera stream.
} SceCameraActiveStatusFlag;

/**
 * Check which active cameras a process owns.
 *
 * A status bit is set only when the target process has opened and started the
 * corresponding camera and remains its current global owner. An invalid or
 * nonexistent process ID, or an uninitialized Camera driver, is reported as
 * inactive, not as an error.
 *
 * @param[in] pid - Target process ID.
 * @param[out] status - Receives a bitwise OR of
 *                       ::SceCameraActiveStatusFlag values. Must not be NULL.
 *
 * @return 1 if either camera is active, 0 if neither camera is active, or
 *         0x802E0000 (::SCE_CAMERA_ERROR_PARAM) if \a status is NULL.
 */
int ksceCameraIsActive(ScePID pid, SceUInt32 *status);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_CAMERA_H_ */
