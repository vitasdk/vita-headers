/**
 * \usergroup{SceIme}
 * \usage{psp2/libime.h,SceIme_stub,SCE_SYSMODULE_IME}
 */

#ifndef _PSP2_LIBIME_H
#define _PSP2_LIBIME_H

#include <string.h>
#include <psp2/types.h>
#include <psp2common/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_IME_WORK_BUFFER_SIZE        (20*1024)

#define SCE_IME_MAX_PREEDIT_LENGTH      (30)
#define SCE_IME_MAX_TEXT_LENGTH         (2048)

typedef enum SceImeErrorCode {
	SCE_IME_ERROR_ALREADY_OPENED               = 0x80100700,
	SCE_IME_ERROR_NOT_OPENED                   = 0x80100701,
	SCE_IME_ERROR_INVALID_POINTER              = 0x80100702,
	SCE_IME_ERROR_INVALID_PARAM                = 0x80100703,
	SCE_IME_ERROR_NO_MEMORY                    = 0x80100704,
	SCE_IME_ERROR_CONNECTION_FAILED            = 0x80100705,
	SCE_IME_ERROR_INVALID_TEXT                 = 0x80100706,
	SCE_IME_ERROR_TOO_MANY_REQUESTS            = 0x80100707,
	SCE_IME_ERROR_INVALID_SIZE                 = 0x80100710,
	SCE_IME_ERROR_INVALID_INPUT_METHOD         = 0x80100712,
	SCE_IME_ERROR_INVALID_SUPPORTED_LANGUAGES  = 0x80100713,
	SCE_IME_ERROR_INVALID_TYPE                 = 0x80100714,
	SCE_IME_ERROR_INVALID_OPTION               = 0x80100715,
	SCE_IME_ERROR_INVALID_WORK                 = 0x80100716,
	SCE_IME_ERROR_INVALID_ARG                  = 0x80100717,
	SCE_IME_ERROR_INVALID_HANDLER              = 0x80100718,
	SCE_IME_ERROR_INVALID_MAX_TEXT_LENGTH      = 0x80100719,
	SCE_IME_ERROR_INVALID_INPUT_TEXT_BUFFER    = 0x8010071a,
	SCE_IME_ERROR_INVALID_RESERVED             = 0x8010071b,
	SCE_IME_ERROR_INVALID_ENTER_LABEL          = 0x8010071c,
	SCE_IME_ERROR_INTERNAL                     = 0x80100750
} SceImeErrorCode;

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

typedef enum SceImeType {
	SCE_IME_TYPE_DEFAULT             = 0,
	SCE_IME_TYPE_BASIC_LATIN         = 1,
	SCE_IME_TYPE_NUMBER              = 2,
	SCE_IME_TYPE_EXTENDED_NUMBER     = 3,
	SCE_IME_TYPE_URL                 = 4,
	SCE_IME_TYPE_MAIL                = 5
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

typedef enum SceImeEvent {
	SCE_IME_EVENT_OPEN              = 0,
	SCE_IME_EVENT_UPDATE_TEXT       = 1,
	SCE_IME_EVENT_UPDATE_CARET      = 2,
	SCE_IME_EVENT_CHANGE_SIZE       = 3,
	SCE_IME_EVENT_PRESS_CLOSE       = 4,
	SCE_IME_EVENT_PRESS_ENTER       = 5
} SceImeEvent;

typedef struct SceImeRect {
	SceUInt32 x;
	SceUInt32 y;
	SceUInt32 width;
	SceUInt32 height;
} SceImeRect;

typedef struct SceImeEditText {
	SceUInt32 preeditIndex;
	SceUInt32 preeditLength;
	SceUInt32 caretIndex;
	SceWChar16 *str;
	SceUInt32 editIndex;
	SceInt32 editLengthChange;
} SceImeEditText;
	
typedef union SceImeEventParam {
	SceImeRect rect;
	SceImeEditText text;
	SceUInt32 caretIndex;
	SceUChar8 reserved[40];
} SceImeEventParam;

typedef struct SceImeEventData {
	SceUInt32 id;
	SceImeEventParam param;
} SceImeEventData;

typedef struct SceImeCaret {
	SceUInt32 x;
	SceUInt32 y;
	SceUInt32 height;
	SceUInt32 index;
} SceImeCaret;

typedef struct SceImePreeditGeometry {
	SceUInt32 x;
	SceUInt32 y;
	SceUInt32 height;
} SceImePreeditGeometry;

typedef SceInt32 (*SceImeTextFilter)(SceWChar16 *outText, SceUInt32 *outTextLength,
										const SceWChar16 *srcText, SceUInt32 srcTextLength);
typedef void (*SceImeEventHandler)(void* arg, const SceImeEventData *e);

typedef struct SceImeParam {
	SceUInt32 sdkVersion;

	SceUInt32 inputMethod;
	SceUInt64 supportedLanguages;	//!< Dialog languages (One or more ::SceImeLanguage)
	SceBool languagesForced;
	SceUInt32 type;					//!< Dialog type (One of ::SceImeType)
	SceUInt32 option;				//!< Dialog options (One or more ::SceImeOption)

	void *work;
	void *arg;
	SceImeEventHandler handler;
	SceImeTextFilter filter;

	SceWChar16 *initialText;
	SceUInt32 maxTextLength;
	SceWChar16 *inputTextBuffer;

	SceUChar8 enterLabel;
	SceUChar8 reserved[7];
} SceImeParam;

static inline
void sceImeParamInit(SceImeParam *param)
{
	memset(param, 0x0, sizeof(SceImeParam));
	param->sdkVersion = PSP2_SDK_VERSION;
}

SceInt32 sceImeOpen(const SceImeParam *param);
SceInt32 sceImeUpdate(void);
SceInt32 sceImeSetText(const SceWChar16 *text, SceUInt32 length);
SceInt32 sceImeSetCaret(const SceImeCaret *caret);
SceInt32 sceImeSetPreeditGeometry(const SceImePreeditGeometry *preedit);
SceInt32 sceImeClose(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_LIBIME_H */
