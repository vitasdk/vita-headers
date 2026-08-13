/**
 * \kernelgroup{ScePfsMgr}
 * \usage{psp2common/pfsmgr.h}
 */

#ifndef _PSP2COMMON_PFSMGR_H_
#define _PSP2COMMON_PFSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScePfsRndDriveId {
	char drive_id[0x10];
} ScePfsRndDriveId;
VITASDK_BUILD_ASSERT_EQ(0x10, ScePfsRndDriveId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_PFSMGR_H_ */
