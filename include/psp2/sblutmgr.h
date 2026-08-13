/**
 * \usergroup{SceSblUtMgr}
 * \usage{psp2/sblutmgr.h,SceSblUtMgr_stub}
 */

#ifndef _PSP2_SBLUTMGR_H_
#define _PSP2_SBLUTMGR_H_

#include <psp2/types.h>
#include <psp2common/sblpostssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the remaining validity time for the initialized Utoken.
 *
 * @param[out] remaining_seconds - Receives -1 when no validity deadline is
 * configured, 0 when the deadline has passed, or the number of seconds until
 * the deadline otherwise.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblUtMgrGetCurrentSecureTick(int *remaining_seconds);

/**
 * Copy the Utoken name.
 *
 * @param[out] name - Destination buffer.
 * @param[in] size - Destination size. At most 0x18 bytes are copied.
 */
int sceSblUtMgrIsTrilithiumFlagEnabled(char *name, SceSize size);

/**
 * Read and decrypt the persisted Utoken.
 *
 * @param[out] buf - Pointer to a ::SceUtoken buffer.
 * @param[in] size - Must be at least 0x800; exactly 0x800 bytes are written.
 */
int sceSblUtMgrReadUtoken(char *buf, SceSize size);

int sceSblUtMgrResetUtokenFile(void);

/**
 * Verify and persist an encrypted Utoken.
 *
 * @param[in] buf - Pointer to a ::SceUtoken buffer.
 * @param[in] size - Must be at least 0x800; exactly 0x800 bytes are consumed.
 */
int sceSblUtMgrUpdateUtoken(char *buf, SceSize size);

#define sceSblUtMgrGetUtName sceSblUtMgrIsTrilithiumFlagEnabled

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLUTMGR_H_ */
