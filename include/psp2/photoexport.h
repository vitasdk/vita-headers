/**
 * \usergroup{ScePhotoExport}
 * \usage{psp2/photoexport.h,ScePhotoExport_stub,SCE_SYSMODULE_PHOTO_EXPORT}
 */


#ifndef _PSP2_PHOTOEXPORT_H_
#define _PSP2_PHOTOEXPORT_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PhotoExportParam {
	int version;                    //!< Version
	const SceWChar32 *photoTitle;   //!< Photo title
	const SceWChar32 *gameTitle;    //!< Game title
	const SceWChar32 *gameComment;  //!< Game description
	int reserved[8];                //!< Reserved data
} PhotoExportParam;
VITASDK_BUILD_ASSERT_EQ(0x30, PhotoExportParam);

int scePhotoExportFromData(const void* data, SceSize size, const PhotoExportParam* param, void* workingMemory, void* cancelCb, void* user, char* outPath, SceSize outPathSize);
int scePhotoExportFromFile(const char* path, const PhotoExportParam* param, void* workingMemory, void* cancelCb, void* user, char* outPath, SceSize outPathSize);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PHOTOEXPORT_H_ */
