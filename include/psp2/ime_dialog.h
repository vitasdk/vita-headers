/**
 * \usergroup{SceIme}
 * \usage{psp2/ime_dialog.h,SceIme_stub,SCE_SYSMODULE_IME}
 */


#ifndef _PSP2_COMMON_DIALOG_IME_DIALOG_H
#define _PSP2_COMMON_DIALOG_IME_DIALOG_H

#include <psp2/common_dialog.h>
#include <psp2/types.h>
#include <psp2/libime.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_IME_DIALOG_MAX_TITLE_LENGTH    (128)
#define SCE_IME_DIALOG_MAX_TEXT_LENGTH     (2048)

typedef enum SceImeDialogErrorCode {
	SCE_IME_DIALOG_ERROR_PARAM                      = 0x80102001,
	SCE_IME_DIALOG_ERROR_INTERNAL                   = 0x80102002,
	SCE_IME_DIALOG_ERROR_INVALID_DIALOG_MODE        = 0x80102003,
	SCE_IME_DIALOG_ERROR_INVALID_TEXT_BOX_MODE      = 0x80102004,
	SCE_IME_DIALOG_ERROR_INVALID_TITLE              = 0x80102005
} SceImeDialogError;

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

typedef struct SceImeDialogParam {
	SceUInt32 sdkVersion;

	SceUInt32 inputMethod;
	SceUInt64 supportedLanguages;         //!< Dialog languages (One or more ::SceImeLanguage)
	SceBool languagesForced;
	SceUInt32 type;                       //!< Dialog type (One of ::SceImeType)
	SceUInt32 option;                     //!< Dialog options (One or more ::SceImeOption)
	SceImeTextFilter filter;

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
	param->sdkVersion = PSP2_SDK_VERSION;
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
