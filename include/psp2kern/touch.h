/**
 * \kernelgroup{SceTouch}
 * \usage{psp2kern/touch.h,SceTouchForDriver_stub}
 */


#ifndef _PSP2KERN_TOUCH_H_
#define _PSP2KERN_TOUCH_H_

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_TOUCH_H_ */
