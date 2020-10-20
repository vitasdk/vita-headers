/**
 * \kernelgroup{SceKernelDebug}
 * \usage{psp2kern/kernel/debug.h,SceDebugForDriver_stub}
 */

// or SceDebugForKernel_stub

#ifndef _PSP2_KERNEL_DEBUD_H_
#define _PSP2_KERNEL_DEBUD_H_

#include <psp2kern/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceDebugPutchar(int character);

int ksceDebugPrintf(const char *fmt, ...);

typedef struct SceKernelDebugMessageContext {
  SceUInt32 hex_value0_hi;
  SceUInt32 hex_value0_lo;
  SceUInt32 hex_value1;
  const char *msg0;
  SceSize num;
  const char *msg1;
} SceKernelDebugMessageContext;

// msg_type_flag : 0 or 0xB

int ksceDebugPrintf2(int msg_type_flag, const SceKernelDebugMessageContext *ctx, const char *fmt, ...);

__attribute__((__noreturn__))
void ksceDebugPrintKernelPanic(const SceKernelDebugMessageContext *ctx, void *some_address);

__attribute__((__noreturn__))
void ksceDebugPrintfKernelPanic(const SceKernelDebugMessageContext *ctx, void *some_address, const char *fmt, ...);

int ksceDebugPrintKernelAssertion(int condition, const SceKernelDebugMessageContext *ctx, void *some_address);
int ksceDebugPrintfKernelAssertion(int unk, int condition, const SceKernelDebugMessageContext *ctx, int some_address, const char *fmt, ...);

int ksceDebugSetHandlers(int (* func)(int unk, const char *format, const va_list args), void *args);

int ksceDebugRegisterPutcharHandler(int (* func)(void *args, char c), void *args);

void *ksceDebugGetPutcharHandler(void);

int ksceDebugDisableInfoDump(int flag);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_DEBUD_H_ */
