/**
 * \kernelgroup{SceKernelSysroot}
 * \usage{psp2kern/kernel/sysroot.h,SceSysrootForDriver_stub}
 */

// or SceSysrootForKernel_stub

#ifndef _PSP2_KERNEL_SYSROOT_H_
#define _PSP2_KERNEL_SYSROOT_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/kbl/kbl.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SYSROOT_H_ */
