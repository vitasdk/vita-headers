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

typedef struct {
  char module_name[0x1C];
} SceKernelModuleName;

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
  char versionString[0x1C];
  SceUInt version;
  SceUInt unk_24;
} SceKernelFwInfo;

typedef struct {
  SceSize size; //!< sizeof(SceKernelSegmentInfo2) (0x14)
  int perm;
  void *vaddr;
  uint32_t memsz;
  int unk_10;
} SceKernelSegmentInfo2;

typedef struct {
  SceSize size;
  SceUID modid;
  uint32_t version;
  uint32_t module_version;
  uint32_t unk10;
  void *unk14;
  uint32_t unk18;
  void *unk1C;
  void *unk20;
  char module_name[28];
  uint32_t unk40;
  uint32_t unk44;
  uint32_t nid;
  int segments_num;
  union {
    struct {
      SceKernelSegmentInfo2 SegmentInfo[1];
      uint32_t addr[4];
    } seg1;
    struct {
      SceKernelSegmentInfo2 SegmentInfo[2];
      uint32_t addr[4];
    } seg2;
    struct {
      SceKernelSegmentInfo2 SegmentInfo[3];
      uint32_t addr[4];
    } seg3;
    struct {
      SceKernelSegmentInfo2 SegmentInfo[4];
      uint32_t addr[4];
    } seg4;
  };
} SceKernelModuleListInfo;

typedef struct {
  SceSize size; //!< sizeof(SceKernelModuleInfo2) : 0x120
  SceUID modid1;
  uint32_t unk_0x08;
  uint16_t unk_0x0C;
  uint16_t unk_0x0E;
  uint16_t unk_0x10;
  uint16_t unk_0x12;
  uint16_t unk_0x14;
  uint16_t unk_0x16;
  char module_name[0x100]; // offset : 0x18
  uint32_t unk_0x118;
  SceUID modid2;
} SceKernelModuleInfo2;

/**
 * @brief Register syscall function
 *
 * @param[in] syscall_id - register syscall id (Must be less than 0x1000)
 * @param[in] func       - syscall function
 *
 * @return none
 */
void ksceKernelRegisterSyscall(int syscall_id, const void *func);

/**
 * @brief Setup kernel for modulemgr
 *
 * @note - allocate and initialize syscall table
 *
 * @return none
 */
void ksceKernelSetupForModulemgr(void);

