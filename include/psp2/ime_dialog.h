/**
 * \usergroup{SceIme}
 * \usage{psp2/ime_dialog.h,SceIme_stub}
 */


#ifndef _PSP2_COMMON_DIALOG_IME_DIALOG_H
#define _PSP2_COMMON_DIALOG_IME_DIALOG_H

#include <psp2/common_dialog.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceImeLanguage {
	SCE_IME_LANGUAGE_DANISH              = 0x00000001ULL,
	SCE_IME_LANGUAGE_GERMAN              = 0x00000002ULL,
	SCE_IME_LANGUAGE_ENGLISH             = 0x00000004ULL,
	SCE_IME_LANGUAGE_SPANISH             = 0x00000008ULL,
	SCE_IME_LANGUAGE_FRENCH              = 0x00000010ULL,
	SCE_IME_LANGUAGE_ITALIAN             = 0x00000020ULL,
	SCE_IME_LANGUAGE_DUTCH               = 0x00000040ULL,
	SCE_IME_LANGUAGE_NORWEGIAN           = 0x00000080ULL,
	SCE_IME_LANGUAGE_POLISH              = 0x00000100ULL,
	SCE_IME_LANGUAGE_PORTUGUESE          = 0x00000200ULL,
	SCE_IME_LANGUAGE_RUSSIAN             = 0x00000400ULL,
	SCE_IME_LANGUAGE_FINNISH             = 0x00000800ULL,
	SCE_IME_LANGUAGE_SWEDISH             = 0x00001000ULL,
	SCE_IME_LANGUAGE_JAPANESE            = 0x00002000ULL,
	SCE_IME_LANGUAGE_KOREAN              = 0x00004000ULL,
	SCE_IME_LANGUAGE_SIMPLIFIED_CHINESE  = 0x00008000ULL,
	SCE_IME_LANGUAGE_TRADITIONAL_CHINESE = 0x00010000ULL,
	SCE_IME_LANGUAGE_PORTUGUESE_BR       = 0x00020000ULL,
	SCE_IME_LANGUAGE_ENGLISH_GB          = 0x00040000ULL,
	SCE_IME_LANGUAGE_TURKISH             = 0x00080000ULL
} SceImeLanguage;

#define SCE_IME_DIALOG_MAX_TITLE_LENGTH    (128)
#define SCE_IME_DIALOG_MAX_TEXT_LENGTH     (512)

typedef enum SceImeType {
	SCE_IME_TYPE_DEFAULT             = 0,
	SCE_IME_TYPE_BASIC_LATIN         = 1,
	SCE_IME_TYPE_NUMBER              = 2,
	SCE_IME_TYPE_EXTENDED_NUMBER     = 3
} SceImeType;

typedef enum SceImeEnterLabel {
	SCE_IME_ENTER_LABEL_DEFAULT = 0,
	SCE_IME_ENTER_LABEL_SEND    = 1,
	SCE_IME_ENTER_LABEL_SEARCH  = 2,
	SCE_IME_ENTER_LABEL_GO      = 3
} SceImeEnterLabel;

typedef enum SceImeOption {
	SCE_IME_OPTION_MULTILINE               = 0x01,
	SCE_IME_OPTION_NO_AUTO_CAPITALIZATION  = 0x02,
	SCE_IME_OPTION_NO_ASSISTANCE           = 0x04
} SceImeOption;

typedef enum SceImeDialogDialogMode {
	SCE_IME_DIALOG_DIALOG_MODE_DEFAULT      = 0,
	SCE_IME_DIALOG_DIALOG_MODE_WITH_CANCEL  = 1
} SceImeDialogDialogMode;

typedef enum SceImeDialogTextboxMode {
	SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT     = 0,
	SCE_IME_DIALOG_TEXTBOX_MODE_PASSWORD    = 1,
	SCE_IME_DIALOG_TEXTBOX_MODE_WITH_CLEAR	= 2
} SceImeDialogTextboxMode;

typedef enum SceImeDialogButton {
	SCE_IME_DIALOG_BUTTON_NONE  = 0,
	SCE_IME_DIALOG_BUTTON_CLOSE = 1,
	SCE_IME_DIALOG_BUTTON_ENTER = 2
} SceImeDialogButton;

typedef SceInt32 (*SceImeCharFilter)(SceWChar16 ch);

typedef struct SceImeDialogParam {
	SceUInt32 sdkVersion;

	SceUInt32 inputMethod;
	SceUInt64 supportedLanguages;         //!< Dialog languages (One or more ::SceImeLanguage)
	SceBool languagesForced;
	SceUInt32 type;                       //!< Dialog type (One of ::SceImeType)
	SceUInt32 option;                     //!< Dialog options (One or more ::SceImeOption)
	SceImeCharFilter filter;

	SceUInt32 dialogMode;                 //!< Dialog mode (One of ::SceImeDialogDialogMode)
	SceUInt32 textBoxMode;                //!< Textbox mode (One of ::SceImeDialogTextboxMode)
	const SceWChar16 *title;
	SceUInt32 maxTextLength;
	SceWChar16 *initialText;
	SceWChar16 *inputTextBuffer;

	SceCommonDialogParam commonParam;

	SceUChar8 enterLabel;
	SceChar8 reserved[35];
} SceImeDialogParam;

typedef struct SceImeDialogResult {
	SceInt32 result;
	SceInt32 button;
	SceChar8 reserved[28];
} SceImeDialogResult;

static inline
void sceImeDialogParamInit( SceImeDialogParam *param )
{
	memset( param, 0x0, sizeof(SceImeDialogParam) );
	_sceCommonDialogSetMagicNumber(&param->commonParam);
	param->sdkVersion = 0x03150021;
}

SceInt32 sceImeDialogInit( const SceImeDialogParam *param );
SceCommonDialogStatus sceImeDialogGetStatus( void );
SceInt32 sceImeDialogAbort( void );
SceInt32 sceImeDialogGetResult( SceImeDialogResult* result );
SceInt32 sceImeDialogTerm( void );

#ifdef __cplusplus
}
#endif

#endif

