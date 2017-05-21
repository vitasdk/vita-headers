/**
 * \usergroup{SceRtc}
 * \usage{psp2/rtc.h,SceRtc_stub}
 */


#ifndef _PSP2_RTC_H_
#define _PSP2_RTC_H_

#include <psp2/types.h>
#include <time.h>

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

/* As returned by sceRtcGetDayOfWeek */
typedef struct SceRtcDayOfWeek {
	SCE_RTC_DAYOFWEEK_SUNDAY    = 0,
	SCE_RTC_DAYOFWEEK_MONDAY    = 1,
	SCE_RTC_DAYOFWEEK_TUESDAY   = 2,
	SCE_RTC_DAYOFWEEK_WEDNESDAY = 3,
	SCE_RTC_DAYOFWEEK_THURSDAY  = 4,
	SCE_RTC_DAYOFWEEK_FRIDAY    = 5,
	SCE_RTC_DAYOFWEEK_SATURDAY  = 6
} SceRtcDayOfWeek;

typedef struct SceRtcTick {
	SceUInt64 tick;
} SceRtcTick;

unsigned int sceRtcGetTickResolution(void);
int sceRtcGetCurrentTick(SceRtcTick *tick);
int sceRtcGetCurrentClock(SceDateTime *time, int time_zone);
int sceRtcGetCurrentClockLocalTime(SceDateTime *time);
int sceRtcGetCurrentNetworkTick(SceRtcTick *tick);
int sceRtcConvertUtcToLocalTime(const SceRtcTick *utc, SceRtcTick *local_time);
int sceRtcConvertLocalTimeToUtc(const SceRtcTick *local_time, SceRtcTick *utc);
int sceRtcIsLeapYear(int year);
int sceRtcCheckValid(const SceDateTime *time);
int sceRtcGetDaysInMonth(int year, int month);
int sceRtcGetDayOfWeek(int year, int month, int day);

/* Win/POSIX compliant function */
int sceRtcSetTime_t(SceDateTime *time, time_t iTime);
int sceRtcSetTime64_t(SceDateTime *time, SceUInt64 ullTime);
int sceRtcGetTime_t(const SceDateTime *time, time_t *piTime);
int sceRtcGetTime64_t(const SceDateTime *time, SceUInt64 *pullTime);
int sceRtcSetDosTime(SceDateTime *time, unsigned int uiDosTime);
int sceRtcGetDosTime(const SceDateTime *time, unsigned int *puiDosTime);
int sceRtcSetWin32FileTime(SceDateTime *time, SceUInt64 ulWin32Time);
int sceRtcGetWin32FileTime(const SceDateTime *time, SceUInt64 *ulWin32Time);
int sceRtcSetTick(SceDateTime *time, const SceRtcTick *tick);
int sceRtcGetTick(const SceDateTime *time, SceRtcTick *tick);

/* Arithmetic function */
int sceRtcCompareTick(const SceRtcTick *pTick1, const SceRtcTick *pTick2);
int sceRtcTickAddTicks(SceRtcTick *pTick0, const SceRtcTick *pTick1, SceLong64 lAdd);
int sceRtcTickAddMicroseconds(SceRtcTick *pTick0, const SceRtcTick *pTick1, SceLong64 lAdd);
int sceRtcTickAddSeconds(SceRtcTick *pTick0, const SceRtcTick *pTick1, SceLong64 lAdd);
int sceRtcTickAddMinutes(SceRtcTick *pTick0, const SceRtcTick *pTick1, SceLong64 lAdd);
int sceRtcTickAddHours(SceRtcTick *pTick0, const SceRtcTick *pTick1, int lAdd);
int sceRtcTickAddDays(SceRtcTick *pTick0, const SceRtcTick *pTick1, int lAdd);
int sceRtcTickAddWeeks(SceRtcTick *pTick0, const SceRtcTick *pTick1, int lAdd);
int sceRtcTickAddMonths(SceRtcTick *pTick0, const SceRtcTick *pTick1, int lAdd);
int sceRtcTickAddYears(SceRtcTick *pTick0, const SceRtcTick *pTick1, int lAdd);

/* Formating function */
int sceRtcFormatRFC2822(char *pszDateTime, const SceRtcTick *utc, int iTimeZoneMinutes);
int sceRtcFormatRFC2822LocalTime(char *pszDateTime, const SceRtcTick *utc);
int sceRtcFormatRFC3339(char *pszDateTime, const SceRtcTick *utc, int iTimeZoneMinutes);
int sceRtcFormatRFC3339LocalTime(char *pszDateTime, const SceRtcTick *utc);
int sceRtcParseDateTime(SceRtcTick *utc, const char *pszDateTime);
int sceRtcParseRFC3339(SceRtcTick *utc, const char *pszDateTime);

