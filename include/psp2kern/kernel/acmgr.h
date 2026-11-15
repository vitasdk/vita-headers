/**
 * \kernelgroup{SceSblACMgr}
 * \usage{psp2kern/kernel/acmgr.h,SceSblACMgrForDriver_stub SceSblACMgrForKernel_stub}
 *
 * Unless documented otherwise, a process ID of zero selects the current
 * process on FW 3.60.
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
 * @return SCE_OK on success, or 0x800F0916 if \a authid is NULL or the
 *         authentication information is unavailable.
 */
int ksceSblACMgrGetProcessProgramAuthId(SceUID pid, SceUInt64 *authid);

/**
 * @brief Get media type for input path.
 *
 * FW 3.60 matches a recognized prefix, skips any following decimal device
 * number, and then matches the path-class suffix when one is required. The
 * comparison is case-sensitive and does not inspect characters after the
 * matched suffix.
 *
 * @param[in] path - NUL-terminated path to classify.
 * @param[out] media_type - Receives one of ::SceSblACMgrMediaType.
 *
 * @return SCE_OK on success, 0x800F090E for a NULL argument, or 0x800F0903
 *         when no rule matches. On the no-match error, \a media_type receives
 *         ::SCE_SBL_ACMGR_MEDIA_TYPE_UX_USER.
 */
int ksceSblACMgrGetMediaType(const char *path, SceUInt32 *media_type);

/**
 * @brief Get development mode state
 *
 * @return If development mode, 1. else 0.
 */
int ksceSblACMgrIsDevelopmentMode(void);

/**
 * Media types produced by the FW 3.60 path classifier.
 *
 * In the path patterns below, `[n]` means zero or more decimal unit digits.
 * For example, both `os:` and the normal `os0:` form are accepted.
 * The path table does not produce media types 8, 9, 10, or 26.
 */
typedef enum SceSblACMgrMediaType {
	SCE_SBL_ACMGR_MEDIA_TYPE_UX_USER   = 0,  //!< `ux[n]:user` or `ux[n]:/user`.
	SCE_SBL_ACMGR_MEDIA_TYPE_SD        = 1,  //!< `sd[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_OS        = 2,  //!< `os[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_VS        = 3,  //!< `vs[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_VD        = 4,  //!< `vd[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_TM        = 5,  //!< `tm[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_UR        = 6,  //!< `ur[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_HOST      = 7,  //!< `host[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_UD        = 11, //!< `ud[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_UX        = 12, //!< Other paths beginning with `ux[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_GRO_APP   = 13, //!< `gro[n]:app` or `gro[n]:/app`.
	SCE_SBL_ACMGR_MEDIA_TYPE_GRW_PATCH = 14, //!< `grw[n]:patch` or `grw[n]:/patch`.
	SCE_SBL_ACMGR_MEDIA_TYPE_SA        = 15, //!< `sa[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_MFA       = 16, //!< `mfa[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_MFB       = 17, //!< `mfb[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_LMA       = 18, //!< `lma[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_LMB       = 19, //!< `lmb[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_LMC       = 20, //!< `lmc[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_LMD       = 21, //!< `lmd[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_PD        = 22, //!< `pd[n]:`.
	SCE_SBL_ACMGR_MEDIA_TYPE_UX_APP    = 23, //!< `ux[n]:app` or `ux[n]:/app`.
	SCE_SBL_ACMGR_MEDIA_TYPE_UX_PATCH  = 24, //!< `ux[n]:patch` or `ux[n]:/patch`.
	SCE_SBL_ACMGR_MEDIA_TYPE_UX_DATA   = 25, //!< `ux[n]:data` or `ux[n]:/data`.
	SCE_SBL_ACMGR_MEDIA_TYPE_UMA       = 27  //!< `uma[n]:`.
} SceSblACMgrMediaType;

