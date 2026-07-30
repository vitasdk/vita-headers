/**
 * \kernelgroup{SceSblACMgr}
 * \usage{psp2kern/kernel/acmgr.h,SceSblACMgrForDriver_stub SceSblACMgrForKernel_stub}
 */

#ifndef _PSP2KERN_SBLACMGR_H_
#define _PSP2KERN_SBLACMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If root mode process, 1. else 0.
 */
int ksceSblACMgrIsRootProgram(SceUID pid);

#define ksceSblACMgrIsSystem(pid) ksceSblACMgrIsRootProgram(pid)

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If system mode process, 1. else 0.
 */
int ksceSblACMgrIsSystemProgram(SceUID pid);

#define ksceSblACMgrIsShell(pid) ksceSblACMgrIsSystemProgram(pid)

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If game mode process, 1. else 0.
 */
int ksceSblACMgrIsGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If non game mode process, 1. else 0.
 */
int ksceSblACMgrIsNonGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If pspemu process, 1. else 0.
 */
int ksceSblACMgrIsPspEmu(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If SceShell process(authid:0x2800000000000001), 1. else 0.
 */
int ksceSblACMgrIsSceShell(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If fake self process, 1. else 0.
 */
int ksceSblACMgrIsFself(SceUID pid);

/**
 * @brief Get process authority id
 *
 * @param[in]  pid    - The target process id
 * @param[out] authid - The authid output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblACMgrGetProcessProgramAuthId(SceUID pid, SceUInt64 *authid);

/**
 * @brief Get media type for input path.
 *
 * @param[in]        path - The target path
 * @param[out] media_type - The media type output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblACMgrGetMediaType(const char *path, SceUInt32 *media_type);

/**
 * @brief Get development mode state
 *
 * @return If development mode, 1. else 0.
 */
int ksceSblACMgrIsDevelopmentMode(void);

/**
 * Legacy type retained for backwards compatibility.
 *
 * FW 3.60 does not consume this type as a structure. It treats
 * ::SceSblACMgrFsAttrInfo::st_attr as a pointer to a scalar attribute value,
 * not as a pointer to an instance of this structure.
 */
typedef struct SceSblACMgrFsAttr {
	SceUInt32 st_attr;
	int unk_0x04;
} SceSblACMgrFsAttr;

typedef struct SceSblACMgrFsAttrInfo {
	int index;                  //!< Operation selector.
	SceSblACMgrFsAttr *st_attr; //!< Points to a ::SceUInt8 or ::SceUInt16 attribute value.
	SceSize size;               //!< Size of `st_attr`; must be 1 or 2.
} SceSblACMgrFsAttrInfo;
VITASDK_BUILD_ASSERT_EQ(0xC, SceSblACMgrFsAttrInfo); // size is from FW 3.60

/**
 * Convert a file mode to an access-controlled filesystem attribute.
 *
 * @param[in]     pid   - Process ID value of type ::ScePID.
 * @param[in,out] pInfo - Attribute operation and output buffer.
 * @param[in]     mode  - Value of type ::SceMode.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblACMgrSetFSAttributeByMode(SceUID pid, SceSblACMgrFsAttrInfo *pInfo, int mode);
int ksceSblACMgrSetFSAttributeByMode2(SceUID pid, SceSblACMgrFsAttrInfo *pInfo, int mode);

/**
 * Check capability bit 1 (system-program privilege).
 *
 * @param[in] pid - Process ID value of type ::ScePID.
 *
 * @return 1 if the capability is present, otherwise 0.
 */
int ksceSblACMgrIsSystemProgram2(SceUID pid);

int ksceSblACMgrGetMediaType2(const char *path, SceUInt32 *pMediaType);

/**
 * Get the program authority ID from the process self-authentication info.
 *
 * @param[in]  pid   - Process ID value of type ::ScePID.
 * @param[out] pPaid - Program authority ID.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblACMgrGetPaid2(SceUID pid, SceUInt64 *pPaid);

/**
 * Test a process capability bit.
 *
 * Capability bits are numbered from 0 to 255 and stored most-significant bit
 * first within each byte.
 *
 * @param[in] pid           - Process ID value of type ::ScePID.
 * @param[in] capabilityBit - Capability bit number.
 *
 * @return 1 if the capability is present, otherwise 0.
 */
int ksceSblACMgrHasCapability(SceUID pid, int capabilityBit);
int ksceSblACMgrHasCapability2(SceUID pid, int capabilityBit);

/** Return whether a process may create a loopback mount. */
SceBool ksceSblACMgrIsAllowLoopBackMount(SceUID pid);
SceBool ksceSblACMgrIsAllowLoopBackMount2(SceUID pid);

/**
 * Return whether a process may use the USB serial interface.
 *
 * FW 3.60 grants access to system programs, processes with capability bit 131,
 * and fSELF processes when the PSM test flag is enabled.
 */
int ksceSblACMgrIsAllowUsbSerial(SceUID pid);
int ksceSblACMgrIsAllowUsbSerial2(SceUID pid);

/** Return whether a process may use the virtual-machine facility. */
int ksceSblACMgrIsAllowVirtualMachine(SceUID pid);
int ksceSblACMgrIsAllowVirtualMachine2(SceUID pid);

int ksceSblACMgrIsDevelopmentMode2(void);
int ksceSblACMgrIsFself2(SceUID pid);
int ksceSblACMgrIsGameProgram2(SceUID pid);

/** Return whether a process may use the USB device controller. */
SceBool ksceSblACMgrIsAllowUdcd(SceUID pid);
SceBool ksceSblACMgrIsAllowUdcd2(SceUID pid);

int ksceSblACMgrIsNonGameOrGameProgram(SceUID pid);
int ksceSblACMgrIsNonGameOrGameProgram2(SceUID pid);
int ksceSblACMgrIsNonGameProgram2(SceUID pid);

/** Return whether a process may create a memory-stick work-directory mount. */
SceBool ksceSblACMgrIsAllowMsMount(SceUID pid);
SceBool ksceSblACMgrIsAllowMsMount2(SceUID pid);

/**
 * Return whether a process belongs to the PlayStation Mobile program family.
 *
 * On FW 3.60 this includes the PSM development-assistant and runtime PAIDs,
 * plus fSELF processes when the PSM test flag is enabled.
 */
int ksceSblACMgrIsPSMProgram(SceUID pid);
int ksceSblACMgrIsPSMProgram2(SceUID pid);

/** Return whether a process is a PSM development-assistant application. */
int ksceSblACMgrIsPSMDevAssistantApp(SceUID pid);
int ksceSblACMgrIsPSMDevAssistantApp2(SceUID pid);

int ksceSblACMgrIsPSMRuntime(SceUID pid);
int ksceSblACMgrIsPSMRuntime2(SceUID pid);
int ksceSblACMgrIsPspEmu2(SceUID pid);
int ksceSblACMgrIsKernelProgram2(SceUID pid);
int ksceSblACMgrIsSceShell2(SceUID pid);
int ksceSblACMgrIsUpdaterUISetupperOrPkgInstallerSpawn(SceUID pid);
int ksceSblACMgrIsUpdaterUISetupperOrPkgInstallerSpawn2(SceUID pid);
int ksceSblACMgrIsWebCoreOrWebKitProcess(SceUID pid);
int ksceSblACMgrIsWebCoreOrWebKitProcess2(SceUID pid);

/* Compatibility names used by previous VitaSDK headers. */
#define kscePfsACSetFSAttrByMode ksceSblACMgrSetFSAttributeByMode2
#define ksceSblACIsSystemProgram ksceSblACMgrIsSystemProgram2
#define ksceSblACMgrGetProcessProgramAuthId2 ksceSblACMgrGetPaid2
#define ksceSblACMgrIsAllowedExtendedMemory ksceSblACMgrIsAllowLoopBackMount
#define ksceSblACMgrIsAllowedExtendedMemory2 ksceSblACMgrIsAllowLoopBackMount2
#define ksceSblACMgrIsAllowedUsbSerial ksceSblACMgrIsAllowUsbSerial
#define ksceSblACMgrIsAllowedVirtualMachine ksceSblACMgrIsAllowVirtualMachine
#define ksceSblACMgrIsAllowedVirtualMachine2 ksceSblACMgrIsAllowVirtualMachine2
#define ksceSblACMgrIsMiniSettingsForQA ksceSblACMgrIsAllowUdcd
#define ksceSblACMgrIsMiniSettingsForQA2 ksceSblACMgrIsAllowUdcd2
#define ksceSblACMgrIsNotSandboxed ksceSblACMgrIsAllowMsMount
#define ksceSblACMgrIsNotSandboxed2 ksceSblACMgrIsAllowMsMount2
#define ksceSblACMgrIsPSMDevAssistant ksceSblACMgrIsPSMProgram
#define ksceSblACMgrIsPSMDevAssistant2 ksceSblACMgrIsPSMProgram2
#define ksceSblACMgrIsRootProgram2 ksceSblACMgrIsKernelProgram2
#define ksceSblACMgrIsSIEApp ksceSblACMgrIsPSMDevAssistantApp
#define ksceSblACMgrIsSIEApp2 ksceSblACMgrIsPSMDevAssistantApp2

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SBLACMGR_H_ */
