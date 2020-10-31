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

typedef struct SceKernelDebugMessageContext {
  SceUInt32 hex_value0_hi;
  SceUInt32 hex_value0_lo;
  SceUInt32 hex_value1;
  const char *msg0;
  SceSize num;
  const char *msg1;
} SceKernelDebugMessageContext;

typedef enum SceKernelDebugPrintFlags {
  SCE_DBG_PRINT_FLAG_NONE = 0,
  SCE_DBG_PRINT_FLAG_CORE = 1,
  SCE_DBG_PRINT_FLAG_FUNC = 2,
  SCE_DBG_PRINT_FLAG_LINE = 4,
  SCE_DBG_PRINT_FLAG_FILE = 8
} SceKernelDebugPrintFlags;

int ksceDebugPutchar(int character);

/**
 * @brief Print log
 *
 * @param[in]    fmt   - print fmt
 *
 * @return 0 on success, < 0 on error.
 *
 * note - log is pass to ksceDebugRegisterPutcharHandler's handler.
 */
int ksceDebugPrintf(const char *fmt, ...);

/**
 * @brief Print log with ctx
 *
 * @param[in]    flags - ctx print flags, see:SceKernelDebugPrintFlags
 * @param[in]    ctx   - debug msg ctx
 * @param[in]    fmt   - print fmt
 *
 * @return 0 on success, < 0 on error.
 *
 * note - main log is pass to ksceDebugRegisterPutcharHandler's handler.
 *        ctx  log is pass to ksceDebugSetHandlers's handler.
 */
int ksceDebugPrintf2(int flags, const SceKernelDebugMessageContext *ctx, const char *fmt, ...);

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
