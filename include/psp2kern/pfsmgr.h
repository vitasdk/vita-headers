/**
 * \kernelgroup{ScePfsMgr}
 * \usage{psp2kern/pfsmgr.h,ScePfsMgrForKernel_stub}
 */

#ifndef _PSP2KERN_PFSMGR_H_
#define _PSP2KERN_PFSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/pfsmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Mount pfs directory
 *
 * @param[in] path         - The pfs encrypted directory path
 * @param[in] rnd_drive_id - The pfs mount target Pseudo Drive strings
 * @param[in] program_authority_id - The program authority ID
 * @param[in] klicensee    - The klicensee
 * @param[in] mode_index   - The mode_index
 *
 * @return 0 on success, < 0 on error.
 */
int kscePfsMount(const char *path, const ScePfsRndDriveId *rnd_drive_id, SceUInt64 program_authority_id, const void *klicensee, uint16_t mode_index);

/**
 * Mount pfs directory without authid
 *
 * @param[in] path         - The pfs encrypted directory path
 * @param[in] rnd_drive_id - The pfs mount target Pseudo Drive strings
 * @param[in] klicensee    - The klicensee
 * @param[in] mode_index   - The mode_index
 *
 * @return 0 on success, < 0 on error.
 */
int kscePfsMount2(const char *path, const ScePfsRndDriveId *rnd_drive_id, const void *klicensee, uint16_t mode_index);

/**
 * Unmount pfs directory
 *
 * @param[in] rnd_drive_id - The pfs mount drive strings
 *
 * @return 0 on success, < 0 on error.
 */
int kscePfsUnmount(const ScePfsRndDriveId *rnd_drive_id);

int kscePfsApprove(const ScePfsRndDriveId *rnd_drive_id, SceUInt64 program_authority_id);
int kscePfsDisapprove(const ScePfsRndDriveId *rnd_drive_id, SceUInt64 program_authority_id);

/**
 * Approve an ACID-protected add-on-content directory.
 *
 * FW 3.60 opens `<mount_point_prefix>0:<dlc_folder>`, issues ioctl 0x4403,
 * and closes the directory. Both strings must remain valid until this function
 * returns; they are not used afterwards. The maximum lengths are 31 bytes for
 * \a mount_point_prefix and 62 bytes for \a dlc_folder, excluding NUL terminators.
 * NULL, empty, or overlong strings return 0x80010016.
 *
 * @param[in] mount_point_prefix - Prefix used to build the directory path.
 * @param[in] dlc_folder - Add-on-content directory component.
 *
 * @return The ioctl result, an error from closing the directory if the ioctl
 * succeeded, or another negative I/O error.
 */
int kscePfsAcidDirApprove(const char *mount_point_prefix, const char *dlc_folder);

/**
 * Mount an ACID-protected add-on-content directory.
 *
 * FW 3.60 opens `<mount_point_prefix>0:<dlc_folder>`, then issues ioctl 0x4402
 * with exactly 16 input bytes from \a klicensee and no output buffer. The
 * klicensee may be NULL. After validating the add-on-content license metadata,
 * AppMgr passes NULL when its 16-byte key is all zero and otherwise passes the key.
 * The strings and optional key buffer must remain valid until this function
 * returns; they are not used afterwards.
 * AppMgr invokes this operation with thread-access permission 0x40; the PFS
 * VFS implementation checks whether the caller is authorized.
 * NULL, empty, or overlong strings return 0x80010016.
 *
 * @param[in] mount_point_prefix - Prefix used to build the directory path.
 * @param[in] dlc_folder - Add-on-content directory component.
 * @param[in] klicensee - Optional 16-byte content key.
 *
 * @return The ioctl result, an error from closing the directory if the ioctl
 * succeeded, or another negative I/O error.
 */
int kscePfsAcidDirMount(const char *mount_point_prefix, const char *dlc_folder, const void *klicensee);

/**
 * Unmount an ACID-protected add-on-content directory.
 *
 * FW 3.60 opens `<mount_point_prefix>0:<dlc_folder>`, issues ioctl 0x4404,
 * and closes the directory. Both strings must remain valid until this function
 * returns; they are not used afterwards. The maximum lengths are 31 bytes for
 * \a mount_point_prefix and 62 bytes for \a dlc_folder, excluding NUL terminators.
 * NULL, empty, or overlong strings return 0x80010016.
 *
 * @param[in] mount_point_prefix - Prefix used to build the directory path.
 * @param[in] dlc_folder - Add-on-content directory component.
 *
 * @return The ioctl result, an error from closing the directory if the ioctl
 * succeeded, or another negative I/O error.
 */
int kscePfsAcidDirUnmount(const char *mount_point_prefix, const char *dlc_folder);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_PFSMGR_H_ */
