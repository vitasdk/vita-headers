/**
 * \usergroup{SceModulemgr}
 * \usage{psp2/kernel/modulemgr.h,SceKernelModulemgr_stub}
 */

#ifndef _PSP2_KERNEL_MODULEMGR_H_
#define _PSP2_KERNEL_MODULEMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/kernel/modulemgr.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceKernelGetModuleInfo(SceUID uid, SceKernelModuleInfo *info);
int sceKernelGetModuleList(SceUInt8 type, SceUID *uids, SceSize *num);

SceUID sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);
int sceKernelUnloadModule(SceUID modid, int flags, SceKernelULMOption *option);

int sceKernelStartModule(SceUID modid, SceSize args, void *argp, int flags, void *option, int *status);
int sceKernelStopModule(SceUID modid, SceSize args, void *argp, int flags, void *option, int *status);

SceUID sceKernelLoadStartModule(const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
int sceKernelStopUnloadModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

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

