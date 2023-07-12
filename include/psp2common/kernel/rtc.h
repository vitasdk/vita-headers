/**
 * \usergroup{SceRtc}
 * \usage{psp2common/kernel/rtc.h}
 */


#ifndef _PSP2COMMON_KERNEL_RTC_H_
#define _PSP2COMMON_KERNEL_RTC_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum SceRtcErrorCode {
	SCE_RTC_ERROR_INVALID_VALUE        = 0x80251000,
	SCE_RTC_ERROR_INVALID_POINTER      = 0x80251001,
	SCE_RTC_ERROR_NOT_INITIALIZED      = 0x80251002,
	SCE_RTC_ERROR_ALREADY_REGISTERD    = 0x80251003,
	SCE_RTC_ERROR_NOT_FOUND            = 0x80251004,
	SCE_RTC_ERROR_BAD_PARSE            = 0x80251080,
	SCE_RTC_ERROR_INVALID_YEAR         = 0x80251081,
	SCE_RTC_ERROR_INVALID_MONTH        = 0x80251082,
	SCE_RTC_ERROR_INVALID_DAY          = 0x80251083,
	SCE_RTC_ERROR_INVALID_HOUR         = 0x80251084,
	SCE_RTC_ERROR_INVALID_MINUTE       = 0x80251085,
	SCE_RTC_ERROR_INVALID_SECOND       = 0x80251086,
	SCE_RTC_ERROR_INVALID_MICROSECOND  = 0x80251087
} SceRtcErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceRtcErrorCode);

/* As returned by sceRtcGetDayOfWeek */
typedef enum SceRtcDayOfWeek {
	SCE_RTC_DAYOFWEEK_SUNDAY    = 0,
	SCE_RTC_DAYOFWEEK_MONDAY    = 1,
	SCE_RTC_DAYOFWEEK_TUESDAY   = 2,
	SCE_RTC_DAYOFWEEK_WEDNESDAY = 3,
	SCE_RTC_DAYOFWEEK_THURSDAY  = 4,
	SCE_RTC_DAYOFWEEK_FRIDAY    = 5,
	SCE_RTC_DAYOFWEEK_SATURDAY  = 6,
	__SCE_RTC_DAYOFWEEK = 0xFFFFFFFF
} SceRtcDayOfWeek;
VITASDK_BUILD_ASSERT_EQ(4, SceRtcDayOfWeek);

typedef struct SceRtcTick {
	SceUInt64 tick;
} SceRtcTick;
VITASDK_BUILD_ASSERT_EQ(8, SceRtcTick);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_RTC_H_ */

