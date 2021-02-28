/**
 * \kernelgroup{SceRtc}
 * \usage{psp2kern/kernel/rtc.h,SceRtcForDriver_stub}
 */

#ifndef _PSP2_KERNEL_RTC_H_
#define _PSP2_KERNEL_RTC_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceRtcSetCurrentTick(SceUInt64 *tick);
int ksceRtcGetCurrentTick(SceUInt64 *tick);

int ksceRtcSetCurrentNetworkTick(SceUInt64 *tick);
int ksceRtcGetCurrentNetworkTick(SceUInt64 *tick);

int ksceRtcSetCurrentSecureTick(SceUInt64 *tick);
int ksceRtcGetCurrentSecureTick(SceUInt64 *tick);

int ksceRtcSetCurrentDebugNetworkTick(SceUInt64 *tick);
int ksceRtcGetCurrentDebugNetworkTick(SceUInt64 *tick);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_RTC_H_ */
