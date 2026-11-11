/**
 * \kernelgroup{SceKernelSysroot}
 * \usage{psp2kern/kernel/sysroot.h,SceSysrootForDriver_stub SceSysrootForKernel_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSROOT_H_
#define _PSP2KERN_KERNEL_SYSROOT_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2kern/kernel/kbl/kbl.h>
#include <psp2kern/kernel/cpu.h>
#include <psp2kern/coredump.h>
#include <psp2kern/kernel/sysmem.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelVARange SceKernelVARange;
typedef struct SceKernelBootArgs SceKernelBootArgs;
typedef struct SceClass SceClass;
typedef struct SceSysrootProcessHandler SceSysrootProcessHandler;
typedef struct SceSysrootDbgpHandler SceSysrootDbgpHandler;
typedef struct SceSysrootModulemgrHandlers SceSysrootModulemgrHandlers;
typedef struct SceSysrootForKernel_D29BCA77_struct SceSysrootForKernel_D29BCA77_struct;
typedef struct SceSysrootForDriver_733C243E_struct SceSysrootForDriver_733C243E_struct;

#define SCE_SYSROOT_INIT_CALLBACK_MAX_FUNC (9)
#define SCE_SYSROOT_INIT_CALLBACK_MAX_SLOT (8)

typedef struct SceUIDSysrootObject { // size is 0x41C on FW 3.60
	void *object;
	SceClass *sce_class;
	SceSize size; // Size of this structure
	SceUInt32 magic1;
	int cpu_intr;
	SceSize boot_alloc_memory_size; // 0x400
	void *boot_alloc_memory;      // Used by boot time malloc
	int unk_0x1C; // 0x4
	void *unk_0x20; // size is 0x80-bytes
	SceUInt32 boot_flags; // 0x10 for coldboot, 0x1 for secure state
	SceUInt32 status;
	SceCorelockContext corelock_context;

	// start ModulePrivate
	int unk_0x34;   // ex:0
	int unk_0x38;   // ex:0
	void *unk_0x3C; // size is 4 byte.
	void *unk_0x40; // Related to SceHeap. size is 0xDC byte.
	void *unk_0x44; // SceExcpmgr data vaddr?
	void *unk_0x48; // SceKernelIntrMgr data vaddr?
	void *unk_0x4C;
	void *unk_0x50;
	int unk_0x54;   // ex:0
	void *unk_0x58;
	int unk_0x5C;   // ex:0
	int unk_0x60;   // ex:0
	int unk_0x64;   // ex:0
	int unk_0x68;   // Used by Tzs SceSblSmsched
	// end ModulePrivate

	SceKblParam *kbl_param;
	SceKernelBootArgs *boot_args;
	SceUInt32 soc_revision;
	SceUInt32 unk_0x78; // ex:0
	SceUInt32 soc_revision2;
	SceUInt32 model_info;
	SceUInt32 model_capability;

	void *longtime5base;

	int cpu_intr_for_init_callback;
	SceUInt32 init_callback_registable_base_number;
	struct {
		int (* callback)(int a1, void *args);
		void *args;
	} init_callback_slot[SCE_SYSROOT_INIT_CALLBACK_MAX_FUNC][SCE_SYSROOT_INIT_CALLBACK_MAX_SLOT];

	int (* funcThreadMgrStartAfterProcess)(void);
	int (* funcIofilemgrStart)(void);
	void *unk_0x2DC;
	void *unk_0x2E0;
	char *sysroot_names[9];
	SceUID this_object_uid;
	void *unk_0x30C; // size is 0x2C-bytes, May be guid entry heap object
	void *unk_0x310;
	void *unk_0x314;
	void *VBAR;
	void *MVBAR;
	void *unk_0x320;
	void **unk_func_0x324; // SceSblACMgr
	SceUID (* funcGetThreadId)(void);
	int (* funcThreadFunction3)(void);                   // Temp name, SceKernelThreadMgr + 0xC79,  SceThreadmgrForDriver_91382762
	SceUID (* funcGetProcessId)(void);
	int (* funcThreadFunction4)(void);                   // Temp name, SceKernelThreadMgr + 0x8D1
	int (* funcThreadFunction5)(void);                   // Temp name, SceKernelThreadMgr + 0x8ED
	int (* funcThreadFunction6)(void);                   // Temp name, SceKernelThreadMgr + 0x90D
	void (* funcThreadFunction7)(void);                  // Temp name, SceKernelThreadMgr + 0xE69
	int (* funcThreadFunction8)(void);                   // Temp name, SceKernelThreadMgr + 0x8BD, SceThreadmgrForDriver_332E127C
	int (* funcThreadFunction9)(int a1, int a2, int a3); // Temp name, SceKernelThreadMgr + 0x2541
	int (* funcThreadFunction10)(int a1);                // Temp name, SceKernelThreadMgr + 0xC99, SceThreadmgrForDriver_AB977C72
	SceSysrootModulemgrHandlers *modulemgr_handlers;
	int unk_0x354; // ex:0xFFFFFFFF
	SceSysrootForKernel_D29BCA77_struct *processmgr_callbacks1;
	SceSysrootForDriver_733C243E_struct *processmgr_callbacks2;
	void *unk_func_0x360; // SceDeci4pSDfMgr
	int (* funcGetBusError)(void *dst, uint32_t len);
	int (* funcAppMgrFunction1)(int a1, int a2, int a3, int a4, int a5, int a6); // SceAppMgr + 0x2795, SceAppMgrForDriver_324DD34E
	SceUID (* funcGetShellPid)(void);
	void *unk_func_0x370; // SceCoredump + 0x7109, SceCoredumpForDriver_A7D214A7
	void *unk_func_0x374; // SceCoredump + 0x74F9, SceCoredumpForDriver_340856F7
	void *unk_func_0x378; // SceCoredump + 0x132ED, SceCoredumpForDriver_EF20949F
	int unk_0x37C; // ex:0
	void *unk_func_0x380;         // SceSblPostSsMgr + 0x9001, sceSblLicMgrGetLicenseStatusForDriver
	int (* unk_func_0x384)(void); // SceSblPostSsMgr + 0xB005, SceSblPostSsMgrForDriver_22599675, get flag
	int (* unk_func_0x388)(void); // SceSblPostSsMgr + 0xB011, SceSblPostSsMgrForDriver_9B49C249, get flag
	void *unk_func_0x38C;         // SceSblPostSsMgr + 0xB4ED, SceSblPostSsMgrForDriver_D8A2D465
	void *unk_func_0x390;         // SceSblPostSsMgr + 0xB111, sceSblUtMgrGetTrilithiumBufferForDriver
	int (* funcHasNpTestFlag)(void);
	void *unk_func_0x398; // SceSblUpdateMgr + 0x8B01
	int (* funcLedSetMode)(int led, int mode, void *led_configuration);
	SceKernelVARange *cached_sm_info_ranges;
	int (* funcGetFunctionNameByNID)(SceNID funcnid, const char **name);
	void *unk_0x3A8; // SceDeci4pSDfMgr or SceDeci4pDfMgr
	void *unk_0x3AC; // SceDeci4pSDfMgr
	void *unk_struct_0x3B0; // SceDeci4pDfMgr
	void *unk_0x3B4; // SceDeci4pTsmp
	void *unk_0x3B8; // SceDeci4pTsmp
	void *unk_0x3BC; // SceDeci4pTsmp
	void *unk_0x3C0; // SceDeci4pTsmp
	SceSysrootProcessHandler *process_handler; // maybe for SceDeci4p
	SceSysrootDbgpHandler    *dbgp_handler;    // maybe for SceDeci4p
	void *unk_func_0x3CC; // SceNetPs + 0x3E51, SceNetPsForDriver_83A12CCC
	void *unk_func_0x3D0; // SceNetPs + 0x3F4D, SceNetPsForDriver_C000CA8F
	void *unk_func_0x3D4; // SceDeci4pTmcp
	void *unk_func_0x3D8; // SceDeci4pSDbgp
	void *unk_func_0x3DC; // SceNetPs + 0x3E51, SceNetPsForDriver_83A12CCC
	void *unk_func_0x3E0; // SceNetPs + 0x3F4D, SceNetPsForDriver_C000CA8F
	int (* funcAppMgrFunction3)(int a1, int a2); // SceAppMgr + 0x9F49
	int (* funcAppMgrFunction4)(int a1, int a2); // SceAppMgr + 0x9EED
	int (* funcAppMgrFunction5)(int a1);	 // SceAppMgr + 0x9D31
	void *unk_func_0x3F0; // ScePfsMgr + 0x1, ScePfsMgrForKernel_4C148288
	void *unk_struct_0x3F4; // SceBt
	void *unk_struct_0x3F8; // SceHid
	void *unk_struct_0x3FC; // SceDeci4pSDbgp
	void *unk_data_0x400; // SceDeci4pSDbgp
	void *unk_func_0x404; // SceDeci4pSDfCtl
	void *unk_func_0x408; // SceDeci4pSDfCtl
	void *unk_func_0x40C; // ScePamgr
	void *unk_func_0x410; // ScePamgr
	void *unk_func_0x414; // ScePamgr
	SceUInt32 magic2;
} SceUIDSysrootObject;
VITASDK_BUILD_ASSERT_EQ(0x41C, SceUIDSysrootObject);

typedef SceUIDSysrootObject SceSysroot;

typedef enum SceKernelSysrootSelfIndex {
	SCE_KERNEL_SYSROOT_SELF_INDEX_GCAUTHMGR_SM		= 0,
	SCE_KERNEL_SYSROOT_SELF_INDEX_RMAUTH_SM			= 1,
	SCE_KERNEL_SYSROOT_SELF_INDEX_ENCDEC_W_PORTABILITY_SM	= 2
} SceKernelSysrootSelfIndex;

typedef struct SceKernelSysrootSelfInfo {
	SceSize size;
	void *self_data;
	SceSize self_size;
} SceKernelSysrootSelfInfo;
VITASDK_BUILD_ASSERT_EQ(0xC, SceKernelSysrootSelfInfo);

/**
 * Get sysroot object pointer.
 *
 * @return sysroot object pointer.
 */
