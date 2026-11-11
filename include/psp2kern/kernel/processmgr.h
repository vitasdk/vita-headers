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

typedef struct SceUIDProcessObject SceUIDProcessObject;

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

/**
 * Previous VitaSDK name and prototype for ::ksceKernelUIDtoProcess.
 *
 * This spelling remains a separately generated stub for backwards
 * compatibility. Its return value is the same borrowed internal process
 * object pointer; new code should use ::ksceKernelUIDtoProcess.
 *
 * @param[in] pid Process ID, or 0 for the calling process.
 *
 * @return Process object pointer, or NULL when the process cannot be resolved.
 */
void *ksceKernelGetProcessKernelBuf(SceUID pid);

/**
 * Resolves a process ID to its internal process object without acquiring a
 * reference.
 *
 * The returned pointer is borrowed and remains valid only while the process
 * object exists. PID 0 selects the calling process.
 *
 * @param[in] pid Process ID, or 0 for the calling process.
 *
 * @return Process object pointer, or NULL when the process cannot be resolved.
 */
SceUIDProcessObject *ksceKernelUIDtoProcess(ScePID pid);

int ksceKernelGetProcessInfo(SceUID pid, SceKernelProcessInfo *info);

int ksceKernelCreateProcessLocalStorage(const char *name, SceSize size);
void *ksceKernelGetProcessLocalStorageAddr(int key);
int ksceKernelGetProcessLocalStorageAddrForPid(SceUID pid, int key, void **out_addr, int create_if_doesnt_exist);

typedef SceUInt32 SceKernelProcessType;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelProcessType);

#define SCE_KERNEL_PROCESS_TYPE_GAME               (0x01000000U)
#define SCE_KERNEL_PROCESS_TYPE_MINI_APPLICATION   (0x02000000U)
#define SCE_KERNEL_PROCESS_TYPE_SYSTEM_APPLICATION (0x04000000U)
/** Used by the kernel process object; rejected by the FW 3.60 create/spawn APIs. */
#define SCE_KERNEL_PROCESS_TYPE_KERNEL             (0x05000000U)

/** Requests a debug-suspended start; OR into the type passed to a spawn function. */
#define SCE_KERNEL_PROCESS_START_FLAG_DEBUG        (0x80000000U)

/** Select the calling process's built-in game or system-application budget. */
#define SCE_KERNEL_PROCESS_CURRENT_PROCESS_BUDGET            (0)
/** Select the built-in full-game process budget. */
#define SCE_KERNEL_PROCESS_FULL_GAME_PROCESS_BUDGET          (2)
/** Select the built-in system-application process budget. */
#define SCE_KERNEL_PROCESS_SYSTEM_APPLICATION_PROCESS_BUDGET (3)

/** Known option bits used in ::SceKernelProcessOpt2::attr on FW 3.60. */
typedef enum SceKernelProcessOptAttribute {
	SCE_KERNEL_PROCESS_OPT_ATTR_CPU_AFFINITY_MASK            = 0x00001000, //!< Use ::SceKernelProcessOpt2::cpu_affinity_mask.
	SCE_KERNEL_PROCESS_OPT_ATTR_BUDGET_ID                    = 0x00004000, //!< Use ::SceKernelProcessOpt2::budget_id.
	SCE_KERNEL_PROCESS_OPT_ATTR_PARENT_PROCESS_ID            = 0x00010000, //!< Use ::SceKernelProcessOpt2::parent_pid.
	SCE_KERNEL_PROCESS_OPT_ATTR_PROCESS_EXIT_SPAWN           = 0x00020000, //!< Use the exit-spawn mode and PID.
	SCE_KERNEL_PROCESS_OPT_ATTR_KLICENSEE                    = 0x00040000, //!< Copy the 16-byte klicensee.
	SCE_KERNEL_PROCESS_OPT_ATTR_MAX_OPEN_FILES               = 0x00080000, //!< Use ::SceKernelProcessOpt2::max_open_files.
	SCE_KERNEL_PROCESS_OPT_ATTR_MAX_DIRECTORY_OPEN_LEVEL     = 0x00100000, //!< Use ::SceKernelProcessOpt2::max_directory_open_level.
	SCE_KERNEL_PROCESS_OPT_ATTR_UNIQUE_HEAP_SIZE             = 0x00200000, //!< Use ::SceKernelProcessOpt2::unique_heap_size.
	SCE_KERNEL_PROCESS_OPT_ATTR_DISPLAY_RESOLUTION_FLAGS     = 0x00800000, //!< Use ::SceKernelProcessOpt2::display_resolution_flags.
	SCE_KERNEL_PROCESS_OPT_ATTR_POWER_CONFIGURATION_FLAGS    = 0x01000000, //!< Use ::SceKernelProcessOpt2::power_configuration_flags.
	SCE_KERNEL_PROCESS_OPT_ATTR_INITIAL_PRIORITY             = 0x10000000, //!< Use ::SceKernelProcessOpt2::init_priority instead of the process-image value.
	SCE_KERNEL_PROCESS_OPT_ATTR_STACK_SIZE                   = 0x20000000, //!< Use ::SceKernelProcessOpt2::stack_size instead of the process-image value.
	SCE_KERNEL_PROCESS_OPT_ATTR_REPORT_LOAD_PROGRESS         = 0x40000000, //!< Request process-image load-progress reports.
	SCE_KERNEL_PROCESS_OPT_ATTR_SUPPRESS_START_NOTIFICATIONS = 0x80000000  //!< Suppress the normal Sysroot process-start notifications.
} SceKernelProcessOptAttribute;

