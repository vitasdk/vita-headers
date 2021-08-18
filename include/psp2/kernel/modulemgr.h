/**
 * \usergroup{SceModulemgr}
 * \usage{psp2/kernel/modulemgr.h,SceKernelModulemgr_stub}
 */

#ifndef _PSP2_KERNEL_MODULEMGR_H_
#define _PSP2_KERNEL_MODULEMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      Return values for plugins `module_start` and `module_stop`
 */
/** @{ */
#define SCE_KERNEL_START_SUCCESS      (0)
#define SCE_KERNEL_START_RESIDENT     SCE_KERNEL_START_SUCCESS
#define SCE_KERNEL_START_NO_RESIDENT  (1)
#define SCE_KERNEL_START_FAILED       (2)

#define SCE_KERNEL_STOP_SUCCESS       (0)
#define SCE_KERNEL_STOP_FAIL          (1)
#define SCE_KERNEL_STOP_CANCEL        SCE_KERNEL_STOP_FAIL
/** @} */

typedef enum SceKernelModuleState {
	SCE_KERNEL_MODULE_STATE_READY   = 0x00000002,
	SCE_KERNEL_MODULE_STATE_STARTED = 0x00000006,
	SCE_KERNEL_MODULE_STATE_ENDED   = 0x00000009
} SceKernelModuleState;

/*
 * Assigning the following macro to the variable sceKernelPreloadModuleInhibit with the OR operator inhibit preloading that module.
 *
 * Example
 * <code>
 * // Inhibit preload SceLibc and SceShellSvc.
 * int sceKernelPreloadModuleInhibit = SCE_KERNEL_PRELOAD_INHIBIT_LIBC | SCE_KERNEL_PRELOAD_INHIBIT_LIBSHELLSVC;
 * </code>
 *
 * And these are only valid for modules in the process image, preload is not inhibited even if specified for modules to be loaded later.
 *
 * WARNING
 * If SceLibNet etc. is loaded without SceShellSvc etc. loaded, an unintended system crash will occur.
 */
typedef enum SceKernelPreloadInhibit {
	SCE_KERNEL_PRELOAD_INHIBIT_NONE        = 0x00000000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBC        = 0x10000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBDBG      = 0x20000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBSHELLSVC = 0x80000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBCDLG     = 0x100000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBFIOS2    = 0x200000,
	SCE_KERNEL_PRELOAD_INHIBIT_APPUTIL     = 0x400000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBSCEFT2   = 0x800000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBPVF      = 0x1000000,
	SCE_KERNEL_PRELOAD_INHIBIT_LIBPERF     = 0x2000000
} SceKernelPreloadInhibit;

typedef struct SceKernelSegmentInfo {
	SceSize size;   //!< this structure size (0x18)
	SceUInt perms;  //!< probably rwx in low bits
	void *vaddr;    //!< address in memory
	SceSize memsz;  //!< size in memory
	SceSize filesz; //!< original size of memsz
	SceUInt res;    //!< unused
} SceKernelSegmentInfo;

typedef struct SceKernelModuleInfo {
	SceSize size;                       //!< 0x1B8 for Vita 1.x
	SceUID modid;
	uint16_t modattr;
	uint8_t  modver[2];
	char module_name[28];
	SceUInt unk28;
	void *start_entry;
	void *stop_entry;
	void *exit_entry;
	void *exidx_top;
	void *exidx_btm;
	void *extab_top;
	void *extab_btm;
	void *tlsInit;
	SceSize tlsInitSize;
	SceSize tlsAreaSize;
	char path[256];
	SceKernelSegmentInfo segments[4];
	SceUInt state;                       //!< see:SceKernelModuleState
} SceKernelModuleInfo;

typedef struct SceKernelLMOption {
	SceSize size;
} SceKernelLMOption;

typedef struct SceKernelULMOption {
	SceSize size;
} SceKernelULMOption;

int sceKernelGetModuleInfo(SceUID uid, SceKernelModuleInfo *info);
int sceKernelGetModuleList(SceUInt8 type, SceUID *uids, SceSize *num);

SceUID sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);
int sceKernelUnloadModule(SceUID modid, int flags, SceKernelULMOption *option);

int sceKernelStartModule(SceUID modid, SceSize args, void *argp, int flags, void *option, int *status);
int sceKernelStopModule(SceUID modid, SceSize args, void *argp, int flags, void *option, int *status);

SceUID sceKernelLoadStartModule(const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
int sceKernelStopUnloadModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

typedef struct SceKernelSystemSwVersion {
	SceSize size;
	char versionString[0x1C];
	SceUInt version;
	SceUInt unk_24;
} SceKernelSystemSwVersion;

/* For backward compatibility */
typedef SceKernelSystemSwVersion SceKernelFwInfo;

/**
 * Gets system firmware information.
 *
 * @param[out] version - System sw version.
 *
 * @note - If you spoofed the firmware version it will return the spoofed firmware.
 */
int sceKernelGetSystemSwVersion(SceKernelSystemSwVersion *version);

// missing structs
typedef struct SceKernelLoadModuleOption SceKernelLoadModuleOption;
typedef struct SceKernelUnloadModuleOption SceKernelUnloadModuleOption;
typedef struct SceKernelLibraryInfo SceKernelLibraryInfo;

SceUID _sceKernelLoadModule(const char *module_filename, SceUInt32 flags, const SceKernelLoadModuleOption *option);
SceUID _sceKernelLoadStartModule(const char *module_filename, SceSize args, const void *argp, SceUInt32 flags);
int _sceKernelUnloadModule(SceUID uid, SceUInt32 flags, const SceKernelUnloadModuleOption *option);
int _sceKernelStopModule(SceUID uid, SceSize args, const void *argp, SceUInt32 flags);
int _sceKernelStopUnloadModule(SceUID uid, SceSize args, const void *argp, SceUInt32 flags);

SceUID _sceKernelOpenModule(const char *module_filename, SceSize args, const void *argp, SceUInt32 flags);
SceUID _sceKernelCloseModule(SceUID modid, SceSize args, const void *argp, SceUInt32 flags);

int sceKernelGetLibraryInfoByNID(SceUID modid, SceNID libnid, SceKernelLibraryInfo *info);

int sceKernelIsCalledFromSysModule(void *lr);
SceUID sceKernelGetModuleIdByAddr(void *addr);
SceUInt32 sceKernelGetAllowedSdkVersionOnSystem(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_MODULEMGR_H_ */

