/**
 * \usergroup{SceUpdateMgr}
 * \usage{psp2/update.h,SceSblSsUpdateMgr_stub}
 */

#ifndef _PSP2_UPDATE_MGR_H_
#define _PSP2_UPDATE_MGR_H_

#include <psp2/types.h>

typedef char SceUpdateMode;

#define SCE_UPDATE_MODE_SWU_GUI 0x10
#define SCE_UPDATE_MODE_SWU_CUI 0x30

/**
 * Getting system update mode on boot
 *
 * @param[in] mode - The pointer of SceUpdateMode variable
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsGetUpdateModeForUser(SceUpdateMode *mode);

/**
 * Setting system update mode on boot
 *
 * @param[in] mode - The update mode
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblUsSetUpdateModeForUser(SceUpdateMode mode);

/**
 * Verify PUP
 *
 * @param[in] path - The PUP path
 *
 * @return 0 on success, < 0 on error.
 *
 * note - If verify CEX PUP on Devkit system, got error.
 */
int sceSblUsVerifyPupForUser(const char *path);

#endif /* _PSP2_UPDATE_MGR_H_ */
