/**
 * \usergroup{SceSystemParam}
 * \usage{psp2/system_param.h}
 */


#ifndef _PSP2_SYSTEM_PARAM_H_
#define _PSP2_SYSTEM_PARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* System param id */
typedef enum SceSystemParamId {
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
} SceSystemParamId;

/* Language settings */
typedef enum SceSystemParamLang {
	SCE_SYSTEM_PARAM_LANG_JAPANESE,
	SCE_SYSTEM_PARAM_LANG_ENGLISH_US,
	SCE_SYSTEM_PARAM_LANG_FRENCH,
	SCE_SYSTEM_PARAM_LANG_SPANISH,
	SCE_SYSTEM_PARAM_LANG_GERMAN,
	SCE_SYSTEM_PARAM_LANG_ITALIAN,
	SCE_SYSTEM_PARAM_LANG_DUTCH,
	SCE_SYSTEM_PARAM_LANG_PORTUGUESE_PT,
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
	SCE_SYSTEM_PARAM_LANG_PORTUGUESE_BR,
	SCE_SYSTEM_PARAM_LANG_ENGLISH_GB,
	SCE_SYSTEM_PARAM_LANG_TURKISH
} SceSystemParamLang;

/* Assignment of enter button */
typedef enum SceSystemParamEnterButtonAssign {
	SCE_SYSTEM_PARAM_ENTER_BUTTON_CIRCLE,
	SCE_SYSTEM_PARAM_ENTER_BUTTON_CROSS
} SceSystemParamEnterButtonAssign;

/* Username */
#define SCE_SYSTEM_PARAM_USERNAME_MAXSIZE	(17) //!< Max size of username

/* Date display format */
typedef enum SceSystemParamDateFormat {
	SCE_SYSTEM_PARAM_DATE_FORMAT_YYYYMMDD, //!< Year/Month/Day
	SCE_SYSTEM_PARAM_DATE_FORMAT_DDMMYYYY, //!< Day/Month/Year
	SCE_SYSTEM_PARAM_DATE_FORMAT_MMDDYYYY //!< Month/Day/Year
} SceSystemParamDateFormat;

/* Time display format */
typedef enum SceSystemParamTimeFormat {
	SCE_SYSTEM_PARAM_TIME_FORMAT_12HR, //!< 12-hour clock
	SCE_SYSTEM_PARAM_TIME_FORMAT_24HR //!< 24-hour clock
} SceSystemParamTimeFormat;

#ifdef __cplusplus
}
#endif

#endif