/**
 * \usergroup{SceAppMgr}
 * \usage{psp2/appmgr.h,SceAppMgr_stub}
 */


#ifndef _PSP2_APPMGR_H_
#define _PSP2_APPMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/appmgr.h>
#include <psp2common/pfsmgr.h>
#include <psp2/apputil.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAppMgrErrorCode {
	SCE_APPMGR_ERROR_INVALID_PARAM_SFO  = 0x80800015,
	SCE_APPMGR_ERROR_BUSY               = 0x80802000, //!< Busy
	SCE_APPMGR_ERROR_INTERNAL           = 0x80802001, //!< Internal error
	SCE_APPMGR_ERROR_PARAM              = 0x80802002, //!< Invalid parameter
	SCE_APPMGR_ERROR_STATE              = 0x80802013, //!< Invalid state
	SCE_APPMGR_ERROR_NULL_POINTER       = 0x80802016, //!< NULL pointer
	SCE_APPMGR_ERROR_INVALID            = 0x8080201A, //!< Invalid param
	SCE_APPMGR_ERROR_TOO_LONG_ARGV      = 0x8080201D, //!< argv is too long
	SCE_APPMGR_ERROR_INVALID_SELF_PATH  = 0x8080201E, //!< Invalid SELF path
	SCE_APPMGR_ERROR_NOEXEC             = 0x8080201F, //!< The process is not authorized to run this function
	SCE_APPMGR_ERROR_BGM_PORT_BUSY      = 0x80803000  //!< BGM port was occupied and could not be secured
} SceAppMgrErrorCode;

typedef enum SceAppMgrSystemEventType {
	SCE_APPMGR_SYSTEMEVENT_ON_RESUME             = 0x10000003,
	SCE_APPMGR_SYSTEMEVENT_ON_STORE_PURCHASE     = 0x10000004,
	SCE_APPMGR_SYSTEMEVENT_ON_NP_MESSAGE_ARRIVED = 0x10000005,
	SCE_APPMGR_SYSTEMEVENT_ON_STORE_REDEMPTION   = 0x10000006
} SceAppMgrSystemEventType;

typedef enum SceAppMgrEventType {
	SCE_APP_EVENT_ON_ACTIVATE   = 0x10000001,
	SCE_APP_EVENT_ON_DEACTIVATE = 0x10000002,
	SCE_APP_EVENT_REQUEST_QUIT  = 0x20000001
} SceAppMgrEventType;

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

typedef enum SceAppMgrApplicationMode {
	SCE_APPMGR_APPLICATION_MODE_A = 2, //!< Application without physically contiguous memory access
	SCE_APPMGR_APPLICATION_MODE_B = 3, //!< Application with physically contiguous memory access
	SCE_APPMGR_APPLICATION_MODE_C = 4  //!< Application with physically contiguous memory and extra memory access
} SceAppMgrApplicationMode;

typedef struct SceAppMgrSystemEvent {
	int     systemEvent;   //!< One of ::SceAppMgrSystemEventType
	uint8_t reserved[60];  //!< Reserved data
} SceAppMgrSystemEvent;
VITASDK_BUILD_ASSERT_EQ(0x40, SceAppMgrSystemEvent);

typedef struct SceAppMgrSaveDataData {
	int size;                                //!< Must be 0x4C
	unsigned int slotId;                     //!< Save slot to use
	SceAppUtilSaveDataSlotParam* slotParam;  //!< Save slot params
	uint8_t reserved[32];                    //!< Reserved data
	SceAppUtilSaveDataFile* files;           //!< Pointer to an array of files
	int fileNum;                             //!< Number of files to save
	SceAppUtilSaveDataMountPoint mountPoint; //!< Savedata mountpoint
	unsigned int* requiredSizeKB;            //!< Required size in KBs
	int unk_0x48;
} SceAppMgrSaveDataData;
VITASDK_BUILD_ASSERT_EQ(0x4C, SceAppMgrSaveDataData);

typedef struct SceAppMgrSaveDataDataDelete {
	int size;                                //!< Must be 0x44
	unsigned int slotId;                     //!< Save slot to use
	SceAppUtilSaveDataSlotParam* slotParam;  //!< Save slot params
	uint8_t reserved[32];                    //!< Reserved data
	SceAppUtilSaveDataFile* files;           //!< Pointer to an array of files
	int fileNum;                             //!< Number of files to delete
	SceAppUtilSaveDataMountPoint mountPoint; //!< Savedata mountpoint
} SceAppMgrSaveDataDataDelete;
VITASDK_BUILD_ASSERT_EQ(0x44, SceAppMgrSaveDataDataDelete);

typedef struct SceAppMgrSaveDataSlot {
	int size;                                //!< Must be 0x418
	unsigned int slotId;                     //!< Save slot to use
	SceAppUtilSaveDataSlotParam slotParam;   //!< Save slot params
	uint8_t reserved[116];                   //!< Reserved data
	SceAppUtilSaveDataMountPoint mountPoint; //!< Savedata mountpoint
	uint8_t reserved2[0x40];
} SceAppMgrSaveDataSlot;
VITASDK_BUILD_ASSERT_EQ(0x418, SceAppMgrSaveDataSlot);

typedef struct SceAppMgrSaveDataSlotDelete {
	int size;                                 //!< Must be 0x18
	unsigned int slotId;                      //!< Save slot to use
	SceAppUtilSaveDataMountPoint mountPoint;  //!< Savedata mountpoint
} SceAppMgrSaveDataSlotDelete;
VITASDK_BUILD_ASSERT_EQ(0x18, SceAppMgrSaveDataSlotDelete);

