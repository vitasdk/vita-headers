/**
 * \kernelgroup{SceTouch}
 * \usage{psp2kern/touch.h,SceTouchForDriver_stub}
 */


#ifndef _PSP2KERN_TOUCH_H_
#define _PSP2KERN_TOUCH_H_

#include <psp2common/touch.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set touch enable flag
 *
 * @param[in] port   - The port number.
 * @param[in] enable - The enable flag.
 *
 * @return 0 on success. < 0 on error.
 */
int ksceTouchSetEnableFlag(SceUInt32 port, SceBool enable);

/**
 * Get touch-panel device information.
 *
 * @param[in] panel One of ::SceTouchPortType.
 * @param[out] pInfo The buffer to receive the device information.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceTouchGetDeviceInfo(SceUInt32 panel, SceTouchDeviceInfo *pInfo);

/**
 * Set front and back touch-emulation data.
 *
 * @param[in] pFrontData An optional read-only pointer to a front-panel ::SceTouchData structure.
 * @param[in] pBackData An optional read-only pointer to a back-panel ::SceTouchData structure.
 *
 * @return 0 on FW 3.60.
 * @note Both buffers are ignored on FW 3.60.
 */
int ksceTouchSetTouchEmulationData(void *pFrontData, void *pBackData);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_TOUCH_H_ */
