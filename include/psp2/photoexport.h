/**
 * \usergroup{ScePhotoExport}
 * \usage{psp2/photoexport.h,-lScePhotoExport_stub}
 */

/**
 * \file
 * \brief Header file which defines camera related variables and functions
 *
 * Copyright (C) 2016 vitasdk
 * This header file is licensed under the MIT license.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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

