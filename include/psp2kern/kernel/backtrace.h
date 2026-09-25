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
 * Get a thread backtrace.
 *
 * @param[in] thread_id Thread ID, or ::SCE_KERNEL_BACKTRACE_CONTEXT_CURRENT.
 * @param[out] call_frame_buffer Buffer that receives call frames, or NULL when
 * num_bytes_buffer is 0.
 * @param[in] num_bytes_buffer Size of the call-frame buffer in bytes. A non-NULL
 * buffer must have room for at least one frame.
 * @param[out] num_frames Receives the number of frames written to the output
 * buffer. May be NULL.
 * @param[in] mode Bitwise OR of ::SceKernelBacktraceMode values.
 *
 * @return On success, 0 with ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED set;
 * otherwise, the total number of frames in the call stack, including frames
 * that did not fit in the output buffer. Returns < 0 on error.
 *
 * @note On FW 3.60 this function requires development mode. Kernel-mode
 * unwinding also requires the corresponding QAF permission.
 */
int ksceKernelBacktrace(SceUID thread_id, SceKernelCallFrame *call_frame_buffer, SceSize num_bytes_buffer, SceUInt32 *num_frames, SceInt32 mode);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_BACKTRACE_H_ */