typedef struct SceAppMgrAppState {
	SceUInt32 systemEventNum;
	SceUInt32 appEventNum;
	SceBool isSystemUiOverlaid;
	SceUInt8 reserved[116];
} SceAppMgrAppState;
VITASDK_BUILD_ASSERT_EQ(0x80, SceAppMgrAppState);

typedef struct SceAppMgrBudgetInfo {
	int size;                           //!< Must be 0x88
	int app_mode;                       //!< One of ::SceAppMgrApplicationMode
	int unk0;                           //!< Unknown Data
	unsigned int total_user_rw_mem;     //!< Total amount of accessible USER_RW memory
	unsigned int free_user_rw;          //!< Free amount of accessible USER_RW memory
	SceBool extra_mem_allowed;          //!< Flag for extra memory accessibility
	int unk1;                           //!< Unknown Data
	unsigned int total_extra_mem;       //!< Total amount of accessible extra memory
	unsigned int free_extra_mem;        //!< Free amount of accessible extra memory
	int unk2[2];                        //!< Unknown Data
	unsigned int total_phycont_mem;     //!< Total amount of accessible physically contiguous memory
	unsigned int free_phycont_mem;      //!< Free amount of accessible physically contiguous memory
	int unk3[10];                       //!< Unknown Data
	unsigned int total_cdram_mem;       //!< Total amount of accessible CDRAM memory
	unsigned int free_cdram_mem;        //!< Free amount of accessible CDRAM memory
	int reserved[9];                    //!< Reserved data
} SceAppMgrBudgetInfo;
VITASDK_BUILD_ASSERT_EQ(0x88, SceAppMgrBudgetInfo);

typedef struct SceAppMgrExecOptParam SceAppMgrExecOptParam; // Missing struct
typedef struct SceAppMgrLaunchAppOptParam SceAppMgrLaunchAppOptParam; // Missing struct

typedef struct SceAppMgrLoadExecOptParam {
	int reserved[64];    //!< Reserved data
} SceAppMgrLoadExecOptParam;
VITASDK_BUILD_ASSERT_EQ(0x100, SceAppMgrLoadExecOptParam);

#define SCE_APPMGR_MAX_APP_NAME_LENGTH	(31)

/**
 * Save data on savedata0: partition
 *
 * @param[in] data - Data to save
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrSaveDataDataSave(SceAppMgrSaveDataData *data);

/**
 * Remove data on savedata0: partition
 *
 * @param[in] data - Data to remove
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrSaveDataDataRemove(SceAppMgrSaveDataDataDelete *data);

/**
 * Create a savedata slot
 *
 * @param[in] data - Slot data
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrSaveDataSlotCreate(SceAppMgrSaveDataSlot *data);

/**
 * Get current param of a savedata slot
 *
 * @param[out] data - Slot data
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrSaveDataSlotGetParam(SceAppMgrSaveDataSlot *data);

/**
 * Set current param of a savedata slot
 *
 * @param[in] data - Slot data
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrSaveDataSlotSetParam(SceAppMgrSaveDataSlot *data);

/**
 * Delete a savedata slot
 *
 * @param[in] data - Slot data
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrSaveDataSlotDelete(SceAppMgrSaveDataSlotDelete *data);

/**
 * Get Process ID by Title ID
 *
 * @param[out] pid - Process ID
 * @param[in] name - Title ID
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetIdByName(SceUID *pid, const char *name);

/**
 * Get Title ID by Process ID
 *
 * @param[in] pid - Process ID
 * @param[out] name - Title ID
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetNameById(SceUID pid, char *name);

/**
 * Destroy other apps
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrDestroyOtherApp(void);

/**
 * Destroy an application by Title ID
 *
 * @param[in] name - Title ID of the application
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrDestroyAppByName(const char *name);

/**
 * Destroy an application by Application ID
 *
 * @param[in] appId - Application ID of the application
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrDestroyAppByAppId(SceInt32 appId);

/**
 * Get PID of an application for Shell
 *
 * @param[in] appId - Application ID of the application
 *
 * @return The PID on success, < 0 on error.
 */
SceUID sceAppMgrGetProcessIdByAppIdForShell(SceInt32 appId);

/**
 * Get a list of running applications
 *
 * @param[out] appIds - Array of running application IDs
 * @param[in] count - Max number of running applications to search
 *
 * @return Number of running applications.
 */
int sceAppMgrGetRunningAppIdListForShell(SceInt32 *appIds, int count);

/**
 * Get an application state
 *
 * @param[out] appState - State of the application
 * @param[in] len - sizeof(SceAppMgrState)
 * @param[in] version - Version (?)

 * @return 0 on success, < 0 on error.
 */
int _sceAppMgrGetAppState(SceAppMgrAppState *appState, SceSize len, uint32_t version);

/**
 * Receive system event
 *
 * @param[out] systemEvent - Received system event

 * @return 0 on success, < 0 on error.
 */
int sceAppMgrReceiveSystemEvent(SceAppMgrSystemEvent *systemEvent);

/**
 * Copies app param to an array
 *
 * @param[out] param - pointer to a 1024 byte location to store the app param
 *
 * @return 0 on success, < 0 on error.
 *
 * @note App param example: type=LAUNCH_APP_BY_URI&uri=psgm:play?titleid=NPXS10031
 */
int sceAppMgrGetAppParam(char *param);

