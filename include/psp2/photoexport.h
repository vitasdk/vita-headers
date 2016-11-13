/**
 * \addtogroup SystemParams System Parameters
 * Various parameters about the system
 * \{
 */

/**
 * \addtogroup ScePhotoExport Photo Export Library
 * Export a photo from a file or data
 */

/** \} */

/**
 * \defgroup ScePhotoExportUser User
 *  \ingroup ScePhotoExport
 * Exports for User
 *
 * ------------------------
 * ### Using this library in your project ###
 * Include the header file in your project:
 * \code
 * #include <psp2/photoexport.h>
 * \endcode
 *
 * Link the library in your makefile:
 * \code
 * -lScePhotoExport_stub
 * \endcode
 * ------------------------
 * \{
 */

/**
 * \file
 * \brief Header file which defines camera related variables and functions
 */

#ifndef _PSP2_PHOTO_EXPORT_H_
#define _PSP2_PHOTO_EXPORT_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PhotoExportParam {
	int version;
	const SceWChar32 *photoTitle; //!< Photo title
	const SceWChar32 *gameTitle;  //!< Game title
	const SceWChar32 *gameComment;  //!< Game description
	int reserved[8];
} PhotoExportParam;

int scePhotoExportFromData(const void* data, SceSize size, const PhotoExportParam* param, void* workingMemory, void* cancelCb, void* user, char* outPath, SceSize outPathSize);
int scePhotoExportFromFile(const char* path, const PhotoExportParam* param, void* workingMemory, void* cancelCb, void* user, char* outPath, SceSize outPathSize);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PHOTO_EXPORT_H_ */

/** \} */
