/**
 * \kernelgroup{ScePfsMgr}
 * \usage{psp2kern/pfsmgr.h,ScePfsMgrForKernel_stub}
 */

#ifndef _PSP2_KERNEL_PFSMGR_H_
#define _PSP2_KERNEL_PFSMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScePfsRndDriveId {
	char s[0x10];
} ScePfsRndDriveId;

/**
 * Mount pfs directory
 *
 * @param[in] path         - The pfs encrypted directory path
 * @param[in] rnd_drive_id - The pfs mount output drive strings
 * @param[in] authid       - The authid
 * @param[in] klicensee    - The klicensee
 * @param[in] mode_index   - The mode_index
 *
 * @return 0 on success, < 0 on error.
 */
int kscePfsMount(const char *path, ScePfsRndDriveId *rnd_drive_id, SceUInt64 authid, void *klicensee, uint16_t mode_index);

/**
 * Mount pfs directory without authid
 *
 * @param[in] path         - The pfs encrypted directory path
 * @param[in] rnd_drive_id - The pfs mount output drive strings
 * @param[in] klicensee    - The klicensee
 * @param[in] mode_index   - The mode_index
 *
 * @return 0 on success, < 0 on error.
 */
int kscePfsMount2(const char *path, ScePfsRndDriveId *rnd_drive_id, void *klicensee, uint16_t mode_index);

/**
 * Unmount pfs directory
 *
 * @param[in] rnd_drive_id - The pfs mount drive strings
 *
 * @return 0 on success, < 0 on error.
 */
int kscePfsUnmount(ScePfsRndDriveId *rnd_drive_id);

int kscePfsApprove(ScePfsRndDriveId *rnd_drive_id, SceUInt64 authid);
int kscePfsDisapprove(ScePfsRndDriveId *rnd_drive_id, SceUInt64 program_authority_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PFSMGR_H_ */
