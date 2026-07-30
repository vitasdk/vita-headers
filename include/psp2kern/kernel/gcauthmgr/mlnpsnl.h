/**
 * \kernelgroup{SceSblGcAuthMgrMlnpsnl}
 * \usage{psp2kern/kernel/gcauthmgr/mlnpsnl.h,SceSblGcAuthMgrMlnpsnlForDriver_stub}
 */

#ifndef __PSP2KERN_GCAUTHMGR_MLNPSNL_H__
#define __PSP2KERN_GCAUTHMGR_MLNPSNL_H__

#include <vitasdk/build_utils.h>
#include <psp2common/kernel/rtc.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceSblGcAuthMgrMlnpsnlAuth1Request {
	SceUInt8 mode; //!< Authentication mode. System callers use 0, 0x10, or 0x11.
	SceUInt8 requestData[0x1F]; //!< Opaque request bytes; their individual semantics remain unresolved.
} SceSblGcAuthMgrMlnpsnlAuth1Request;
VITASDK_BUILD_ASSERT_EQ(0x20, SceSblGcAuthMgrMlnpsnlAuth1Request); // size is from FW 3.60

typedef struct SceSblGcAuthMgrMlnpsnlAuth1Response {
	SceUInt8 packetType; //!< Packet type, set to 0x20.
	SceUInt8 phase; //!< Authentication phase, set to 1.
	SceUInt8 packetSize; //!< Packet size, set to 0x80.
	SceUInt8 reserved[0xD]; //!< Set to zero.
	SceUInt8 protectedData[0x60]; //!< Protected authentication data.
	SceUInt8 authenticationTag[0x10]; //!< Packet authentication tag.
} SceSblGcAuthMgrMlnpsnlAuth1Response;
VITASDK_BUILD_ASSERT_EQ(0x80, SceSblGcAuthMgrMlnpsnlAuth1Response); // size is from FW 3.60

typedef struct SceSblGcAuthMgrMlnpsnlSessionData {
	SceUInt8 sessionKey[0x10]; //!< Session key returned after successful second-phase authentication.
	SceUInt8 bindingData[0x10]; //!< Data used to bind the second-phase response to this session.
	SceUInt8 phaseOneSize; //!< Set to 0x80 and echoed in the second-phase response header.
	SceUInt8 reserved[0x1F]; //!< Set to zero.
} SceSblGcAuthMgrMlnpsnlSessionData;
VITASDK_BUILD_ASSERT_EQ(0x40, SceSblGcAuthMgrMlnpsnlSessionData); // size is from FW 3.60

/**
 * Performs the first MLNPSNL authentication phase.
 *
 * @param[in] request - Phase-one request.
 * @param[in] secure_tick - Current secure tick.
 * @param[out] response - Generated 0x80-byte client authentication packet.
 * @param[out] session_data - Generated 0x40-byte session data, which must be retained unchanged for the second phase.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceSblGcAuthMgrMlnpsnlAuth1(const SceSblGcAuthMgrMlnpsnlAuth1Request *request, const SceRtcTick *secure_tick, SceSblGcAuthMgrMlnpsnlAuth1Response *response, SceSblGcAuthMgrMlnpsnlSessionData *session_data);

#ifdef __cplusplus
}
#endif

#endif /* __PSP2KERN_GCAUTHMGR_MLNPSNL_H__ */
