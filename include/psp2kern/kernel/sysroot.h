/**
 * \kernelgroup{SceKernelSysroot}
 * \usage{psp2kern/kernel/sysroot.h,SceSysrootForDriver_stub}
 */

// or SceSysrootForKernel_stub

#ifndef _PSP2_KERNEL_SYSROOT_H_
#define _PSP2_KERNEL_SYSROOT_H_

#include <psp2kern/types.h>

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

void *ksceKernelGetSysrootBuffer(void);

int ksceKernelGetProcessTitleId(SceUID pid, char *titleid, SceSize len);

int ksceSysrootGetSelfInfo(SceKernelSysrootSelfIndex index, SceKernelSysrootSelfInfo *info);

int ksceSysrootUseExternalStorage(void);

#define ksceSysrootIsManufacturingMode() ksceSysrootUseExternalStorage()

int ksceSysrootUseInternalStorage(void);

typedef struct {
    SceSize size; //!< sizeof(SceSysrootProcessHandler)
    int (* unk_4)(void);
    int (* unk_8)(void);
    int (* unk_C)(void);
    int (* unk_10)(void);
    int (* unk_14)(void);
    int (* unk_18)(void);
    int (* on_process_created)(void); //!< called when process is created
    int (* unk_20)(void);
    int (* unk_24)(void);
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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SYSROOT_H_ */
