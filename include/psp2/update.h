/**
 * \usergroup{SceSblSsUpdateMgr}
 * \usage{psp2/update.h,SceSblUpdateMgr_stub}
 *
 * Every function in this header requires system-program privilege on FW 3.60.
 */

#ifndef _PSP2_UPDATE_H_
#define _PSP2_UPDATE_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef char SceUpdateMode;
VITASDK_BUILD_ASSERT_EQ(1, SceUpdateMode);

#define SCE_UPDATE_MODE_SWU_GUI 0x10
#define SCE_UPDATE_MODE_SWU_CUI 0x30

/**
 * Getting system update mode on boot
 *
 * @param[out] mode - The pointer of SceUpdateMode variable
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetUpdateMode(SceUpdateMode *mode);

#define sceSblSsUpdateMgrGetBootMode sceSblUsGetUpdateMode

/**
 * Setting system update mode on boot
 *
 * @param[in] mode - The update mode
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetUpdateMode(SceUpdateMode mode);

#define sceSblSsUpdateMgrSetBootMode sceSblUsSetUpdateMode

/**
 * Verify PUP
 *
 * @param[in] path - The PUP path
 *
 * @return 0 on success, < 0 on error.
 *
 * note - If verify CEX PUP on Devkit system, got error.
 */
int sceSblUsVerifyPup(const char *path);

/**
 * Secure-package component types accepted on FW 3.60.
 *
 * Types 3, 4, and 27 support extraction only. Types 10, 21, 22, 23, and 28
 * support inspection, update, and extraction. The other values declared here
 * support inspection and update. Other numeric package types are rejected.
 */
typedef enum SceSblUsSpackageType {
	SCE_SBL_US_SPACKAGE_TYPE_OS0                   = 1,
	SCE_SBL_US_SPACKAGE_TYPE_UNKNOWN_3             = 3,
	SCE_SBL_US_SPACKAGE_TYPE_UNKNOWN_4             = 4,
	SCE_SBL_US_SPACKAGE_TYPE_SYSCON_9A54           = 8,
	SCE_SBL_US_SPACKAGE_TYPE_SLB2                  = 9,
	SCE_SBL_US_SPACKAGE_TYPE_VS0                   = 10,
	SCE_SBL_US_SPACKAGE_TYPE_CP_FIRMWARE           = 11,
	SCE_SBL_US_SPACKAGE_TYPE_MOTION_FIRMWARE_0     = 12,
	SCE_SBL_US_SPACKAGE_TYPE_BBMC_FIRMWARE         = 13,
	SCE_SBL_US_SPACKAGE_TYPE_MOTION_FIRMWARE_1     = 15,
	SCE_SBL_US_SPACKAGE_TYPE_TOUCH_FIRMWARE        = 16,
	SCE_SBL_US_SPACKAGE_TYPE_TOUCH_CONFIGURATION   = 17,
	SCE_SBL_US_SPACKAGE_TYPE_BIC_FIRMWARE          = 18,
	SCE_SBL_US_SPACKAGE_TYPE_BIC_DATA_FLASH        = 19,
	SCE_SBL_US_SPACKAGE_TYPE_SYSCON_3665           = 20,
	SCE_SBL_US_SPACKAGE_TYPE_OS0_PATCH             = 21,
	SCE_SBL_US_SPACKAGE_TYPE_VS0_PATCH             = 22,
	SCE_SBL_US_SPACKAGE_TYPE_SA0                   = 23,
	SCE_SBL_US_SPACKAGE_TYPE_PD0                   = 24,
	SCE_SBL_US_SPACKAGE_TYPE_SYSCON_C5E7           = 25,
	SCE_SBL_US_SPACKAGE_TYPE_PREINSTALL_DATA       = 27,
	SCE_SBL_US_SPACKAGE_TYPE_PREINSTALL_DATA_PATCH = 28
} SceSblUsSpackageType;
VITASDK_BUILD_ASSERT_EQ(1, SceSblUsSpackageType);

/** Asynchronous secure-package operation types. */
typedef enum SceSblUsSpackageRequestType {
	SCE_SBL_US_SPACKAGE_REQUEST_UPDATE  = 1, //!< Validate and install a package.
	SCE_SBL_US_SPACKAGE_REQUEST_INSPECT = 2, //!< Validate a package without installing it.
	SCE_SBL_US_SPACKAGE_REQUEST_EXTRACT = 3  //!< Validate and decrypt a package without installing it.
} SceSblUsSpackageRequestType;
VITASDK_BUILD_ASSERT_EQ(1, SceSblUsSpackageRequestType);

