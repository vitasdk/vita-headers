/**
 * \usergroup{SceIncomingDialog}
 * \usage{psp2/incoming_dialog.h,SceIncomingDialog_stub,SCE_SYSMODULE_INCOMING_DIALOG}
 */


#ifndef _PSP2_INCOMING_DIALOG_H_
#define _PSP2_INCOMING_DIALOG_H_

#include <psp2/kernel/clib.h>
#include <psp2/types.h>
#include <psp2common/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Dialog status
 */
typedef enum SceIncomingDialogStatus {
	SCE_INCOMING_DIALOG_NOT_RUNNING,
	SCE_INCOMING_DIALOG_ACCEPTED,
	SCE_INCOMING_DIALOG_RUNNING,
	SCE_INCOMING_DIALOG_REJECTED,
	SCE_INCOMING_DIALOG_CLOSED,
	SCE_INCOMING_DIALOG_BUSY,
	SCE_INCOMING_DIALOG_TIMEOUT
} SceIncomingDialogStatus;

/**
 * Error Codes
 */
typedef enum SceIncomingDialogErrorCode {
	SCE_INCOMINGDIALOG_ERROR_INVALID_ARG = 0x80106201
} SceIncomingDialogErrorCode;

typedef struct SceIncomingDialogParam {
	SceInt32 sdkVersion;
	SceChar8 audioPath[0x80];           //Path to audio file that will be played during dialog, .mp3, .at9, m4a. Can be NULL
	SceChar8 titleid[0x10];             //TitleId of the application to open when "accept" button has been pressed. Can be NULL
	SceInt32 unk_BC;                    //Can be set to 0
	SceUInt32 dialogTimer;              //Time to show dialog in seconds
	SceChar8 reserved1[0x3E];
	SceWChar16 buttonRightText[0x1F];   //Text for "accept" button
	SceInt16 separator0;                //must be 0
	SceWChar16 buttonLeftText[0x1F];    //Text for "reject" button. If NULL, only "accept" button will be created
	SceInt16 separator1;                //must be 0
	SceWChar16 dialogText[0x80];        //Text for dialog window, also shared with notification
	SceInt16 separator2;                //must be 0
} SceIncomingDialogParam;

/**
 * Initialize incoming dialog library, init_type must be 1.
 */
SceInt32 sceIncomingDialogInitialize(int init_type);

/**
 * Open incoming dialog.
 */
SceInt32 sceIncomingDialogOpen(SceIncomingDialogParam* dialogParam);

/**
 * Returns current status of incoming dialog.
 */
SceInt32 sceIncomingDialogGetStatus(void);

/**
 * Force exit to LiveArea and show dialog window
 */
SceInt32 sceIncomingDialogSwitchToDialog(void);

/**
 * Close incoming dialog.
 */
SceInt32 sceIncomingDialogClose(void);

/**
 * Finish incoming dialog library
 */
SceInt32 sceIncomingDialogFinish(void);

static inline
void sceIncomingDialogParamInit(SceIncomingDialogParam* dialogParam)
{
	sceClibMemset(dialogParam, 0x0, sizeof(SceIncomingDialogParam));
	dialogParam->sdkVersion = PSP2_SDK_VERSION;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_INCOMING_DIALOG_H_ */
