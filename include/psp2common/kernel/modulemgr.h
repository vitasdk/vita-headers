/**
 * \kernelgroup{SceModulemgr}
 * \usage{psp2common/kernel/modulemgr.h}
 */

#ifndef _PSP2COMMON_KERNEL_MODULEMGR_H_
#define _PSP2COMMON_KERNEL_MODULEMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

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
VITASDK_BUILD_ASSERT_EQ(4, SceKernelPreloadInhibit);


typedef struct SceKernelSegmentInfo {
  SceSize size;   //!< this structure size (0x18)
  SceUInt perms;  //!< probably rwx in low bits
  void *vaddr;    //!< address in memory
  SceSize memsz;  //!< size in memory
  SceSize filesz; //!< original size of memsz
  SceUInt res;    //!< unused
} SceKernelSegmentInfo;
VITASDK_BUILD_ASSERT_EQ(0x18, SceKernelSegmentInfo);

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
VITASDK_BUILD_ASSERT_EQ(0x1B8, SceKernelModuleInfo);

typedef struct {
  SceSize size;
} SceKernelLMOption;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelLMOption);

typedef struct {
  SceSize size;
} SceKernelULMOption;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelULMOption);

typedef struct SceKernelSystemSwVersion {
	SceSize size;
	char versionString[0x1C];
	SceUInt version;
	SceUInt unk_24;
} SceKernelSystemSwVersion;
VITASDK_BUILD_ASSERT_EQ(0x28, SceKernelSystemSwVersion);

/* For backward compatibility */
typedef SceKernelSystemSwVersion SceKernelFwInfo;

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
VITASDK_BUILD_ASSERT_EQ(0x120, SceKernelModuleLibraryInfo);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_MODULEMGR_H_ */