/** Values reported through ::SceKernelSpackageArgs::request_state. */
typedef enum SceSblUsSpackageRequestState {
	SCE_SBL_US_SPACKAGE_STATE_ACCEPTED   = 1,
	SCE_SBL_US_SPACKAGE_STATE_VALIDATING = 2,
	SCE_SBL_US_SPACKAGE_STATE_APPLYING   = 3,
	SCE_SBL_US_SPACKAGE_STATE_FINALIZING = 4,
	SCE_SBL_US_SPACKAGE_STATE_COMPLETED  = 5
} SceSblUsSpackageRequestState;
VITASDK_BUILD_ASSERT_EQ(1, SceSblUsSpackageRequestState);

/**
 * Flag values used by package-operation callers on FW 3.60.
 *
 * FW 3.60 requires the bits in mask 0x5 or 0x9 to be set, but does not reject
 * additional bits. Value 0x9 enables version checks. Value 0x5 skips version
 * checks for the boot and system-partition package types, but not peripheral
 * firmware checks. When the system does not use external storage, value 0x5
 * is rejected on CEX units.
 */
typedef enum SceSblUsSpackageFlags {
	SCE_SBL_US_SPACKAGE_FLAGS_SKIP_SYSTEM_VERSION_CHECK = 0x00000005,
	SCE_SBL_US_SPACKAGE_FLAGS_CHECK_SYSTEM_VERSION      = 0x00000009
} SceSblUsSpackageFlags;
VITASDK_BUILD_ASSERT_EQ(1, SceSblUsSpackageFlags);

typedef enum SceSblUsPowerControlMode {
	SCE_SBL_US_POWER_CONTROL_REBOOT            = 0,
	SCE_SBL_US_POWER_CONTROL_SHUTDOWN          = 1,
	SCE_SBL_US_POWER_CONTROL_LOCK              = 2,
	SCE_SBL_US_POWER_CONTROL_UNLOCK            = 3,
	SCE_SBL_US_POWER_CONTROL_LED_ON            = 4,
	SCE_SBL_US_POWER_CONTROL_LED_OFF           = 5,
	SCE_SBL_US_POWER_CONTROL_LED_INIT          = 6,
	SCE_SBL_US_POWER_CONTROL_TICK              = 7,
	/** On tool/test units, check DIP switch 194; other units return success. */
	SCE_SBL_US_POWER_CONTROL_CHECK_CP_ENABLED  = 8
} SceSblUsPowerControlMode;
VITASDK_BUILD_ASSERT_EQ(1, SceSblUsPowerControlMode);

typedef struct SceKernelSpackageArgs {
	SceSize size; //!< Initialize to sizeof(SceKernelSpackageArgs); copied but not validated on FW 3.60.
	SceUInt32 package_type; //!< One of ::SceSblUsSpackageType; the function uses its package_type argument instead on FW 3.60.
	void *buffer; //!< Process-owned buffer returned by ::sceSblUsAllocateBuffer.
	SceSize buffer_size; //!< Must equal the size passed to ::sceSblUsAllocateBuffer for this buffer.
	SceUInt32 flags; //!< One of ::SceSblUsSpackageFlags.
	SceUInt32 reserved[2]; //!< Preserved by ::sceSblUsGetExtractSpackage and ignored by SceSblUpdateMgr.
	SceUInt32 *sequence_number; //!< Receives a counter incremented each time the request state changes.
	SceInt32 *request_result; //!< Receives the operation result; valid when the request is completed.
	SceUInt32 *request_state; //!< Receives one of ::SceSblUsSpackageRequestState.
	SceUInt32 *written_rate; //!< Receives the write-rate value; applicable update paths report 100 when finished.
} SceKernelSpackageArgs;
VITASDK_BUILD_ASSERT_EQ(0x2C, SceKernelSpackageArgs); // size is from FW 0.931

/**
 * Installed secure-package information.
 *
 * On FW 3.60, ::SceSblUsSpkgInfo::status element 0 is used only for the BBMC
 * firmware package and is zero only when the BBMC status query succeeds and
 * returns a nonzero value. Element 1 is used only for the preinstall-data
 * patch package and is one when its secondary stored status is nonzero.
 */
typedef struct SceSblUsSpkgInfo {
	SceSize size; //!< Set to sizeof(SceSblUsSpkgInfo) on success.
	SceUInt32 version; //!< Installed package version.
	SceUInt8 status[4]; //!< Package-specific status bytes; only elements 0 and 1 are used on FW 3.60.
	SceInt32 reserved; //!< Set to 0 on FW 3.60.
} SceSblUsSpkgInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSblUsSpkgInfo); // size is from FW 0.931-0.990

/**
 * Applicable version information for OS0 and SLB2 packages.
 */