/** Filesystem-attribute conversion request. */
typedef struct SceSblACMgrFsAttrInfo {
	int operation;         //!< Values 1-5 select ordinary filesystem attributes; 6 selects a PFS
	                       //!< attribute; 7-8 are unsupported by the mode-conversion functions.
	void *attribute;       //!< Caller-owned pointer to a ::SceUInt8 or ::SceUInt16 value,
	                       //!< selected by ::SceSblACMgrFsAttrInfo::attribute_size.
	SceSize attribute_size; //!< Attribute size in bytes. Use 1 or 2; other values can make FW 3.60
	                       //!< return success without writing anything.
} SceSblACMgrFsAttrInfo;
VITASDK_BUILD_ASSERT_EQ(0xC, SceSblACMgrFsAttrInfo); // size is from FW 3.60

/**
 * Convert a file mode to an access-controlled filesystem attribute.
 *
 * Operations 1-5 replace the low three bits of the existing output value.
 * For operations 1-5, mode 0x01000000 writes the value 0xF directly.
 * Other modes are mapped according to the calling thread's access level;
 * privileged attribute bit 2 is rejected outside access levels 0x40/0x80.
 *
 * Operation 6 writes a PFS attribute. It selects the restricted mapping for
 * target processes whose first capability word is 0x10 or 0x20, and the
 * privileged mapping for 0x40 or 0x80. Modes 0x00100000 and 0x00200000 are
 * accepted only by the privileged mapping and produce PFS attribute bits
 * 0x4000 and 0x2000 respectively. Use a two-byte value to preserve those
 * high PFS bits. Operations 7 and 8 return 0x800F0925.
 *
 * @param[in]     pid   - Target process ID (::ScePID).
 * @param[in,out] info - Attribute operation and output buffer.
 * @param[in]     mode  - File mode (::SceMode).
 *
 * @return SCE_OK on success; 0x800F0902 when an operation-6 mode has no
 *         mapping; 0x800F0903 if process authentication information is
 *         unavailable; 0x800F0916 for a NULL/invalid request; 0x800F0925 for
 *         operations 7-8; 0x800F0928 for an unsupported operation-6 process
 *         class; 0x8001000D when the selected attribute is forbidden; or
 *         0x80010016 when a mode/access-level mapping is invalid.
 */
int ksceSblACMgrConvertModeToFsAttribute(SceUID pid, SceSblACMgrFsAttrInfo *info, int mode);
int ksceSblACMgrConvertModeToFsAttribute2(SceUID pid, SceSblACMgrFsAttrInfo *info, int mode);

/**
 * Check capability bit 1 (system-program privilege).
 *
 * @param[in] pid - Target process ID (::ScePID).
 *
 * @return 1 if the capability is present, otherwise 0.
 */
int ksceSblACMgrIsSystemProgram2(SceUID pid);

/**
 * Get the media type selected by a path's device and path-class prefix.
 *
 * @param[in] path - NUL-terminated path to classify.
 * @param[out] media_type - Receives one of ::SceSblACMgrMediaType.
 *
 * @return SCE_OK on success, 0x800F090E for a NULL argument, or 0x800F0903
 *         when no rule matches. On the no-match error, \a media_type receives
 *         ::SCE_SBL_ACMGR_MEDIA_TYPE_UX_USER.
 */
int ksceSblACMgrGetMediaType2(const char *path, SceUInt32 *media_type);

/**
 * Get the program authority ID from the process self-authentication information.
 *
 * @param[in]  pid   - Target process ID (::ScePID).
 * @param[out] paid - Program authority ID.
 *
 * @return SCE_OK on success, or 0x800F0916 if \a paid is NULL or the
 *         authentication information is unavailable.
 */
int ksceSblACMgrGetPaid2(SceUID pid, SceUInt64 *paid);

/**
 * Test a process capability bit.
 *
 * Capability bits are numbered from 0 to 255 and stored most-significant bit
 * first within each byte. FW 3.60 does not bounds-check \a capability_bit;
 * callers must keep it in this range.
 *
 * Known values used by FW 3.60 include 0 (kernel program), 1 (system program),
 * 2 (game program), 3 (non-game program), 128 (Marlin), 129 (MagicGate),
 * 130 (UDCD/loopback mount), 131 (USB serial), 132 (virtual machine),
 * 133 (force-open message pipe), 134 (PlayReady system data), and 135
 * (system data).
 *
 * @param[in] pid           - Target process ID (::ScePID).
 * @param[in] capability_bit - Capability bit number.
 *
 * @return 1 if the capability is present, otherwise 0. Failure to obtain the
 *         process authentication information also returns 0.
 */