/* Inline SceDateTime Getters */
static inline int sceRtcGetYear(const SceDateTime *time){return time->year;}
static inline int sceRtcGetMonth(const SceDateTime *time){return time->month;}
static inline int sceRtcGetDay(const SceDateTime *time){return time->day;}
static inline int sceRtcGetHour(const SceDateTime *time){return time->hour;}
static inline int sceRtcGetMinute(const SceDateTime *time){return time->minute;}
static inline int sceRtcGetSecond(const SceDateTime *time){return time->second;}
static inline int sceRtcGetMicrosecond(const SceDateTime *time){return (int)time->microsecond;}

/* Inline SceDateTime Setters */
static inline int sceRtcSetYear(SceDateTime *time, int year){
	if (year<1 || year>9999)
		return (SCE_RTC_ERROR_INVALID_YEAR);
	time->year = (unsigned short)year;
	return 0;
}
static inline int sceRtcSetMonth(SceDateTime *time, int month){
	if (month<1 || month>12) {
		return (SCE_RTC_ERROR_INVALID_MONTH);
	}
	time->month = (unsigned short)month;
	return 0;
}
static inline int sceRtcSetDay(SceDateTime *time, int day){
	if (day<1 || day>31) {
		return (SCE_RTC_ERROR_INVALID_DAY);
	}
	time->day = (unsigned short)day;
	return 0;
}
static inline int sceRtcSetHour(SceDateTime *time, int hour){
	if (hour<0 || hour>23) {
		return (SCE_RTC_ERROR_INVALID_HOUR);
	}
	time->hour = (unsigned short)hour;
	return 0;
}
static inline int sceRtcSetMinute(SceDateTime *time, int minute){
	if (minute<0 || minute>59) {
		return (SCE_RTC_ERROR_INVALID_MINUTE);
	}
	time->minute = (unsigned short)minute;
	return 0;
}
static inline int sceRtcSetSecond(SceDateTime *time, int second){
	if (second<0 || second>59) {
		return (SCE_RTC_ERROR_INVALID_SECOND);
	}
	time->second = (unsigned short)second;
	return 0;
}
static inline int sceRtcSetMicrosecond(SceDateTime *time, int microsecond){
	if (microsecond<0 || microsecond>999999) {
		return (SCE_RTC_ERROR_INVALID_MICROSECOND);
	}
	time->microsecond = (unsigned int)microsecond;
	return 0;
}

/* Aliases */
#define sceRtcGetCurrentTickUtc(_tick)                          sceRtcGetCurrentTick(_tick)
#define sceRtcGetCurrentClockUtc(_p)                            sceRtcGetCurrentClock(_p,0)
#define sceRtcGetCurrentNetworkTickUtc(_tick)                   sceRtcGetCurrentNetworkTick(_tick)
#define sceRtcConvertTime_tToDateTime(_timet, _pdatetime)       sceRtcSetTime_t(_pdatetime, _timet)
#define sceRtcConvertTime64_tToDateTime(_timet, _pdatetime)     sceRtcSetTime64_t(_pdatetime, _timet)
#define sceRtcConvertDateTimeToTime_t(_pdatetime, _ptimet)      sceRtcGetTime_t(_pdatetime, _ptimet)
#define sceRtcConvertDateTimeToTime64_t(_pdatetime, _ptimet)    sceRtcGetTime64_t(_pdatetime, _ptimet)
#define sceRtcConvertDosTimeToDateTime(_dostime, _pdatetime)    sceRtcSetDosTime(_pdatetime, _dostime)
#define sceRtcConvertDateTimeToDosTime(_pdatetime, _pdostime)   sceRtcGetDosTime(_pdatetime, _pdostime)
#define sceRtcConvertWin32TimeToDateTime(_pw32time, _pdatetime) sceRtcSetWin32FileTime(_pdatetime, _pw32time)
#define sceRtcConvertDateTimeToWin32Time(_pdatetime, _pw32time) sceRtcGetWin32FileTime(_pdatetime, _pw32time)
#define sceRtcConvertTickToDateTime(_ptick, _pdatetime)         sceRtcSetTick(_pdatetime, _ptick)
#define sceRtcConvertDateTimeToTick(_pdatetime, _ptick)         sceRtcGetTick(_pdatetime, _ptick)

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_RTC_H_ */

