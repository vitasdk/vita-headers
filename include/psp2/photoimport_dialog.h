/**
 * \usergroup{ScePhotoImportDialog}
 * \usage{psp2/photo_import_dialog.h,SceCommonDialog_stub}
 */

#ifndef _PSP2_COMMON_DIALOG_PHOTO_IMPORT_DIALOG_H
#define _PSP2_COMMON_DIALOG_PHOTO_IMPORT_DIALOG_H

#include <vitasdk/build_utils.h>
#include <psp2/common_dialog.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _ScePhotoImportDialogImportInfo {
	char path[0x400];
	char unk_0x400[0x100];
	SceUInt8 unk_0x500[0x20];
	int unk_0x520;
	int unk_0x524;
	int unk_0x528;
	int unk_0x52C;
} ScePhotoImportDialogImportInfo;
VITASDK_BUILD_ASSERT_EQ(0x530, ScePhotoImportDialogImportInfo); // not sure for size.

typedef struct _ScePhotoImportDialogParam {
	SceUInt32 sdkVersion;
	SceCommonDialogParam commonParam;
	SceUInt32 unk_0x50; // should be 0
	SceUInt32 unk_0x54; // should be `(unk_0x54 & 7) != 0 && (unk_0x54 & ~7) == 0`
	SceUInt32 unk_0x58;
	void *unk_0x5C;
	SceUInt8 unk_0x60[0x20];
} ScePhotoImportDialogParam;
VITASDK_BUILD_ASSERT_EQ(0x80, ScePhotoImportDialogParam);

typedef struct _ScePhotoImportDialogResult {
	SceInt32 result;
	SceInt32 unk_0x04;
	SceChar8 reserved[0x20];
} ScePhotoImportDialogResult;
VITASDK_BUILD_ASSERT_EQ(0x28, ScePhotoImportDialogResult);

static inline void scePhotoImportDialogParamInit(ScePhotoImportDialogParam *param)
{
	sceClibMemset( param, 0x0, sizeof(*param));
	_sceCommonDialogSetMagicNumber(&(param->commonParam));
	param->sdkVersion = PSP2_SDK_VERSION;
}

int scePhotoImportDialogInit(ScePhotoImportDialogParam *param);
int scePhotoImportDialogTerm(void);
int scePhotoImportDialogGetResult(ScePhotoImportDialogResult *result);
int scePhotoImportDialogGetStatus(void);
int scePhotoImportDialogAbort(void);


#ifdef __cplusplus
}
#endif

#endif
