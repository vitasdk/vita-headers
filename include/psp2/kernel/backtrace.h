/**
 * \usergroup{SceBacktrace}
 * \usage{psp2/kernel/backtrace.h,SceKernelModulemgr_stub}
 */

#ifndef _PSP2_KERNEL_BACKTRACE_H_
#define _PSP2_KERNEL_BACKTRACE_H_

#include <psp2common/kernel/backtrace.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceBacktraceArgs {
	SceUInt32 *pNumReturn; //!< Optional pointer that receives the number of frames gathered.
	SceInt32 mode; //!< Bitwise OR of ::SceKernelBacktraceMode values.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceBacktraceArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceBacktraceArgs); // size is from FW 3.60

/**
 * Gets a thread backtrace.
 *
 * @param[in] threadId Thread ID, or ::SCE_KERNEL_BACKTRACE_CONTEXT_CURRENT.
 * @param[out] pCallFrameBuffer Buffer that receives call frames, or NULL when
 * numBytesBuffer is 0.
 * @param[in] numBytesBuffer Size of the call-frame buffer in bytes. A non-NULL
 * buffer must have room for at least one frame.
 * @param[in] pArgs Required backtrace parameters.
 *
 * @return With ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED, 0 on success.
 * Otherwise, the call-stack depth on success. Returns < 0 on error.
 *
 * @note On FW 3.60 this function requires development mode. Kernel-mode
 * unwinding also requires the corresponding QAF permission.
 */
SceInt32 _sceKernelBacktrace(SceUID threadId, SceKernelCallFrame *pCallFrameBuffer, SceSize numBytesBuffer, SceBacktraceArgs *pArgs);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_BACKTRACE_H_ */
