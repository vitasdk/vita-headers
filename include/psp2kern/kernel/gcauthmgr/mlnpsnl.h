/**
 * \kernelgroup{SceSblGcAuthMgrMlnpsnl}
 * \usage{psp2kern/kernel/gcauthmgr/mlnpsnl.h,SceSblGcAuthMgrMlnpsnlForDriver_stub}
 */

#ifndef __PSP2KERN_GCAUTHMGR_MLNPSNL_H__
#define __PSP2KERN_GCAUTHMGR_MLNPSNL_H__

#include <psp2common/kernel/gcauthmgr/mlnpsnl.h>
#include <psp2common/kernel/rtc.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the first MLNPSNL authentication phase.
 *
 * All pointers must be non-NULL. The input buffers must remain valid until this
 * function returns; they are not used afterwards. The function clears both
 * output structures before cryptographic processing and retains no caller
 * pointer after returning. Do not use either output unless the function succeeds.
 *
 * @param[in] request - Complete 0x20-byte phase-one request.
 * @param[in] secure_tick - Complete current secure tick.
 * @param[out] response - Generated 0x80-byte client authentication packet.
 * @param[out] session_data - Generated 0x40-byte state to retain unchanged for phase two.
 *
 * @return 0 on success; 0x808A0200 for a NULL pointer; 0x808A0202 through
 *         0x808A0205 for random/cryptographic failures; 0x808A0206 for a
 *         semaphore failure; or 0x808A0300 for an internal permission or
 *         console-identity failure.
 */
int ksceSblGcAuthMgrMlnpsnlAuth1(const SceSblGcAuthMgrMlnpsnlAuth1Request *request, const SceRtcTick *secure_tick, SceSblGcAuthMgrMlnpsnlAuth1Response *response, SceSblGcAuthMgrMlnpsnlSessionData *session_data);

#ifdef __cplusplus
}
#endif

#endif /* __PSP2KERN_GCAUTHMGR_MLNPSNL_H__ */
