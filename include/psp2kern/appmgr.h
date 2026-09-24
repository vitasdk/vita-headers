/**
 * \kernelgroup{SceAppMgr}
 * \usage{psp2kern/appmgr.h,SceAppMgrForDriver_stub}
 */


#ifndef _PSP2KERN_APPMGR_H_
#define _PSP2KERN_APPMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/appmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       Kill a process.
 * @param[in]   pid The process to kill.
 * @return      Zero on success, else < 0.
 */
int ksceAppMgrKillProcess(SceUID pid);

/**
 * Attribute bits accepted in ::SceAppMgrLaunchParam::attr.
 *
 * FW 3.60 rejects bits outside 0xF02FF000. Bits 0x00002000 and
 * 0x00008000 are accepted but ignored. Bits 0x00040000 and 0x00080000 tell
 * Processmgr to read fields absent from this structure; AppMgr supplies or
 * clears those fields according to the launch class. Bit 0x00100000 is rejected when
 * supplied by the caller, although AppMgr may set it in the Processmgr options
 * it builds internally. Bit 0x00200000 tells Processmgr to read a nonzero
 * unique-heap size from its 0x40-byte process options. This 0x34-byte structure
 * has no corresponding member, so AppMgr leaves
 * ::SceKernelProcessOpt2::unique_heap_size at zero and process creation fails on
 * FW 3.60.
 *
 * Bit 0x80000000 prevents Processmgr from calling the process-start callbacks
 * registered through ::ksceKernelSysrootSetProcessHandler and
 * ::ksceKernelSysrootRegisterDbgpHandler. Process creation, image loading, and
 * main-thread startup continue normally.
 */
typedef enum SceAppMgrLaunchParamAttr {
	SCE_APPMGR_LAUNCH_PARAM_ATTR_CPU_AFFINITY_MASK           = 0x00001000, //!< Use the CPU affinity mask.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_BUDGET_ID                   = 0x00004000, //!< Use ::SceAppMgrLaunchParam::budget_id.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_PARENT_PROCESS_ID           = 0x00010000, //!< Use AppMgr's parent process ID.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_PROCESS_EXIT_SPAWN          = 0x00020000, //!< Use the process-replacement mode and exiting-process PID.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_KLICENSEE                   = 0x00040000, //!< Use the klicensee supplied internally by AppMgr.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_MAX_FILE_HANDLES            = 0x00080000, //!< Use the file-handle limit supplied internally by AppMgr.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_UNIQUE_HEAP_SIZE            = 0x00200000, //!< Select an unavailable value; process creation fails on FW 3.60.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_INIT_PRIORITY               = 0x10000000, //!< Use ::SceAppMgrLaunchParam::init_priority.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_STACK_SIZE                  = 0x20000000, //!< Use ::SceAppMgrLaunchParam::stack_size.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_REPORT_LOAD_PROGRESS        = 0x40000000, //!< Report executable-load progress.
	SCE_APPMGR_LAUNCH_PARAM_ATTR_SKIP_START_CALLBACKS        = 0x80000000  //!< Skip the Sysroot process-start callbacks.
} SceAppMgrLaunchParamAttr;

/**
 * Process-replacement modes for Processmgr's exit-spawn mechanism.
 *
 * On FW 3.60, calling ::ksceKernelKillProcess with option 2 prepares to replace
 * the process identified by `pid`: Processmgr allocates a temporary replacement
 * object and preserves an internal 0x90-byte portion of the exiting process's
 * state. A subsequent create request in enabled mode, with
 * ::SceAppMgrLaunchParam::process_exit_spawn_pid set to the same `pid`, consumes
 * that temporary object and restores the preserved state into the replacement
 * process. The replacement receives its own PID; the exiting PID only
 * identifies the handoff.
 *
 * Enabled mode with a zero process ID allocates an ordinary new process object
 * instead, but the mode is still passed to Processmgr's process-event handlers.
 * These fields are used only when
 * ::SCE_APPMGR_LAUNCH_PARAM_ATTR_PROCESS_EXIT_SPAWN is present in
 * ::SceAppMgrLaunchParam::attr.
 */
typedef enum SceAppMgrProcessExitSpawnMode {
	SCE_APPMGR_PROCESS_EXIT_SPAWN_MODE_NORMAL  = 0, //!< Allocate an ordinary new process object.
	SCE_APPMGR_PROCESS_EXIT_SPAWN_MODE_ENABLED = 1  //!< Consume the prepared replacement for a matching nonzero PID.
} SceAppMgrProcessExitSpawnMode;