int ksceSblACMgrHasCapability(SceUID pid, int capability_bit);
int ksceSblACMgrHasCapability2(SceUID pid, int capability_bit);

/**
 * Return whether a process may create a loopback mount.
 *
 * FW 3.60 grants this to capability bit 130 or to PAID
 * 0x220000101CC73883, 0x2800000000000010, 0x280000000000001E, or
 * 0x2800000000000031.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when permitted, otherwise 0. Authentication lookup failure also
 *         returns 0.
 */
SceBool ksceSblACMgrIsAllowLoopBackMount(SceUID pid);
SceBool ksceSblACMgrIsAllowLoopBackMount2(SceUID pid);

/**
 * Return whether a process may use the USB serial interface.
 *
 * FW 3.60 grants access to capability bit 1, capability bit 131, and fSELF
 * processes when Utoken flag bit 1 is enabled.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when permitted, otherwise 0. Authentication lookup failure also
 *         returns 0.
 */
int ksceSblACMgrIsAllowUsbSerial(SceUID pid);
int ksceSblACMgrIsAllowUsbSerial2(SceUID pid);

/**
 * Return whether a process may use the virtual-machine facility.
 *
 * FW 3.60 grants access to capability bit 132 and to fSELF processes when
 * Utoken flag bit 1 is enabled.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when permitted, otherwise 0. Authentication lookup failure also
 *         returns 0.
 */
int ksceSblACMgrIsAllowVirtualMachine(SceUID pid);
int ksceSblACMgrIsAllowVirtualMachine2(SceUID pid);

/**
 * Return whether development DIP switch 159 is enabled.
 *
 * @return The value returned by ::ksceKernelCheckDipsw for switch 159.
 */
int ksceSblACMgrIsDevelopmentMode2(void);

/**
 * Return whether the PAID belongs to the 0x2F0 fSELF family.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when it belongs to the family, otherwise 0. Authentication lookup
 *         failure also returns 0.
 */
int ksceSblACMgrIsFself2(SceUID pid);

/**
 * Return whether the PAID belongs to the 0x210 game family or is the fSELF
 * game PAID 0x2F00000000000001.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for a matching PAID, otherwise 0. Authentication lookup failure
 *         also returns 0.
 */
int ksceSblACMgrIsGameProgram2(SceUID pid);

/**
 * Return whether a process may use the USB device controller.
 *
 * FW 3.60 grants this to capability bit 130, PAID 0x220000101CC73883,
 * and PAID 0x2800000000000010.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when permitted, otherwise 0. Authentication lookup failure also
 *         returns 0.
 */
SceBool ksceSblACMgrIsAllowUdcd(SceUID pid);
SceBool ksceSblACMgrIsAllowUdcd2(SceUID pid);

/**
 * Return whether capability bit 2 or capability bit 3 is present.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when either bit is present, otherwise 0. Authentication lookup
 *         failure also returns 0.
 */
int ksceSblACMgrIsNonGameOrGameProgram(SceUID pid);
int ksceSblACMgrIsNonGameOrGameProgram2(SceUID pid);

/**
 * Return whether capability bit 3 is present.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when the bit is present, otherwise 0. Authentication lookup
 *         failure also returns 0.
 */
int ksceSblACMgrIsNonGameProgram2(SceUID pid);

/**
 * Return whether a process may create a memory-stick work-directory mount.
 *
 * FW 3.60 grants this only to PAID 0x2800000000000001,
 * 0x2800000000000010, 0x2800000000000013, 0x2800000000000022,
 * 0x280000000000002D, 0x280000000000002E, 0x2800000000000039, or
 * 0x2800000000007009.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when permitted, otherwise 0. Authentication lookup failure also
 *         returns 0.
 */
SceBool ksceSblACMgrIsAllowMsMount(SceUID pid);
SceBool ksceSblACMgrIsAllowMsMount2(SceUID pid);

