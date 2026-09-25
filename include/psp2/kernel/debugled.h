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
 * Call debug LED handler 0 if one is registered.
 *
 * @param[in] arg0 - First handler argument; meaning unspecified.
 * @param[in] arg1 - Second handler argument; meaning unspecified.
 * @param[in] arg2 - Third handler argument; meaning unspecified.
 * @param[in] arg3 - Fourth handler argument; meaning unspecified.
 */
void sceDebugLedInvokeHandle0(int arg0, int arg1, int arg2, int arg3);

/**
 * Call debug LED handler 1 if one is registered.
 *
 * @param[in] arg0 - First handler argument; meaning unspecified.
 * @param[in] arg1 - Second handler argument; meaning unspecified.
 * @param[in] arg2 - Third handler argument; meaning unspecified.
 * @param[in] arg3 - Fourth handler argument; meaning unspecified.
 */
void sceDebugLedInvokeHandle1(int arg0, int arg1, int arg2, int arg3);

/**
 * Get the current general-purpose input bitfield.
 *
 * @return The current GPI bitfield.
 */
SceUInt32 sceKernelGetGPI(void);

/**
 * Set the general-purpose output bitfield.
 *
 * The full value is saved. On PDEL units, bits 0 through 7 control the
 * debug LED display.
 *
 * @param[in] bits - Output bitfield.
 *
 * @return 0.
 */
int sceKernelSetGPO(SceUInt32 bits);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_DEBUGLED_H_ */
