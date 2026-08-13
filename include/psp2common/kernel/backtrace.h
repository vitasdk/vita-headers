/**
 * \kernelgroup{SceBacktrace}
 * \usage{psp2common/kernel/backtrace.h}
 */

#ifndef _PSP2COMMON_KERNEL_BACKTRACE_H_
#define _PSP2COMMON_KERNEL_BACKTRACE_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_KERNEL_BACKTRACE_CONTEXT_CURRENT (0x00000000) //!< Current thread.

typedef enum SceKernelBacktraceMode {
	SCE_KERNEL_BACKTRACE_MODE_USER           = 0x00000000, //!< Unwind the user-mode stack.
	SCE_KERNEL_BACKTRACE_MODE_KERNEL         = 0x00000001, //!< Unwind the kernel-mode stack.
	SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED    = 0x00000002, //!< Stop when the output buffer is full.
	SCE_KERNEL_BACKTRACE_MODE_UNK_0x00000008 = 0x00000008  //!< Accepted on FW 3.60; purpose unknown.
} SceKernelBacktraceMode;
VITASDK_BUILD_ASSERT_EQ(1, SceKernelBacktraceMode);

typedef struct SceKernelCallFrame {
	SceUIntVAddr sp; //!< Stack pointer.
	SceUIntVAddr pc; //!< Program counter.
} SceKernelCallFrame;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelCallFrame); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_BACKTRACE_H_ */
