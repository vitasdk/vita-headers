/**
 * \file
 * \brief Header file which defines RTC variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_RTC_H_
#define _PSP2_RTC_H_

#include <psp2/types.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* struct/union */

typedef struct SceRtcTime {
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minutes;
	unsigned short seconds;
	unsigned int microseconds;
} SceRtcTime;

typedef enum SceRtcCheckValidError {
	SCE_RTC_INVALID_YEAR	= -1,
	SCE_RTC_INVALID_MONTH	= -2,
	SCE_RTC_INVALID_DAY	= -3,
	SCE_RTC_INVALID_HOUR	= -4,
	SCE_RTC_INVALID_MINUTES	= -5,
	SCE_RTC_INVALID_SECONDS	= -6,
	SCE_RTC_INVALID_MICROSECONDS	= -7
} SceRtcCheckValidError;

/* prototypes */

unsigned int sceRtcGetTickResolution();
int sceRtcGetCurrentTick(uint64_t *tick);
int sceRtcGetCurrentClock(SceRtcTime *time, int tz);
int sceRtcGetCurrentClockLocalTime(SceRtcTime *time);

int sceRtcConvertUtcToLocalTime(const uint64_t *tickUTC, uint64_t *tickLocal);
int sceRtcConvertLocalTimeToUTC(const uint64_t *tickLocal, uint64_t *tickUTC);

int sceRtcIsLeapYear(int year);

int sceRtcGetDaysInMonth(int year, int month);
int sceRtcGetDayOfWeek(int year, int month, int day);

int sceRtcCheckValid(const SceRtcTime *date);

int sceRtcSetTick(SceRtcTime *date, const uint64_t *tick);
int sceRtcGetTick(const SceRtcTime *date, uint64_t *tick);
int sceRtcCompareTick(const uint64_t *tick1, const uint64_t *tick2);

int sceRtcTickAddTicks(uint64_t *destTick, const uint64_t *srcTick, uint64_t numTicks);
int sceRtcTickAddMicroseconds(uint64_t *destTick, const uint64_t *srcTick, uint64_t numMS);
int sceRtcTickAddSeconds(uint64_t *destTick, const uint64_t *srcTick, uint64_t numSecs);
int sceRtcTickAddMinutes(uint64_t *destTick, const uint64_t *srcTick, uint64_t numMins);
int sceRtcTickAddHours(uint64_t *destTick, const uint64_t *srcTick, int numHours);
int sceRtcTickAddDays(uint64_t *destTick, const uint64_t *srcTick, int numDays);
int sceRtcTickAddWeeks(uint64_t *destTick, const uint64_t *srcTick, int numWeeks);
int sceRtcTickAddMonths(uint64_t *destTick, const uint64_t *srcTick, int numMonths);
int sceRtcTickAddYears(uint64_t *destTick, const uint64_t *srcTick, int numYears);

int sceRtcSetTime_t(SceRtcTime *date, const time_t time);
int sceRtcGetTime_t(const SceRtcTime *date, time_t *time);
int sceRtcSetDosTime(SceRtcTime *date, unsigned int dosTime);
int sceRtcGetDosTime(SceRtcTime *date, unsigned int dosTime);
int sceRtcSetWin32FileTime(SceRtcTime *date, uint64_t *win32Time);
int sceRtcGetWin32FileTime(SceRtcTime *date, uint64_t *win32Time);

int sceRtcParseDateTime(uint64_t *destTick, const char *dateString);
int sceRtcFormatRFC2822(char *pszDateTime, const uint64_t *pUtc, int iTimeZoneMinutes);
int sceRtcFormatRFC2822LocalTime(char *pszDateTime, const uint64_t *pUtc);
int sceRtcFormatRFC3339(char *pszDateTime, const uint64_t *pUtc, int iTimeZoneMinutes);
int sceRtcFormatRFC3339LocalTime(char *pszDateTime, const uint64_t *pUtc);
int sceRtcParseRFC3339(uint64_t *pUtc, const char *pszDateTime);

/* missing prototypes */

// sceRtcGetLastAdjustedTick
// sceRtcSetTime64_t
// sceRtcGetLastReincarnatedTick
// sceRtcGetDayOfYear
// sceRtcGetTime64_t
// sceRtcGetCurrentNetworkTick

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_RTC_H_ */
