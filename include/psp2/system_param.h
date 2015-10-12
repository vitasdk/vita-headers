/**
 * \file
 * \brief Header file which defines output audio related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_SYSTEM_PARAM_H_
#define _PSP2_SYSTEM_PARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* System param id */
typedef SceUInt32 SceSystemParamId;

enum {
	//!< Language settings
	SCE_SYSTEM_PARAM_ID_LANG = 1,

	//!< Enter button assignment
	SCE_SYSTEM_PARAM_ID_ENTER_BUTTON,

	//!< Username string
	SCE_SYSTEM_PARAM_ID_USERNAME,

	//!< Date format
	SCE_SYSTEM_PARAM_ID_DATE_FORMAT,

	//!< Time format
	SCE_SYSTEM_PARAM_ID_TIME_FORMAT,

	//!< Time zone
	SCE_SYSTEM_PARAM_ID_TIME_ZONE,

	//!< Daylight savings time (0 = Disabled, 1 = Enabled)
	SCE_SYSTEM_PARAM_ID_DAYLIGHT_SAVINGS
};

/* Language settings */
typedef SceInt32 SceSystemParamLang;

enum {
	SCE_SYSTEM_PARAM_LANG_JAPANESE,
	SCE_SYSTEM_PARAM_LANG_ENGLISH_US,
	SCE_SYSTEM_PARAM_LANG_FRENCH,
	SCE_SYSTEM_PARAM_LANG_SPANISH,
	SCE_SYSTEM_PARAM_LANG_GERMAN,
	SCE_SYSTEM_PARAM_LANG_ITALIAN,
	SCE_SYSTEM_PARAM_LANG_DUTCH,
	SCE_SYSTEM_PARAM_LANG_PORTUGUESE,
	SCE_SYSTEM_PARAM_LANG_RUSSIAN,
	SCE_SYSTEM_PARAM_LANG_KOREAN,

	//! Traditional Chinese
	SCE_SYSTEM_PARAM_LANG_CHINESE_T,

	//! Simplified Chinese
	SCE_SYSTEM_PARAM_LANG_CHINESE_S,
	SCE_SYSTEM_PARAM_LANG_FINNISH,
	SCE_SYSTEM_PARAM_LANG_SWEDISH,
	SCE_SYSTEM_PARAM_LANG_DANISH,
	SCE_SYSTEM_PARAM_LANG_NORWEGIAN,
	SCE_SYSTEM_PARAM_LANG_POLISH,

	//! Brazil Portuguese
	SCE_SYSTEM_PARAM_LANG_POLISH_BR,
	SCE_SYSTEM_PARAM_LANG_ENGLISH_GB
};

/* Assignment of enter button */
typedef SceInt32 SceSystemParamEnterButtonAssign;

enum {
	SCE_SYSTEM_PARAM_ENTER_BUTTON_CIRCLE,
	SCE_SYSTEM_PARAM_ENTER_BUTTON_CROSS
};

/* Username */
#define SCE_SYSTEM_PARAM_USERNAME_MAXSIZE	(17) //!< Max size of username

/* Date display format */
enum {
	SCE_SYSTEM_PARAM_DATE_FORMAT_YYYYMMDD, //!< Year/Month/Day
	SCE_SYSTEM_PARAM_DATE_FORMAT_DDMMYYYY, //!< Day/Month/Year
	SCE_SYSTEM_PARAM_DATE_FORMAT_MMDDYYYY //!< Month/Day/Year
};

/* Time display format */
enum {
	SCE_SYSTEM_PARAM_TIME_FORMAT_12HR, //!< 12-hour clock
	SCE_SYSTEM_PARAM_TIME_FORMAT_24HR //!< 24-hour clock
};

#ifdef __cplusplus
}
#endif

#endif
