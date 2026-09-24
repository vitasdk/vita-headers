/**
 * \kernelgroup{SceDebugLed}
 * \usage{psp2kern/kernel/debugled.h,SceDebugLedForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_DEBUGLED_H_
#define _PSP2KERN_KERNEL_DEBUGLED_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Debug LED handler.
 *
 * The invoke functions pass the arguments to the handler unchanged.
 */
typedef void (*SceDebugLedHandler)(int arg0, int arg1, int arg2, int arg3);

/**
 * Set the general-purpose output bitfield.
 *
 * The full value is saved. On PDEL units, enabled bits 0 through 7 control
 * the debug LED display.
 *
 * @param[in] bits - Output bitfield.
 *
 * @return 0 on FW 3.60.
 */
int ksceKernelSetGPO(SceUInt32 bits);

/**
 * Get the saved general-purpose output bitfield.
 *
 * @return The full bitfield from the last GPO write.
 */
SceUInt32 ksceKernelGetGPO(void);

/**
 * Replace the general-purpose input bitfield stored in software.
 *
 * @param[in] bits - Input bitfield.
 */
void ksceKernelSetGPI(SceUInt32 bits);

/**
 * Get the current general-purpose input bitfield.
 *
 * @return The current GPI bitfield.
 */
SceUInt32 ksceKernelGetGPI(void);

/**
 * Atomically update the GPO enable mask.
 *
 * The new mask is `(oldMask & ~clear_mask) | set_mask` and takes effect on the
 * next GPO write or when GPO state is restored on resume.
 *
 * @param[in] clear_mask - Bits to clear from the current mask.
 * @param[in] set_mask - Bits to set in the current mask.
 *
 * @return 0.
 */
int ksceKernelSetGPOMask(SceUInt32 clear_mask, SceUInt32 set_mask);

/**
 * Register or clear debug LED handler 0.
 *
 * @param[in] handler - Handler to register, or NULL to clear it.
 */
void ksceDebugLedRegisterHandle0(SceDebugLedHandler handler);

/**
 * Call debug LED handler 0 if one is registered.
 *
 * @param[in] arg0 - First handler argument; meaning unspecified.
 * @param[in] arg1 - Second handler argument; meaning unspecified.
 * @param[in] arg2 - Third handler argument; meaning unspecified.
 * @param[in] arg3 - Fourth handler argument; meaning unspecified.
 */
void ksceDebugLedInvokeHandle0(int arg0, int arg1, int arg2, int arg3);

/**
 * Register or clear debug LED handler 1.
 *
 * @param[in] handler - Handler to register, or NULL to clear it.
 */
void ksceDebugLedRegisterHandle1(SceDebugLedHandler handler);

/**
 * Call debug LED handler 1 if one is registered.
 *
 * @param[in] arg0 - First handler argument; meaning unspecified.
 * @param[in] arg1 - Second handler argument; meaning unspecified.
 * @param[in] arg2 - Third handler argument; meaning unspecified.
 * @param[in] arg3 - Fourth handler argument; meaning unspecified.
 */
void ksceDebugLedInvokeHandle1(int arg0, int arg1, int arg2, int arg3);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_DEBUGLED_H_ */
