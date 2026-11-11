/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/timer.h,SceThreadmgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_THREADMGR_TIMER_H_
#define _PSP2KERN_KERNEL_THREADMGR_TIMER_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceKernelCreateTimer(const char* name, SceUInt32 attr, const SceKernelTimerOptParam* opt);
int ksceKernelDeleteTimer(SceUID timer);
int ksceKernelStartTimer(SceUID timer);
int ksceKernelStopTimer(SceUID timer);
int ksceKernelSetTimerEvent(SceUID timer, SceUInt32 type, SceUInt64* pInterval, SceBool repeat);
int ksceKernelSetTimerTime(SceUID timer, SceUInt32 time);
int ksceKernelSetTimerTimeWide(SceUID timer, SceUInt64 time);
int ksceKernelGetTimerTime(SceUID timer, SceUInt64* pTime);
SceUInt64 ksceKernelGetTimerTimeWide(SceUID timer);
int ksceKernelGetTimerBase(SceUID timer, SceUInt64* pBase);
SceUInt64 ksceKernelGetTimerBaseWide(SceUID timer);
int ksceKernelCancelTimer(SceUID timer, SceUInt32* pNumThreads);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_TIMER_H_ */
