/**
 * \kernelgroup{SceSblGcAuthMgrMlnpsnl}
 * \usage{psp2common/kernel/gcauthmgr/mlnpsnl.h}
 */

#ifndef _PSP2COMMON_KERNEL_GCAUTHMGR_MLNPSNL_H_
#define _PSP2COMMON_KERNEL_GCAUTHMGR_MLNPSNL_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * MLNPSNL phase-one request.
 *
 * FW 3.60 uses all 0x20 bytes when generating the protected response. Observed
 * system callers zero the structure and set \a mode to 0, 0x10, or 0x11.
 */
typedef struct SceSblGcAuthMgrMlnpsnlAuth1Request {
	SceUInt8 mode; //!< Authentication mode used by the remote protocol.
	SceUInt8 request_data[0x1F]; //!< Remaining authenticated request data.
} SceSblGcAuthMgrMlnpsnlAuth1Request;
VITASDK_BUILD_ASSERT_EQ(0x20, SceSblGcAuthMgrMlnpsnlAuth1Request); // size is from FW 3.60

/** MLNPSNL phase-one client packet. */
typedef struct SceSblGcAuthMgrMlnpsnlAuth1Response {
	SceUInt8 packet_type; //!< Set to 0x20.
	SceUInt8 phase; //!< Set to 1.
	SceUInt8 packet_size; //!< Set to 0x80.
	SceUInt8 reserved[0xD]; //!< Set to zero.
	SceUInt8 protected_data[0x60]; //!< Protected phase-one authentication data.
	SceUInt8 authentication_tag[0x10]; //!< Packet authentication tag.
} SceSblGcAuthMgrMlnpsnlAuth1Response;
VITASDK_BUILD_ASSERT_EQ(0x80, SceSblGcAuthMgrMlnpsnlAuth1Response); // size is from FW 3.60

/**
 * Caller-owned state linking MLNPSNL authentication phases one and two.
 *
 * Keep this structure unchanged until phase two completes. The phase-one
 * function does not retain its address after returning.
 */
typedef struct SceSblGcAuthMgrMlnpsnlSessionData {
	SceUInt8 session_key[0x10]; //!< Candidate key copied to the final output only after phase-two verification.
	SceUInt8 binding_data[0x10]; //!< Value used to bind the decrypted phase-two response to this session.
	SceUInt8 phase_one_packet_size; //!< Set to 0x80 and required in the phase-two header.
	SceUInt8 reserved[0x1F]; //!< Set to zero.
} SceSblGcAuthMgrMlnpsnlSessionData;
VITASDK_BUILD_ASSERT_EQ(0x40, SceSblGcAuthMgrMlnpsnlSessionData); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_GCAUTHMGR_MLNPSNL_H_ */
