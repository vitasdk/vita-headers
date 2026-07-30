/**
 * \kernelgroup{SceBacktrace}
 * \usage{psp2kern/kernel/backtrace.h,SceBacktraceForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_BACKTRACE_H_
#define _PSP2KERN_KERNEL_BACKTRACE_H_

#include <psp2common/kernel/backtrace.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets a thread backtrace.
 *
 * @param[in] threadId Thread ID, or ::SCE_KERNEL_BACKTRACE_CONTEXT_CURRENT.
 * @param[out] pCallFrameBuffer Buffer that receives call frames, or NULL when
 * numBytesBuffer is 0.
 * @param[in] numBytesBuffer Size of the call-frame buffer in bytes. A non-NULL
 * buffer must have room for at least one frame.
 * @param[out] pNumReturn Optional pointer that receives the number of frames gathered.
 * @param[in] mode Bitwise OR of ::SceKernelBacktraceMode values.
 *
 * @return With ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED, 0 on success.
 * Otherwise, the call-stack depth on success. Returns < 0 on error.
 *
 * @note On FW 3.60 this function requires development mode. Kernel-mode
 * unwinding also requires the corresponding QAF permission.
 */
int ksceKernelBacktrace(SceUID threadId, SceKernelCallFrame *pCallFrameBuffer, SceSize numBytesBuffer, SceUInt32 *pNumReturn, SceInt32 mode);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_BACKTRACE_H_ */
