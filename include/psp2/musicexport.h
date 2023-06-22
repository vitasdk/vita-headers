/**
 * \usergroup{SceMusicExport}
 * \usage{psp2/musicexport.h,SceMusicExport_stub}
 */


#ifndef _PSP2_MUSICEXPORT_H_
#define _PSP2_MUSICEXPORT_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MusicExportParam {
	char reserved[128];  //!< Reserved data
} MusicExportParam;
VITASDK_BUILD_ASSERT_EQ(0x80, MusicExportParam);

int sceMusicExportFromFile(const char* path, const MusicExportParam* param, void* workingMemory, void* cancelCb, void (*progress)(void*, int), void* user, char* outPath, SceSize outPathSize);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MUSICEXPORT_H_ */

