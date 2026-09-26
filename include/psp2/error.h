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

typedef struct SceErrorString {
	char s[16]; //!< NUL-terminated formatted external error code, for example "C2-12828-1".
} SceErrorString;
VITASDK_BUILD_ASSERT_EQ(0x10, SceErrorString); // size is from FW 3.60

/**
 * Convert an internal error code to its formatted external error code.
 *
 * Known public errors use `PREFIX-number-checkdigit`. Unknown errors use
 * `E-xxxxxxxx`, and known non-public errors use `*-xxxxxxxx`. Hexadecimal
 * digits are lowercase on FW 3.60. A non-NULL destination receives exactly
 * 16 bytes, including the NUL terminator and zero padding.
 *
 * @param[out] error_string - Optional external error-code buffer. If non-NULL, it must point to at least 16 bytes.
 * @param[in] error_code - Internal error code.
 *
 * @return 0 on success, or a user-memory copy error.
 */
int _sceErrorGetExternalString(char *error_string, int error_code);

typedef struct SceErrorDefaultFormat {
	SceInt32 network_status; //!< Default network status; not validated. Settings maps 3..5 to NAT types 1..3.
	SceInt32 enable; //!< Must be exactly 1. The default remains enabled until SceError is reloaded.
} SceErrorDefaultFormat;
VITASDK_BUILD_ASSERT_EQ(8, SceErrorDefaultFormat); // size is from FW 3.60

typedef struct SceErrorHistoryPostInfo {
	char error_message[0x100]; //!< NUL-terminated diagnostic message. Termination is not validated on FW 3.60.
	SceUInt32 suggested_actions[15]; //!< Suggested-action IDs used by the Settings UI.
	SceUInt8 reserved0[2]; //!< Reserved; copied into history unchanged.
	SceUInt8 suggested_action_count; //!< Number of valid actions; must be <= 15. FW 3.60 does not check it.
	SceUInt8 reserved1; //!< Reserved; copied into history unchanged.
	int error_code_hex; //!< Internal error code.
	SceUInt32 application_code; //!< Application error number displayed as XX-XXX-XXX.
	SceUInt version; //!< Set by SceError from ::SceKernelSystemSwVersion::version; the caller-provided value is ignored.
	SceInt32 network_status; //!< Unchecked unless overridden; Settings maps 3..5 to NAT types 1..3.
	char titleid[0xC]; //!< NUL-terminated title ID; not validated. Duplicate checks use its first 10 bytes.
	SceUInt32 system_software_version_unk24; //!< Set from ::SceKernelSystemSwVersion::unk_24; input is ignored.
	SceUInt8 reserved2[0x20]; //!< Cleared by SceError before the entry is stored.
} SceErrorHistoryPostInfo;
VITASDK_BUILD_ASSERT_EQ(0x180, SceErrorHistoryPostInfo); // size is from FW 3.60

typedef struct SceErrorHistoryInfo {
	SceUInt8 reserved0; //!< Zero-initialized for newly posted entries.
	SceUInt8 flags; //!< Bit 0 is set when Settings opens the entry.
	SceUInt8 sequence_id; //!< Matched together with \a time when updating the entry.
	SceUInt8 reserved1; //!< Zero-initialized for newly posted entries.
	SceUInt32 reserved2; //!< Zero-initialized for newly posted entries.
	SceInt64 time; //!< Value of type ::SceRtcTick.
	SceErrorString error_code; //!< Formatted external error code.
	SceUInt8 reserved3[0x10]; //!< Zero-initialized for newly posted entries.
	SceErrorHistoryPostInfo post; //!< Posted error information.
} SceErrorHistoryInfo;
VITASDK_BUILD_ASSERT_EQ(0x1B0, SceErrorHistoryInfo); // size is from FW 3.60

typedef struct SceErrorSequenceInfo {
	SceUInt8 sequence_id; //!< Sequence identifier of the history entry to update.
	SceUInt8 flags; //!< Replacement flags for the matching history entry.
	SceUInt8 reserved0[6]; //!< Ignored by SceError.
	SceInt64 time; //!< Value of type ::SceRtcTick.
	SceUInt8 reserved1[0x10]; //!< Ignored by SceError.
} SceErrorSequenceInfo;
VITASDK_BUILD_ASSERT_EQ(0x20, SceErrorSequenceInfo); // size is from FW 3.60

/**
 * Clear the in-memory error history and remove `vd0:history/data.bin`.
 *
 * `vd0:history/data.bak` is not removed immediately. The empty history is
 * written to both files on the next suspend event.
 *
 * @param[in] zero - Reserved. Must be 0.
 *
 * @return 0 on success, or 0x80010016 if \a zero is not 0.
 */
int _sceErrorHistoryClearError(int zero);

/**
 * Get an error-history entry.
 *
 * Empty slots are returned as zero-filled records. For a non-NULL output and
 * an invalid index, FW 3.60 also writes a zero-filled record before returning
 * the error.
 *
 * @param[in] error_idx - Entry index. 0 is the newest entry and 9 is the oldest.
 * @param[out] info - The returned error-history entry.
 *
 * @return 0 on success, 0x80010016 for a NULL output or an index greater than
 *         9, or a user-memory copy error.
 */
int _sceErrorHistoryGetError(SceUInt32 error_idx, SceErrorHistoryInfo *info);

/**
 * Post an error-history entry.
 *
 * SceError copies the record before returning. It replaces the system-version
 * fields, conditionally replaces \a network_status with the registered default,
 * clears \a reserved2, assigns the RTC timestamp and sequence ID, and generates
 * the external error string. A prior entry with the same internal error code,
 * application code, and first 10 title-ID bytes is removed. The history is
 * not written to storage until a suspend event.
 *
 * @param[in] info - Error information to post.
 *
 * @return 0 on success, 0x80010016 for a NULL record, or a user-memory copy
 *         error.
 */
int _sceErrorHistoryPostError(const SceErrorHistoryPostInfo *info);

/**
 * Set the default network status for error-history entries posted later.
 *
 * FW 3.60 provides no call to disable the default once enabled.
 *
 * @param[in] format - Default format. Its \a enable member must be 1.
 *
 * @return 0 on success, 0x80010016 for a NULL record or an \a enable value
 *         other than 1, or a user-memory copy error.
 */
int _sceErrorHistorySetDefaultFormat(const SceErrorDefaultFormat *format);

/**
 * Update the flags of an error-history entry.
 *
 * The entry is matched using both \a sequence_id and \a time.
 *
 * @param[in] info - Sequence information and replacement flags.
 * @param[in] zero - Reserved. Must be 0.
 *
 * @return 0 on success; 0x80010016 for a NULL record, a nonzero \a zero value,
 *         or no matching entry; or a user-memory copy error.
 */
int _sceErrorHistoryUpdateSequenceInfo(const SceErrorSequenceInfo *info, int zero);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_ERROR_H_ */