SceSysroot *ksceSysrootGetSysroot(void);

/**
 * Set sysroot object uid.
 *
 * @return none.
 *
 * note - Not should be call this function after boot.
 */
void ksceKernelSysrootSetSysroot(SceUID sysroot_uid);

/**
 * Get SceKblParam.
 *
 * @return The pointer of SceKblParam data or NULL.
 */
void *ksceKernelSysrootGetKblParam(void);

/* Macro for backward compatibility */
#define ksceKernelGetSysrootBuffer() ksceKernelSysrootGetKblParam()

int ksceKernelSysrootGetProcessTitleId(SceUID pid, char *titleid, SceSize len);

/* Macro for backward compatibility */
#define ksceKernelGetProcessTitleId(pid, titleid, len) ksceKernelSysrootGetProcessTitleId(pid, titleid, len)

int ksceSysrootGetSelfInfo(SceKernelSysrootSelfIndex index, SceKernelSysrootSelfInfo *info);

/**
 * Get UseExternalStorage status.
 *
 * Returns 1 if an external device(sdcard) is available.
 *
 * @return 0 or 1.
 */
int ksceSysrootUseExternalStorage(void);

/**
 * Get UseInternalStorage status.
 *
 * Returns 1 if using an internal device(pre-memcard).
 *
 * @return 0 or 1.
 */
