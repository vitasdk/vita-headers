/**
 * \kernelgroup{SceModulemgr}
 * \usage{psp2kern/kernel/modulemgr.h,SceModulemgrForKernel_stub}
 */


#ifndef _PSP2_KERNEL_MODULEMGR_H_
#define _PSP2_KERNEL_MODULEMGR_H_

#include <psp2kern/types.h>

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

typedef struct
{
  SceUInt size;   //!< this structure size (0x18)
  SceUInt perms;  //!< probably rwx in low bits
  void *vaddr;    //!< address in memory
  SceUInt memsz;  //!< size in memory
  SceUInt flags;  //!< meaning unknown
  SceUInt res;    //!< unused?
} SceKernelSegmentInfo;

typedef struct
{
  SceUInt size;   //!< 0x1B8 for Vita 1.x
  SceUInt handle; //!< kernel module handle?
  SceUInt flags;  //!< some bits. could be priority or whatnot
  char module_name[28];
  SceUInt unk28;
  void *module_start;
  SceUInt unk30;
  void *module_stop;
  void *exidxTop;
  void *exidxBtm;
  SceUInt unk40;
  SceUInt unk44;
  void *tlsInit;
  SceSize tlsInitSize;
  SceSize tlsAreaSize;
  char path[256];
  SceKernelSegmentInfo segments[4];
  SceUInt type;   //!< 6 = user-mode PRX?
} SceKernelModuleInfo;

typedef struct {
  SceSize size;
} SceKernelLMOption;

typedef struct {
  SceSize size;
} SceKernelULMOption;

typedef struct
{
  SceSize size;
  char versionString[16];
  SceUInt unk_14;
  SceUInt unk_18;
  SceUInt unk_1C;
  SceUInt version;
  SceUInt unk_24;
} SceKernelFwInfo;

int ksceKernelGetModuleList(SceUID pid, int flags1, int flags2, SceUID *modids, size_t *num);
int ksceKernelGetModuleInfo(SceUID pid, SceUID modid, SceKernelModuleInfo *info);
int ksceKernelGetModuleInternal(SceUID modid, void **module);

int ksceKernelGetSystemSwVersion(SceKernelFwInfo *data);

int ksceKernelLoadStartModule(const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
SceUID ksceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);
int ksceKernelStartModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
int ksceKernelUnloadModule(SceUID modid, int flags, SceKernelULMOption *option);
int ksceKernelStopModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);
int ksceKernelStopUnloadModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

SceUID ksceKernelLoadStartSharedModuleForPid(SceUID pid, const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
SceUID ksceKernelLoadStartModuleForPid(SceUID pid, const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
int ksceKernelStartModuleForPid(SceUID pid, SceUID modid, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
SceUID ksceKernelLoadModuleForPid(SceUID pid, const char *path, int flags, SceKernelLMOption *option);
SceUID ksceKernelUnloadModuleForPid(SceUID pid, SceUID modid, int flags, SceKernelULMOption *option);
int ksceKernelStopModuleForPid(SceUID pid, SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);
int ksceKernelStopUnloadModuleForPid(SceUID pid, SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

int ksceKernelMountBootfs(const char *bootImagePath);
int ksceKernelUmountBootfs(void);

int ksceKernelSearchModuleByName(const char *module_name, const char *path, int pid);

/**
 * @brief Get the main module for a given process.
 * @param pid The process to query.
 * @return the UID of the module else < 0 for an error.
 */
SceUID ksceKernelGetProcessMainModule(SceUID pid);

typedef struct{
	uint32_t size; // sizeof(SceKernelLoadedModuleInfo)
	SceUID modid;
	uint32_t version;
	uint32_t unkC;
	uint32_t unk10;
	uint32_t unk14;
	uint32_t unk18;
	uint32_t unk1C;
	uint32_t unk20;
	char module_name[28];
	uint32_t unk40;
	uint32_t unk44;
	uint32_t unk48;
	uint32_t unk4C;
	uint32_t unk50;
	uint32_t unk54;
	uint32_t unk58;
	uint32_t unk5C;
	uint32_t unk60;
	uint32_t unk64;
	uint32_t unk68;
	uint32_t unk6C;
	uint32_t unk70;
	uint32_t unk74;
	uint32_t unk78;
	uint32_t unk7C;
	uint32_t unk80;
	uint32_t unk84;
} SceKernelLoadedModuleInfo;

typedef struct{
	uint32_t size; // sizeof(SceKernelModuleInfo2)
	SceUID modid1;
	uint32_t unk1;
	uint32_t unk2;
	uint32_t unk3;
	uint32_t unk4;
	char module_name[0x100];
	uint32_t unk6;
	SceUID modid2;
} SceKernelModuleInfo2;

/**
 * @par Example1: Acquire max to 10 module info
 * @code
 * SceKernelLoadedModuleInfo infolists[10];
 * size_t num = 10;// Get max
 * ret = ksceKernelGetModuleList2(pid, infolists, &num);
 * @endcode
 *
 * @param[in] pid
 * @param[out] infolists
 * @param[in&out] num - Specify the maximum number of modinfolist to retrieve.
 *                      If the function returns 0, it returns the number of modules loaded in the target pid in num
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleList2(SceUID pid, SceKernelLoadedModuleInfo *infolists, size_t *num);

/**
 * @param[in] pid
 * @param[in] modid
 * @param[out] info
 * @param[in] unk1 - set 0x120
 * @param[in] unk2 - set 0x120
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleInfo2(SceUID pid, SceUID modid, SceKernelModuleInfo2 *info, int unk1, int unk2);

int ksceKernelGetModuleLibraryInfo(SceUID pid, SceUID modid, void *unk1, const void *unk2, int unk3);
int ksceKernelGetModuleUid(SceUID pid, SceUID modid, int *modid_out, const void *unk1, int unk2);
int ksceKernelGetModuleUidList(SceUID pid, SceUID *modids, size_t *num);
int ksceKernelGetProcessMainModulePath(SceUID pid, char *path, int pathlen);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_MODULEMGR_H_ */