/**
 * @brief Get module id list
 *
 * @param[in]    pid    - target pid
 * @param[in]    flags1 - unknown, use 0x7FFFFFFF
 * @param[in]    flags2 - unknown, use 1
 * @param[out]   modids - info output pointer
 * @param[inout] num    - in:list max num, out:get modid num
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleList(SceUID pid, int flags1, int flags2, SceUID *modids, size_t *num);

/**
 * @par Example1: Get max to 10 kernel module info
 * @code
 * SceKernelModuleListInfo infolists[10];
 * size_t num = 10;// Get max
 * uint32_t offset = 0;
 * SceKernelModuleListInfo *info = &infolists[0];
 *
 * ksceKernelGetModuleList2(0x10005, infolists, &num);
 *
 * for(int i=0;i<num;i++){
 *   printf("name : %s\n", info->module_name);
 *
 *   if(info->segments_num == 1){
 *     printf("vaddr:0x%08X\n", info->seg1.SegmentInfo[0].vaddr);
 *   }else if(info->segments_num == 2){
 *     printf("vaddr:0x%08X\n", info->seg2.SegmentInfo[0].vaddr);
 *   }
 *   info = ((char *)info) + info->size;
 * }
 * @endcode
 *
 * @param[in]    pid       - target pid
 * @param[out]   infolists - infolists output
 * @param[inout] num       - Specify the maximum number of modinfolist to retrieve. If the function returns 0, it returns the number of modules loaded in the target pid in num
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleList2(SceUID pid, SceKernelModuleListInfo *infolists, size_t *num);

/**
 * @brief Get module info
 *
 * @param[in]  pid   - target pid
 * @param[in]  modid - target module id
 * @param[out] info  - info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleInfo(SceUID pid, SceUID modid, SceKernelModuleInfo *info);

/**
 * @brief Get module info2
 *
 * @param[in]  pid   - target pid
 * @param[in]  modid - target module id
 * @param[out] info  - info output
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleInfo2(SceUID pid, SceUID modid, SceKernelModuleInfo2 *info);

/**
 * @brief Get module info mini by module address
 *
 * @param[in]  pid               - target pid
 * @param[in]  module_addr       - target module address, Also possible with data segment address
 * @param[out] module_nid        - can also set NULL, module nid output
 * @param[out] program_text_addr - can also set NULL, program text addr output
 * @param[out] module_name       - can also set NULL, module name output
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleInfoMinByAddr(SceUID pid, const void *module_addr, uint32_t *module_nid, const void **program_text_addr, SceKernelModuleName *module_name);

/**
 * @brief Get module info (internal)
 *
 * @param[in]  modid       - target module id
 * @param[out] module_info - module_info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleInternal(SceUID modid, void **module_info);

/**
 * @brief Get module id by module address
 *
 * @param[in] pid         - target pid
 * @param[in] module_addr - target module address
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelGetModuleIdByAddr(SceUID pid, const void *module_addr);

/**
 * @brief search kernel module by module name
 *
 * @param[in] module_name - target module name
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelSearchModuleByName(const char *module_name);

/**
 * @brief Get fw info
 *
 * @param[out] data - fw info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetSystemSwVersion(SceKernelFwInfo *data);

/**
 * @brief load module (kernel only)
 *
 * @param[in] path   - module path
 * @param[in] flags  - unknown, set zero
 * @param[in] option - unknown
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);

/**
 * @brief start module (kernel only)
 *
 * @param[in]  modid  - target module id
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStartModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);

/**
 * @brief load and start module (kernel only)
 *
 * @param[in]  path   - module path
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelLoadStartModule(const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);

/**
 * @brief stop module (kernel only)
 *
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStopModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

/**
 * @brief unload module (kernel only)
 *
 * @param[in]  modid  - target module id
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelUnloadModule(SceUID modid, int flags, SceKernelULMOption *option);

/**
 * @brief stop and unload module (kernel only)
 *
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStopUnloadModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

/**
 * @brief load module
 *
 * @param[in]  pid    - target pid
 * @param[in]  path   - module path
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelLoadModuleForPid(SceUID pid, const char *path, int flags, SceKernelLMOption *option);

/**
 * @brief start module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStartModuleForPid(SceUID pid, SceUID modid, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);

/**
 * @brief load and start module
 *
 * @param[in]  pid    - target pid
 * @param[in]  path   - module path
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelLoadStartModuleForPid(SceUID pid, const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);

/**
 * @brief stop module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStopModuleForPid(SceUID pid, SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

/**
 * @brief unload module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelUnloadModuleForPid(SceUID pid, SceUID modid, int flags, SceKernelULMOption *option);

/**
 * @brief stop and unload module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStopUnloadModuleForPid(SceUID pid, SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

/**
 * @brief load and start module as shared module
 *
 * @param[in]  pid    - target pid
 * @param[in]  path   - module path
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelLoadStartSharedModuleForPid(SceUID pid, const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);

/**
 * @brief stop and unload module as shared module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStopUnloadSharedModuleForPid(SceUID pid, SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

/**
 * @brief mount bootfs (load bootfs module)
 *
 * @param[in] bootImagePath - bootfs module path
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMountBootfs(const char *bootImagePath);

/**
 * @brief unmount bootfs (unload bootfs module)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelUmountBootfs(void);

/**
 * @brief Get the main module for a given process.
 * @param pid The process to query.
 * @return the UID of the module else < 0 for an error.
 */
SceUID ksceKernelGetProcessMainModule(SceUID pid);

/**
 * @brief Get the main module path for a given process.
 *
 * @param[in]  pid     - target pid
 * @param[out] path    - module path output
 * @param[in]  pathlen - path output max len
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetProcessMainModulePath(SceUID pid, char *path, int pathlen);

int ksceKernelGetModuleLibraryInfo(SceUID pid, SceUID modid, void *unk1, const void *unk2, int unk3);
int ksceKernelGetModuleUid(SceUID pid, SceUID modid, SceUID *modid_out, const void *unk1, int unk2);
int ksceKernelGetModuleUidList(SceUID pid, SceUID *modids, size_t *num);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_MODULEMGR_H_ */
