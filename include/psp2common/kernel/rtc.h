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


typedef enum SceRtcErrorCode : SceInt32 {
	SCE_RTC_ERROR_INVALID_VALUE        = (SceInt32)0x80251000,
	SCE_RTC_ERROR_INVALID_POINTER      = (SceInt32)0x80251001,
	SCE_RTC_ERROR_NOT_INITIALIZED      = (SceInt32)0x80251002,
	SCE_RTC_ERROR_ALREADY_REGISTERD    = (SceInt32)0x80251003,
	SCE_RTC_ERROR_NOT_FOUND            = (SceInt32)0x80251004,
	SCE_RTC_ERROR_BAD_PARSE            = (SceInt32)0x80251080,
	SCE_RTC_ERROR_INVALID_YEAR         = (SceInt32)0x80251081,
	SCE_RTC_ERROR_INVALID_MONTH        = (SceInt32)0x80251082,
	SCE_RTC_ERROR_INVALID_DAY          = (SceInt32)0x80251083,
	SCE_RTC_ERROR_INVALID_HOUR         = (SceInt32)0x80251084,
	SCE_RTC_ERROR_INVALID_MINUTE       = (SceInt32)0x80251085,
	SCE_RTC_ERROR_INVALID_SECOND       = (SceInt32)0x80251086,
	SCE_RTC_ERROR_INVALID_MICROSECOND  = (SceInt32)0x80251087
} SceRtcErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceRtcErrorCode);

/* As returned by sceRtcGetDayOfWeek */
typedef enum SceRtcDayOfWeek : SceInt32 {
	SCE_RTC_DAYOFWEEK_SUNDAY    = 0,
	SCE_RTC_DAYOFWEEK_MONDAY    = 1,
	SCE_RTC_DAYOFWEEK_TUESDAY   = 2,
	SCE_RTC_DAYOFWEEK_WEDNESDAY = 3,
	SCE_RTC_DAYOFWEEK_THURSDAY  = 4,
	SCE_RTC_DAYOFWEEK_FRIDAY    = 5,
	SCE_RTC_DAYOFWEEK_SATURDAY  = 6
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

