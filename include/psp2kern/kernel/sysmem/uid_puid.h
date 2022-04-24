/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/uid_puid.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_UID_PUID_H_
#define _PSP2KERN_KERNEL_SYSMEM_UID_PUID_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Open Process UID by Global UID (Create PUID)
 *
 * param[in] pid  - The target process id.
 * param[in] guid - The target GUID.
 *
 * return PUID on success, < 0 on error
 */
SceUID kscePUIDOpenByGUID(SceUID pid, SceUID guid);

/*
 * Close Process UID (Remove PUID)
 *
 * param[in] pid  - The target process id.
 * param[in] puid - The target PUID.
 *
 * return PUID on success, < 0 on error
 */
int kscePUIDClose(SceUID pid, SceUID puid);

/*
 * Get Global UID by Process UID
 *
 * param[in] pid  - The target process id.
 * param[in] puid - The target PUID.
 *
 * return GUID on success, < 0 on error
 */
SceUID kscePUIDtoGUID(SceUID pid, SceUID puid);

#define ksceKernelKernelUidForUserUid(pid, puid) kscePUIDtoGUID(pid, puid)
#define ksceKernelCreateUserUid(pid, guid) kscePUIDOpenByGUID(pid, guid)
#define ksceKernelDeleteUserUid(pid, puid) kscePUIDClose(pid, puid)

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_UID_PUID_H_ */