int ksceSysrootUseInternalStorage(void);

/**
 * Get ManufacturingMode status.
 *
 * Returns 1 if the device is in manufacturing mode.
 *
 * @return 0 or 1.
 */
int ksceSysrootIsManufacturingMode(void);

/**
 * Get NonRemovableCardMode status.
 *
 * Returns 1 if using an non removable card(pre-memcard).
 *
 * @return 0 or 1.
 */
int ksceSysrootIsNonRemovableCardMode(void);

typedef struct SceSysrootProcessHandler {
    SceSize size;                                                       //!< sizeof(SceSysrootProcessHandler)
    void (* unk_4)(SceUID pid, SceUID modid, int flags, uint64_t time); //!< process start shared modules
    void (* exit)(SceUID pid, int flags, uint64_t time);
    void (* kill)(SceUID pid);                                          //!< by SceShell
    void (* unk_10)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_14)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_18)(SceUID pid, SceUID modid, uint64_t time);
    int (* on_process_created)(int a1, int a2, int a3);                 //!< called when process is created
    void (* unk_20)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_24)(SceUID pid, SceUID modid, int flags, uint64_t time);
} SceSysrootProcessHandler;
VITASDK_BUILD_ASSERT_EQ(0x28, SceSysrootProcessHandler);

/**
 * Set handlers for the process lifecycle.
 *
 * This internal function allows a developer to introspect and receive events based
 * on the process lifecycle.
 *
 * @param[in]  handlers   Pointer to struct containing the handlers. This function does not copy the handlers, so this pointer must remain valid after a successful call.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysrootSetProcessHandler(const SceSysrootProcessHandler *handlers);

typedef struct SceSysrootDbgpHandler {
    SceSize size; //!< sizeof(SceSysrootDbgpHandler):0x5C
    void (* unk_0x04)(int a1, int a2, int a3, int a4);
    void (* unk_0x08)(int a1, int a2, int a3, int a4);
    void (* unk_0x0C)(int a1);
    void (* unk_0x10)(int a1, int a2, int a3, int a4);
    void (* unk_0x14)(int a1, int a2, int a3, int a4);
    void (* unk_0x18)(SceUID pid, SceUID modid, int flags, uint64_t time);
    void (* unk_0x1C)(int a1, int a2, int a3);
    void (* unk_0x20)(int a1, int a2, int a3);
    void (* unk_0x24)(int a1, int a2, int a3);
    void (* unk_0x28)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_0x2C)(SceUID pid, SceUID modid, uint64_t time);
    int  (* unk_0x30)(SceUID pid);
    int  (* unk_0x34)(int a1, int a2, int a3);
    int  (* unk_0x38)(int a1, int a2, void *a3);
    int  (* unk_0x3C)(int a1, int a2, int a3);
    int  (* unk_0x40)(SceUID pid, int *some_flag);
    int  (* unk_0x44)(SceUID pid, SceUID modid, int flags, uint64_t time);
    int  (* unk_0x48)(int a1, int a2, int a3);
    void (* unk_0x4C)(void);
    void (* unk_0x50)(void);
    int  (* unk_0x54)(int a1, int a2, int a3, int a4, int a5);
    int  (* unk_0x58)(int a1, int a2, int a3);
} SceSysrootDbgpHandler;
VITASDK_BUILD_ASSERT_EQ(0x5C, SceSysrootDbgpHandler);

/**
 * Register Dbgp handlers.
 *
 * @param[in]  handlers   pointer of handlers
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysrootRegisterDbgpHandler(const SceSysrootDbgpHandler *handlers);

/**
 * Unregister Dbgp handlers.
 *
 * @return none.
 */
