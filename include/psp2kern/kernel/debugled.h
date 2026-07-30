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
 * The handler arguments are forwarded unchanged by the invoke functions.
 */
typedef void (*SceDebugLedHandler)(int arg0, int arg1, int arg2, int arg3);

/**
 * Sets the general-purpose output bitfield.
 *
 * The full value is retained. On PDEL units, enabled bits 0 through 7 control
 * the debug LED display.
 *
 * @param[in] bits - Output bitfield.
 */
void ksceKernelSetGPO(SceUInt32 bits);

/**
 * Gets the retained general-purpose output bitfield.
 *
 * @return The full bitfield from the last GPO write.
 */
SceUInt32 ksceKernelGetGPO(void);

/**
 * Replaces the software-maintained general-purpose input bitfield.
 *
 * @param[in] bits - Input bitfield.
 */
void ksceKernelSetGPI(SceUInt32 bits);

/**
 * Gets the current general-purpose input bitfield.
 *
 * @return The current GPI bitfield.
 */
SceUInt32 ksceKernelGetGPI(void);

/**
 * Atomically updates the GPO enable mask.
 *
 * The new mask is `(oldMask & ~clearMask) | setMask` and takes effect on the
 * next GPO write or resume restoration.
 *
 * @param[in] clearMask - Bits to clear from the current mask.
 * @param[in] setMask - Bits to set in the current mask.
 *
 * @return 0.
 */
int ksceKernelSetGPOMask(SceUInt32 clearMask, SceUInt32 setMask);

/**
 * Registers or clears debug LED handler 0.
 *
 * @param[in] handler - Handler to register, or NULL to clear it.
 */
void ksceDebugLedRegisterHandle0(SceDebugLedHandler handler);

/**
 * Invokes debug LED handler 0 if one is registered.
 *
 * @param[in] arg0 - First opaque handler argument.
 * @param[in] arg1 - Second opaque handler argument.
 * @param[in] arg2 - Third opaque handler argument.
 * @param[in] arg3 - Fourth opaque handler argument.
 */
void ksceDebugLedInvokeHandle0(int arg0, int arg1, int arg2, int arg3);

/**
 * Registers or clears debug LED handler 1.
 *
 * @param[in] handler - Handler to register, or NULL to clear it.
 */
void ksceDebugLedRegisterHandle1(SceDebugLedHandler handler);

/**
 * Invokes debug LED handler 1 if one is registered.
 *
 * @param[in] arg0 - First opaque handler argument.
 * @param[in] arg1 - Second opaque handler argument.
 * @param[in] arg2 - Third opaque handler argument.
 * @param[in] arg3 - Fourth opaque handler argument.
 */
void ksceDebugLedInvokeHandle1(int arg0, int arg1, int arg2, int arg3);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_DEBUGLED_H_ */
