/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/timer.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_TIMER_H_
#define _PSP2_KERNEL_THREADMGR_TIMER_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceKernelCreateTimer(const char* name, SceUInt32 attr, const SceKernelTimerOptParam* opt);
int sceKernelDeleteTimer(SceUID timer);
int sceKernelStartTimer(SceUID timer);
int sceKernelStopTimer(SceUID timer);
int sceKernelSetTimerEvent(SceUID timer, SceUInt32 type, SceUInt64* pInterval, SceBool repeat);
int sceKernelSetTimerTime(SceUID timer, SceUInt32 time);
int sceKernelSetTimerTimeWide(SceUID timer, SceUInt64 time);
int sceKernelGetTimerTime(SceUID timer, SceUInt64* pTime);
SceUInt64 sceKernelGetTimerTimeWide(SceUID timer);
int sceKernelGetTimerBase(SceUID timer, SceUInt64* pBase);
SceUInt64 sceKernelGetTimerBaseWide(SceUID timer);
SceUID sceKernelOpenTimer(SceUID timer);
int sceKernelCloseTimer(SceUID timer);
int sceKernelCancelTimer(SceUID timer, SceUInt32* pNumThreads);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_TIMER_H_ */
