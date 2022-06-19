/**
 * \usergroup{SceNotificationUtil}
 * \usage{psp2/notificationutil.h,SceNotificationUtil_stub,SCE_SYSMODULE_NOTIFICATION_UTIL}
 */

#ifndef _PSP2_NOTIFICATIONUTIL_H_
#define _PSP2_NOTIFICATIONUTIL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constants
 */
#define SCE_NOTIFICATIONUTIL_TEXT_MAX			0x3F

/**
 * Error Codes
 */
typedef enum SceNotificationUitlErrorCode {
	SCE_NOTIFICATIONUTIL_ERROR_INTERNAL = 0x80106300
} SceNotificationUtilErrorCode;

/**
 * BGDL-type notification event handler function
 */
typedef void(*SceNotificationUtilProgressEventHandler)(int eventId);

typedef struct SceNotificationUtilProgressInitParam {
	SceWChar16 notificationText[SCE_NOTIFICATIONUTIL_TEXT_MAX];
	SceInt16 separator0;						//must be 0
	SceWChar16 notificationSubText[SCE_NOTIFICATIONUTIL_TEXT_MAX];
	SceInt16 separator1;						//must be 0
	SceChar8 unk[0x3E6];
	SceInt32 unk_4EC;						//can be set to 0
	SceNotificationUtilProgressEventHandler eventHandler;
} SceNotificationUtilProgressInitParam;

typedef struct SceNotificationUtilProgressUpdateParam {
	SceWChar16 notificationText[SCE_NOTIFICATIONUTIL_TEXT_MAX];
	SceInt16 separator0;						//must be 0
	SceWChar16 notificationSubText[SCE_NOTIFICATIONUTIL_TEXT_MAX];
	SceInt16 separator1;						//must be 0
	SceFloat targetProgress;
	SceChar8 reserved[0x38];
} SceNotificationUtilProgressUpdateParam;

typedef struct SceNotificationUtilProgressFinishParam {
	SceWChar16 notificationText[SCE_NOTIFICATIONUTIL_TEXT_MAX];
	SceInt16 separator0;						//must be 0
	SceWChar16 notificationSubText[SCE_NOTIFICATIONUTIL_TEXT_MAX];
	SceInt16 separator1;						//must be 0
	SceChar8 path[0x3E8];
} SceNotificationUtilProgressFinishParam;

/**
 * Initialize notification util for use with BG application.
 *
 * Does not need to be called for normal applications.
 */
SceInt32 sceNotificationUtilBgAppInitialize(void);

/**
 * Send notification.
 *
 * Text buffer size must be 0x410.
 */
SceInt32 sceNotificationUtilSendNotification(const SceWChar16* text);

/**
 * Clean notifications for calling app from notification history.
 */
SceInt32 sceNotificationUtilCleanHistory(void);

/**
 * Start BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressBegin(SceNotificationUtilProgressInitParam* initParams);

/**
 * Update BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressUpdate(SceNotificationUtilProgressUpdateParam* updateParams);

/**
 * Finish BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressFinish(SceNotificationUtilProgressFinishParam* finishParams);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_NOTIFICATIONUTIL_H_ */
