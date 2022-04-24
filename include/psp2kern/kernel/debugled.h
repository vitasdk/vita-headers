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

void ksceKernelSetGPO(SceUInt32 gpo);
SceUInt32 ksceKernelGetGPO(void);

void ksceKernelSetGPI(SceUInt32 gpi);
SceUInt32 ksceKernelGetGPI(void);

void ksceDebugLedRegisterHandle0(void (* func)(int a1, int a2, int a3, int a4));
void ksceDebugLedInvokeHandle0(int a1, int a2, int a3, int a4);

void ksceDebugLedRegisterHandle1(void (* func)(int a1, int a2, int a3, int a4));
void ksceDebugLedInvokeHandle1(int a1, int a2, int a3, int a4);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_DEBUGLED_H_ */
