/**
 * \file
 * \brief Header file which defines message dialog functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_MSG_DIALOG_H_
#define _PSP2_MSG_DIALOG_H_

#include "common_dialog.h"
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	//! Illegal parameter
	SCE_MSG_DIALOG_ERROR_PARAM	= 0x80100a01
};

enum {
	//! Max length of a user message
	SCE_MSG_DIALOG_USER_MSG_SIZE	= 512
};

typedef SceInt32 SceMsgDialogMode;
enum {
	SCE_MSG_DIALOG_MODE_INVALID      = 0,
	SCE_MSG_DIALOG_MODE_USER_MSG     = 1,
	SCE_MSG_DIALOG_MODE_SYSTEM_MSG   = 2,
	SCE_MSG_DIALOG_MODE_ERROR_CODE   = 3,
	SCE_MSG_DIALOG_MODE_PROGRESS_BAR	= 4
};

typedef SceInt32 SceMsgDialogSystemMessageType;
enum {
	SCE_MSG_DIALOG_SYSMSG_TYPE_INVALID					= 0,

	//! Displays "Please wait."
	SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT						= 1,

	//! Displays "There is not enough free space on the memory card."
	SCE_MSG_DIALOG_SYSMSG_TYPE_NOSPACE					= 2,

	//! Displays "Move away from the source of interference, or adjust the compass by moving your PS Vita system as shown below."
	SCE_MSG_DIALOG_SYSMSG_TYPE_MAGNETIC_CALIBRATION		= 3,

	//! Displays "Please wait." in a small message dialog
	SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT_SMALL				= 5,

	//! Displays "Please wait..." with a cancel button
	SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT_CANCEL				= 6,

	//! Displays "Cannot continue the application. No memory card is inserted."
	SCE_MSG_DIALOG_SYSMSG_TYPE_NEED_MC_CONTINUE			= 7,

	//! Displays "Cannot perform this operation. No memory card is inserted."
	SCE_MSG_DIALOG_SYSMSG_TYPE_NEED_MC_OPERATION		= 8,

	//! Displays "You must enable the microphone."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_MIC_DISABLED					= 100,

	//! Displays "You must use Wi-Fi to do this."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_WIFI_REQUIRED_OPERATION		= 101,

	//! Displays "You must use Wi-Fi to use this application."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_WIFI_REQUIRED_APPLICATION	= 102,

	//! Displays "No content is available yet."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_EMPTY_STORE					= 103,
};

typedef SceInt32 SceMsgDialogButtonType;

enum {
	SCE_MSG_DIALOG_BUTTON_TYPE_OK          = 0,
	SCE_MSG_DIALOG_BUTTON_TYPE_YESNO       = 1,
	SCE_MSG_DIALOG_BUTTON_TYPE_NONE        = 2,
	SCE_MSG_DIALOG_BUTTON_TYPE_OK_CANCEL   = 3,
	SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL      = 4
};

typedef SceInt32 SceMsgDialogButtonId;

enum {
	SCE_MSG_DIALOG_BUTTON_ID_INVALID    = 0,
	SCE_MSG_DIALOG_BUTTON_ID_OK         = 1,
	SCE_MSG_DIALOG_BUTTON_ID_YES        = 1,
	SCE_MSG_DIALOG_BUTTON_ID_NO         = 2
};

typedef SceInt32 SceMsgDialogProgressBarType;

enum {
	SCE_MSG_DIALOG_PROGRESSBAR_TYPE_PERCENTAGE   = 0
};

typedef SceInt32 SceMsgDialogProgressBarTarget;

enum {
	SCE_MSG_DIALOG_PROGRESSBAR_TARGET_BAR_DEFAULT   = 0
};

typedef SceUInt32 SceMsgDialogEnvFlag;

enum {
	SCE_MSG_DIALOG_ENV_FLAG_DEFAULT		= 0
};

typedef struct SceMsgDialogUserMessageParam {
	SceMsgDialogButtonType buttonType; // Type of button set
	const SceChar8 *msg;		// Displayed message 
	SceChar8 reserved[32];		// Reserved range
} SceMsgDialogUserMessageParam;

typedef struct SceMsgDialogSystemMessageParam {
	SceMsgDialogSystemMessageType sysMsgType;	// System message type
	SceInt32 value;		// Additional value
	SceChar8 reserved[32];	// Reserved range
} SceMsgDialogSystemMessageParam;

typedef struct SceMsgDialogErrorCodeParam {
	SceInt32 errorCode;		// Displayed error code
	SceChar8 reserved[32];	// Reserved range
} SceMsgDialogErrorCodeParam;

typedef struct SceMsgDialogProgressBarParam {
	SceMsgDialogProgressBarType barType;		// Progress bar type
	SceMsgDialogSystemMessageParam sysMsgParam;	// Displayed system message
	const SceChar8 *msg;		// Displayed user message
	SceInt32 reserved[32/4];		// Reserved range
} SceMsgDialogProgressBarParam;

typedef struct SceMsgDialogParam {
	SceUInt32 sdkVersion;      // Required to use MsgDialog. Just use NULL
	SceCommonDialogParam commonParam;	// Common parameter
	SceMsgDialogMode mode;		// MsgDialog Mode
	SceMsgDialogUserMessageParam *userMsgParam;		// Parameter for user message
	SceMsgDialogSystemMessageParam *sysMsgParam;	// Parameter for system prepared message
	SceMsgDialogErrorCodeParam *errorCodeParam;		// Parameter for display error code
	SceMsgDialogProgressBarParam *progBarParam;		// Parameter for progress bar
	SceMsgDialogEnvFlag flag;		// Settings for dialog environment
	SceChar8 reserved[32];		// Reserved range
} SceMsgDialogParam;

typedef struct SceMsgDialogResult {
	SceMsgDialogMode mode;		// Mode of function
	SceInt32 result;		// Result of executing function
	SceMsgDialogButtonId buttonId;	// Id of button user selected
	SceChar8 reserved[32];		// Reserved range
} SceMsgDialogResult;

static inline
void sceMsgDialogParamInit(SceMsgDialogParam *param)
{
	memset( param, 0x0, sizeof(SceMsgDialogParam) );
	_sceCommonDialogSetMagicNumber( &param->commonParam );
	param->sdkVersion = 0x03150021;
}

int sceMsgDialogInit(const SceMsgDialogParam *param);
SceCommonDialogStatus sceMsgDialogGetStatus(void);
int sceMsgDialogAbort(void);
int sceMsgDialogGetResult(SceMsgDialogResult *result);
int sceMsgDialogTerm(void);
int sceMsgDialogClose(void);

/***
 * Increases the rate of the progress bar in the message dialog
 *
 * @param target - Target progress bar
 * @param delta - Progress rate to increase (%)
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as FrameBuf pointer, output is blacked out.
*/
int sceMsgDialogProgressBarInc( SceMsgDialogProgressBarTarget target, SceUInt32 delta );

/***
 * Set the progress rate of the progress bar in the message dialog immediately
 *
 * @param target - Target progress bar
 * @param delta - Progress rate to increase (%)
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as FrameBuf pointer, output is blacked out.
*/
int sceMsgDialogProgressBarSetValue( SceMsgDialogProgressBarTarget target, SceUInt32 rate );

/***
 * Set the string displayed in the progress bar of the message dialog immediately
 *
 * @param target - Target progress bar
 * @param barMsg - The string displayed in the progress bar
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as FrameBuf pointer, output is blacked out.
*/
int sceMsgDialogProgressBarSetMsg( SceMsgDialogProgressBarTarget target, const SceChar8 *barMsg );

#ifdef __cplusplus
}
#endif

#endif
