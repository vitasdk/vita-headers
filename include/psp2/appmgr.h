/**
 * \usergroup{SceAppMgr}
 * \usage{psp2/appmgr.h,SceAppMgr_Stub}
 */


#ifndef _PSP2_APPMGR_H_
#define _PSP2_APPMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAppMgrErrorCode {
	//! Busy
	SCE_APPMGR_ERROR_BUSY               = 0x80802000,
	//! Invalid state
	SCE_APPMGR_ERROR_STATE              = 0x80802013,
	//! NULL pointer
	SCE_APPMGR_ERROR_NULL_POINTER		= 0x80802016,
	//!< Invalid param
	SCE_APPMGR_ERROR_INVALID            = 0x8080201a,
	//!< Invalid self path
	SCE_APPMGR_ERROR_INVALID_SELF_PATH  = 0x8080201e,
	//!< argv is too long
	SCE_APPMGR_ERROR_TOO_LONG_ARGV      = 0x8080201d
} SceAppMgrErrorCode;

typedef enum SceAppMgrSystemEventType {
	SCE_APPMGR_SYSTEMEVENT_ON_RESUME             = 0x10000003,
	SCE_APPMGR_SYSTEMEVENT_ON_STORE_PURCHASE     = 0x10000004,
	SCE_APPMGR_SYSTEMEVENT_ON_NP_MESSAGE_ARRIVED = 0x10000005,
	SCE_APPMGR_SYSTEMEVENT_ON_STORE_REDEMPTION   = 0x10000006
} SceAppMgrSystemEventType;

typedef enum SceAppMgrInfoBarVisibility {
	SCE_APPMGR_INFOBAR_VISIBILITY_INVISIBLE = 0,
	SCE_APPMGR_INFOBAR_VISIBILITY_VISIBLE   = 1
} SceAppMgrInfoBarVisibility;

typedef enum SceAppMgrInfoBarColor {
	SCE_APPMGR_INFOBAR_COLOR_BLACK  = 0,
	SCE_APPMGR_INFOBAR_COLOR_WHITE  = 1
} SceAppMgrInfoBarColor;

typedef enum SceAppMgrInfoBarTransparency {
	SCE_APPMGR_INFOBAR_TRANSPARENCY_OPAQUE      = 0,
	SCE_APPMGR_INFOBAR_TRANSPARENCY_TRANSLUCENT = 1
} SceAppMgrInfoBarTransparency;

typedef struct SceAppMgrSystemEvent {
	int systemEvent; //!< One of ::SceAppMgrSystemEventType
	uint8_t reserved[60];
} SceAppMgrSystemEvent;

typedef struct SceAppMgrAppState SceAppMgrAppState; // Missing struct
typedef struct SceAppMgrExecOptParam SceAppMgrExecOptParam; // Missing struct
typedef struct SceAppMgrLaunchAppOptParam SceAppMgrLaunchAppOptParam; // Missing struct

typedef struct sceAppMgrLoadExecOptParam {
	int reserved[64];
} sceAppMgrLoadExecOptParam;

#define SCE_APPMGR_MAX_APP_NAME_LENGTH	(31)

//! Destroy all other apps
int sceAppMgrDestroyOtherApp(void);

//! name: The Title ID of the application
int sceAppMgrDestroyAppByName(char *name);

//! appId: The application id of the application
int sceAppMgrDestroyAppByAppId(SceUID appId);

//! Get process id by app id for shell
SceUID sceAppMgrGetProcessIdByAppIdForShell(SceUID appId);

//! Get list of running app ids (usually returns 1 app id)
int sceAppMgrGetRunningAppIdListForShell(SceUID *appIds, int count);

int _sceAppMgrGetAppState(SceAppMgrAppState *appState, uint32_t len, uint32_t version);

/**
 * static __inline int sceAppMgrGetAppState(SceAppMgrAppState *appState) {
 *	 return _sceAppMgrGetAppState(appState, sizeof(SceAppMgrAppState), version);
 * };
 */

int sceAppMgrReceiveSystemEvent(SceAppMgrSystemEvent *systemEvent);

//! Copies app param to an array
//! App param example: type=LAUNCH_APP_BY_URI&uri=psgm:play?titleid=NPXS10031
//! param: pointer to a 1024 byte location to store the app param
//! Returns 0 for success
int sceAppMgrGetAppParam(char *param);

//! Obtains the BGM port, even when it is not in front
int sceAppMgrAcquireBgmPort(void);

//! Release acquired BGM port
int sceAppMgrReleaseBgmPort(void);

//! Set infobar state
int sceAppMgrSetInfobarState(SceAppMgrInfoBarVisibility visibility, SceAppMgrInfoBarColor color, SceAppMgrInfoBarTransparency transparency);

int sceAppMgrLoadExec(const char *appPath, char * const argv[],
	const SceAppMgrExecOptParam *optParam);

//! flags: 0x20000 to launch, otherwise it just goes to the livearea page
int sceAppMgrLaunchAppByUri(int flags, char *uri);

//! name: The Title ID of the application
//! param: The parameter passed to the application which can be retrieved with sceAppMgrGetAppParam
int sceAppMgrLaunchAppByName2(const char *name, const char *param, SceAppMgrLaunchAppOptParam *optParam);

//! name: The Title ID of the application
//! param: The parameter passed to the application which can be retrieved with sceAppMgrGetAppParam
//! return AppId ?
SceUID sceAppMgrLaunchAppByName2ForShell(const char *name, const char *param, SceAppMgrLaunchAppOptParam *optParam);

//! id: 100 (photo0), 101 (friends), 102 (messages), 103 (near), 105 (music), 108 (calendar)
int sceAppMgrAppDataMount(int id, char *mount_point);

//! id: 106 (ad), 107 (ad)
int sceAppMgrAppDataMountById(int id, char *titleid, char *mount_point);

//! param: 8 (category), 9 (stitle/title?), 10 (title/stitle?), 12 (titleid)
int sceAppMgrAppParamGetString(int pid, int param, char *string, int length);

int sceAppMgrConvertVs0UserDrivePath(char *path, char *mount_point, int unk);

//! dev: ux0:
int sceAppMgrGetDevInfo(char *dev, uint64_t *max_size, uint64_t *free_size);

int sceAppMgrGetRawPath(char *path, char *mount_point, char *unk);

//! id: 400 (ad), 401 (ad), 402 (ad)
int sceAppMgrMmsMount(int id, char *mount_point);

//! ms
int sceAppMgrPspSaveDataRootMount(char *mount_point);

//! id: 200 (td), 201 (td), 203 (td), 204 (td), 206 (td)
int sceAppMgrWorkDirMount(int id, char *mount_point);

//! id: 205 (cache0), 207 (td)
int sceAppMgrWorkDirMountById(int id, char *titleid, char *mount_point);

//! Unmount a mountpoint
//! Unmount app0: for example to enable write access to ux0:app/TITLEID
//! Returns 0 on success
int sceAppMgrUmount(const char *mount_point);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_APPMGR_H_ */