/**
 * Obtains the BGM port, even when it is not in front
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAppMgrAcquireBgmPort(void);

/**
 * Release acquired BGM port
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAppMgrReleaseBgmPort(void);

/**
 * Set infobar state
 *
 * @param[in] visibility - Infobar visibility
 * @param[in] color - Infobar color
 * @param[in] transparency - Infobar transparency
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAppMgrSetInfobarState(SceAppMgrInfoBarVisibility visibility, SceAppMgrInfoBarColor color, SceAppMgrInfoBarTransparency transparency);

/**
 * Load and start a SELF executable
 *
 * @param[in] appPath - Path of the SELF file
 * @param[in] argv - Args to pass to SELF module_start
 * @param[in] optParam - Optional params
 *
 * @return 0 on success, < 0 on error.
 *
 * @note SELF file must be located in app0: partition.
 */
int sceAppMgrLoadExec(const char *appPath, char * const argv[],
	const SceAppMgrExecOptParam *optParam);

/**
 * Start an application by URI
 *
 * @param[in] flags - Must be 0x20000
 * @param[in] uri - Uri to launch
 *
 * @return 0 on success, < 0 on error.
 *
 * @note If flags != 0x20000, Livearea is opened.
 */
int sceAppMgrLaunchAppByUri(int flags, const char *uri);

/**
 * Start an application by Title ID
 *
 * @param[in] name - Title ID of the application
 * @param[in] param - The params passed to the application which can be retrieved with ::sceAppMgrGetAppParam
 * @param[in] optParam - Optional params
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrLaunchAppByName2(const char *name, const char *param, SceAppMgrLaunchAppOptParam *optParam);

/**
* Start an Application by Title ID
*
* @param[in] flags - Usually 0x60000
* @param[in] name - Title ID of the application
* @param[in] param - The params passed to the application which can be retrieved with ::sceAppMgrGetAppParam
*
* @return 0 on success < 0 on error.
*/
int sceAppMgrLaunchAppByName(int flags, const char* name, const char* param);
	
/**
 * Start an application by Title ID for Shell
 *
 * @param[in] name - Title ID of the application
 * @param[in] param - The params passed to the application which can be retrieved with ::sceAppMgrGetAppParam
 * @param[in] optParam - Optional params
 *
 * @return Application ID (?)
 */
SceUID sceAppMgrLaunchAppByName2ForShell(const char *name, const char *param, SceAppMgrLaunchAppOptParam *optParam);

/**
 * Mount game data
 *
 * @param[in] app_path    - example : "ux0:/app/${TITLEID}"
 * @param[in] patch_path  - example : "ux0:/patch/${TITLEID}", "invalid:"
 * @param[in] rif_path    - If NULL the system will automatically search the rif path. example : "ux0:/license/app/${TITLEID}/${HEX}.rif"
 * @param[in] mount_point - Mountpoint output
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAppMgrGameDataMount(const char *app_path, const char *patch_path, const char *rif_path, char *mount_point);

/**
 * Mount application data
 *
 * @param[in] id - App data ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 100 (photo0), 101 (friends), 102 (messages), 103 (near), 105 (music), 108 (calendar)
 */
int sceAppMgrAppDataMount(int id, const char *mount_point);

/**
 * Mount application data by Title ID
 *
 * @param[in] id - App data ID
 * @param[in] titleid - Application title ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 106 (ad), 107 (ad)
 */
int sceAppMgrAppDataMountById(int id, const char *titleid, const char *mount_point);

/**
 * Get application params from SFO descriptor
 *
 * @param[in] pid - Process ID
 * @param[in] param - Param ID in the SFO descriptor
 * @param[out] string - Param data
 * @param[in] length - Length of the param data
 *
 * @return 0 on success, < 0 on error.
 *
 * @note param: 6 (contentid) 8 (category), 9 (stitle/title?), 10 (title/stitle?), 12 (titleid)
 */
int sceAppMgrAppParamGetString(int pid, int param, char *string, SceSize length);

/**
 * Get device info
 *
 * @param[in] dev - Device to get info about
 * @param[out] max_size - Capacity of the device
 * @param[out] free_size - Free space of the device
 *
 * @return 0 on success, < 0 on error.
 *
 * @note dev: ux0:
 */
int sceAppMgrGetDevInfo(const char *dev, uint64_t *max_size, uint64_t *free_size);

/**
 * Mount application data (PSPEmu)
 *
 * @param[in] id - App data ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 400 (ad), 401 (ad), 402 (ad)
 */
int sceAppMgrMmsMount(int id, const char *mount_point);

/**
 * Mount PSPEmu virtual memory stick
 *
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note mount_point: ms
 */
int sceAppMgrPspSaveDataRootMount(const char *mount_point);

/**
 * Mount working directory
 *
 * @param[in] id - Working directory ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 200 (td), 201 (td), 203 (td), 204 (td), 206 (td)
 */
int sceAppMgrWorkDirMount(int id, const char *mount_point);

/**
 * Mount working directory by Title ID
 *
 * @param[in] id - Working directory ID
 * @param[in] titleid - Application Title ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 205 (cache0), 207 (td)
 */
int sceAppMgrWorkDirMountById(int id, const char *titleid, const char *mount_point);

/**
 * Unmount a mountpoint
 *
 * @param[in] mount_point - Mountpoint to unmount
 *
 * @return 0 on success, < 0 on error.
 *
 * @note Unmount app0: for example to enable write access to ux0:app/TITLEID
 */
