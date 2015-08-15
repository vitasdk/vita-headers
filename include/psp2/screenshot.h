/**
 * \file
 * \brief Header file which defines output audio related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_SCREENSHOT_H_
#define _PSP2_SCREENSHOT_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_SCREENSHOT_ERROR_INVALID_ARGUMENT		= 0x80102f01,
	SCE_SCREENSHOT_ERROR_NO_MEMORY			= 0x80102f02,
	SCE_SCREENSHOT_ERROR_FILE_NOT_FOUND		= 0x80102f03,
	SCE_SCREENSHOT_ERROR_NOT_SUPPORTED_FORMAT	= 0x80102f04,
	SCE_SCREENSHOT_ERROR_MEDIA_FULL			= 0x80102f05,
	SCE_SCREENSHOT_ERROR_INTERNAL			= 0x80102f06
};

//! Max size of path strings (includes device name and NULL terminator)
#define SCE_SCREENSHOT_MAX_FS_PATH		(1024)

//! Max length of photo title
#define SCE_SCREENSHOT_MAX_PHOTO_TITLE_LEN	(64)

//! Max size of photo title (includes NULL terminater)
#define SCE_SCREENSHOT_MAX_PHOTO_TITLE_SIZE (SCE_SCREENSHOT_MAX_PHOTO_TITLE_LEN * 4)

//! Max length of game title
#define SCE_SCREENSHOT_MAX_GAME_TITLE_LEN	(64)

//! Max size of game title (includes NUL terminator)
#define SCE_SCREENSHOT_MAX_GAME_TITLE_SIZE	(SCE_SCREENSHOT_MAX_GAME_TITLE_LEN * 4)

//! Max length of comment (description)
#define SCE_SCREENSHOT_MAX_GAME_COMMENT_LEN	(128)

//! Max size of comment (description) (includes NUL terminator)
#define SCE_SCREENSHOT_MAX_GAME_COMMENT_SIZE	(SCE_SCREENSHOT_MAX_GAME_COMMENT_LEN * 4)

typedef struct ScreenshotParam {
	const SceWChar32 *photoTitle; //!< Photo title
	const SceWChar32 *gameTitle;  //!< Game title
	const SceWChar32 *gameComment;  //!< Game description
	void *reserved; //!< Reserved range (Must be NULL)
} ScreenshotParam;

//! Set screenshot params
int sceScreenshotSetParam(const ScreenshotParam *param);

//! Set overlay image
int sceScreenshotOverlayImage(const char *filepath, int offsetX, int offsetY);

//! Disable screenshot
int sceScreenshotDisable(void);

//! Enable screnshot
int sceScreenshotEnable(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SCREENSHOT_H_ */
