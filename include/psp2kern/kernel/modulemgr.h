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

typedef struct{
  SceSize size; //!< sizeof(SceKernelSegmentInfo2) (0x14)
  int perm;
  void *vaddr;
  uint32_t memsz;
  int unk_10;
}SceKernelSegmentInfo2;

struct SceKernelModuleListInfoType1{
  SceSize size; //!< sizeof(SceKernelModuleListInfoType1) (0x74)
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
  SceKernelSegmentInfo2 SegmentInfo[1];
  uint32_t addr[4];
};

struct SceKernelModuleListInfoType2{
  SceSize size; //!< sizeof(SceKernelModuleListInfoType2) (0x88)
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
  SceKernelSegmentInfo2 SegmentInfo[2];
  uint32_t addr[4];
};

struct SceKernelModuleListInfoType3{
  SceSize size; //!< sizeof(SceKernelModuleListInfoType3) (0x9C)
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
  SceKernelSegmentInfo2 SegmentInfo[3];
  uint32_t addr[4];
};

struct SceKernelModuleListInfoType4{
  SceSize size; //!< sizeof(SceKernelModuleListInfoType4) (0xB0)
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
  SceKernelSegmentInfo2 SegmentInfo[4];
  uint32_t addr[4];
};

typedef union{
  SceSize size;
  struct SceKernelModuleListInfoType1 type1;
  struct SceKernelModuleListInfoType2 type2;
  struct SceKernelModuleListInfoType3 type3;
  struct SceKernelModuleListInfoType4 type4;
} SceKernelModuleListInfo;

typedef struct
{
  SceSize size; //!< sizeof(SceKernelModuleInfo2)
  SceUID modid1;
  uint32_t unk1;
  uint32_t unk2;
  uint32_t unk3;
  uint32_t unk4;
  char module_name[256];
  uint32_t unk5;
  SceUID modid2;
} SceKernelModuleInfo2;

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

/**
 * @par Example1: Get max to 10 kernel module info
 * @code
 * char infolists[sizeof(SceKernelModuleListInfo) * 10];
 * size_t num = 10;// Get max
 * uint32_t offset = 0;
 * SceKernelModuleListInfo *info;
 * ret = ksceKernelGetModuleList2(0x10005, infolists, &num);
 *
 * for(int i=0;i<num;i++){
 *   info = (SceKernelModuleListInfo*)(infolists+offset);
 *   if( info->size == sizeof(struct SceKernelModuleListInfoType1) ) {
 *     printf("name %s\n", info->type1.module_name);
 *     printf("nid 0x%X\n", info->type1.nid);
 *   }else if( info->size == sizeof(struct SceKernelModuleListInfoType2) ) {
 *     printf("name %s\n", info->type2.module_name);
 *     printf("nid 0x%X\n", info->type2.nid);
 *   }else if( info->size == sizeof(struct SceKernelModuleListInfoType3) ) {
 *     printf("name %s\n", info->type3.module_name);
 *     printf("nid 0x%X\n", info->type3.nid);
 *   }else if( info->size == sizeof(struct SceKernelModuleListInfoType4) ) {
 *     printf("name %s\n", info->type4.module_name);
 *     printf("nid 0x%X\n", info->type4.nid);
 *   }
 *   offset += info->size;
 * }
 * @endcode
 *
 * @param[in] pid - target pid
 * @param[out] infolists - infolists output
 * @param[in] num - Specify the maximum number of modinfolist to retrieve. If the function returns 0, it returns the number of modules loaded in the target pid in num
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleList2(SceUID pid, void *infolists, size_t *num);

/**
 * @param[in] pid - target pid
 * @param[in] modid - target modid
 * @param[out] info - info output
 * @param[in] unk1 - set 0x120
 * @param[in] unk2 - set 0x120
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetModuleInfo2(SceUID pid, SceUID modid, SceKernelModuleInfo2 *info, int unk1, int unk2);

int ksceKernelGetModuleLibraryInfo(SceUID pid, SceUID modid, void *unk1, const void *unk2, int unk3);
int ksceKernelGetModuleUid(SceUID pid, SceUID modid, SceUID *modid_out, const void *unk1, int unk2);
int ksceKernelGetModuleUidList(SceUID pid, SceUID *modids, size_t *num);
int ksceKernelGetProcessMainModulePath(SceUID pid, char *path, int pathlen);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_MODULEMGR_H_ */