/**
 * @brief Options for ::ksceAppMgrLaunchAppByPath.
 *
 * FW 3.60 ignores \a size, but callers should initialize it to
 * `sizeof(SceAppMgrLaunchParam)`. The launch function requires a non-NULL
 * pointer to this structure and reads \a attr before doing other validation.
 *
 * Field use depends on the application class selected by the separate
 * argument block passed to ::ksceAppMgrLaunchAppByPath. Game launches use the
 * CPU affinity mask, initial priority, stack size, budget ID, and process-
 * replacement mode/PID pair. For mini-application launches, AppMgr supplies
 * the other Processmgr values internally and copies only the process-
 * replacement pair from this structure; \a attr still selects which option
 * fields Processmgr reads. System-application launches use the initial
 * priority, stack size, and replacement mode, but force the exiting-process PID
 * to zero, so they cannot consume a prepared replacement object.
 * A nonzero CPU affinity mask must use a subset of either bits 0-3 or bits
 * 16-19; the two encodings cannot be combined.
 */
typedef struct SceAppMgrLaunchParam {
	SceSize size;                       //!< Ignored on FW 3.60; initialize to the size of this structure.
	unsigned int attr;                  //!< Bitwise OR of ::SceAppMgrLaunchParamAttr values.
	unsigned int cpu_affinity_mask;       //!< Game-only CPU affinity mask; zero selects the default.
	SceInt32 init_priority;               //!< Initial priority for game and system applications.
	SceSize stack_size;                   //!< Main-thread stack size for game and system applications.
	unsigned int reserved0;             //!< Copied for game launches but ignored by Processmgr on FW 3.60.
	SceUID budget_id;                     //!< Game-only process-budget selector or UID.
	unsigned int reserved1;             //!< Ignored by AppMgr on FW 3.60.
	unsigned int process_exit_spawn_mode;  //!< One of ::SceAppMgrProcessExitSpawnMode.
	ScePID process_exit_spawn_pid;          //!< PID prepared using ::ksceKernelKillProcess with option 2.
	unsigned int reserved2[3];          //!< Ignored by AppMgr on FW 3.60.
} SceAppMgrLaunchParam;
VITASDK_BUILD_ASSERT_EQ(0x34, SceAppMgrLaunchParam); // size is from FW 3.60

/**
 * @brief Path-mapping options for ::ksceAppMgrLaunchAppByPath.
 *
 * FW 3.60 uses the path fields only when \a size is 0x814. If
 * \a mapping_file_path is empty, AppMgr looks for `configuration.psp2path` in
 * the executable's directory. When the selected mapping file contains an
 * `app0=` entry, that entry takes precedence over \a app0_path.
 *
 * An explicit mapping-file path must begin with `host0:` or `sd0:` on FW
 * 3.60. The `app0:` source path is resolved through the current process's
 * FIOS overlays before it is used as the application root.
 */
typedef struct SceAppMgrLaunchAppByPathOpt {
	SceSize size;                //!< Must be the size of this structure.
	char mapping_file_path[0x400]; //!< Optional path to a `configuration.psp2path` file.
	char app0_path[0x400];        //!< Optional fallback source path for the `app0:` mount.
	SceUInt8 reserved[0x10];     //!< Ignored on FW 3.60.
} SceAppMgrLaunchAppByPathOpt;
VITASDK_BUILD_ASSERT_EQ(0x814, SceAppMgrLaunchAppByPathOpt); // size is from FW 3.60

/**
 * @brief Launch an application from an executable path.
 *
 * The \a args block is scanned as a sequence of NUL-terminated strings.
 * `-budget big` and `-budget game` select a game launch; `-budget small` and
 * `-budget mini` select a mini-application launch; and `-budget sys` and
 * `-budget shell` select a system-application launch.
 *
 * @param[in] path - Path to the executable to load.
 * @param[in] args - Optional sequence of NUL-terminated argument strings.
 * @param[in] arg_size - Size of the argument block.
 * @param[in] type - Set bit 31 to request a debug launch.
 * @param[in] launch_param - Required launch options.
 * @param[in] path_mapping_opt - Optional path-mapping options.
 *
 * @return Process ID on success, or a negative error code.
 */
int ksceAppMgrLaunchAppByPath(const char *path, const char *args, SceSize arg_size, unsigned int type, const SceAppMgrLaunchParam *launch_param, const SceAppMgrLaunchAppByPathOpt *path_mapping_opt);

typedef struct SceAppMgrDrmOpt {
	SceSize size; //!< Must be the size of this structure.
	char addcont_id[20]; //!< NUL-terminated additional-content ID of at most 16 characters.
	char mount_point[16]; //!< `addcont0:` or `addcont1:`.
} SceAppMgrDrmOpt;
VITASDK_BUILD_ASSERT_EQ(0x28, SceAppMgrDrmOpt); // size is from FW 3.60

typedef enum SceAppMgrCloudDataMcIdLocation {
	SCE_APPMGR_CLOUD_DATA_MC_ID_LOCATION_AUTO     = 0, //!< External when NVS type 5 bit 0 is set, otherwise internal.
	SCE_APPMGR_CLOUD_DATA_MC_ID_LOCATION_EXTERNAL = 1, //!< `sdstor0:xmc-lp-act-mediaid`.
	SCE_APPMGR_CLOUD_DATA_MC_ID_LOCATION_INTERNAL = 2  //!< `tm0:/clouddata/mcid.dat`.
} SceAppMgrCloudDataMcIdLocation;