void ksceKernelSysrootUnregisterDbgpHandler(void);

/**
 * Get hardware flags.
 *
 * @param[out] flags - The flags output buffer. size is 0x10 byte
 *
 * @return always 0.
 */
int ksceSysrootGetHardwareFlags(void *flags);

int ksceSysrootIsBsodReboot(void);
int ksceSysrootIsSafeMode(void);
int ksceSysrootIsUpdateMode(void);
int ksceSysrootIsUsbEnumWakeup(void);
int ksceSysrootIsExternalBootMode(void);

typedef int (* SceKernelGetSystemSwVersionFunc)(void);

/**
 * Set GetSystemSwVersion function.
 *
 * @param[in] func - The GetSystemSwVersion function pointer.
 *
 * @return none.
 */
void ksceKernelSysrootSetGetSystemSwVersionFunc(SceKernelGetSystemSwVersionFunc func);

/**
 * Get System software version from ksceKernelSysrootSetGetSystemSwVersionFunc setting function
 *
 * @return SystemSwVersion on success, < 0 on error.
 */
int ksceKernelSysrootGetSystemSwVersion(void);

/**
 * Get SceShell process id
 *
 * @return pid on success, < 0 on error.
 */
SceUID ksceKernelSysrootGetShellPid(void);

typedef int (* SceKernelCoredumpTriggerFunc)(
	ScePID pid,
	SceKernelCoredumpStateUpdateCallback update_func,
	SceKernelCoredumpStateFinishCallback finish_func,
	const SceCoredumpTriggerParam *param
);

