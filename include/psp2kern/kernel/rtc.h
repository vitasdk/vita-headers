/**
 * \kernelgroup{SceRtc}
 * \usage{psp2kern/kernel/rtc.h,SceRtcForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_RTC_H_
#define _PSP2KERN_KERNEL_RTC_H_

#include <vitasdk/build_utils.h>
#include <psp2common/kernel/rtc.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


int ksceRtcSetCurrentTick(SceRtcTick *tick);
int ksceRtcGetCurrentTick(SceRtcTick *tick);

/**
 * Get current real time clock time.
 *
 * @param[out] time - see ::SceDateTime.
 * @param[in] time_zone - The time zone the return value will be.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceRtcGetCurrentClock(SceDateTime *time, int time_zone);

/**
 * Get current real time clock time with system time zone.
 *
 * @param[out] time - see ::SceDateTime.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceRtcGetCurrentClockLocalTime(SceDateTime *time);

int ksceRtcSetCurrentNetworkTick(SceRtcTick *tick);
int ksceRtcGetCurrentNetworkTick(SceRtcTick *tick);

int ksceRtcSetCurrentSecureTick(SceRtcTick *tick);
int ksceRtcGetCurrentSecureTick(SceRtcTick *tick);

int ksceRtcSetCurrentDebugNetworkTick(SceRtcTick *tick);
int ksceRtcGetCurrentDebugNetworkTick(SceRtcTick *tick);

/**
 * Convert tick to date time
 *
 * @param[out] dst - The output SceDateTime struct pointer.
 * @param[in]  src - The input tick pointer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceRtcConvertTickToDateTime(SceDateTime *dst, SceRtcTick *src);

/**
 * Convert date time to unix time
 *
 * @param[in]  src - The input SceDateTime struct pointer.
 * @param[out] dst - The output unix time buffer pointer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceRtcConvertDateTimeToUnixTime(const SceDateTime *src, SceUInt64 *dst);

/**
 * Format an RTC tick as an RFC 3339 timestamp.
 *
 * FW 3.60 writes `YYYY-MM-DDThh:mm:ss.ffZ` for UTC, or
 * `YYYY-MM-DDThh:mm:ss.ff+hh:mm` / `-hh:mm` for a nonzero offset. The
 * fractional field contains hundredths of a second, truncated from the tick's
 * microseconds. The output buffer must hold at least 29 bytes.
 *
 * @param[out] date_time - Output string buffer.
 * @param[in] utc - UTC tick to format, or NULL to use the current tick.
 * @param[in] time_zone_minutes - Signed UTC offset in minutes, from -1439 through 1439.
 *
 * @return 0 on success, ::SCE_RTC_ERROR_INVALID_POINTER when \a date_time is
 * NULL, or ::SCE_RTC_ERROR_INVALID_VALUE for an invalid offset or adjusted tick.
 */
int ksceRtcFormatRFC3339(char *date_time, const SceRtcTick *utc, int time_zone_minutes);

/**
 * Return the accumulated system-time counter in microseconds.
 *
 * FW 3.60 combines the current kernel system time with RTC/Syscon baselines so
 * wall-clock adjustments and system-time rebasing do not reset this counter.
 * The function has no error return. Before RTC initialization, it returns
 * the current kernel system time.
 */
SceULong64 ksceRtcGetAccumulativeTime(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_RTC_H_ */