/** Process-object handling mode selected during process creation. */
typedef enum SceKernelProcessExitSpawnMode {
	SCE_KERNEL_PROCESS_EXIT_SPAWN_MODE_NORMAL  = 0, //!< Allocate an ordinary new process object.
	SCE_KERNEL_PROCESS_EXIT_SPAWN_MODE_ENABLED = 1  //!< Enable exit-spawn handling and reuse a matching prepared object when requested.
} SceKernelProcessExitSpawnMode;

/** FW 3.60 process-creation options. */
typedef struct SceKernelProcessOpt2 {
	SceSize size; //!< Must be 0x40 on FW 3.60.
	SceUInt32 attr; //!< Bitwise OR of ::SceKernelProcessOptAttribute values. FW 3.60 does not reject unlisted bits, whose purpose is unknown.
	SceUInt32 cpu_affinity_mask; //!< Four-bit mask in bits 0-3 or bits 16-19; 0 selects the default. Do not combine the two encodings.
	SceInt32 init_priority; //!< Initial main-thread priority when selected; otherwise the process-image value or 0x10000100 is used.
	SceSize stack_size; //!< Main-thread stack size when selected; otherwise the process-image value or 0x40000 is used.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
	SceUID budget_id; //!< Budget selector or process-budget UID; the default selector is ::SCE_KERNEL_PROCESS_FULL_GAME_PROCESS_BUDGET.
	ScePID parent_pid; //!< Parent process ID; the calling process's ID is used when this field is not selected.
	SceKernelProcessExitSpawnMode process_exit_spawn_mode; //!< Exit-spawn handling mode when selected.
	ScePID process_exit_spawn_pid; //!< Pending exit-spawn PID to reuse in enabled mode; zero allocates a new object.
	const void *klicensee; //!< Pointer to a 16-byte klicensee when selected.
	SceSize max_open_files; //!< Maximum open-file count when selected; default is 64.
	SceSize max_directory_open_level; //!< Maximum directory-open nesting level when selected; default is 10.
	SceSize unique_heap_size; //!< Required and nonzero when selected by attr.
	SceUInt32 display_resolution_flags; //!< Selected value must use only bit 0 for 1280-wide modes and bit 1 for 1440/1920-wide modes.
	SceUInt32 power_configuration_flags; //!< Selected value must fit in two bits; the default queried by ScePower is 3.
} SceKernelProcessOpt2;
VITASDK_BUILD_ASSERT_EQ(0x40, SceKernelProcessOpt2); // size is from FW 3.60

/**
 * @brief Create a dormant process.
 *
 * FW 3.60 accepts game, mini-application, and system-application process
 * types. A non-NULL option must have a size of exactly 0x40. Passing NULL
 * selects the built-in full-game budget and the documented field defaults.
 * Creation is rejected in interrupt context and when either the global or
 * selected-budget process count has already reached 16.
 * The option block and its klicensee bytes must remain valid until this
 * function returns; they are not used afterwards.
 *
 * @param[in] name Non-NULL process name.
 * @param[in] type Process type. Bit 31 is discarded by this function; use a
 *                 spawn or start function to request debug suspension.
 * @param[in] path Non-NULL process-image path.
 * @param[in] opt Optional FW 3.60 process options. NULL uses defaults.
 *
 * @return Process ID on success, or < 0 on error.
 */
ScePID ksceKernelCreateProcess(const char *name, SceKernelProcessType type, const char *path, const SceKernelProcessOpt2 *opt);

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
 * @param[in] pid - The target process ID.
 *
 * @return      The process module control-block pointer.
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


