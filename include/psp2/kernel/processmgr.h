/**
 * \usergroup{SceProcessmgr}
 * \usage{psp2/kernel/processmgr.h,SceProcessmgr_stub}
 */


#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Exit current Process with specified return code
 *
 * @param[in] res - Exit code to return
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelExitProcess(int res);

/**
 * Cancel specified idle timers to prevent entering in power save processing.
 *
 * @param[in] type - One of ::SceKernelPowerTickType
 *
 * @return 0
 */
int sceKernelPowerTick(SceKernelPowerTickType type);

/**
 * Locks certain timers from triggering.
 *
 * @param[in] type - One of ::SceKernelPowerTickType
 *
 * @return 0
  */
int sceKernelPowerLock(SceKernelPowerTickType type);

/**
 * Unlocks certain timers.
 *
 * @param[in] type - One of ::SceKernelPowerTickType
 *
 * @return 0
 */
int sceKernelPowerUnlock(SceKernelPowerTickType type);

/**
 * Get the process time of the current process.
 *
 * @param[out] type - Pointer to a ::SceKernelSysClock structure which will receive the process time.
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetProcessTime(SceKernelSysClock *pSysClock);

/**
 * Get the lower 32 bits part of process time of the current process.
 *
 * @return process time of the current process
 */
SceUInt32 sceKernelGetProcessTimeLow(void);

/**
 * Get the process time of the current process.
 *
 * @return process time of the current process
 */
SceUInt64 sceKernelGetProcessTimeWide(void);

SceUID sceKernelGetCurrentProcess(void);
SceInt32 sceKernelGetRemoteProcessTime(SceUID processId, SceKernelSysClock *pClock);

SceUID sceKernelGetStderr(void);
SceUID sceKernelGetStdin(void);
SceUID sceKernelGetStdout(void);

const void * sceKernelGetProcessParam(void);

SceKernelClock sceKernelLibcClock(void);
SceKernelTime sceKernelLibcTime(SceKernelTime *tloc);

int sceKernelLibcGettimeofday(SceKernelTimeval *tv, SceKernelTimezone *tz);

typedef struct SceLibkernelAddresses {
	SceSize size; //!< Size of this structure
	int (*sceKernelExitThread)(int exitStatus);
	int (*sceKernelExitDeleteThread)(int exitStatus);
	int (*sceKernelExitCallback)(void);
	void *coredumpHandler; //!< A pointer to a function with signature `int (SceSize args, void *argp)`.
	int *pProcessTime; //!< Points to the ::SceKernelSysClock process-time base.
	int *pPMUSERENR; //!< Points to the cached ::SceUInt32 PMUSERENR value.
} SceLibkernelAddresses;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceLibkernelAddresses); // size is from FW 3.60

int _sceKernelExitProcessForUser(int status);
int _sceKernelRegisterLibkernelAddresses(SceLibkernelAddresses *pAddresses);
int sceKernelGetProcessTimeCore(SceUInt64 *pTime);
int sceKernelGetProcessTimeLowCore(void);
SceUInt64 sceKernelGetProcessTimeWideCore(void);
int sceKernelIsCDialogAvailable(void);
SceBool sceKernelIsGameBudget(void);
SceInt32 sceKernelRegisterProcessTerminationCallback(SceUID pid, SceUID cbId);
SceInt32 sceKernelUnregisterProcessTerminationCallback(SceUID pid, SceUID cbId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */
