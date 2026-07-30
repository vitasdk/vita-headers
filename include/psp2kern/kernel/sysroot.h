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
	SceUID pid,
	SceKernelCoredumpStateUpdateCallback update_func,
	SceKernelCoredumpStateFinishCallback finish_func,
	SceCoredumpTriggerParam *param
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
	SceSize size; //!< Size of this structure.
	SceUInt32 moduleId; //!< Value of type ::SceUID.
	SceUInt16 moduleAttr;
	SceUInt8 moduleVersion[2];
	char moduleName[0x1C];
	SceNID moduleNid;
	char *libraryName; //!< Points to a read-only string.
	SceUInt32 reserved; //!< Reserved; set to zero on FW 3.60.
	SceUInt16 libraryVersion;
	SceUInt16 reserved2; //!< Reserved; not written on FW 3.60.
	SceUInt32 functionNid; //!< Value of type ::SceNID.
} SceSyscallInfo;
VITASDK_BUILD_ASSERT_EQ(0x3C, SceSyscallInfo); // size is from FW 3.60

typedef struct SceUIDAddressSpaceObject SceUIDAddressSpaceObject;

/**
 * Size-versioned coredump trigger options used by the legacy
 * \c SceCoredumpForDriver_A7D214A7 export.
 *
 * The type remains opaque for backwards compatibility with callers that provide
 * a short legacy layout. On FW 3.60, the first field is a \c SceSize:
 *
 * - A size from 4 through 7 uses the default dump level, 0xF.
 * - A size from 8 through 19 also supplies the dump level.
 * - A size from 20 through 51 also supplies the output mode, custom-path
 *   length, and custom-path pointer.
 * - A size of at least 0x34 supplies the complete ::SceCoredumpTriggerParam
 *   layout.
 */
typedef struct SceCoredumpForDriver_A7D214A7_Opt SceCoredumpForDriver_A7D214A7_Opt;

/**
 * Allocates memory from the heap associated with a UID.
 *
 * FW 3.60 redirects the kernel and dummy-process UIDs to the shared kernel
 * heap before using the registered process-heap allocator for other UIDs.
 *
 * @param[in] uid UID selecting the process heap.
 * @param[in] size Allocation size.
 * @param[in,out] pOpt Optional heap-allocation options and mapping results.
 *
 * @return The allocation address, or NULL on failure.
 */
void *ksceKernelAllocHeapMemory2(SceUID uid, SceSize size, SceKernelHeapMemoryOpt *pOpt);

/**
 * Invokes the registered callbacks in an initialization slot.
 *
 * @param[in] index Initialization slot index from 0 through 8.
 *
 * @return For an index greater than 8, the index is returned unchanged. The
 * valid-index path has no defined result value on FW 3.60.
 */
int ksceKernelInvokeInitCallback(int index);
int ksceKernelIsColdBoot(void);

/**
 * Tests whether the boot parameters request SD card mode.
 *
 * @return 1 when bit 19 of the ::SceKblParam boot type indicator is set,
 * otherwise 0.
 */
int ksceSysrootIsSdCardMode(void);
#define ksceKernelIsSomeBootMode ksceSysrootIsSdCardMode

/**
 * Tests a hardware-model capability bit.
 *
 * The low byte of \p capabilityIndex selects the bit to test.
 *
 * @return 1 if the capability is present, otherwise 0.
 */
int ksceKernelSysrootCheckModelCapability(int capabilityIndex);

/**
 * Triggers a coredump through the registered coredump callback.
 *
 * @param[in] pid Process identifier; a value of type ::SceUID.
 * @param[in] updateCallback State-update callback; a function pointer of type
 * ::SceKernelCoredumpStateUpdateCallback represented as an \c int.
 * @param[in] finishCallback Completion callback; a function pointer of type
 * ::SceKernelCoredumpStateFinishCallback represented as an \c int.
 * @param[in] pParam Size-versioned coredump parameters. See
 * ::SceCoredumpForDriver_A7D214A7_Opt.
 *
 * @return The registered callback's result.
 */
int ksceKernelSysrootCoredumpTrigger(int pid, int updateCallback, int finishCallback, SceCoredumpForDriver_A7D214A7_Opt *pParam);
SceUIDAddressSpaceObject *ksceKernelSysrootGetCurrentAddressSpaceCB(void);

/**
 * Gets a module-private area from the sysroot object.
 *
 * FW 3.60 performs no bounds check on \p index. Known indices include 3 for
 * Sysmem and 9 for Kernel Module Manager.
 *
 * @param[in] index Module-private area index.
 *
 * @return The registered module-private area.
 */
void *ksceKernelSysrootGetModulePrivate(int index);
int ksceKernelSysrootGetPUIDEntryHeap(SceUID pid, void **entryHeap);
int ksceKernelSysrootGetStatus(void);

/**
 * Gets the calling thread's access level.
 *
 * @return The FW 3.60 access level: 0x10, 0x20, 0x40, or 0x80; or 0 when the
 * provider is not registered.
 */
int ksceKernelSysrootGetThreadAccessLevel(void);
void *ksceKernelSysrootGetVbaseResetVector(void);
int ksceSysrootGetFactorySystemSwVersion(void);

/**
 * Gets the hardware-information bitfield.
 *
 * @return The hardware-information bitfield.
 */
int ksceSysrootGetHardwareInfo(void);
int ksceSysrootGetModuleInfoForPid(SceUID pid, const void *pc, SceSyscallInfo *pInfo);
int ksceSysrootGetNidName(SceNID funcnid, const char **name);
int ksceSysrootGetSelfAuthInfo(SceUID pid, SceSelfAuthInfo *pSelfAuthInfo);

/**
 * Gets the 16-byte system session identifier.
 *
 * On FW 3.60, the function returns the input buffer address in R0 after
 * copying the identifier.
 *
 * @param[out] pSessionId Buffer that receives exactly 16 bytes.
 *
 * @return The \p pSessionId address represented as an \c int.
 */
int ksceSysrootGetSessionId(char *pSessionId);
int ksceSysrootGetWakeupFactor(void);
int ksceSysrootRegisterLicMgrGetLicenseStatus(int (*sceSblLicMgrGetLicenseStatusForDriver)(void));

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSROOT_H_ */
