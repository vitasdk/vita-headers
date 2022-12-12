/**
 * \kernelgroup{SceProcessmgr}
 * \usage{psp2kern/kernel/processmgr.h,SceProcessmgrForKernel_stub}
 */


#ifndef _PSP2KERN_KERNEL_PROCESSMGR_H_
#define _PSP2KERN_KERNEL_PROCESSMGR_H_

#include <psp2kern/types.h>

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

void *ksceKernelGetProcessKernelBuf(SceUID pid);

int ksceKernelGetProcessInfo(SceUID pid, SceKernelProcessInfo *info);

int ksceKernelCreateProcessLocalStorage(const char *name, SceSize size);
void *ksceKernelGetProcessLocalStorageAddr(int key);
int ksceKernelGetProcessLocalStorageAddrForPid(SceUID pid, int key, void **out_addr, int create_if_doesnt_exist);

typedef SceUInt32 SceKernelProcessType;

/**
 * @brief       Create process
 * @param[in]   titleid - The TitleId of the app to open.
 * @param[in]   type    - The process type.
 * @param[in]   path    - Path of the process image.
 * @param[in]   opt     - The create process option.
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


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_PROCESSMGR_H_ */