typedef enum SceAppMgrDebugSetting {
	SCE_APPMGR_DEBUG_SETTING_FAKE_NO_MEMORY_CARD = 0,
	SCE_APPMGR_DEBUG_SETTING_UPGRADABLE          = 1,
	SCE_APPMGR_DEBUG_SETTING_BUTTON_ASSIGN       = 2,
	SCE_APPMGR_DEBUG_SETTING_TRC_CHECK_NOTIFY    = 3,
	SCE_APPMGR_DEBUG_SETTING_SHOW_DEBUG_INFO     = 4
} SceAppMgrDebugSetting;

/**
 * @param[in] title_id Title ID of exactly 9 characters: four
 *                    uppercase letters followed by five decimal digits.
 * @param[in] addcont_id Additional-content ID of exactly 16 uppercase
 *                      alphanumeric characters.
 * @param[out] output_data The 0xE0-byte result.
 */
int ksceAppMgrAcInstGetAcdirParam(const char *title_id, const char *addcont_id, SceAppMgrAcInstResult *output_data);

/**
 * Mount application data for the calling process.
 *
 * FW 3.60 accepts mount IDs 100, 101, 102, 103, 105, 108, 109, 111, and 112.
 *
 * @param[in] mount_id Application-data mount ID.
 * @param[out] mount_point Buffer that receives a 16-byte randomized mount point.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceAppMgrAppDataMount(int mount_id, char mount_point[16]);

/**
 * FW 3.60 accepts mount IDs 104, 106, 107, and 110.
 *
 * @param[in] title_id A NUL-terminated identifier whose required syntax
 *                    depends on \a mount_id.
 * @param[out] mount_point Buffer that receives a 16-byte randomized mount point.
 */
int ksceAppMgrAppDataMountById(int mount_id, const char *title_id, char mount_point[16]);

/**
 * @param[in] process_id Process ID of type ::ScePID; 0 selects the calling process.
 *
 * @return 0 while the process is in a content-install period, or a negative
 *         error code otherwise.
 */
int ksceAppMgrCheckContentInstallPeriod(ScePID process_id);

/**
 * @param[in] path A NUL-terminated `ux0:` directory path shorter than 0x124
 *                 bytes.
 *
 * @return 0 when the path is a mounted PFS directory, or a negative error
 *         code.
 */
int ksceAppMgrCheckPfsMounted(const char *path);

/**
 * @param[in] location One of ::SceAppMgrCloudDataMcIdLocation.
 */
int ksceAppMgrCloudDataClearMcId(int location);

/**
 * @param[in] title_id A NUL-terminated identifier containing at most 31
 *                    letters, decimal digits, hyphens, or underscores.
 * @param[out] mount_point Buffer that receives a 16-byte randomized mount point.
 */
int ksceAppMgrCloudDataDstCreateMount(const char *title_id, char mount_point[16]);

/**
 * @param[in] mode Value 1 selects grw0 save data; values 2 and 3 select the
 *                 per-user ux0 save-data location.
 * @param[in] title_id Title ID of exactly 9 characters: four
 *                    uppercase letters followed by five decimal digits.
 * @param[out] mount_point Buffer that receives a 16-byte randomized mount point.
 */
int ksceAppMgrCloudDataSrcMount(int mode, const char *title_id, char mount_point[16]);

/**
 * @param[in] setting One of ::SceAppMgrDebugSetting.
 */
int ksceAppMgrDebugSettingNotifyUpdate(int setting);
int ksceAppMgrDrmOpen(const SceAppMgrDrmOpt *drm_opt);

/**
 * @param[in] path Save-data path.
 * @param[out] mount_point A 16-byte mount-point output buffer.
 */
int ksceAppMgrFakeSaveDataCreateMount(const char *path, char mount_point[16]);
int ksceAppMgrGameDataMount(const char *app_path, const char *patch_path, const char *rif_path, char mount_point[16]);

/**
 * Check whether an exclusive process is running.
 *
 * @param[in] title_id Optional exact nine-character title ID; NULL accepts any
 *                    qualifying exclusive process.
 *
 * @return 1 when found, 0 when not found, or a negative error code.
 */
int ksceAppMgrIsExclusiveProcessRunning(const char *title_id);
int ksceAppMgrMmsMount(int mount_id, char mount_point[16]);
int ksceAppMgrPhotoMount(const SceAppMgrPhotoMountParam *param);
int ksceAppMgrTrophyMount(int mount_id, ScePID process_id, char mount_point[16]);
int ksceAppMgrUmount(const char *mount_point);
int ksceAppMgrWorkDirMount(int mount_id, char mount_point[16]);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_APPMGR_H_ */