int sceAppMgrUmount(const char *mount_point);

/**
 * Convert vs0 path string to a new one usable by applications
 *
 * @param[in] path - Path to convert
 * @param[in] mount_point - Mountpoint to use
 * @param[in] unk - Unknown
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrConvertVs0UserDrivePath(char *path, char *mount_point, int unk);

/**
 * Get raw path for a given path
 *
 * @param[out] path               - Path to convert
 * @param[in]  resolved_path      - The input process path
 * @param[in]  resolved_path_size - The input process path length
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetRawPath(char *path, char *resolved_path, int resolved_path_size);

/**
 * Get the real/resolved path of app0: (where it's actually mounted)
 *
 * @param[in] appId - Use -2 for the current application
 * @param[out] resolved_path - Buffer that will hold the resolved path. It should have enough room to hold 292 characters or it will buffer overflow (noname120).
 *
 * @return 0 on success.
 */
int sceAppMgrGetRawPathOfApp0ByAppIdForShell(int appId, char resolved_path[292]);

/**
 * Get memory budget info for a running system application
 *
 * @param[out] info - Info related to the memory budget of the running application.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note This function will always return an error if used in a normal application.
 */
int sceAppMgrGetBudgetInfo(SceAppMgrBudgetInfo *info);

typedef struct SceAppMgrCoredumpState {
	SceUID pid;
	int process_state;
	int progress; // 0-100
	int is_coredump_completed;
	int data_0x10;
	SceSize path_len;
	char path[0x400];
	int data_0x418;
	int data_0x41C;
	int data_0x420;
	int data_0x424;
} SceAppMgrCoredumpState;
VITASDK_BUILD_ASSERT_EQ(0x428, SceAppMgrCoredumpState);

/**
 * Get current coredump state for shell
 *
 * @param[out] state - state info output.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetCoredumpStateForShell(SceAppMgrCoredumpState *state);

typedef struct SceAppMgrDrmOpenParam SceAppMgrDrmOpenParam;
typedef struct SceAppMgrAppInfo {
	SceBool isRunning; //!< Non-zero while the selected process is in AppMgr's started lifecycle state.
	SceUInt8 reserved[0x7C]; //!< Set to 0 on FW 3.60.
} SceAppMgrAppInfo;
VITASDK_BUILD_ASSERT_EQ(0x80, SceAppMgrAppInfo); // size is from FW 3.60

SceInt32 sceAppMgrDrmOpen(const SceAppMgrDrmOpenParam *param);

/**
 * Get AppInfo via syscall directly
 *
 * @param[in]  appName - Application name of at most 31 characters; NULL
 *                       selects the calling process.
 * @param[out] appInfo - A buffer whose FW 3.60 layout is ::SceAppMgrAppInfo.
 *                       Still declared as ::SceAppMgrAppState * for backwards
 *                       compatibility.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceAppMgrGetAppInfo(const char *appName, SceAppMgrAppState *appInfo);

typedef struct SceAppMgrAppMgrState {
	SceUInt32 prioritizeSystemChat;
	SceUInt32 systemImposeState;
	SceInt32 reserved08; //!< Initialized to -1 on FW 3.60.
	SceUInt32 audioRoutingState;
	SceUInt32 recommendedScreenOrientation; //!< A value from 1 through 4.
	SceUInt32 systemImposeState2;
	SceUInt8 reserved[0x68]; //!< Reserved in the FW 3.60 state block.
} SceAppMgrAppMgrState;
VITASDK_BUILD_ASSERT_EQ(0x80, SceAppMgrAppMgrState); // size is from FW 3.60

typedef struct SceAppMgrAppParam {
	char data[0x400];
} SceAppMgrAppParam;
VITASDK_BUILD_ASSERT_EQ(0x400, SceAppMgrAppParam); // size is from FW 0.990

typedef enum SceAppMgrApplicationType {
	SCE_APPMGR_APPLICATION_TYPE_MINI_APPLICATION   = 0,
	SCE_APPMGR_APPLICATION_TYPE_GAME               = 1,
	SCE_APPMGR_APPLICATION_TYPE_SYSTEM_APPLICATION = 2
} SceAppMgrApplicationType;

/**
 * Launch-request flags observed on FW 3.60.
 */
typedef enum SceAppMgrLaunchFlag {
	SCE_APPMGR_LAUNCH_FLAG_LIVEAREA_OFF       = 0x00010000, //!< Launch without activating LiveArea.
	SCE_APPMGR_LAUNCH_FLAG_DEBUG_CALLBACK     = 0x00020000, //!< Set up AppMgr's debug semaphore and callback.
	SCE_APPMGR_LAUNCH_FLAG_EXIT_TO            = 0x00040000, //!< Enable exit-to behavior.
	SCE_APPMGR_LAUNCH_FLAG_ALLOW_EMPTY_TARGET = 0x00100000  //!< Permit an empty launch target.
} SceAppMgrLaunchFlag;

/**
 * Application status returned by the raw status exports.
 *
 * FW 3.60 always writes the complete 0x80-byte structure; the output is not
 * size-prefixed.
 */
