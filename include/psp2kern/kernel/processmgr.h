/**
 * \kernelgroup{SceProcessmgr}
 * \usage{psp2kern/kernel/processmgr.h,SceProcessmgrForKernel_stub SceProcessmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_PROCESSMGR_H_
#define _PSP2KERN_KERNEL_PROCESSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/kernel/processmgr.h>
#include <psp2kern/types.h>
#include <psp2kern/kernel/sysmem.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelProcessInfo {
	SceSize size;           //!< size of this struct, make sure it's 0xE8
	SceUID pid;             //!< our process ID
	int unk1;
	int unk2;
	int unk3;
	SceUID ppid;            //!< parent process ID
	int unk[0xE8 / 4 - 6];  //!< the rest is unknown
} SceKernelProcessInfo;
VITASDK_BUILD_ASSERT_EQ(0xE8, SceKernelProcessInfo);

void *ksceKernelGetProcessKernelBuf(SceUID pid);

int ksceKernelGetProcessInfo(SceUID pid, SceKernelProcessInfo *info);

int ksceKernelCreateProcessLocalStorage(const char *name, SceSize size);
void *ksceKernelGetProcessLocalStorageAddr(int key);
int ksceKernelGetProcessLocalStorageAddrForPid(SceUID pid, int key, void **out_addr, int create_if_doesnt_exist);

typedef SceUInt32 SceKernelProcessType;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelProcessType);

/**
 * @brief       Create process
 * @param[in]   titleid - The TitleId of the app to open.
 * @param[in]   type    - The process type.
 * @param[in]   path    - Path of the process image.
 * @param[in]   opt     - A pointer to a ::SceKernelProcessOpt2 structure on FW 3.60.
 * @return      PID of the created process on success, < 0 on error.
 */
SceUID ksceKernelCreateProcess(const char *titleid, SceKernelProcessType type, const char *path, void *opt);

/**
 * @brief       Resume a suspended process.
 * @param[in]   pid The process to resume.
 * @return      Zero on success, < 0 on error.
 */
int ksceKernelResumeProcess(SceUID pid);

/**
 * @brief       Suspend a running process.
 * @param[in]   pid The process to suspend.
 * @param[in]	status The new status for the process.
 * @return      Zero on success, < 0 on error.
 */
int ksceKernelSuspendProcess(SceUID pid, int status);

/**
 * @brief       Get the status of a given process.
 * @param[in]   pid The process ID to query.
 * @param[out]  status The bit field status of the process.
 * @return      Zero on success, < 0 on error.
 */
int ksceKernelGetProcessStatus(SceUID pid, int *status);

/**
 * @brief       Get the main thread for a given process.
 * @param[in]   pid The process id to query for.
 * @return      The thread UID on success, else < 0 on error.
 */
SceUID ksceKernelGetProcessMainThread(SceUID pid);

/**
 * @brief       Get the process module control block.
 *
 * @param[in] - The target process id.
 *
 * @return      The process module cb pointer
 */
ScePVoid ksceKernelGetProcessModuleInfo(SceUID pid);

/**
 * @brief      Get the process self auth info.
 *
 * @param[in]  pid            - The target process id.
 * @param[out] self_auth_info - The output buffer pointer of self auth info.
 *
 * @return     Zero on success, < 0 on error.
 */
int ksceKernelGetProcessSelfAuthInfo(SceUID pid, SceSelfAuthInfo *self_auth_info);


int ksceKernelLibcGettimeofday(SceKernelTimeval *tv, SceKernelTimezone *tz);
SceKernelTime ksceKernelLibcTime(SceKernelTime *tloc);
int ksceKernelExitProcess(int status);
SceClass *ksceKernelGetUIDProcessClass(void);


