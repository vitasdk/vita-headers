/**
 * \usergroup{SceSystemParam}
 * \usage{psp2/system_param.h}
 */


#ifndef _PSP2_SYSTEM_PARAM_H_
#define _PSP2_SYSTEM_PARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

/** System param id */
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
	SCE_SYSTEM_PARAM_ID_DAYLIGHT_SAVINGS,
	//!< Max allowed value
	SCE_SYSTEM_PARAM_ID_MAX_VALUE = 0xFFFFFFFF
} SceSystemParamId;

/** Language settings */
typedef enum SceSystemParamLang {
	//! Japanese
	SCE_SYSTEM_PARAM_LANG_JAPANESE,
	//! American English
	SCE_SYSTEM_PARAM_LANG_ENGLISH_US,
	//! French
	SCE_SYSTEM_PARAM_LANG_FRENCH,
	//! Spanish
	SCE_SYSTEM_PARAM_LANG_SPANISH,
	//! German
	SCE_SYSTEM_PARAM_LANG_GERMAN,
	//! Italian
	SCE_SYSTEM_PARAM_LANG_ITALIAN,
	//! Dutch
	SCE_SYSTEM_PARAM_LANG_DUTCH,
	//! Portugal Portuguese
	SCE_SYSTEM_PARAM_LANG_PORTUGUESE_PT,
	//! Russian
	SCE_SYSTEM_PARAM_LANG_RUSSIAN,
	//! Korean
	SCE_SYSTEM_PARAM_LANG_KOREAN,
	//! Traditional Chinese
	SCE_SYSTEM_PARAM_LANG_CHINESE_T,
	//! Simplified Chinese
	SCE_SYSTEM_PARAM_LANG_CHINESE_S,
	//! Finnish
	SCE_SYSTEM_PARAM_LANG_FINNISH,
	//! Swedish
	SCE_SYSTEM_PARAM_LANG_SWEDISH,
	//! Danish
	SCE_SYSTEM_PARAM_LANG_DANISH,
	//! Norwegian
	SCE_SYSTEM_PARAM_LANG_NORWEGIAN,
	//! Polish
	SCE_SYSTEM_PARAM_LANG_POLISH,
	//! Brazil Portuguese
	SCE_SYSTEM_PARAM_LANG_PORTUGUESE_BR,
	//! British English
	SCE_SYSTEM_PARAM_LANG_ENGLISH_GB,
	//! Turkish
	SCE_SYSTEM_PARAM_LANG_TURKISH,
	//! Max allowed value
	SCE_SYSTEM_PARAM_LANG_MAX_VALUE = 0xFFFFFFFF
} SceSystemParamLang;

/** Assignment of enter button */
typedef enum SceSystemParamEnterButtonAssign {
	SCE_SYSTEM_PARAM_ENTER_BUTTON_CIRCLE,
	SCE_SYSTEM_PARAM_ENTER_BUTTON_CROSS,
	SCE_SYSTEM_PARAM_ENTER_BUTTON_MAX_VALUE = 0xFFFFFFFF
} SceSystemParamEnterButtonAssign;

/* Username */
#define SCE_SYSTEM_PARAM_USERNAME_MAXSIZE	(17) //!< Max size of username

/** Date display format */
typedef enum SceSystemParamDateFormat {
	SCE_SYSTEM_PARAM_DATE_FORMAT_YYYYMMDD, //!< Year/Month/Day
	SCE_SYSTEM_PARAM_DATE_FORMAT_DDMMYYYY, //!< Day/Month/Year
	SCE_SYSTEM_PARAM_DATE_FORMAT_MMDDYYYY //!< Month/Day/Year
} SceSystemParamDateFormat;

/** Time display format */
typedef enum SceSystemParamTimeFormat {
	SCE_SYSTEM_PARAM_TIME_FORMAT_12HR, //!< 12-hour clock
	SCE_SYSTEM_PARAM_TIME_FORMAT_24HR //!< 24-hour clock
} SceSystemParamTimeFormat;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SYSTEM_PARAM_H_ */