/**
 * Gets the current process's elapsed time in microseconds.
 *
 * @param[out] time Non-NULL output for the elapsed time.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelGetProcessTimeCore(SceKernelSysClock *time);

/** Returns the wrapping low 32 bits of the current process's elapsed time in microseconds. */
SceUInt32 ksceKernelGetProcessTimeLowCore(void);

/**
 * Gets a process's running elapsed time or stored final time in microseconds.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 * @param[out] time Non-NULL output for the elapsed time.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelGetRemoteProcessTime(ScePID pid, SceKernelSysClock *time);

/**
 * Tests whether the current process budget reserves common-dialog memory.
 *
 * @return 1 when available, 0 when unavailable, or < 0 on error.
 */
SceBool ksceKernelIsCDialogAvailable(void);

/**
 * Requests process termination.
 *
 * Option 0 requests normal termination, option 1 selects the alternate 0x20
 * process-event path, and option 2 prepares the process for exit-spawn reuse.
 * Other option values are rejected on FW 3.60. This function cannot be called
 * from interrupt or nested-exception context.
 *
 * @param[in] pid Target process ID.
 * @param[in] option Termination option described above.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelKillProcess(ScePID pid, SceInt32 option);

/**
 * Creates and starts a process. A failure while starting automatically kills
 * the newly created process.
 *
 * For a normal start, the argument block must remain valid until this function
 * returns; it is not used afterwards. For a debug-suspended start, the preload
 * thread keeps the pointer, so the argument block must remain valid until the
 * process is resumed and the main thread is started.
 *
 * @param[in] name Non-NULL process name.
 * @param[in] type Process type, optionally ORed with
 *                 ::SCE_KERNEL_PROCESS_START_FLAG_DEBUG.
 * @param[in] path Non-NULL process-image path.
 * @param[in] arg_size Argument-block size.
 * @param[in] arg_block Optional argument block; may be NULL when arg_size is 0.
 * @param[in] opt Optional FW 3.60 process options. NULL uses defaults.
 *
 * @return Process ID on success, or < 0 on error.
 */
ScePID ksceKernelSpawnProcess(const char *name, SceKernelProcessType type, const char *path, SceSize arg_size, const void *arg_block, const SceKernelProcessOpt2 *opt);

/**
 * Extended form of ::ksceKernelSpawnProcess.
 *
 * @param[in] name Non-NULL process name.
 * @param[in] type Process type, optionally ORed with
 *                 ::SCE_KERNEL_PROCESS_START_FLAG_DEBUG.
 * @param[in] path Non-NULL process-image path.
 * @param[in] arg_size Argument-block size.
 * @param[in] arg_block Optional argument block; may be NULL when arg_size is 0.
 * @param[in] opt Optional FW 3.60 process options. NULL uses defaults.
 * @param[in] preload_flags Flags forwarded to the preloading-module loader.
 *                         AppMgr uses bit 0 when its GXM-debug setting is
 *                         enabled. A debug-suspended start additionally sets
 *                         bit 0x00020000 internally.
 *
 * @return Process ID on success, or < 0 on error.
 */
ScePID ksceKernelSpawnProcessExt(const char *name, SceKernelProcessType type, const char *path, SceSize arg_size, const void *arg_block, const SceKernelProcessOpt2 *opt, SceUInt32 preload_flags);

/**
 * Starts a dormant process.
 *
 * On FW 3.60, only bit 31 of start_flags has an effect: it requests a start
 * suspended for debugging. This form passes zero preloading flags.
 * For a normal start, the argument block must remain valid until this function
 * returns; it is not used afterwards. For a debug-suspended start, the pointer
 * is kept, so the argument block must remain valid until the process is resumed
 * and the main thread is started.
 *
 * @param[in] pid Dormant process ID.
 * @param[in] start_flags Start flags.
 * @param[in] arg_size Argument-block size.
 * @param[in] arg_block Optional argument block; may be NULL when arg_size is 0.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelStartProcess(ScePID pid, SceUInt32 start_flags, SceSize arg_size, const void *arg_block);

/**
 * Extended form of ::ksceKernelStartProcess.
 *
 * @param[in] pid Dormant process ID.
 * @param[in] start_flags Start flags; only bit 31 affects FW 3.60.
 * @param[in] arg_size Argument-block size.
 * @param[in] arg_block Optional argument block; may be NULL when arg_size is 0.
 * @param[in] preload_flags Flags forwarded to the preloading-module loader.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelStartProcessExt(ScePID pid, SceUInt32 start_flags, SceSize arg_size, const void *arg_block, SceUInt32 preload_flags);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_PROCESSMGR_H_ */
