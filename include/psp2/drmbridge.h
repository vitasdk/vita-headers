/**
 * \usergroup{SceDrmBridge}
 * \usage{psp2/drmbridge.h,SceDrmBridge_stub}
 */

#ifndef _PSP2_DRMBRIDGE_H_
#define _PSP2_DRMBRIDGE_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/kernel/gcauthmgr/mlnpsnl.h>
#include <psp2common/kernel/rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceDrmBridgeMlnpsnlAuth1Opt {
	SceSblGcAuthMgrMlnpsnlSessionData *session_data; //!< Destination for the phase-one session data.
	SceSize request_size; //!< Must be 0x20; smaller copies leave some authentication input bytes uninitialized.
	SceSize secure_tick_size; //!< Must be 8; smaller copies leave some authentication input bytes uninitialized.
	SceSize response_size; //!< Number of response bytes to copy, at most 0x80.
	SceSize session_data_size; //!< Number of session-data bytes to copy, at most 0x40.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDrmBridgeMlnpsnlAuth1Opt;
VITASDK_BUILD_ASSERT_EQ(0x18, SceDrmBridgeMlnpsnlAuth1Opt); // size is from FW 3.60

/**
 * Reports whether remote-play debugging is allowed.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 1 when allowed, 0 when disabled, or a negative authorization error.
 */
SceBool _sceDrmBridgeIsAllowRemotePlayDebug(void);

/**
 * Performs the first MLNPSNL authentication phase.
 *
 * The SceDriverUser wrapper takes four buffers and sets all copy sizes to their
 * maximum values. Keep the returned session data unchanged for the second
 * authentication phase. All pointers must be non-NULL. Both output structures
 * are built in zero-initialized kernel buffers. The requested byte counts are
 * copied back even when authentication reports an error. This function does
 * not use any caller buffer after it returns.
 *
 * @param[in] request - Phase-one request. Set \c opt->request_size to exactly 0x20.
 * @param[in] secure_tick - Secure tick. Set \c opt->secure_tick_size to exactly 8.
 * @param[out] response - Receives the phase-one response. \c opt->response_size
 * must be at most 0x80; the system wrapper requests the complete structure.
 * @param[in] opt - Copy sizes and session-data destination.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success; 0x808A0200 when an authentication buffer is NULL; or
 *         another negative copy, authorization, size, or authentication error.
 */
int _sceDrmBridgeMlnpsnlAuth1(const SceSblGcAuthMgrMlnpsnlAuth1Request *request, const SceRtcTick *secure_tick, SceSblGcAuthMgrMlnpsnlAuth1Response *response, const SceDrmBridgeMlnpsnlAuth1Opt *opt);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DRMBRIDGE_H_ */
