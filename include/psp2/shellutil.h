/**
 * \addtogroup SystemStatus System Status
 * Time, battery...
 * \{
 */

/**
 * \addtogroup SceShellSvc Shell Utils Library 
 * Set handlers for opening various menus
 */

/** \} */

/**
 * \defgroup SceShellSvcUser User
 *  \ingroup SceShellSvc
 * Exports for User
 *
 * ------------------------
 * ### Using this library in your project ###
 * Include the header file in your project:
 * \code
 * #include <psp2/shellutil.h>
 * \endcode
 *
 * Link the library in your makefile:
 * \code
 * -lSceShellSvc_stub
 * \endcode
 * ------------------------
 * \{
 */

/**
 * \file
 * \brief Header file which defines shell utils
 *
 * Copyright (C) 2016 Vitasdk developers
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_SHELLUTIL_H_
#define _PSP2_SHELLUTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN			= 0x1,
	SCE_SHELL_UTIL_LOCK_TYPE_QUICK_MENU		= 0x2,
	SCE_SHELL_UTIL_LOCK_TYPE_POWEROFF_MENU	= 0x4,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK8			= 0x8,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK10			= 0x10,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK20			= 0x20,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK40			= 0x40,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK80			= 0x80,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK100			= 0x100,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK200			= 0x200,
	SCE_SHELL_UTIL_LOCK_TYPE_MUSIC_PLAYER	= 0x400,
	SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN_2		= 0x800, //! without the stop symbol
};

enum {
	SCE_SHELL_UTIL_LOCK_MODE_LOCK		= 0x1,
	SCE_SHELL_UTIL_LOCK_MODE_UNLOCK		= 0x2,
};

typedef void (SceShellUtilEventHandler)(int result, int mode, int type, void *userData);

/**
 * Init events
 *
 * @param[in] unk - Unknown, use 0
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilInitEvents(int unk);

/**
 * Register event handler
 *
 * @param[in] handler - Event handler
 *
 * @param[in] userData - The user data passed to the handler
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilRegisterEventHandler(SceShellUtilEventHandler *handler, void *userData);

/**
 * Lock event
 *
 * @param[in] type - One of ::ShellUtilLockType
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilLock(int type);

/**
 * Unlock event
 *
 * @param[in] type - One of ::ShellUtilLockType
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilUnlock(int type);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SHELLUTIL_H_ */

/** \} */
