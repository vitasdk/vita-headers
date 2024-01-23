/**
 * \kernelgroup{SceSblGcAuthMgr}
 * \usage{psp2kern/kernel/gcauthmgr/drm_bb.h,SceSblGcAuthMgrDrmBBForDriver_stub}
 */

#ifndef __PSP2KERN_GCAUTHMGR_DRM_BB_H__
#define __PSP2KERN_GCAUTHMGR_DRM_BB_H__

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Removes derived cart secret from memory.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblGcAuthMgrDrmBBClearCartSecret(void);

/**
 * @brief Gets derived cart secret from memory.
 *
 * @param[in]  secret - Pointer to 0x20 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblGcAuthMgrDrmBBGetCartSecret(void* secret);

#ifdef __cplusplus
}
#endif

#endif /* __PSP2KERN_GCAUTHMGR_DRM_BB_H__ */