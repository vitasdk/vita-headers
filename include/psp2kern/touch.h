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
 * The complete output is cleared to zero, then filled from the selected
 * panel's cached information while CPU interrupts are suspended and the Touch
 * state spinlock is held. The panel does not need to be actively sampling.
 *
 * @param[in] panel - One of ::SceTouchPortType.
 * @param[out] info - Receives the complete 0xC-byte device-information record.
 *
 * @return 0 on success, or ::SCE_TOUCH_ERROR_INVALID_ARG if \a panel is not
 *         ::SCE_TOUCH_PORT_FRONT or ::SCE_TOUCH_PORT_BACK, or if \a info is
 *         NULL.
 */
int ksceTouchGetDeviceInfo(SceUInt32 panel, SceTouchDeviceInfo *info);

/**
 * Set front and back touch-emulation data.
 *
 * Each argument may be NULL. A non-NULL argument points to one 0x90-byte
 * ::SceTouchData structure for the corresponding panel. On FW 3.60, this
 * function ignores both arguments: it does not read, retain, or modify either
 * structure.
 *
 * @param[in] front_data - Optional pointer to a front-panel ::SceTouchData.
 * @param[in] back_data - Optional pointer to a back-panel ::SceTouchData.
 *
 * @return Always 0 on FW 3.60, including when both pointers are NULL.
 */
int ksceTouchSetTouchEmulationData(const void *front_data, const void *back_data);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_TOUCH_H_ */
