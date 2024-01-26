/**
 * \kernelgroup{SceSblGcAuthMgr}
 * \usage{psp2kern/kernel/gcauthmgr/gc_auth.h,SceSblGcAuthMgrGcAuthForDriver_stub}
 */

#ifndef __PSP2KERN_GCAUTHMGR_GC_AUTH_H__
#define __PSP2KERN_GCAUTHMGR_GC_AUTH_H__

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Runs gamecart authentication
 *
 * @param[in]  key_id - Not used for anything but must be < 0x10000.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblGcAuthMgrGcAuthCartAuthentication(SceUInt32 key_id);

#ifdef __cplusplus
}
#endif

#endif /* __PSP2KERN_GCAUTHMGR_GC_AUTH_H__ */