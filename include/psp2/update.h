/**
 * \usergroup{SceSblSsUpdateMgr}
 * \usage{psp2/update.h,SceSblUpdateMgr_stub}
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

typedef enum SceSblUsSpackageRequestType {
	SCE_SBL_US_SPACKAGE_REQUEST_UPDATE  = 1,
	SCE_SBL_US_SPACKAGE_REQUEST_INSPECT = 2,
	SCE_SBL_US_SPACKAGE_REQUEST_EXTRACT = 3
} SceSblUsSpackageRequestType;
VITASDK_BUILD_ASSERT_EQ(1, SceSblUsSpackageRequestType);

typedef enum SceSblUsPowerControlMode {
	SCE_SBL_US_POWER_CONTROL_REBOOT            = 0,
	SCE_SBL_US_POWER_CONTROL_SHUTDOWN          = 1,
	SCE_SBL_US_POWER_CONTROL_LOCK              = 2,
	SCE_SBL_US_POWER_CONTROL_UNLOCK            = 3,
	SCE_SBL_US_POWER_CONTROL_LED_ON            = 4,
	SCE_SBL_US_POWER_CONTROL_LED_OFF           = 5,
	SCE_SBL_US_POWER_CONTROL_LED_INIT          = 6,
	SCE_SBL_US_POWER_CONTROL_TICK              = 7,
	SCE_SBL_US_POWER_CONTROL_CHECK_DVT_SUPPORT = 8
} SceSblUsPowerControlMode;
VITASDK_BUILD_ASSERT_EQ(1, SceSblUsPowerControlMode);

typedef struct SceKernelSpackageArgs {
	SceSize arg_size; //!< Size of this structure. Copied but actually unused on FW 3.60.
	SceUInt32 package_type; //!< Copy of the package type. Ignored on FW 3.60.
	void *addr; //!< Address of the update buffer.
	SceSize size; //!< Size of the update buffer.
	SceUInt32 flags; //!< Operation flags.
	char reserved[0x8]; //!< Ignored on FW 3.60. Initialize to zero.
	SceUInt32 seq_no; //!< Holds the address of a user-space ::SceUInt32 that receives the sequence number.
	SceUInt32 result; //!< Holds the address of a user-space ::SceUInt32 that receives the request result.
	SceUInt32 progress; //!< Holds the address of a user-space ::SceUInt32 that receives the progress.
	SceUInt32 written_rates; //!< Holds the address of a user-space ::SceUInt32 that receives the written rate.
} SceKernelSpackageArgs;
VITASDK_BUILD_ASSERT_EQ(0x2C, SceKernelSpackageArgs); // size is from FW 0.931

typedef struct SceSblUsSpkgInfo {
	SceSize size; //!< Size of this structure.
	uint32_t version; //!< Installed package version.
	uint8_t status[4]; //!< FW 3.60 uses status[0] for package type 13 and status[1] for package type 28.
	int reserved; //!< Set to 0 on FW 3.60.
} SceSblUsSpkgInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSblUsSpkgInfo); // size is from FW 0.931-0.990

typedef struct SceSblUsApplicableVersionInfo {
	SceUInt32 version; //!< Applicable package version.
	SceUInt32 applicable; //!< Set to 1 for package types 1 and 9 on FW 3.60.
	SceUInt32 reserved[2]; //!< Set to 0 on FW 3.60.
} SceSblUsApplicableVersionInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSblUsApplicableVersionInfo); // size is from FW 3.60

/**
 * Allocate a process-owned update buffer.
 *
 * @param[in] size - Buffer size.
 * @param[out] user_buffer - Address of the allocated user-space buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsAllocateBuffer(SceSize size, void **user_buffer);

/**
 * Check system integrity.
 *
 * FW 3.60 performs the access check but no additional integrity scan.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceSblUsCheckSystemIntegrity(void);

/**
 * Submit an asynchronous package-extraction request.
 *
 * @param[in] package_type - Package type.
 * @param[in] args - Update buffer, size, and flags.
 * @param[out] request_id - Request identifier used by
 * ::sceSblUsGetStatus and ::sceSblUsGetExtractSpackage.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsExtractSpackage(int package_type, SceKernelSpackageArgs *args, int *request_id);

/**
 * Get an applicable package version.
 *
 * @param[in] package_type - Package type. FW 3.60 only handles types 1 and 9.
 * @param[out] version_info - Pointer to a
 * ::SceSblUsApplicableVersionInfo structure.
 *
 * Unsupported package types return success with a zeroed output buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetApplicableVersion(int package_type, void *version_info);

/**
 * Map a completed extraction buffer into the caller.
 *
 * @param[in] request_type - One of ::SceSblUsSpackageRequestType.
 * @param[in] request_id - Request identifier.
 * @param[in,out] args - The mapped user-space buffer is returned through
 * the address field encoded in args.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetExtractSpackage(int request_type, int request_id, SceKernelSpackageArgs *args);

/**
 * Get information about an installed package.
 *
 * @param[in] package_type - Package type.
 * @param[out] info - Package information.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetSpkgInfo(int package_type, SceSblUsSpkgInfo *info);

/**
 * Get the state of an asynchronous package request.
 *
 * @param[in] request_type - One of ::SceSblUsSpackageRequestType.
 * @param[in] request_id - Request identifier.
 * @param[in] args - The final four fields hold user-space output addresses
 * for the sequence number, result, progress, and written rate.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetStatus(int request_type, int request_id, SceKernelSpackageArgs *args);

/**
 * Inform the system that an update has finished.
 *
 * @param[in] number - Opaque value forwarded to the system root manager.
 * @param[in] text - Text buffer.
 * @param[in] text_length - Text length, from 1 through 64 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsInformUpdateFinished(int number, const char *text, SceSize text_length);

/**
 * Inform the system that an update is ongoing.
 *
 * @param[in] number1 - First opaque value.
 * @param[in] number2 - Second opaque value.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsInformUpdateOngoing(int number1, int number2);

/**
 * Inform the system that an update has started.
 *
 * @param[in] number1 - First opaque value.
 * @param[in] number2 - Second opaque value.
 * @param[in] text - Text buffer.
 * @param[in] text_length - Text length, from 1 through 64 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsInformUpdateStarted(int number1, int number2, const char *text, SceSize text_length);

/**
 * Submit an asynchronous package-inspection request.
 *
 * @param[in] package_type - Package type.
 * @param[in] args - Update buffer, size, and flags.
 * @param[out] request_id - Request identifier used by ::sceSblUsGetStatus.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsInspectSpackage(int package_type, SceKernelSpackageArgs *args, int *request_id);

/**
 * Perform an update-related power-control operation.
 *
 * @param[in] mode - One of ::SceSblUsPowerControlMode.
 * @param[in] flags - Mode-dependent flags.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsPowerControl(int mode, int flags);

/**
 * Release an update buffer allocated by ::sceSblUsAllocateBuffer.
 *
 * @param[in] user_buffer - User-space update buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsReleaseBuffer(void *user_buffer);

/**
 * Set a binary software-information value.
 *
 * @param[in] name - Read-only name buffer.
 * @param[in] name_length - Name length, from 1 through 31 bytes.
 * @param[in] value - Read-only binary value buffer.
 * @param[in] value_length - Value length, from 1 through 127 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetSwInfoBin(char *name, SceSize name_length, char *value, SceSize value_length);

/**
 * Set an integer software-information value.
 *
 * @param[in] name - Read-only name buffer.
 * @param[in] name_length - Name length, from 1 through 31 bytes.
 * @param[in] value - Integer value.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetSwInfoInt(char *name, SceSize name_length, SceUInt32 value);

/**
 * Set a string software-information value.
 *
 * @param[in] name - Read-only name buffer.
 * @param[in] name_length - Name length, from 1 through 31 bytes.
 * @param[in] value - Read-only string value buffer.
 * @param[in] value_length - Value length, from 1 through 127 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetSwInfoStr(char *name, SceSize name_length, char *value, SceSize value_length);

/**
 * Submit an asynchronous package-update request.
 *
 * @param[in] package_type - Package type.
 * @param[in] args - Update buffer, size, and flags.
 * @param[out] request_id - Request identifier used by ::sceSblUsGetStatus.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsUpdateSpackage(int package_type, SceKernelSpackageArgs *args, int *request_id);

/**
 * Verify an additional PUP signature.
 *
 * @param[in] path - PUP path.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupAdditionalSign(const char *path);

/**
 * Verify a PUP header.
 *
 * @param[in] path - PUP path.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupHeader(const char *path);

/**
 * Verify a PUP segment by index.
 *
 * @param[in] path - PUP path.
 * @param[in] segment_index - 64-bit segment index.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupSegment(const char *path, SceUInt64 segment_index);

/**
 * Verify a PUP segment by ID.
 *
 * @param[in] path - PUP path.
 * @param[in] segment_id - 64-bit segment ID.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupSegmentById(const char *path, uint64_t segment_id);

/**
 * Verify a PUP watermark.
 *
 * @param[in] path - PUP path.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsVerifyPupWatermark(const char *path);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_UPDATE_H_ */
