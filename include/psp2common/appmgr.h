/**
 * \kernelgroup{SceAppMgr}
 * \usage{psp2common/appmgr.h}
 */

#ifndef _PSP2COMMON_APPMGR_H_
#define _PSP2COMMON_APPMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef char SceTitleId[16];
VITASDK_BUILD_ASSERT_EQ(0x10, SceTitleId);

typedef struct sceAppMgrPhotoMountParam {
	SceSize size;
	char reserved[0x80]; //!< Copied from user memory but actually unused on FW 3.60.
} sceAppMgrPhotoMountParam;
VITASDK_BUILD_ASSERT_EQ(0x84, sceAppMgrPhotoMountParam); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_APPMGR_H_ */
