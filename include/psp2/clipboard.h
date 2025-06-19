/**
 * \usergroup{SceClipboard}
 * \usage{psp2/clipboard.h,SceClipboard_stub,SCE_SYSMODULE_CLIPBOARD}
 */
#ifndef _PSP2_CLIPBOARD_H
#define _PSP2_CLIPBOARD_H

#include <psp2/types.h>
#include <psp2/libime.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SCE_CLIPBOARD_MAX_STRING_LENGTH		8189

#define SCE_CLIPBOARD_ERROR_INTERNAL				-2146417152	/* 0x80104600 */
#define SCE_CLIPBOARD_ERROR_NULL_POINTER			-2146417151	/* 0x80104601 */
#define SCE_CLIPBOARD_ERROR_TEXT_TOO_LONG			-2146417150	/* 0x80104602 */
#define SCE_CLIPBOARD_ERROR_UNSUPPORTED_CHARACTER	-2146417149	/* 0x80104603 */

SceInt32 sceClipboardSetText(const SceWChar16* newContents, SceUInt length);

SceInt32 sceClipboardGetText(SceWChar16* buffer, SceUInt maxLength, SceUInt* pLength);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_CLIPBOARD_H */
