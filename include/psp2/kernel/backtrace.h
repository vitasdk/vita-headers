/**
 * \usergroup{SceBacktrace}
 * \usage{psp2/kernel/backtrace.h,SceLibKernel_stub}
 */


#ifndef _PSP2_KERNEL_BACKTRACE_H_
#define _PSP2_KERNEL_BACKTRACE_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

SceInt32 _sceKernelBacktrace(SceUID threadId, SceKernelCallFrame *pCallFrameBuffer, SceSize numBytesBuffer, SceUInt32 *pNumReturn);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_BACKTRACE_H_ */