typedef struct SceAppMgrAppStatus {
	SceUInt32 parentProcessId; //!< Value of type ::ScePID.
	SceUInt32 launchFlags; //!< Bitwise OR of ::SceAppMgrLaunchFlag values.
	SceUInt32 appProtectionModeOnMemoryShortage;
	char appName[32];
	SceUInt32 hasLaunchParam; //!< Non-zero when launch parameters are available.
	SceUID appId;
	SceUID processId;
	SceUInt32 isActive; //!< Non-zero when the process-context state has low nibble 2.
	SceUInt32 isRunning; //!< Non-zero after AppMgr starts the process and before it enters shutdown.
	SceBool networkDisconnectionWarningDialogEnabled;
	SceUID parentAppId;
	SceUInt8 infoBarVisibility; //!< One of ::SceAppMgrInfoBarVisibility.
	SceUInt8 infoBarColor; //!< One of ::SceAppMgrInfoBarColor.
	SceUInt8 infoBarTransparency; //!< One of ::SceAppMgrInfoBarTransparency.
	SceUInt8 reserved4B; //!< High byte of the packed info-bar state.
	SceUInt32 reserved4C; //!< Copied from the process context; its purpose is unknown.
	char bgmProxyAppName[32];
	SceUInt8 processLaunchType; //!< FW 3.60 writes 0, 1, or 2; value 2 identifies a direct path launch.
	                            //!< The purposes of 0 and 1 are unknown.
	SceUInt8 applicationType; //!< One of ::SceAppMgrApplicationType.
	SceUInt8 reserved72[2]; //!< Set to 0 on FW 3.60.
	SceUInt32 appFlags;
	SceUInt32 recommendedScreenOrientation; //!< A value from 1 through 4.
	SceBool recommendedScreenOrientationActivated;
} SceAppMgrAppStatus;
VITASDK_BUILD_ASSERT_EQ(0x80, SceAppMgrAppStatus); // size is from FW 3.60

/**
 * Size-prefixed application boot parameters.
 *
 * FW 3.60 accepts and returns any prefix up to 0x2C bytes. The former
 * 0xC-byte layout therefore remains supported when \c size is 0xC.
 */
typedef struct SceAppMgrBootParam {
	SceUInt size; //!< Number of bytes requested from the raw export; maximum value is 0x2C.
	SceUInt reserved04[2]; //!< Set to 0 on FW 3.60.
	SceUInt reserved0C[8]; //!< Preserved from the caller on FW 3.60.
} SceAppMgrBootParam;
VITASDK_BUILD_ASSERT_EQ(0x2C, SceAppMgrBootParam); // size is from FW 3.60

#define SCE_APP_MGR_MAX_EVENT_PARM_LENGTH (56)

typedef struct SceAppMgrEvent {
	int event; //!< One of ::SceAppMgrEventType.
	SceUID appId; //!< Application ID. Added when required by the event
	char param[SCE_APP_MGR_MAX_EVENT_PARM_LENGTH]; //!< Parameters to pass with the event
} SceAppMgrEvent;
VITASDK_BUILD_ASSERT_EQ(0x40, SceAppMgrEvent);

typedef struct SceAppMgrLaunchAppByUri2Param {
	SceSize size; //!< Ignored on FW 3.60.
	SceUInt32 flags; //!< Bitwise OR of ::SceAppMgrLaunchFlag values; FW 3.60 forces
	                 //!< ::SCE_APPMGR_LAUNCH_FLAG_ALLOW_EMPTY_TARGET.
	SceUInt32 reserved08; //!< Ignored on FW 3.60.
	SceUInt32 appLaunchCallbackId; //!< Value of type ::SceUID for the application-launch callback, or -1.
	SceUInt32 getParamCallbackId; //!< Value of type ::SceUID for the get-parameter callback, or -1.
	SceUInt32 parentAppId; //!< Value of type ::SceInt32 containing the parent application ID, or -1;
	                       //!< used when \a flags includes ::SCE_APPMGR_LAUNCH_FLAG_EXIT_TO.
	SceUInt32 launchMode; //!< Application mode from 0 through 4; values 2 through 4 are ::SceAppMgrApplicationMode values.
	SceUInt32 reserved1C; //!< Stored in the target process context on FW 3.60.
	SceUInt8 reserved[0x20]; //!< Must be zero on FW 3.60.
} SceAppMgrLaunchAppByUri2Param;
VITASDK_BUILD_ASSERT_EQ(0x40, SceAppMgrLaunchAppByUri2Param); // size is from FW 3.60

typedef struct SceAppMgrNetworkDisconnectionWarningDialogStateOptParam {
	SceUInt8 reserved[0x80]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrNetworkDisconnectionWarningDialogStateOptParam;
VITASDK_BUILD_ASSERT_EQ(0x80, SceAppMgrNetworkDisconnectionWarningDialogStateOptParam); // size is from FW 3.60

typedef struct SceAppMgrCheckRifGDOpt {
	uint32_t reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrCheckRifGDOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrCheckRifGDOpt); // size is from FW 3.60

typedef struct SceAppMgrGameDataMountOpt {
	char *mount_point; //!< Receives a 16-byte mount point of the form "gpXXXXXXXXXXXd:".
	uint32_t reserved[5]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGameDataMountOpt;
VITASDK_BUILD_ASSERT_EQ(0x18, SceAppMgrGameDataMountOpt); // size is from FW 3.60

typedef struct SceAppMgrGetAppInfoOpt {
	SceUInt32 reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetAppInfoOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetAppInfoOpt); // size is from FW 3.60

typedef struct SceAppMgrGetAppParamOpt {
	SceSize appParamSize; //!< Copied from user memory but actually unused on FW 3.60.
	SceUInt32 reserved0; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetAppParamOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetAppParamOpt); // size is from FW 0.990

typedef struct SceAppMgrGetBootParamOpt {
	SceSize bootParamSize;
	SceUInt reserved; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetBootParamOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetBootParamOpt); // size is from FW 0.990

typedef struct SceAppMgrGetIdByNameOpt {
	SceSize appNameSize; //!< Copied from user memory but actually unused on FW 3.60.
	SceUInt32 reserved0; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetIdByNameOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetIdByNameOpt); // size is from FW 0.990

typedef struct SceAppMgrGetNameByIdOpt {
	SceSize appNameSize; //!< Copied from user memory but actually unused on FW 3.60.
	SceUInt32 reserved0; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetNameByIdOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetNameByIdOpt); // size is from FW 0.990

typedef struct SceAppMgrGetSaveDataInfoForSpecialExportOpt {
	int reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetSaveDataInfoForSpecialExportOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetSaveDataInfoForSpecialExportOpt); // size is from FW 3.60

typedef enum SceAppMgrSaveDataStorageType {
	SCE_APPMGR_SAVE_DATA_STORAGE_OTHER       = 1,
	SCE_APPMGR_SAVE_DATA_STORAGE_SYSTEM      = 2,
	SCE_APPMGR_SAVE_DATA_STORAGE_GAME_CARD   = 3,
	SCE_APPMGR_SAVE_DATA_STORAGE_USER        = 4
} SceAppMgrSaveDataStorageType;

typedef struct SceAppMgrGetSaveDataInfoResult {
	int storageType; //!< One of ::SceAppMgrSaveDataStorageType.
	int isMounted; //!< Non-zero when the save data is mounted.
	int hasBrokenData; //!< Set for specific PFS validation failures or when sdslot.dat is absent.
	int accountId[2]; //!< Low and high words of the param.sfo ACCOUNT_ID value.
	int saveDataParam44; //!< Value at offset 0x44 of the param.sfo PARAMS entry.
	int allocatedSizeKB;
} SceAppMgrGetSaveDataInfoResult;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceAppMgrGetSaveDataInfoResult); // size is from FW 3.60

typedef struct SceAppMgrGetSaveDataInfoOpt {
	SceAppMgrGetSaveDataInfoResult *res; //!< Receives a 0x1C-byte result.
	int reserved[3]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetSaveDataInfoOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceAppMgrGetSaveDataInfoOpt); // size is from FW 3.60

//! FW 0.990-only, this option structure is not accepted on FW 3.60.
typedef struct SceAppMgrGetStatusByIdOpt {
	SceSize appStatusSize;
	SceUInt32 reserved1;
} SceAppMgrGetStatusByIdOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetStatusByIdOpt); // size is from FW 0.990

typedef struct SceAppMgrGetUserDirPathOpt {
	SceSize path_maxlen; //!< FW 0.990: must be <= 1024. Ignored on FW 3.60.
	SceUInt32 reserved1; //!< Ignored on FW 3.60.
} SceAppMgrGetUserDirPathOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrGetUserDirPathOpt); // size is from FW 0.990

typedef struct SceAppMgrGenericMountContext {
	SceTitleId titleId;
	char passCode[32];
	char mountDrive[16];
} SceAppMgrGenericMountContext;
VITASDK_BUILD_ASSERT_EQ(0x40, SceAppMgrGenericMountContext); // size is from FW 3.60

typedef struct sceAppMgrAppDataMountByIdOpt {
	int reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrAppDataMountByIdOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceAppMgrAppDataMountByIdOpt); // size is from FW 3.60

typedef struct sceAppMgrAppParamGetString_opt {
	SceSize size; //!< Copied from user memory but actually unused on FW 3.60.
	int32_t reserved[3]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrAppParamGetString_opt;
VITASDK_BUILD_ASSERT_EQ(0x10, sceAppMgrAppParamGetString_opt); // size is from FW 3.60

typedef struct SceAppMgrGetStatusByNameOpt {
	SceSize appNameSize; //!< FW 0.990 application-name size; copied but ignored on FW 3.60.
	SceSize appStatusSize; //!< FW 0.990 application-status size; copied but ignored on FW 3.60.
	SceUInt32 reserved[2]; //!< FW 0.990 reserved words; not copied on FW 3.60.
} SceAppMgrGetStatusByNameOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceAppMgrGetStatusByNameOpt); // size is from FW 0.990

typedef struct sceAppMgrLoadSaveDataSystemFileOpt {
	int reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrLoadSaveDataSystemFileOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceAppMgrLoadSaveDataSystemFileOpt); // size is from FW 3.60

typedef struct sceAppMgrLoopBackMountOpt {
	int reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrLoopBackMountOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceAppMgrLoopBackMountOpt); // size is from FW 3.60

typedef struct sceAppMgrPhotoMountOpt {
	int size; //!< Number of bytes to copy from ::sceAppMgrPhotoMountParam; maximum value is 0x84.
	int reserved0; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrPhotoMountOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceAppMgrPhotoMountOpt); // size is from FW 3.60

typedef struct sceAppMgrThemeDataMountOpt {
	char *mount_point; //!< Receives a 16-byte mount point of the form "tmXXXXXXXXXXXX:".
	int reserved[5]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrThemeDataMountOpt;
VITASDK_BUILD_ASSERT_EQ(0x18, sceAppMgrThemeDataMountOpt); // size is from FW 3.60

typedef struct sceAppMgrTrophyMountByIdOpt {
	int reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrTrophyMountByIdOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceAppMgrTrophyMountByIdOpt); // size is from FW 3.60

typedef struct sceAppMgrUpdateSaveDataParamOpt {
	int reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrUpdateSaveDataParamOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceAppMgrUpdateSaveDataParamOpt); // size is from FW 3.60

typedef struct sceAppMgrWorkDirMountByIdOpt {
	int reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrWorkDirMountByIdOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceAppMgrWorkDirMountByIdOpt); // size is from FW 3.60

typedef struct SceAppMgrConvertVs0UserDrivePathOpt {
	SceUInt32 reserved[4]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrConvertVs0UserDrivePathOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceAppMgrConvertVs0UserDrivePathOpt); // size is from FW 3.60

typedef struct SceAppMgrDeclareShellProcess2Opt {
	SceUInt32 reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrDeclareShellProcess2Opt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrDeclareShellProcess2Opt); // size is from FW 3.60

typedef struct SceAppMgrGetRawPathOpt {
	SceUInt32 reserved[4]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrGetRawPathOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceAppMgrGetRawPathOpt); // size is from FW 3.60

typedef struct SceAppMgrLaunchAppByUri2Opt {
	SceUInt32 reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrLaunchAppByUri2Opt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrLaunchAppByUri2Opt); // size is from FW 3.60

typedef SceAppMgrLaunchAppByUri2Param SceAppMgrLaunchVideoStreamingAppOpt;
VITASDK_BUILD_ASSERT_EQ(0x40, SceAppMgrLaunchVideoStreamingAppOpt); // size is from FW 3.60

typedef struct SceAppMgrLoadExecOpt {
	SceUInt32 reserved[2]; //!< Copied from user memory but actually unused on FW 3.60.
} SceAppMgrLoadExecOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceAppMgrLoadExecOpt); // size is from FW 3.60

int __sceAppMgrGetAppState(SceAppMgrAppState *appState, SceUInt32 sizeofSceAppMgrAppState, SceUInt32 buildVersion);
int _sceAppMgrAddContAddMount(SceAppMgrGenericMountContext *data, int force_mount_ux);
int _sceAppMgrAddContMount(SceUID pid, SceAppMgrGenericMountContext *mctx);
int _sceAppMgrAppDataMount(int mountId, char *mountPoint);

/**
 * @param[in] titleId A NUL-terminated identifier of at most 63 characters;
 *                    its required syntax depends on \a mountId.
 */
int _sceAppMgrAppDataMountById(int mountId, const char *titleId, char *mountPoint, sceAppMgrAppDataMountByIdOpt *opt);
int _sceAppMgrAppParamGetString(int pid, int param, char *string, sceAppMgrAppParamGetString_opt *opt);
int _sceAppMgrCheckRifGD(const char *path, void *dest, SceAppMgrCheckRifGDOpt *opt);
int _sceAppMgrContentInstallPeriodStart(void);
int _sceAppMgrContentInstallPeriodStop(void);

/**
 * @param[out] converted_path Output buffer for a path of at most 0x124 bytes,
 *                            including the terminating NUL.
 * @param[in] converted_path_size Output-buffer capacity. FW 3.60 requires a
 *                                value greater than 0x3F and caps it at 0x124.
 */
int _sceAppMgrConvertVs0UserDrivePath(const char *path, char *converted_path, SceSize converted_path_size, SceAppMgrConvertVs0UserDrivePathOpt *opt);

/**
 * @param[in] opt A pointer to a ::SceAppMgrDeclareShellProcess2Opt
 *                structure. Still declared as void * for backwards
 *                compatibility.
 */
int _sceAppMgrDeclareShellProcess2(const char *appName, void *opt);
int _sceAppMgrForceUmount(int id);
int _sceAppMgrGameDataMount(char *app_path, char *patch_path, char *rif_file_path, SceAppMgrGameDataMountOpt *opt);

/**
 * @param[in] appName Application name of at most 31 characters; NULL selects
 *                    the calling process.
 */
int _sceAppMgrGetAppInfo(const char *appName, SceAppMgrAppInfo *appInfo, SceAppMgrGetAppInfoOpt *opt);
int _sceAppMgrGetAppMgrState(SceAppMgrAppMgrState *appMgrState);
int _sceAppMgrGetAppParam(SceAppMgrAppParam *appParam, SceAppMgrGetAppParamOpt *opt);
int _sceAppMgrGetBootParam(SceUInt32 selector, SceAppMgrBootParam *bootParam, SceAppMgrGetBootParamOpt *opt);

/**
 * @param[out] processId A pointer to a value of type ::ScePID.
 * @param[out] bgmState A pointer to a value of type ::SceUInt32.
 */
int _sceAppMgrGetCurrentBgmState(void **processId, void **bgmState);
int _sceAppMgrGetIdByName(SceUID *processId, const char *appName, SceAppMgrGetIdByNameOpt *opt);
int _sceAppMgrGetNameById(SceUID processId, char *appName, SceAppMgrGetNameByIdOpt *opt);

/**
 * @param[out] resolved_path Output buffer for a path of at most 0x124 bytes,
 *                           including the terminating NUL.
 * @param[in] resolved_path_size Output-buffer capacity passed to the FIOS
 *                               overlay resolver, capped at 0x124 on FW 3.60.
 * @param[in] opt A ::SceAppMgrGetRawPathOpt structure. Still declared as
 *                char[16] for backwards compatibility.
 */
int _sceAppMgrGetRawPath(char *path, char *resolved_path, int resolved_path_size, char opt[16]);
int _sceAppMgrGetRawPathOfApp0ByAppIdForShell(int appId, char resolved_path[292]);
int _sceAppMgrGetSaveDataInfo(char *path, SceTitleId *titleid, int force_mount_ux, SceAppMgrGetSaveDataInfoOpt *opt);

/**
 * @param[out] accountId A pointer to a ::SceUInt64 ACCOUNT_ID value. Still
 *                       declared as char * for backwards compatibility.
 */
int _sceAppMgrGetSaveDataInfoForSpecialExport(char *path, char *accountId, SceAppMgrGetSaveDataInfoForSpecialExportOpt *opt);
int _sceAppMgrGetStatusByAppId(int appId, SceAppMgrAppStatus *appStatus);
int _sceAppMgrGetStatusById(SceUID processId, SceAppMgrAppStatus *appStatus);
int _sceAppMgrGetStatusByName(const char *appName, SceAppMgrAppStatus *appStatus, SceAppMgrGetStatusByNameOpt *opt);

/**
 * @param[out] pSDPR A pointer to a value of type ::SceUInt64.
 */
int _sceAppMgrGetSystemDataFilePlayReady(SceUInt32 location, void *pSDPR);
int _sceAppMgrGetUserDirPath(int partition_id, char *userDirPath, SceSize path_maxlen, SceAppMgrGetUserDirPathOpt *opt);
int _sceAppMgrGetVs0UserDataDrive(ScePfsRndDriveId *rnd_drive_id);
int _sceAppMgrGetVs0UserModuleDrive(ScePfsRndDriveId *rnd_drive_id);
int _sceAppMgrLaunchAppByUri2(const char *uri, SceAppMgrLaunchAppByUri2Param *pParam, SceAppMgrLaunchAppByUri2Opt *opt);

/**
 * @param[in] opt A pointer to a ::SceAppMgrLaunchVideoStreamingAppOpt
 *                structure. Still declared as void * for backwards
 *                compatibility.
 */
int _sceAppMgrLaunchVideoStreamingApp(char *buf, size_t buf_size, void *opt);
int _sceAppMgrLoadExec(const char *appPath, char *const argv[], const SceAppMgrLoadExecOptParam *optParam, SceAppMgrLoadExecOpt *opt);

/**
 * @param[out] paramSfoBuffer Address of the output buffer, retained as int for
 *                            backwards compatibility.
 * @param[in] bufferSize Maximum number of bytes to write.
 */
int _sceAppMgrLoadSaveDataSystemFile(char *path, int paramSfoBuffer, int bufferSize, sceAppMgrLoadSaveDataSystemFileOpt *opt);
int _sceAppMgrLoopBackMount(int mountId, char *part_name, char *mountPoint, sceAppMgrLoopBackMountOpt *opt);
int _sceAppMgrMmsMount(int mountId, char *mountPoint);
int _sceAppMgrPhotoMount(sceAppMgrPhotoMountParam *param, sceAppMgrPhotoMountOpt *opt);
int _sceAppMgrPspSaveDataRootMount(char *mountPoint);
int _sceAppMgrReceiveEvent(SceAppMgrEvent *appEvent);
int _sceAppMgrReceiveEventNum(int *eventNum);
int _sceAppMgrReceiveSystemEvent(SceAppMgrSystemEvent *systemEvent);
int _sceAppMgrSaveDataAddMount(SceAppMgrGenericMountContext *opt);
int _sceAppMgrSetNetworkDisconnectionWarningDialogState(SceBool enable, const SceAppMgrNetworkDisconnectionWarningDialogStateOptParam *optParam);

/**
 * @param[in] pSDPR A pointer to a value of type ::SceUInt64.
 * @param[in] data Data to store when location is 1.
 * @param[in] dataSize Size of data; the maximum value is 0x4000.
 */
int _sceAppMgrSetSystemDataFilePlayReady(SceUInt32 location, void *pSDPR, const void *data, SceSize dataSize);

/**
 * @param[in] contentId A NUL-terminated content ID of at most 26 characters.
 *                      Still declared as ::SceTitleId * for backwards
 *                      compatibility.
 */
int _sceAppMgrThemeDataMount(SceTitleId *contentId, const char *theme_path, const char *rif_file_path, sceAppMgrThemeDataMountOpt *opt);
int _sceAppMgrTrophyMount(int mountId, SceUID pid, char *mountPoint);

/**
 * @param[in] titleId A NUL-terminated identifier of at most 63 characters;
 *                    its required syntax depends on \a mountId. Still declared
 *                    as ::SceTitleId * for backwards compatibility.
 */
int _sceAppMgrTrophyMountById(int mountId, SceTitleId *titleId, char *mountPoint, sceAppMgrTrophyMountByIdOpt *opt);
int _sceAppMgrUmount(const char *mount_point);
int _sceAppMgrUpdateSaveDataParam(char *path, sceAppMgrUpdateSaveDataParamOpt *opt);
int _sceAppMgrWorkDirMount(int mountId, char *mountPoint);

/**
 * @param[in] titleId A NUL-terminated identifier of at most 63 characters;
 *                    its required syntax depends on \a mountId. Still declared
 *                    as ::SceAppMgrGenericMountContext * for backwards
 *                    compatibility.
 */
int _sceAppMgrWorkDirMountById(int mountId, SceAppMgrGenericMountContext *titleId, char *mount_point, sceAppMgrWorkDirMountByIdOpt *opt);
int sceAppMgrActivateApp(int appId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_APPMGR_H_ */
