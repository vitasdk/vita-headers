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

typedef struct SceAppMgrPhotoMountParam {
	SceSize size; //!< Must be the size of this structure.
	char reserved[0x80]; //!< Ignored on FW 3.60.
} SceAppMgrPhotoMountParam;
VITASDK_BUILD_ASSERT_EQ(0x84, SceAppMgrPhotoMountParam); // size is from FW 3.60

typedef struct SceAppMgrAcInstResult {
	SceUInt8 keystone[0x60]; //!< Add-on-content keystone.
	char game_title[0x80]; //!< NUL-terminated localized game title.
} SceAppMgrAcInstResult;
VITASDK_BUILD_ASSERT_EQ(0xE0, SceAppMgrAcInstResult); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_APPMGR_H_ */
