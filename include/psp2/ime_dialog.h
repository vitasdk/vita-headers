/**
 * \file
 * \brief Header file which defines power variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_COMMON_DIALOG_IME_DIALOG_H
#define _PSP2_COMMON_DIALOG_IME_DIALOG_H

#include <psp2/common_dialog.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_IME_LANGUAGE_DANISH              0x00000001ULL
#define SCE_IME_LANGUAGE_GERMAN              0x00000002ULL
#define SCE_IME_LANGUAGE_ENGLISH             0x00000004ULL
#define SCE_IME_LANGUAGE_SPANISH             0x00000008ULL
#define SCE_IME_LANGUAGE_FRENCH              0x00000010ULL
#define SCE_IME_LANGUAGE_ITALIAN             0x00000020ULL
#define SCE_IME_LANGUAGE_DUTCH               0x00000040ULL
#define SCE_IME_LANGUAGE_NORWEGIAN           0x00000080ULL
#define SCE_IME_LANGUAGE_POLISH              0x00000100ULL
#define SCE_IME_LANGUAGE_PORTUGUESE          0x00000200ULL
#define SCE_IME_LANGUAGE_RUSSIAN             0x00000400ULL
#define SCE_IME_LANGUAGE_FINNISH             0x00000800ULL
#define SCE_IME_LANGUAGE_SWEDISH             0x00001000ULL
#define SCE_IME_LANGUAGE_JAPANESE            0x00002000ULL
#define SCE_IME_LANGUAGE_KOREAN              0x00004000ULL
#define SCE_IME_LANGUAGE_SIMPLIFIED_CHINESE  0x00008000ULL
#define SCE_IME_LANGUAGE_TRADITIONAL_CHINESE 0x00010000ULL

#define SCE_IME_TYPE_DEFAULT                 0
#define SCE_IME_TYPE_BASIC_LATIN             1

#define SCE_IME_DIALOG_MAX_TITLE_LENGTH			(128)
#define SCE_IME_DIALOG_MAX_TEXT_LENGTH		    (512)

#define SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT     0
#define SCE_IME_DIALOG_TEXTBOX_MODE_PASSWORD    1

typedef SceInt32 (*SceImeCharFilter)(SceWChar16 ch);

typedef struct SceImeDialogParam {
	SceUInt32 sdkVersion;

	SceUInt32 inputMethod;
	SceUInt64 supportedLanguages;
	SceBool languagesForced;
	SceUInt32 type;
	SceUInt32 option;
	SceImeCharFilter filter;

	SceUInt32 dialogMode;
	SceUInt32 textBoxMode;
	const SceWChar16 *title;
	SceUInt32 maxTextLength;
	SceWChar16 *initialText;
	SceWChar16 *inputTextBuffer;

	SceCommonDialogParam commonParam;

	SceChar8 reserved[32];
} SceImeDialogParam;

typedef struct SceImeDialogResult {
	SceInt32 unk;
	SceInt32 result;
	SceChar8 reserved[32];
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