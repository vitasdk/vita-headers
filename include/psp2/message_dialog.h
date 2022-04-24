/**
 * \usergroup{SceMessageDialog}
 * \usage{psp2/message_dialog.h,SceCommonDialog_stub}
 */


#ifndef _PSP2_MESSAGE_DIALOG_H_
#define _PSP2_MESSAGE_DIALOG_H_

#include <psp2/common_dialog.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceMsgDialogErrorCode {
	//! Illegal parameter
	SCE_MSG_DIALOG_ERROR_PARAM	= 0x80100A01
} SceMsgDialogErrorCode;

//! Max length of a user message
#define SCE_MSG_DIALOG_USER_MSG_SIZE	512

typedef enum SceMsgDialogMode {
	SCE_MSG_DIALOG_MODE_INVALID      = 0,
	SCE_MSG_DIALOG_MODE_USER_MSG     = 1,
	SCE_MSG_DIALOG_MODE_SYSTEM_MSG   = 2,
	SCE_MSG_DIALOG_MODE_ERROR_CODE   = 3,
	SCE_MSG_DIALOG_MODE_PROGRESS_BAR = 4
} SceMsgDialogMode;

typedef enum SceMsgDialogSystemMessageType {
	SCE_MSG_DIALOG_SYSMSG_TYPE_INVALID                        = 0,
	//! Displays "Please wait."
	SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT                           = 1,
	//! Displays "There is not enough free space on the memory card."
	SCE_MSG_DIALOG_SYSMSG_TYPE_NOSPACE                        = 2,
	//! Displays "Move away from the source of interference, or adjust the compass by moving your PS Vita system as shown below."
	SCE_MSG_DIALOG_SYSMSG_TYPE_MAGNETIC_CALIBRATION           = 3,
	//! Displays "Please wait." in a small message dialog
	SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT_SMALL                     = 5,
	//! Displays "Please wait..." with a cancel button
	SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT_CANCEL                    = 6,
	//! Displays "Cannot continue the application. No memory card is inserted."
	SCE_MSG_DIALOG_SYSMSG_TYPE_NEED_MC_CONTINUE               = 7,
	//! Displays "Cannot perform this operation. No memory card is inserted."
	SCE_MSG_DIALOG_SYSMSG_TYPE_NEED_MC_OPERATION              = 8,
	//! Displays "You must enable the microphone."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_MIC_DISABLED               = 100,
	//! Displays "You must use Wi-Fi to do this."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_WIFI_REQUIRED_OPERATION    = 101,
	//! Displays "You must use Wi-Fi to use this application."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_WIFI_REQUIRED_APPLICATION  = 102,
	//! Displays "No content is available yet."
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_EMPTY_STORE                = 103
} SceMsgDialogSystemMessageType;

typedef enum SceMsgDialogButtonType {
	SCE_MSG_DIALOG_BUTTON_TYPE_OK          = 0,
	SCE_MSG_DIALOG_BUTTON_TYPE_YESNO       = 1,
	SCE_MSG_DIALOG_BUTTON_TYPE_NONE        = 2,
	SCE_MSG_DIALOG_BUTTON_TYPE_OK_CANCEL   = 3,
	SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL      = 4,
	SCE_MSG_DIALOG_BUTTON_TYPE_3BUTTONS    = 5
} SceMsgDialogButtonType;

typedef enum SceMsgDialogButtonId {
	SCE_MSG_DIALOG_BUTTON_ID_INVALID    = 0,
	SCE_MSG_DIALOG_BUTTON_ID_OK         = 1,
	SCE_MSG_DIALOG_BUTTON_ID_YES        = 1,
	SCE_MSG_DIALOG_BUTTON_ID_NO         = 2,
	SCE_MSG_DIALOG_BUTTON_ID_RETRY      = 3,
	SCE_MSG_DIALOG_BUTTON_ID_BUTTON1    = 1,
	SCE_MSG_DIALOG_BUTTON_ID_BUTTON2    = 2,
	SCE_MSG_DIALOG_BUTTON_ID_BUTTON3    = 3
} SceMsgDialogButtonId;

typedef enum SceMsgDialogProgressBarType {
	SCE_MSG_DIALOG_PROGRESSBAR_TYPE_PERCENTAGE   = 0
} SceMsgDialogProgressBarType;

typedef enum SceMsgDialogProgressBarTarget {
	SCE_MSG_DIALOG_PROGRESSBAR_TARGET_BAR_DEFAULT   = 0
} SceMsgDialogProgressBarTarget;

typedef enum SceMsgDialogEnvFlag {
	SCE_MSG_DIALOG_ENV_FLAG_DEFAULT		= 0
} SceMsgDialogEnvFlag;

