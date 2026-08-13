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
 * @param[in] pHash - Pointer to a 0x14-byte SHA-1 digest.
 * @param[in] pSig - Pointer to a 0x28-byte ECDSA signature.
 *
 * @return 0 if the signature is valid, < 0 on error.
 */
int ksceSblGcAuthMgrPkgVry(const char *pHash, const char *pSig);

#ifdef __cplusplus
}
#endif

#endif /* __PSP2KERN_GCAUTHMGR_PKG_H__ */