typedef struct SceSblUsApplicableVersionInfo {
	SceUInt32 version; //!< Applicable package version.
	SceUInt32 handled; //!< Set to 1 for OS0 and SLB2, or 0 for an unsupported package type.
	SceUInt32 reserved[2]; //!< Set to 0 on FW 3.60.
} SceSblUsApplicableVersionInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSblUsApplicableVersionInfo); // size is from FW 3.60

/**
 * Allocate a process-owned update buffer.
 *
 * FW 3.60 rounds \a size up to a 4 KiB boundary and has four update-buffer
 * slots shared by all processes.
 *
 * @param[in] size - Nonzero buffer size.
 * @param[out] user_buffer - Receives the user-space mapping.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsAllocateBuffer(SceSize size, void **user_buffer);

/**
 * Check system integrity.
 *
 * FW 3.60 checks only that the caller is a system program. It performs no
 * additional integrity scan.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceSblUsCheckSystemIntegrity(void);

/**
 * Submit an asynchronous package-extraction request.
 *
 * The operation validates and decrypts the package without installing it.
 * The buffer must have been allocated by ::sceSblUsAllocateBuffer for the
 * calling process.
 *
 * @param[in] package_type - One of ::SceSblUsSpackageType.
 * @param[in] args - Update buffer, size, and flags.
 * @param[out] request_id - Request identifier used by
 * ::sceSblUsGetStatus and ::sceSblUsGetExtractSpackage.
 *
 * @return 0 if the request was submitted, < 0 on error.
 */
int sceSblUsExtractSpackage(int package_type, const SceKernelSpackageArgs *args, int *request_id);

/**
 * Get an applicable package version.
 *
 * For OS0 and SLB2, FW 3.60 selects a built-in applicable version and, on
 * CEX systems, raises it to at least the installed version. Other package
 * types return success with a zeroed result.
 *
 * @param[in] package_type - One of ::SceSblUsSpackageType.
 * @param[out] version_info - Receives the applicable-version information.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetApplicableVersion(int package_type, SceSblUsApplicableVersionInfo *version_info);

/**
 * Return a request buffer's user-space mapping.
 *
 * FW 3.60 accepts every valid request type and does not itself require the
 * request to be completed. The request type and ID must identify the current
 * request. Only ::SceKernelSpackageArgs::buffer is replaced; every other
 * byte of the caller's structure is preserved.
 *
 * @param[in] request_type - One of ::SceSblUsSpackageRequestType.
 * @param[in] request_id - Request identifier.
 * @param[in,out] args - Receives the mapped user-space buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetExtractSpackage(int request_type, int request_id, SceKernelSpackageArgs *args);

/**
 * Get information about an installed package.
 *
 * The function writes the complete 0x10-byte output structure; its
 * ::SceSblUsSpkgInfo::size member is not an input.
 *
 * @param[in] package_type - One of ::SceSblUsSpackageType.
 * @param[out] info - Package information.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetSpkgInfo(int package_type, SceSblUsSpkgInfo *info);

/**
 * Get the state of an asynchronous package request.
 *
 * All four output pointers in \a args must be non-NULL. A nonzero request ID
 * must match the current request for \a request_type. Request ID zero selects
 * the module's legacy fallback-result path.
 *
 * @param[in] request_type - One of ::SceSblUsSpackageRequestType.
 * @param[in] request_id - Request identifier.
 * @param[in] args - Contains the four user-space output pointers.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetStatus(int request_type, int request_id, const SceKernelSpackageArgs *args);

/**
 * Inform the system that an update has finished.
 *
 * FW 3.60 copies the message into a 64-byte local buffer and forwards all
 * arguments unchanged to the registered system-root callback. If no callback
 * is registered, the call succeeds after validating and copying the message.
 *
 * @param[in] task - Update task value.
 * @param[in] message - Message buffer.
 * @param[in] message_length - Number of bytes to copy, from 1 through 64.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsInformUpdateFinished(SceUInt32 task, const char *message, SceSize message_length);

/**
 * Inform the system that an update is ongoing.
 *
 * Both arguments are forwarded unchanged to the registered system-root
 * callback. If no callback is registered, the call succeeds without otherwise
 * using the values.
 *
 * @param[in] task - Update task value.
 * @param[in] percentage - Update completion percentage.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsInformUpdateOngoing(SceUInt32 task, SceUInt32 percentage);

/**
 * Inform the system that an update has started.
 *
 * FW 3.60 copies the message into a 64-byte local buffer and forwards all
 * arguments unchanged to the registered system-root callback. If no callback
 * is registered, the call succeeds after validating and copying the message.
 *
 * @param[in] task - Update task value.
 * @param[in] value - Callback value whose purpose is unknown.
 * @param[in] message - Message buffer.
 * @param[in] message_length - Number of bytes to copy, from 1 through 64.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsInformUpdateStarted(SceUInt32 task, SceUInt32 value, const char *message, SceSize message_length);

/**
 * Submit an asynchronous package-inspection request.
 *
 * The operation performs the same package authentication, platform checks,
 * and version checks as an update request, but does not install the package.
 *
 * @param[in] package_type - One of ::SceSblUsSpackageType.
 * @param[in] args - Update buffer, size, and flags.
 * @param[out] request_id - Request identifier used by ::sceSblUsGetStatus.
 *
 * @return 0 if the request was submitted, < 0 on error.
 */
