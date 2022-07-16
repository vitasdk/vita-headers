/**
 * \usergroup{SceProcessmgr}
 * \usage{psp2/kernel/processmgr.h,SceProcessmgr_stub}
 */


#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2/kernel/threadmgr.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SceUInt64 SceKernelClock;
typedef SceUInt32 SceKernelTime;

typedef enum SceKernelProcessPrioritySystem {
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_HIGH     = 32,
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_DEFAULT  = 96,
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_LOW      = 159
} SceKernelProcessPrioritySystem;

typedef enum SceKernelProcessPriorityUser {
	SCE_KERNEL_PROCESS_PRIORITY_USER_HIGH       = 64,
	SCE_KERNEL_PROCESS_PRIORITY_USER_DEFAULT    = 96,
	SCE_KERNEL_PROCESS_PRIORITY_USER_LOW        = 127
} SceKernelProcessPriorityUser;

typedef enum SceKernelPowerTickType {
	/** Cancel all timers */
	SCE_KERNEL_POWER_TICK_DEFAULT               = 0,
	/** Cancel automatic suspension timer */
	SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND  = 1,
	/** Cancel OLED-off timer */
	SCE_KERNEL_POWER_TICK_DISABLE_OLED_OFF      = 4,
	/** Cancel OLED dimming timer */
	SCE_KERNEL_POWER_TICK_DISABLE_OLED_DIMMING  = 6
} SceKernelPowerTickType;

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

typedef struct SceKernelTimeval {
	SceInt32 sec;
	SceInt32 usec;
} SceKernelTimeval;

typedef struct SceKernelTimezone {
	SceUInt64 value;
} SceKernelTimezone;

int sceKernelLibcGettimeofday(SceKernelTimeval *tv, SceKernelTimezone *tz);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */

