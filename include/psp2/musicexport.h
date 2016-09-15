/**
 * \file
 * \brief Header file which defines music related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_MUSIC_EXPORT_H_
#define _PSP2_MUSIC_EXPORT_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MusicExportParam {
	char reserved[128];
} MusicExportParam;

int sceMusicExportFromFile(const char* path, const MusicExportParam* param, void* workingMemory, void* cancelCb, void (*progress)(void*, int), void* user, char* outPath, SceSize outPathSize);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MUSIC_EXPORT_H_ */