/**
 * Register coredump trigger function.
 *
 * @param[in] func - The coredump trigger function pointer.
 *
 * @return none.
 */
void ksceKernelSysrootRegisterCoredumpTrigger(SceKernelCoredumpTriggerFunc func);


typedef struct SceSyscallInfo {
	SceSize size; //!< Must be set to `sizeof(SceSyscallInfo)`.
	SceUID module_id; //!< Global module UID.
	SceUInt16 module_attr;
	SceUInt8 module_version[2];
	char module_name[0x1C];
	SceNID module_nid;
	const char *library_name; //!< Read-only imported-library name.
	SceUInt32 reserved; //!< Reserved; set to zero on FW 3.60.
	SceUInt16 library_version;
	SceUInt16 reserved2; //!< Reserved; not written on FW 3.60.
	SceNID function_nid; //!< Imported function NID corresponding to the stub address.
} SceSyscallInfo;
VITASDK_BUILD_ASSERT_EQ(0x3C, SceSyscallInfo); // size is from FW 3.60

/** Opaque class-specific data for an address-space UID object. */
typedef struct SceUIDAddressSpaceObject SceUIDAddressSpaceObject;

/**
 * Allocate memory from a process heap.
 *
 * FW 3.60 redirects ::SCE_KERNEL_PROCESS_ID,
 * ::SCE_KERNEL_DUMMY_PROCESS_GAME_ID, and
 * ::SCE_KERNEL_DUMMY_PROCESS_SYSTEM_ID to ::SCE_KERNEL_HEAP_ID. Other process
 * IDs are passed to the registered process-heap allocator.
 *
 * @param[in] pid Process whose heap supplies the allocation.
 * @param[in] size Allocation size.
 * @param[in,out] opt Optional heap-allocation options and mapping results.
 *
 * @return The allocation address, or NULL on failure.
 */
void *ksceKernelAllocHeapMemory2(ScePID pid, SceSize size, SceKernelHeapMemoryOpt *opt);

/**
 * Call all pending initialization callbacks up to and including a target slot.
 *
 * Slots are processed in order, at most once, and each slot contains at most
 * eight callbacks. FW 3.60 passes zero and the callback's registered private
 * argument to each callback. An index outside 0 through 8 has no effect.
 *
 * @param[in] index Initialization slot index from 0 through 8.
 *
 */
void ksceKernelInvokeInitCallback(int index);

/**
 * Test whether the current boot is a cold boot.
 *
 * @return 1 when bit 4 of the FW 3.60 boot-state word is clear, otherwise 0.
 */
int ksceKernelIsColdBoot(void);

/**
 * Test whether the boot parameters request SD card mode.
 *
 * @return 1 when bit 19 of the ::SceKblParam boot type indicator is set,
 * otherwise 0.
 */
int ksceSysrootIsSdCardMode(void);
#define ksceKernelIsSomeBootMode ksceSysrootIsSdCardMode

/**
 * Test a hardware-model capability bit.
 *
 * The low byte of \p capability_index is used as the ARM shift count. A value
 * from 0 through 31 selects that bit; a larger low-byte value returns zero.
 * Known FW 3.60 callers use index 11 to enable the alternate removable-SD
 * storage slot. The RTL USB-Ethernet driver uses index 12 to select a board
 * variant that skips its GPIO port 1, bit 2 power sequence.
 *
 * @return 1 if the capability is present, otherwise 0.
 */
int ksceKernelSysrootCheckModelCapability(int capability_index);

