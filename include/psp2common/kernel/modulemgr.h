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

#define SCE_MODULE_ATTR_NONE        (0x0000)
#define SCE_KERNEL_MODULE_ATTR_NONE SCE_MODULE_ATTR_NONE

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

typedef struct SceKernelStartModuleOpt {
	SceSize size; //!< Size of this structure.
	SceUInt32 reserved[3]; //!< Copied from user memory but unused on FW 3.60; initialize to 0.
} SceKernelStartModuleOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceKernelStartModuleOpt); // size is from FW 3.60

typedef struct SceKernelStopModuleOpt {
	SceSize size; //!< Size of this structure.
	SceUInt32 reserved[3]; //!< Copied from user memory but unused on FW 3.60; initialize to 0.
} SceKernelStopModuleOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceKernelStopModuleOpt); // size is from FW 3.60

typedef struct SceKernelSegmentInfo {
	SceSize size;      //!< Size of this structure.
	SceUInt perms;     //!< Access-permission byte combined with a loader metadata byte shifted left by 20 on FW 3.60.
	void *vaddr;       //!< Segment virtual address.
	SceSize memsz;     //!< Segment size in memory.
	SceSize filesz;    //!< Segment size in the module file.
	SceUInt reserved;  //!< Left unchanged by the FW 3.60 kernel APIs.
} SceKernelSegmentInfo;
VITASDK_BUILD_ASSERT_EQ(0x18, SceKernelSegmentInfo);

/**
 * Information about a loaded module.
 *
 * The FW 3.60 kernel APIs use this fixed 0x1B8-byte layout, but do not clear
 * the output buffer or write every reserved byte. Before calling these kernel
 * APIs, zero the entire structure and initialize \a size. The user function
 * ::sceKernelGetModuleInfo does this internally.
 */
typedef struct SceKernelModuleInfo {
	SceSize size;                       //!< Size of this structure; left unchanged by the FW 3.60 kernel APIs.
	SceUID modid;                       //!< Module identifier.
	uint16_t modattr;                   //!< Module attributes.
	uint8_t  modver[2];                 //!< Module version.
	char module_name[28];               //!< Module name; zero the structure first to ensure NUL termination.
	SceUInt reserved;                   //!< Left unchanged by the FW 3.60 kernel APIs.
	void *start_entry;                  //!< Module start entry point.
	void *stop_entry;                   //!< Module stop entry point.
	void *exit_entry;                   //!< Module exit entry point.
  void *exidx_top;                    //!< Start of the ARM exception index table.
  void *exidx_btm;                    //!< End of the ARM exception index table.
  void *extab_top;                    //!< Start of the ARM exception table.
  void *extab_btm;                    //!< End of the ARM exception table.
  void *tlsInit;                      //!< TLS initialization image.
  SceSize tlsInitSize;                //!< Size of the TLS initialization image.
  SceSize tlsAreaSize;                //!< Total TLS area size.
	char path[256];                     //!< Module path.
	SceKernelSegmentInfo segments[4];   //!< Information for up to four mapped segments.
  SceUInt state;                      //!< One of ::SceKernelModuleState.
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
  union {
    SceSize client_count; //!< Number of modules importing this library.
    SceSize number_of_imported; //!< Legacy name for ::client_count.
  };
  union {
    SceUID owner_module_id; //!< ID of the module that owns the library.
    SceUID modid2; //!< Legacy name for ::owner_module_id.
  };
} SceKernelModuleLibraryInfo;
VITASDK_BUILD_ASSERT_EQ(0x120, SceKernelModuleLibraryInfo);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_MODULEMGR_H_ */
