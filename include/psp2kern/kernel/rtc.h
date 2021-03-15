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

typedef struct SceRtcTick {
	SceUInt64 tick;
} SceRtcTick;

int ksceRtcSetCurrentTick(SceRtcTick *tick);
int ksceRtcGetCurrentTick(SceRtcTick *tick);

int ksceRtcSetCurrentNetworkTick(SceRtcTick *tick);
int ksceRtcGetCurrentNetworkTick(SceRtcTick *tick);

int ksceRtcSetCurrentSecureTick(SceRtcTick *tick);
int ksceRtcGetCurrentSecureTick(SceRtcTick *tick);

int ksceRtcSetCurrentDebugNetworkTick(SceRtcTick *tick);
int ksceRtcGetCurrentDebugNetworkTick(SceRtcTick *tick);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_RTC_H_ */