typedef enum SceMsgDialogFontSize {
	SCE_MSG_DIALOG_FONT_SIZE_DEFAULT = 0,
	SCE_MSG_DIALOG_FONT_SIZE_SMALL   = 1
} SceMsgDialogFontSize;

typedef struct SceMsgDialogButtonsParam {
	const char* msg1;          //!< Text of the first button
	SceInt32 fontSize1;        //!< Font size of the first button (one of ::SceMsgDialogFontSize)
	const char* msg2;          //!< Text of the second button
	SceInt32 fontSize2;        //!< Font size of the second button (one of ::SceMsgDialogFontSize)
	const char* msg3;          //!< Text of the third button
	SceInt32 fontSize3;        //!< Font size of the third button (one of ::SceMsgDialogFontSize)
	SceChar8 reserved[32];     //!< Reserved range
} SceMsgDialogButtonsParam;

typedef struct SceMsgDialogUserMessageParam {
	SceInt32 buttonType;                    //!< Type of button set (one of ::SceMsgDialogButtonType)
	const SceChar8 *msg;                    //!< Displayed message
	SceMsgDialogButtonsParam *buttonParam;  //!< Buttons parameters
	SceChar8 reserved[28];                  //!< Reserved range
} SceMsgDialogUserMessageParam;

typedef struct SceMsgDialogSystemMessageParam {
	SceInt32 sysMsgType;                    //!< System message type (one of ::SceMsgDialogSystemMessageType)
	SceInt32 value;                         //!< Additional value
	SceChar8 reserved[32];                  //!< Reserved range
} SceMsgDialogSystemMessageParam;

typedef struct SceMsgDialogErrorCodeParam {
	SceInt32 errorCode;     //!< Displayed error code
	SceChar8 reserved[32];  //!< Reserved range
} SceMsgDialogErrorCodeParam;

typedef struct SceMsgDialogProgressBarParam {
	SceInt32 barType;                           //!< Progress bar type (one of ::SceMsgDialogProgressBarType)
	SceMsgDialogSystemMessageParam sysMsgParam; //!< Displayed system message
	const SceChar8 *msg;                        //!< Displayed user message
	SceInt32 reserved[8];                       //!< Reserved range
} SceMsgDialogProgressBarParam;

typedef struct SceMsgDialogParam {
	SceUInt32 sdkVersion;                         //!< Required to use MsgDialog. Just use NULL
	SceCommonDialogParam commonParam;             //!< Common parameter
	SceInt32 mode;                                //!< Mode of function (one of ::SceMsgDialogMode)
	SceMsgDialogUserMessageParam *userMsgParam;   //!< Parameter for user message
	SceMsgDialogSystemMessageParam *sysMsgParam;  //!< Parameter for system prepared message
	SceMsgDialogErrorCodeParam *errorCodeParam;   //!< Parameter for display error code
	SceMsgDialogProgressBarParam *progBarParam;   //!< Parameter for progress bar
	SceInt32 flag;                                //!< Settings for dialog environment (one of ::SceMsgDialogEnvFlag)
	SceChar8 reserved[32];                        //!< Reserved range
} SceMsgDialogParam;

typedef struct SceMsgDialogResult {
	SceInt32 mode;                       //!< Mode of function (one of ::SceMsgDialogMode)
	SceInt32 result;                     //!< Result of executing function
	SceInt32 buttonId;                   //!< Id of button user selected (one of ::SceMsgDialogButtonId)
	SceChar8 reserved[32];               //!< Reserved range
} SceMsgDialogResult;

static inline
void sceMsgDialogParamInit(SceMsgDialogParam *param)
{
	memset( param, 0x0, sizeof(SceMsgDialogParam) );
	_sceCommonDialogSetMagicNumber( &param->commonParam );
	param->sdkVersion = PSP2_SDK_VERSION;
}

int sceMsgDialogInit(const SceMsgDialogParam *param);
SceCommonDialogStatus sceMsgDialogGetStatus(void);
int sceMsgDialogAbort(void);
int sceMsgDialogGetResult(SceMsgDialogResult *result);
int sceMsgDialogTerm(void);
int sceMsgDialogClose(void);

/**
 * Increases the rate of the progress bar in the message dialog
 *
 * @param target - Target progress bar
 * @param delta - Progress rate to increase (%)
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as FrameBuf pointer, output is blacked out.
*/
int sceMsgDialogProgressBarInc( SceMsgDialogProgressBarTarget target, SceUInt32 delta );

/**
 * Set the progress rate of the progress bar in the message dialog immediately
 *
 * @param target - Target progress bar
 * @param delta - Progress rate to increase (%)
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as FrameBuf pointer, output is blacked out.
*/
int sceMsgDialogProgressBarSetValue( SceMsgDialogProgressBarTarget target, SceUInt32 rate );

/**
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

#endif /* _PSP2_MESSAGE_DIALOG_H_ */

