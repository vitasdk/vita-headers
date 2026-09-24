/**
 * \usergroup{SceSblQafMgr}
 * \usage{psp2/sblqafmgr.h,SceSblSsMgr_stub}
 */

#ifndef _PSP2_SBLQAFMGR_H_
#define _PSP2_SBLQAFMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Unencrypted header and encrypted payload in the first 0x80 token bytes. */
typedef struct SceQafTokenEnc {
	char magic[4];           //!< Token magic.
	SceUInt32 qaf_version;   //!< QAF token version; FW 3.60 uses its second byte as the version counter.
	char qaf_name[0x18];     //!< NUL-terminated or padded QAF profile name.
	SceUInt8 enc_data[0x60]; //!< Encrypted token payload.
} SceQafTokenEnc;
VITASDK_BUILD_ASSERT_EQ(0x80, SceQafTokenEnc); // size is from FW 3.60

typedef struct SceQafTokenEx {
	/**
	 * Input to ::sceSblQafMgrSetQafToken2 has the layout of
	 * ::SceQafTokenEnc. ::sceSblQafMgrGetQafToken2 transforms this region,
	 * but its output layout is not established.
	 */
	SceUInt8 token_data[0x80]; //!< Encrypted token on input to ::sceSblQafMgrSetQafToken2.
	SceUInt8 sig[0x100];       //!< 0x100-byte token signature.
} SceQafTokenEx;
VITASDK_BUILD_ASSERT_EQ(0x180, SceQafTokenEx); // size is from FW 3.60

/**
 * Does nothing on FW 3.60; does not delete a legacy QAF token.
 *
 * @return Always `0x80010058` on FW 3.60.
 */
int sceSblQafManagerDeleteQafTokenForUser(void);

/**
 * Copy up to 0x18 bytes of the active QAF profile name to user memory.
 *
 * The calling process must be a system program. The function reads and writes
 * the selected portion of \a buffer, so it must be both readable and writable.
 * Values of \a max_length above 0x18 are treated as 0x18.
 *
 * @param[in,out] buffer - Required profile-name buffer.
 * @param[in] max_length - Number of bytes available in \a buffer; must be
 *                        nonzero.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblQafManagerGetQafNameForUser(char *buffer, SceSize max_length);

/** @return 1 when QA flag byte 0xD bit 0 is set, otherwise 0. */
int sceSblQafManagerIsAllowKernelDebugForUser(void);

/**
 * Delete the stored extended QAF token and mark the NVS token slot empty.
 *
 * The calling process must be a system program.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblQafMgrDeleteQafToken2(void);

/**
 * Validate the stored extended QAF token and return its active profile name.
 *
 * The calling process must be a system program. \a buffer must be readable
 * and writable, and \a max_length must be at least 0x18. Exactly 0x18 bytes
 * are transferred.
 *
 * @param[in,out] buffer - Required 0x18-byte profile-name buffer.
 * @param[in] max_length - Buffer capacity; must be at least 0x18.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblQafMgrGetQafName(char *buffer, SceSize max_length);

/**
 * Retrieve and transform the stored 0x180-byte extended QAF token.
 *
 * The calling process must be a system program. When the NVS empty flag is
 * clear, the first 0x80 bytes and the 0x100-byte signature are read from NVS.
 * Otherwise a token filled with zeros is used. qaf_sm command 13 then
 * transforms the complete token before it is copied to user memory.
 *
 * @param[out] qaf_token - Required output token.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblQafMgrGetQafToken2(SceQafTokenEx *qaf_token);

/** @return 1 when QA flag byte 0xC bit 1 is set, otherwise 0. */
int sceSblQafMgrIsAllowAllDebugMenuDisplay(void);

/** @return 1 when QA flag byte 0xF bit 1 is set, otherwise 0. */
int sceSblQafMgrIsAllowForceUpdate(void);

/** @return 1 when QA flag byte 6 bit 1 is set, otherwise 0. */
int sceSblQafMgrIsAllowLimitedDebugMenuDisplay(void);

/** @return 1 when QA flag byte 0xF bit 0 is set, otherwise 0. */
int sceSblQafMgrIsAllowMinimumDebugMenuDisplay(void);

/** @return 1 when QA flag byte 0xF bit 0 is set, otherwise 0. */
int sceSblQafMgrIsAllowNonQAPup(void);

/** @return 1 when QA flag byte 6 bit 1 is set, otherwise 0. */
int sceSblQafMgrIsAllowNpFullTest(void);

/**
 * Check whether NP test mode is enabled.
 *
 * @return 1 when QA flag byte 0xF bit 0 or Sysroot's NP-test flag is set,
 *         otherwise 0.
 */
int sceSblQafMgrIsAllowNpTest(void);

/** @return 1 when QA flag byte 0xD bit 1 is set, otherwise 0. */
int sceSblQafMgrIsAllowRemoteSysmoduleLoad(void);

/** @return 1 when QA flag byte 6 bit 1 is set, otherwise 0. */
int sceSblQafMgrIsAllowScreenShotAlways(void);

/**
 * Validate and install an extended QAF token.
 *
 * The calling process must be a system program. qaf_sm command 12 validates
 * the 0x180-byte token. The secure version counter is then initialized or
 * advanced from byte 5. The token is enabled before it is written to NVS and
 * read back for verification.
 *
 * @param[in] qaf_token - Required encrypted token and signature.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblQafMgrSetQafToken2(const SceQafTokenEx *qaf_token);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLQAFMGR_H_ */