/**
 * Return whether a process belongs to the PlayStation Mobile program family.
 *
 * On FW 3.60 this includes PSM-family PAIDs
 * 0x210000101CD20007-0x210000101CD2000A, runtime PAID
 * 0x2800C0101CD2000B, and fSELF processes when Utoken flag bit 1 is enabled.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for a matching process, otherwise 0. Authentication lookup
 *         failure also returns 0.
 */
int ksceSblACMgrIsPSMProgram(SceUID pid);
int ksceSblACMgrIsPSMProgram2(SceUID pid);

/**
 * Return whether the PAID is in the PSM development-assistant range
 * 0x210000101CD20007-0x210000101CD20009.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for a matching PAID, otherwise 0. Authentication lookup failure
 *         also returns 0.
 */
int ksceSblACMgrIsPSMDevAssistantApp(SceUID pid);
int ksceSblACMgrIsPSMDevAssistantApp2(SceUID pid);

/**
 * Return whether the PAID is 0x210000101CD2000A or
 * 0x2800C0101CD2000B, the two FW 3.60 PSM runtime identities.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for a matching PAID, otherwise 0. Authentication lookup failure
 *         also returns 0.
 */
int ksceSblACMgrIsPSMRuntime(SceUID pid);
int ksceSblACMgrIsPSMRuntime2(SceUID pid);

/**
 * Return whether the PAID is 0x2800000000007009 or 0x2800000000000013.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for a matching PAID, otherwise 0. Authentication lookup failure
 *         also returns 0.
 */
int ksceSblACMgrIsPspEmu2(SceUID pid);

/**
 * Return whether capability bit 0 is present.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 when the bit is present, otherwise 0. Authentication lookup
 *         failure also returns 0.
 */
int ksceSblACMgrIsKernelProgram2(SceUID pid);

/**
 * Return whether the PAID is the SceShell PAID 0x2800000000000001.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for SceShell, otherwise 0. Authentication lookup failure also
 *         returns 0.
 */
int ksceSblACMgrIsSceShell2(SceUID pid);

/**
 * Return whether the PAID is in the updater-program range
 * 0x2800800000000000-0x280080000000000F.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for a matching PAID, otherwise 0. Authentication lookup failure
 *         also returns 0.
 */
int ksceSblACMgrIsUpdaterProgram(SceUID pid);
int ksceSblACMgrIsUpdaterProgram2(SceUID pid);

/**
 * Return whether the PAID is 0x2800000000008003 or
 * 0x2800000000008005, the WebCore/WebKit process identities on FW 3.60.
 *
 * @param[in] pid - Target process ID.
 *
 * @return 1 for a matching PAID, otherwise 0. Authentication lookup failure
 *         also returns 0.
 */
int ksceSblACMgrIsWebCoreOrWebKitProcess(SceUID pid);
int ksceSblACMgrIsWebCoreOrWebKitProcess2(SceUID pid);

/* Compatibility names used by previous VitaSDK headers. */
#define kscePfsACSetFSAttrByMode ksceSblACMgrConvertModeToFsAttribute2
#define ksceSblACIsSystemProgram ksceSblACMgrIsSystemProgram2
#define ksceSblACMgrSetFSAttributeByMode ksceSblACMgrConvertModeToFsAttribute
#define ksceSblACMgrSetFSAttributeByMode2 ksceSblACMgrConvertModeToFsAttribute2
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
#define ksceSblACMgrIsUpdaterUISetupperOrPkgInstallerSpawn ksceSblACMgrIsUpdaterProgram
#define ksceSblACMgrIsUpdaterUISetupperOrPkgInstallerSpawn2 ksceSblACMgrIsUpdaterProgram2
#define ksceSblACMgrIsRootProgram2 ksceSblACMgrIsKernelProgram2
#define ksceSblACMgrIsSIEApp ksceSblACMgrIsPSMDevAssistantApp
#define ksceSblACMgrIsSIEApp2 ksceSblACMgrIsPSMDevAssistantApp2

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SBLACMGR_H_ */
