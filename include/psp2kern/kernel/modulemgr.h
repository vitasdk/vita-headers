/**
 * \kernelgroup{SceModulemgr}
 * \usage{psp2kern/kernel/modulemgr.h,SceModulemgrForKernel_stub}
 */

#ifndef _PSP2KERN_KERNEL_MODULEMGR_H_
#define _PSP2KERN_KERNEL_MODULEMGR_H_

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

typedef enum SceKernelModuleState {
    SCE_KERNEL_MODULE_STATE_READY   = 0x00000002,
    SCE_KERNEL_MODULE_STATE_STARTED = 0x00000006,
    SCE_KERNEL_MODULE_STATE_ENDED   = 0x00000009
} SceKernelModuleState;

typedef struct SceKernelModuleName {
  char s[0x1C];
} SceKernelModuleName;

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

typedef struct {
  SceSize size;
} SceKernelLMOption;

typedef struct {
  SceSize size;
} SceKernelULMOption;

typedef struct {
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
  SceSize segments_num;
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

typedef struct SceKernelModuleLibraryInfo {
  SceSize size; //!< sizeof(SceKernelModuleLibraryInfo) : 0x120
  SceUID library_id;
  uint32_t libnid;
  uint16_t version;
  uint16_t flags;
  uint16_t entry_num_function;
  uint16_t entry_num_variable;
  uint16_t unk_0x14;
  uint16_t unk_0x16;
  char library_name[0x100];
  SceSize number_of_imported;
  SceUID modid2;
} SceKernelModuleLibraryInfo;

/**
 * @brief Register syscall function
 *
 * @param[in] syscall_id - register syscall id (Must be less than 0x1000)
 * @param[in] func       - syscall function
 *
 * @return none
 */
void ksceKernelRegisterSyscall(SceSize syscall_id, const void *func);

/**
 * @brief Setup kernel for modulemgr
 *
 * @note - allocate and initialize syscall table
 *
 * @return none
 */
void ksceKernelRegisterModulesAfterBoot(void);

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
int ksceKernelGetModuleList(SceUID pid, int flags1, int flags2, SceUID *modids, SceSize *num);

/**
 * @par Example1: Get max to 10 kernel module info
 * @code
 * SceKernelModuleListInfo infolists[10];
 * size_t num = 10;// Get max
 * uint32_t offset = 0;
 * SceKernelModuleListInfo *info = &infolists[0];
 *
 * ksceKernelGetModuleInfoForDebugger(0x10005, infolists, &num);
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
int ksceKernelGetModuleInfoForDebugger(SceUID pid, SceKernelModuleListInfo *infolists, SceSize *num);

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
 * @param[in]  modid - target module id
 * @param[out] info  - module_info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleCB(SceUID modid, void **info);

/**
 * @brief Get module info by address (internal)
 *
 * @param[in]  pid         - target process id
 * @param[in]  module_addr - target module address
 * @param[out] info        - module_info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleCBByAddr(SceUID pid, const void *module_addr, void **info);

/**
 * @brief Get module id by module address
 *
 * @param[in] pid         - target pid
 * @param[in] module_addr - target module address
 *
 * @return modid on success, < 0 on error.
 */
SceUID ksceKernelGetModuleIdByAddrForDebugger(SceUID pid, const void *module_addr);

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
 * @brief Get the main module id for a given process.
 * @param pid The process to query.
 * @return the UID of the module else < 0 for an error.
 */
SceUID ksceKernelGetModuleIdByPid(SceUID pid);

/**
 * @brief Get the module path
 *
 * @param[in]  pid     - target pid
 * @param[out] path    - module path output
 * @param[in]  pathlen - path output max len
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModulePath(SceUID modid, char *path, SceSize pathlen);

/**
 * @brief Get library info
 *
 * @param[in]  pid   - target pid
 * @param[in]  modid - target library id
 * @param[out] info  - info output
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetLibraryInfoForDebugger(SceUID pid, SceUID library_id, SceKernelModuleLibraryInfo *info);


#define ksceKernelGetModuleInternal ksceKernelGetModuleCB
#define ksceKernelGetProcessMainModule ksceKernelGetModuleIdByPid


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_MODULEMGR_H_ */