int sceSblUsInspectSpackage(int package_type, const SceKernelSpackageArgs *args, int *request_id);

/**
 * Perform an update-related power-control operation.
 *
 * For reboot and shutdown, observed flag values use bits 0 through 2; value
 * 0x2 selects the CP path and value 0x5 selects the system/Ernie path. For
 * lock and unlock, bit 0 requests the corresponding kernel power lock. LED
 * and CP-check modes ignore \a flags. Power-tick mode passes \a flags directly
 * as a ::SceKernelPowerTickType value.
 *
 * @param[in] mode - One of ::SceSblUsPowerControlMode.
 * @param[in] flags - Mode-dependent flags.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsPowerControl(int mode, SceUInt32 flags);

/**
 * Release an update buffer allocated by ::sceSblUsAllocateBuffer.
 *
 * If an asynchronous request still owns the buffer, this call removes the
 * caller's mapping. FW 3.60 frees the underlying memory only after the request
 * stops using it.
 *
 * @param[in] user_buffer - User-space update buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsReleaseBuffer(void *user_buffer);

/**
 * Set a binary software-information value.
 *
 * The input buffers are copied before the registered system-root callback is
 * called. If no callback is registered, the call succeeds after validating
 * and copying the inputs.
 *
 * @param[in] name - Name buffer.
 * @param[in] name_length - Number of name bytes to copy, from 1 through 31.
 * @param[in] value - Binary value buffer.
 * @param[in] value_length - Number of value bytes to copy, from 1 through 127.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetSwInfoBin(const char *name, SceSize name_length, const void *value, SceSize value_length);

/**
 * Set an integer software-information value.
 *
 * If no system-root callback is registered, the call succeeds after validating
 * and copying the name.
 *
 * @param[in] name - Name buffer.
 * @param[in] name_length - Number of name bytes to copy, from 1 through 31.
 * @param[in] value - Integer value.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetSwInfoInt(const char *name, SceSize name_length, SceUInt32 value);

/**
 * Set a string software-information value.
 *
 * The input buffers are copied before the registered system-root callback is
 * called. If no callback is registered, the call succeeds after validating
 * and copying the inputs.
 *
 * @param[in] name - Name buffer.
 * @param[in] name_length - Number of name bytes to copy, from 1 through 31.
 * @param[in] value - String value buffer.
 * @param[in] value_length - Number of value bytes to copy, from 1 through 127.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetSwInfoStr(const char *name, SceSize name_length, const char *value, SceSize value_length);

/**
 * Submit an asynchronous package-update request.
 *
 * The operation authenticates the package, checks target compatibility and
 * version policy, and installs the package-specific payload.
 *
 * @param[in] package_type - One of ::SceSblUsSpackageType.
 * @param[in] args - Update buffer, size, and flags.
 * @param[out] request_id - Request identifier used by ::sceSblUsGetStatus.
 *
 * @return 0 if the request was submitted, < 0 on error.
 */
int sceSblUsUpdateSpackage(int package_type, const SceKernelSpackageArgs *args, int *request_id);

/**
 * Verify an additional PUP signature.
 *
 * @param[in] path - NUL-terminated PUP path, at most 0x3FF characters.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupAdditionalSign(const char *path);

/**
 * Verify a PUP header.
 *
 * @param[in] path - NUL-terminated PUP path, at most 0x3FF characters.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupHeader(const char *path);

/**
 * Verify a PUP segment by index.
 *
 * @param[in] path - NUL-terminated PUP path, at most 0x3FF characters.
 * @param[in] segment_index - 64-bit segment index.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupSegment(const char *path, SceUInt64 segment_index);

/**
 * Verify a PUP segment by ID.
 *
 * @param[in] path - NUL-terminated PUP path, at most 0x3FF characters.
 * @param[in] segment_id - 64-bit segment ID.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupSegmentById(const char *path, SceUInt64 segment_id);

/**
 * Verify a PUP watermark.
 *
 * @param[in] path - NUL-terminated PUP path, at most 0x3FF characters.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupWatermark(const char *path);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_UPDATE_H_ */