/**
 * Trigger a coredump through the registered coredump callback.
 *
 * @param[in] pid Process identifier.
 * @param[in] update_callback Optional progress callback.
 * @param[in] finish_callback Required completion callback.
 * @param[in] param Coredump parameters.
 *
 * FW 3.60 accepts the first part of the structure: size 4 through 7 uses the
 * default dump level; size 8 through 19 also supplies \c dump_level; size 20 through
 * 51 also supplies the output mode and custom path; and size 0x34 supplies the
 * complete structure.
 *
 * @return A positive coredump task ID on success, < 0 on error.
 */
int ksceKernelSysrootCoredumpTrigger(ScePID pid, SceKernelCoredumpStateUpdateCallback update_callback, SceKernelCoredumpStateFinishCallback finish_callback, const SceCoredumpTriggerParam *param);

/**
 * Get the current address-space UID object's class-specific data.
 *
 * FW 3.60 uses the registered current-address-space callback when present and
 * otherwise returns Sysroot's stored address-space pointer. This function does
 * not acquire a reference to the object. The current process/Sysroot state
 * still owns it.
 */
SceUIDAddressSpaceObject *ksceKernelSysrootGetCurrentAddressSpaceCB(void);

/**
 * Get a module-private area from the sysroot object.
 *
 * FW 3.60 performs no bounds check on \p index. Known indices include 3 for
 * Sysmem and 9 for Kernel Module Manager.
 *
 * @param[in] index Module-private area index.
 *
 * @return The registered module-private area.
 */
void *ksceKernelSysrootGetModulePrivate(int index);

/**
 * Get a process's internal PUID-entry heap.
 *
 * @param[in] pid Process identifier passed to the registered Processmgr
 * callback.
 * @param[out] entry_heap Receives the heap pointer; must be non-NULL. When
 * Processmgr has not yet registered its callback, FW 3.60 supplies Sysroot's
 * default entry heap.
 *
 * @return 0 when no callback is registered, otherwise the callback's result.
 */
int ksceKernelSysrootGetPUIDEntryHeap(ScePID pid, void **entry_heap);

/** @return The raw Sysroot lifecycle state value. */
SceUInt32 ksceKernelSysrootGetStatus(void);

/**
 * Get the calling thread's access level.
 *
 * @return The FW 3.60 access level: 0x10, 0x20, 0x40, or 0x80; or 0 when the
 * function that supplies it is not registered.
 */
int ksceKernelSysrootGetThreadAccessLevel(void);

/** @return The configured virtual base of the reset vector. */
void *ksceKernelSysrootGetVbaseResetVector(void);

/** @return The factory system-software version word. */
SceUInt32 ksceSysrootGetFactorySystemSwVersion(void);

/**
 * Get the hardware-information bitfield.
 *
 * @return The hardware-information bitfield.
 */
SceUInt32 ksceSysrootGetHardwareInfo(void);

/**
 * Get information about the imported function stub containing \p pc.
 *
 * @param[in] pid Process whose loaded modules are searched.
 * @param[in] pc Address in an imported function stub.
 * @param[in,out] info Output structure. Set its \c size to 0x3C before calling.
 *
 * @return 0 on success, < 0 on error or when Modulemgr is not registered.
 */
int ksceSysrootGetModuleInfoForPid(ScePID pid, const void *pc, SceSyscallInfo *info);

/** Get a read-only symbolic name for a function NID when one is registered. */
int ksceSysrootGetNidName(SceNID function_nid, const char **name);

/**
 * Get the 0x90-byte SELF authorization information for a process.
 *
 * Before Processmgr registers its callback, FW 3.60 returns the boot/default
 * authorization information.
 */
int ksceSysrootGetSelfAuthInfo(ScePID pid, SceSelfAuthInfo *self_auth_info);

/**
 * Get the 16-byte system session identifier.
 *
 * @param[out] session_id Buffer that receives exactly 16 bytes.
 *
 * @return \p session_id.
 */
void *ksceSysrootGetSessionId(void *session_id);

/** @return The raw wakeup-factor bitfield. */
SceUInt32 ksceSysrootGetWakeupFactor(void);
int ksceSysrootRegisterLicMgrGetLicenseStatus(int (*sce_sbl_lic_mgr_get_license_status_for_driver)(void));

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSROOT_H_ */
