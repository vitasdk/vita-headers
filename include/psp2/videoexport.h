/**
 * \usergroup{SceVideoExport}
 * \usage{psp2/videoexport.h,SceVideoExport_stub}
 */


#ifndef _PSP2_VIDEOEXPORT_H_
#define _PSP2_VIDEOEXPORT_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VideoExportInputParam {
	char path[1024]; //!< Path of file to be exported
	char reserved[64]; //!< Reserved data
} VideoExportInputParam;

typedef struct VideoExportOutputParam {
	char path[1024]; //!< Path of exported file
	char reserved[8]; //!< Reserved data
} VideoExportOutputParam;

/**
 * Export video file
 *
 * @param[in] in_param - Input param
 * @param[in] unk - Unknown, pass 1
 * @param[in] workingMemory - Working memory
 * @param[in] cancelCb - Cancel callback
 * @param[in] progress - Progress callback
 * @param[in] user - User data passed to the callbacks
 * @param[in] unk2 - Unknown, pass 0
 * @param[out] out_param - Output param
 *
 * @return 0 on success, < 0 on error.
*/
int sceVideoExportFromFile(const VideoExportInputParam* in_param, int unk, void* workingMemory, void* cancelCb, void (*progress)(void*, int), void* user, int unk2, VideoExportOutputParam* out_param);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_VIDEOEXPORT_H_ */