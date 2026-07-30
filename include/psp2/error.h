/**
 * \usergroup{SceError}
 * \usage{psp2/error.h,SceError_stub}
 */


#ifndef _PSP2_ERROR_H_
#define _PSP2_ERROR_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceErrorStrings {
	char s[16]; //!< NUL-terminated formatted external error code.
} SceErrorStrings;
VITASDK_BUILD_ASSERT_EQ(0x10, SceErrorStrings); // size is from FW 3.60

/**
 * Convert an internal error code to an external one
 *
 * @param[out] error_string - Optional external error-code buffer. If non-NULL, it must point to at least 16 bytes.
 * @param[in] error_code - Internal error code
 *
 * @return 0 on success, < 0 on error.
 */
int _sceErrorGetExternalString(char *error_string, int error_code);

typedef struct SceErrorDefaultFormat {
	SceInt32 networkStatus; //!< Default value for ::SceErrorHistoryPostInfo::networkStatus.
	SceInt32 enable; //!< Must be 1; enables the default for subsequently posted entries.
} SceErrorDefaultFormat;
VITASDK_BUILD_ASSERT_EQ(8, SceErrorDefaultFormat); // size is from FW 3.60

typedef struct SceErrorHistoryPostInfo {
	char error_message[0x100]; //!< Human-readable diagnostic message.
	SceUInt32 suggestedActions[15]; //!< Suggested-action IDs consumed by the Settings UI.
	SceUInt8 reserved0[2]; //!< Reserved; copied into history unchanged.
	SceUInt8 suggestedActionCount; //!< Number of valid entries in \a suggestedActions, up to 15.
	SceUInt8 reserved1; //!< Reserved; copied into history unchanged.
	int error_code_hex; //!< Internal error code.
	SceUInt32 applicationCode; //!< Application error number displayed as XX-XXX-XXX.
	SceUInt version; //!< System software version from ::SceKernelSystemSwVersion::version.
	SceInt32 networkStatus; //!< Network status used by Settings to display NAT information.
	char titleid[0xC]; //!< Title ID associated with the application error; observed callers copy up to 10 bytes, including the terminator.
	SceUInt32 systemSoftwareVersionUnk24; //!< From ::SceKernelSystemSwVersion::unk_24.
	SceUInt8 reserved2[0x20]; //!< Cleared by SceError before the entry is stored.
} SceErrorHistoryPostInfo;
VITASDK_BUILD_ASSERT_EQ(0x180, SceErrorHistoryPostInfo); // size is from FW 3.60

typedef struct SceErrorHistoryInfo {
	SceUInt8 reserved0; //!< Zero-initialized for newly posted entries.
	SceUInt8 flags; //!< Bit 0 is set when Settings opens the entry.
	SceUInt8 sequenceId; //!< Matched together with \a time when updating the entry.
	SceUInt8 reserved1; //!< Zero-initialized for newly posted entries.
	SceUInt32 reserved2; //!< Zero-initialized for newly posted entries.
	SceInt64 time; //!< Value of type ::SceRtcTick.
	SceErrorStrings error_code; //!< Formatted external error code.
	SceUInt8 reserved3[0x10]; //!< Zero-initialized for newly posted entries.
	SceErrorHistoryPostInfo post; //!< Posted error information.
} SceErrorHistoryInfo;
VITASDK_BUILD_ASSERT_EQ(0x1B0, SceErrorHistoryInfo); // size is from FW 3.60

typedef struct SceErrorSequenceInfo {
	SceUInt8 sequenceId; //!< Sequence identifier of the history entry to update.
	SceUInt8 flags; //!< Replacement flags for the matching history entry.
	SceUInt8 reserved0[6]; //!< Ignored by SceError.
	SceInt64 time; //!< Value of type ::SceRtcTick.
	SceUInt8 reserved1[0x10]; //!< Ignored by SceError.
} SceErrorSequenceInfo;
VITASDK_BUILD_ASSERT_EQ(0x20, SceErrorSequenceInfo); // size is from FW 3.60

/**
 * Clear the in-memory and persisted error history.
 *
 * @param[in] zero - Reserved. Must be 0.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceErrorHistoryClearError(int zero);

/**
 * Get an error-history entry.
 *
 * @param[in] error_idx - Entry index. 0 is the newest entry and 9 is the oldest.
 * @param[out] info - The returned error-history entry.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceErrorHistoryGetError(SceUInt32 error_idx, SceErrorHistoryInfo *info);

/**
 * Post an error-history entry.
 *
 * @param[in] info - Error information to post.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceErrorHistoryPostError(const SceErrorHistoryPostInfo *info);

/**
 * Set the default network status applied to subsequently posted error-history entries.
 *
 * @param[in] format - Default format. Its \a enable member must be 1.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceErrorHistorySetDefaultFormat(const SceErrorDefaultFormat *format);

/**
 * Update the flags of an error-history entry.
 *
 * The entry is matched using both \a sequenceId and \a time.
 *
 * @param[in] info - Sequence information and replacement flags.
 * @param[in] zero - Reserved. Must be 0.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceErrorHistoryUpdateSequenceInfo(const SceErrorSequenceInfo *info, int zero);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_ERROR_H_ */
