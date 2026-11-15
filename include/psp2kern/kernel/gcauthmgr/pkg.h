/**
 * \kernelgroup{SceSblGcAuthMgrPkg}
 * \usage{psp2kern/kernel/gcauthmgr/pkg.h,SceSblGcAuthMgrPkgForDriver_stub}
 */

#ifndef __PSP2KERN_GCAUTHMGR_PKG_H__
#define __PSP2KERN_GCAUTHMGR_PKG_H__

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Verify a package ECDSA-160 signature.
 *
 * Both pointers must be non-NULL. Their buffers must remain valid until this
 * function returns; they are not used afterwards.
 *
 * @param[in] hash - Complete 0x14-byte SHA-1 digest.
 * @param[in] signature - Complete 0x28-byte raw ECDSA-160 signature.
 *
 * @return 0 when valid; 0x808A0008 for a semaphore failure; or 0x808A000C for
 *         invalid input or a rejected signature. Errors from the secure
 *         verification call are returned as 0x808A000C.
 */
int ksceSblGcAuthMgrPkgVry(const SceUInt8 *hash, const SceUInt8 *signature);

#ifdef __cplusplus
}
#endif

#endif /* __PSP2KERN_GCAUTHMGR_PKG_H__ */
