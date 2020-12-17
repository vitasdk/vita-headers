/**
 * \usergroup{SceShellSvc}
 * \usage{psp2/shellutil.h,SceShellSvc_stub}
 */


#ifndef _PSP2_SHELLUTIL_H_
#define _PSP2_SHELLUTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceShellUtilLockType {
	SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN             = 0x1,
	SCE_SHELL_UTIL_LOCK_TYPE_QUICK_MENU         = 0x2,
	SCE_SHELL_UTIL_LOCK_TYPE_POWEROFF_MENU      = 0x4,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK8               = 0x8,
	SCE_SHELL_UTIL_LOCK_TYPE_USB_CONNECTION     = 0x10,
	SCE_SHELL_UTIL_LOCK_TYPE_MC_INSERTED        = 0x20,
	SCE_SHELL_UTIL_LOCK_TYPE_MC_REMOVED         = 0x40,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK80              = 0x80,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK100             = 0x100,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK200             = 0x200,
	SCE_SHELL_UTIL_LOCK_TYPE_MUSIC_PLAYER       = 0x400,
	SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN_2           = 0x800 //! without the stop symbol
} SceShellUtilLockType;

typedef enum SceShellUtilLockMode {
	SCE_SHELL_UTIL_LOCK_MODE_LOCK       = 1,
	SCE_SHELL_UTIL_LOCK_MODE_UNLOCK     = 2
} SceShellUtilLockMode;

typedef void (SceShellUtilEventHandler)(int result, SceShellUtilLockMode mode, SceShellUtilLockType type, void *userData);

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
 * @param[in] type - One of ::SceShellUtilLockType
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilLock(SceShellUtilLockType type);

/**
 * Unlock event
 *
 * @param[in] type - One of ::SceShellUtilLockType
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilUnlock(SceShellUtilLockType type);

typedef struct SceShellUtilLaunchAppParam {
	const char *cmd;
} SceShellUtilLaunchAppParam;

int sceShellUtilRequestLaunchApp(SceShellUtilLaunchAppParam *param);
int sceShellUtilLaunchAppRequestLaunchApp(SceShellUtilLaunchAppParam *param);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SHELLUTIL_H_ */

