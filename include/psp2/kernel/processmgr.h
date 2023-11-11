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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */

