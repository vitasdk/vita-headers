/**
 * \usergroup{SceDebugLed}
 * \usage{psp2/kernel/debugled.h,SceSysmem_stub}
 */

#ifndef _PSP2_KERNEL_DEBUGLED_H_
#define _PSP2_KERNEL_DEBUGLED_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Invokes debug LED handler 0 if one is registered.
 *
 * @param[in] arg0 - First opaque handler argument.
 * @param[in] arg1 - Second opaque handler argument.
 * @param[in] arg2 - Third opaque handler argument.
 * @param[in] arg3 - Fourth opaque handler argument.
 */
void sceDebugLedInvokeHandle0(int arg0, int arg1, int arg2, int arg3);

/**
 * Invokes debug LED handler 1 if one is registered.
 *
 * @param[in] arg0 - First opaque handler argument.
 * @param[in] arg1 - Second opaque handler argument.
 * @param[in] arg2 - Third opaque handler argument.
 * @param[in] arg3 - Fourth opaque handler argument.
 */
void sceDebugLedInvokeHandle1(int arg0, int arg1, int arg2, int arg3);

/**
 * Gets the current general-purpose input bitfield.
 *
 * @return The current GPI bitfield.
 */
int sceKernelGetGPI(void);

/**
 * Sets the general-purpose output bitfield.
 *
 * The full value is retained. On PDEL units, bits 0 through 7 control the
 * debug LED display.
 *
 * @param[in] uiBits - Output bitfield.
 *
 * @return 0.
 */
int sceKernelSetGPO(SceUInt32 uiBits);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_DEBUGLED_H_ */
