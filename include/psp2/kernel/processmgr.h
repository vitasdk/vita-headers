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
 * @param[out] pSysClock - Pointer to a ::SceKernelSysClock value which will receive the process time.
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
	SceSize size; //!< Must be 0x1C on FW 3.60.
	int (*sce_kernel_exit_thread)(int exit_status); //!< Exit-thread trampoline.
	int (*sce_kernel_exit_delete_thread)(int exit_status); //!< Exit-and-delete-thread trampoline.
	int (*_sce_kernel_exit_callback)(void); //!< Exit-callback trampoline.
	SceKernelThreadEntry coredump_handler; //!< User coredump-thread entry point.
	SceKernelSysClock *process_time; //!< LibKernel process-time base initialized during registration.
	SceUInt32 *pmuserenr; //!< LibKernel PMUSERENR cache updated by Processmgr.
} SceLibkernelAddresses;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceLibkernelAddresses); // size is from FW 3.60

/**
 * Terminates the calling process through the raw user export.
 *
 * @param[in] exit_status Process exit status.
 *
 * @return This function does not return.
 */
__attribute__((__noreturn__))
int _sceKernelExitProcessForUser(SceInt32 exit_status);

/**
 * Registers LibKernel's process-exit trampolines and addresses of cached values.
 *
 * FW 3.60 copies exactly 0x1C bytes and requires
 * ::SceLibkernelAddresses::size to equal 0x1C. A registered non-NULL address
 * is not replaced by a later call. The process object stores the six addresses;
 * the functions and storage they point to must remain valid for the process
 * lifetime.
 *
 * On FW 3.60, a failure to initialize the user `process_time` destination is
 * not returned to the caller. That failure also prevents `pmuserenr` from
 * being registered by the same call.
 *
 * @param[in] addresses Non-NULL registration block.
 *
 * @return 0 on success, or < 0 on error.
 */
int _sceKernelRegisterLibkernelAddresses(const SceLibkernelAddresses *addresses);

/**
 * Gets the calling process's elapsed time in microseconds.
 *
 * @param[out] time Non-NULL output for the elapsed time as a ::SceKernelSysClock value.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetProcessTimeCore(SceKernelSysClock *time);

/** @return The wrapping low 32 bits of the calling process's elapsed time in microseconds. */
SceUInt32 sceKernelGetProcessTimeLowCore(void);

/** @return The calling process's elapsed time in microseconds. */
SceKernelSysClock sceKernelGetProcessTimeWideCore(void);

/**
 * Tests whether the current process budget reserves common-dialog memory.
 *
 * @return 1 when available, 0 when unavailable, or < 0 on error.
 */
SceBool sceKernelIsCDialogAvailable(void);

/** @return 1 when the calling process uses the built-in full-game budget descriptor, otherwise 0. */
SceBool sceKernelIsGameBudget(void);

/**
 * Registers a callback to be notified when a process object is destroyed.
 *
 * The callback receives the target process ID as its notification argument.
 * The callback must remain valid until it is unregistered or the target
 * process is destroyed. Registering the same pair again creates another
 * registration; each unregister call removes one matching registration.
 *
 * @param[in] pid Nonzero target process ID.
 * @param[in] callback_id Nonzero callback PUID owned by the calling process.
 *
 * @return 0 on success, or < 0 on error.
 */
SceInt32 sceKernelRegisterProcessTerminationCallback(ScePID pid, SceUID callback_id);

/**
 * Unregisters one matching process-termination callback registration.
 *
 * @param[in] pid Nonzero target process ID.
 * @param[in] callback_id Nonzero previously registered callback PUID.
 *
 * @return 0 on success, or < 0 on error.
 */
SceInt32 sceKernelUnregisterProcessTerminationCallback(ScePID pid, SceUID callback_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */
