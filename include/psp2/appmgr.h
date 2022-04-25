/**
 * \usergroup{SceAppMgr}
 * \usage{psp2/appmgr.h,SceAppMgr_stub}
 */


#ifndef _PSP2_APPMGR_H_
#define _PSP2_APPMGR_H_

#include <psp2/types.h>
#include <psp2/apputil.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAppMgrErrorCode {
	SCE_APPMGR_ERROR_BUSY               = 0x80802000, //!< Busy
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

typedef struct SceAppMgrSaveDataData {
	int size;                                //!< Must be 0x4C
	unsigned int slotId;                     //!< Save slot to use
	SceAppUtilSaveDataSlotParam* slotParam;  //!< Save slot params
	uint8_t reserved[32];                    //!< Reserved data
	SceAppUtilSaveDataFile* files;           //!< Pointer to an array of files
	int fileNum;                             //!< Number of files to save
	SceAppUtilSaveDataMountPoint mountPoint; //!< Savedata mountpoint
	unsigned int* requiredSizeKB;            //!< Required size in KBs
} SceAppMgrSaveDataData;

typedef struct SceAppMgrSaveDataDataDelete {
	int size;                                //!< Must be 0x44
	unsigned int slotId;                     //!< Save slot to use
	SceAppUtilSaveDataSlotParam* slotParam;  //!< Save slot params
	uint8_t reserved[32];                    //!< Reserved data
	SceAppUtilSaveDataFile* files;           //!< Pointer to an array of files
	int fileNum;                             //!< Number of files to delete
	SceAppUtilSaveDataMountPoint mountPoint; //!< Savedata mountpoint
} SceAppMgrSaveDataDataDelete;

typedef struct SceAppMgrSaveDataSlot {
	int size;                                //!< Must be 0x418
	unsigned int slotId;                     //!< Save slot to use
	SceAppUtilSaveDataSlotParam slotParam;   //!< Save slot params
	uint8_t reserved[116];                   //!< Reserved data
	SceAppUtilSaveDataMountPoint mountPoint; //!< Savedata mountpoint
} SceAppMgrSaveDataSlot;

typedef struct SceAppMgrSaveDataSlotDelete {
	int size;                                 //!< Must be 0x18
	unsigned int slotId;                      //!< Save slot to use
	SceAppUtilSaveDataMountPoint mountPoint;  //!< Savedata mountpoint
} SceAppMgrSaveDataSlotDelete;

typedef struct SceAppMgrAppState {
	SceUInt32 systemEventNum;
	SceUInt32 appEventNum;
	SceBool isSystemUiOverlaid;
	SceUInt8 reserved[116];
} SceAppMgrAppState;

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

typedef struct SceAppMgrExecOptParam SceAppMgrExecOptParam; // Missing struct
typedef struct SceAppMgrLaunchAppOptParam SceAppMgrLaunchAppOptParam; // Missing struct

typedef struct sceAppMgrLoadExecOptParam {
	int reserved[64];    //!< Reserved data
} sceAppMgrLoadExecOptParam;

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
 * @param[in] path - ux0:app/TITLEID
 * @param[in] unk1 - Unknown, set 0
 * @param[in] unk2 - Unknown, set 0
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAppMgrGameDataMount(const char *path, int unk1, int unk2, const char *mount_point);

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

/**
 * Get current coredump state for shell
 *
 * @param[out] state - state info output.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetCoredumpStateForShell(SceAppMgrCoredumpState *state);

// missing structs
typedef struct SceAppMgrDrmOpenParam SceAppMgrDrmOpenParam;
typedef struct SceAppMgrAppInfo SceAppMgrAppInfo;

SceInt32 sceAppMgrDrmOpen(const SceAppMgrDrmOpenParam *param);

/**
 * Get AppInfo via syscall directly
 *
 * @param[in]  unk              - unknown; maybe titleid
 * @param[out] state            - The app state output buffer pointer
 * @param[in]  syscall_validity - The syscall validity buffer
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceAppMgrGetAppInfo(const char *unk, SceAppMgrAppState *state);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_APPMGR_H_ */
