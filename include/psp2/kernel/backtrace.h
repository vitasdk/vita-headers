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
	SceUInt32 *num_frames; //!< Receives the number of frames written to the output buffer. May be NULL.
	SceInt32 mode; //!< Bitwise OR of ::SceKernelBacktraceMode values.
	SceUInt32 reserved[2]; //!< Copied from user memory but unused on FW 3.60.
} SceBacktraceArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceBacktraceArgs); // size is from FW 3.60

/**
 * Get a thread backtrace.
 *
 * @param[in] thread_id Thread ID, or ::SCE_KERNEL_BACKTRACE_CONTEXT_CURRENT.
 * @param[out] call_frame_buffer Buffer that receives call frames, or NULL when
 * num_bytes_buffer is 0.
 * @param[in] num_bytes_buffer Size of the call-frame buffer in bytes. A non-NULL
 * buffer must have room for at least one frame.
 * @param[in] args Backtrace parameters. Must be non-NULL.
 *
 * @return On success, 0 with ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED set;
 * otherwise, the total number of frames in the call stack, including frames
 * that did not fit in the output buffer. Returns < 0 on error.
 *
 * @note On FW 3.60 this function requires development mode. Kernel-mode
 * unwinding also requires the corresponding QAF permission.
 */
SceInt32 _sceKernelBacktrace(SceUID thread_id, SceKernelCallFrame *call_frame_buffer, SceSize num_bytes_buffer, const SceBacktraceArgs *args);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_BACKTRACE_H_ */
