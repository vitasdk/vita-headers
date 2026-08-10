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

typedef struct
{
    SceSize size;
    unsigned int attr; //!< Set to 0x80000000 to break on launch.
    unsigned int initPriority;
    unsigned int unk_C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int budgetId;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
    unsigned int unk_30;
} SceAppMgrLaunchParam;
VITASDK_BUILD_ASSERT_EQ(0x34, SceAppMgrLaunchParam);

/**
 * @brief       Launch an application for debugging
 *
 * @param[in] path  Path to the executable to load
 * @param[in] args  Arguments to pass to the executable and to configure appmgr
 * @param[in] arg_size  The size of the args passed in
 * @param[in] type  Set to 0x80000000 for debugging launch
 * @param[in] param pointer to launch params
 * @param unk unknown, set to nullptr
 *
 * @return   pid on success, else < 0.
 */
int ksceAppMgrLaunchAppByPath(const char *path, const char *args, SceSize arg_size, unsigned int type, const SceAppMgrLaunchParam *param, void *unk);

typedef struct SceAppMgrAcInstResult {
	char keystone[0x60];
	char game_title[0x80];
} SceAppMgrAcInstResult;
VITASDK_BUILD_ASSERT_EQ(0xE0, SceAppMgrAcInstResult); // size is from FW 3.60

typedef struct SceAppMgrDrmOpt {
	uint32_t size;
	char addcont_id[20];
	char mount_point[16];
} SceAppMgrDrmOpt;
VITASDK_BUILD_ASSERT_EQ(0x28, SceAppMgrDrmOpt); // size is from FW 3.60

typedef enum SceAppMgrCloudDataMcIdLocation {
	SCE_APPMGR_CLOUD_DATA_MC_ID_LOCATION_AUTO     = 0,
	SCE_APPMGR_CLOUD_DATA_MC_ID_LOCATION_EXTERNAL = 1,
	SCE_APPMGR_CLOUD_DATA_MC_ID_LOCATION_INTERNAL = 2
} SceAppMgrCloudDataMcIdLocation;

typedef enum SceAppMgrDebugSetting {
	SCE_APPMGR_DEBUG_SETTING_FAKE_NO_MEMORY_CARD = 0,
	SCE_APPMGR_DEBUG_SETTING_UPGRADABLE          = 1,
	SCE_APPMGR_DEBUG_SETTING_BUTTON_ASSIGN       = 2,
	SCE_APPMGR_DEBUG_SETTING_TRC_CHECK_NOTIFY    = 3,
	SCE_APPMGR_DEBUG_SETTING_SHOW_DEBUG_INFO     = 4
} SceAppMgrDebugSetting;

/**
 * @param[in] titleId A pointer to an exact 9-character title ID: four
 *                    uppercase letters followed by five decimal digits.
 *                    Still declared as ::SceTitleId * for backwards
 *                    compatibility.
 * @param[in] addcontId A pointer to an exact 16-character uppercase
 *                      alphanumeric additional-content ID.
 * @param[out] outputData The 0xE0-byte result.
 */
int ksceAppMgrAcInstGetAcdirParam(SceTitleId *titleId, const char *addcontId, SceAppMgrAcInstResult *outputData);
int ksceAppMgrAppDataMount(int mountId, char *mountPoint);

/**
 * @param[in] titleId A NUL-terminated identifier whose required syntax
 *                    depends on \a mountId. Still declared as ::SceTitleId *
 *                    for backwards compatibility.
 */
int ksceAppMgrAppDataMountById(int mountId, SceTitleId *titleId, char *mountPoint);

/**
 * @param[in] processId Value of type ::ScePID; 0 selects the current process.
 */
int ksceAppMgrCheckContentInstallPeriod(int processId);

/**
 * @param[in] path A pointer to a NUL-terminated ux0 path. Still declared as
 *                 int * for backwards compatibility.
 */
int ksceAppMgrCheckPfsMounted(int *path);

/**
 * @param[in] location One of ::SceAppMgrCloudDataMcIdLocation.
 */
int ksceAppMgrCloudDataClearMcId(int location);

/**
 * @param[in] titleId A title ID containing at most 31 safe path characters.
 *                    Still declared as ::SceTitleId * for backwards
 *                    compatibility.
 */
int ksceAppMgrCloudDataDstCreateMount(SceTitleId *titleId, char *mountPoint);

/**
 * @param[in] mode Value 1 selects grw0 save data; values 2 and 3 select the
 *                 per-user ux0 save-data location.
 * @param[in] titleId A pointer to an exact 9-character title ID: four
 *                    uppercase letters followed by five decimal digits.
 *                    Still declared as ::SceTitleId * for backwards
 *                    compatibility.
 */
int ksceAppMgrCloudDataSrcMount(int mode, SceTitleId *titleId, char *mountPoint);

/**
 * @param[in] setting One of ::SceAppMgrDebugSetting.
 */
int ksceAppMgrDebugSettingNotifyUpdate(int setting);
int ksceAppMgrDrmOpen(SceAppMgrDrmOpt *drmOpt);

/**
 * @param[in] path Save-data path.
 * @param[out] mountPoint A 16-byte mount-point output buffer. Still declared
 *                        as const char * for backwards compatibility.
 */
int ksceAppMgrFakeSaveDataCreateMount(const char *path, const char *mountPoint);
int ksceAppMgrGameDataMount(const char *app_path, const char *patch_path, const char *rif_path, char *mount_point);
int ksceAppMgrIsExclusiveProcessRunning(const char *titleId);
int ksceAppMgrMmsMount(int mountId, char *mountPoint);
int ksceAppMgrPhotoMount(sceAppMgrPhotoMountParam *opt);
int ksceAppMgrTrophyMount(int mountId, SceUID pid, char *mountPoint);
int ksceAppMgrUmount(const char *mount_point);
int ksceAppMgrWorkDirMount(int mountId, char *mountPoint);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_APPMGR_H_ */