typedef struct SceKernelProcessOpt {
	SceSize size; //!< Size of this structure
	SceUInt32 unk_4; //!< Corresponding FW 3.60 field: attr; FW 0.990 semantics unverified.
	SceUInt32 cpuAffinityMask;
	SceUInt32 initPriority;
	SceSize stackSize;
	SceUInt32 unk_14; //!< Corresponding FW 3.60 field is ignored; FW 0.990 semantics unverified.
	SceUInt32 budgetId;
	SceUInt32 unk_1C; //!< Corresponding FW 3.60 field: parent PID; FW 0.990 semantics unverified.
} SceKernelProcessOpt;
VITASDK_BUILD_ASSERT_EQ(0x20, SceKernelProcessOpt); // size is from FW 0.990

typedef struct SceKernelProcessOpt2 {
	SceSize size; //!< Size of this structure
	int attr;
	int cpuAffinityMask; //!< A ::SceUInt32 value.
	int initPriority;
	int stackSize; //!< A ::SceSize value.
	int reserved; //!< Ignored on FW 3.60.
	int budgetId;
	SceUID ppid;
	int processExitSpawnMode; //!< Set to 1 to reuse a pending exit-spawn process object.
	void *processExitSpawnPid; //!< A ::ScePID value identifying the exiting process whose object is reused.
	const void *klicensee;
	SceSize file_open_max_num;
	SceSize dir_open_max_level;
	int uniqueHeapSize; //!< A ::SceSize value used for the process's unique heap.
	int displayResolutionFlags; //!< Bit 0 enables 1280-wide modes; bit 1 enables 1440- and 1920-wide modes.
	int powerConfigurationFlags; //!< Permission bits queried by ScePower for process-specific clock configurations.
} SceKernelProcessOpt2;
VITASDK_BUILD_ASSERT_EQ(0x40, SceKernelProcessOpt2); // size is from FW 3.60

typedef SceUInt32 SceProcessType;

#define SCE_PROCESS_TYPE_GAME               0x01000000
#define SCE_PROCESS_TYPE_MINI_APPLICATION   0x02000000
#define SCE_PROCESS_TYPE_SYSTEM_APPLICATION 0x04000000
#define SCE_PROCESS_TYPE_KERNEL             0x05000000

#define SCE_KERNEL_PROCESS_CURRENT_PROCESS_BUDGET            0
#define SCE_KERNEL_PROCESS_FULL_GAME_PROCESS_BUDGET          2
#define SCE_KERNEL_PROCESS_SYSTEM_APPLICATION_PROCESS_BUDGET 3

#define SCE_KERNEL_CPU_AFFINITY_FLAG_SYSTEM_CORE 0
#define SCE_KERNEL_CPU_AFFINITY_FLAG_ALL_USER    8

typedef struct SceUIDProcessObject SceUIDProcessObject;

int ksceKernelGetProcessTimeCore(SceUInt64 *pTime);
SceUInt32 ksceKernelGetProcessTimeLowCore(void);
int ksceKernelGetRemoteProcessTime(SceUID pid, SceUInt64 *pTime);
int ksceKernelIsCDialogAvailable(void);
int ksceKernelKillProcess(SceUID pid, SceInt32 option);

/**
 * @param[in] pOpt On FW 3.60, points to a ::SceKernelProcessOpt2 structure.
 */
SceUID ksceKernelSpawnProcess(const char *name, SceKernelProcessType type, const char *path, SceSize argSize, const void *pArgBlock, SceKernelProcessOpt *pOpt);

/**
 * @param[in] pOpt On FW 3.60, points to a ::SceKernelProcessOpt2 structure.
 */
SceUID ksceKernelSpawnProcessExt(const char *name, SceKernelProcessType type, const char *path, SceSize argSize, const void *pArgBlock, SceKernelProcessOpt *pOpt, SceUInt32 flags);

int ksceKernelStartProcess(SceUID pid, SceKernelProcessType type, SceSize argSize, const void *pArgBlock);
int ksceKernelStartProcessExt(SceUID pid, SceKernelProcessType type, SceSize argSize, const void *pArgBlock, uint32_t flags);
SceUIDProcessObject *ksceKernelUIDtoProcess(ScePID pid);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_PROCESSMGR_H_ */
