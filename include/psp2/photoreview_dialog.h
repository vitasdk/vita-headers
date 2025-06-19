/**
 * \usergroup{ScePhotoReviewDialog}
 * \usage{psp2/photo_review_dialog.h,SceCommonDialog_stub}
 */

#ifndef _PSP2_COMMON_DIALOG_PHOTO_REVIEW_DIALOG_H
#define _PSP2_COMMON_DIALOG_PHOTO_REVIEW_DIALOG_H

#include <vitasdk/build_utils.h>
#include <psp2/common_dialog.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _ScePhotoReviewDialogParam {
	SceUInt32 sdkVersion;
	SceCommonDialogParam commonParam;
	SceUInt32 unk_0x50; // seems 1 only?
	SceUInt8 path[0x400];
	void *internal_memory;
	SceSize internal_memory_size;
	SceUInt8 unk_0x454[0x20];
} ScePhotoReviewDialogParam;
VITASDK_BUILD_ASSERT_EQ(0x47C, ScePhotoReviewDialogParam);

typedef struct _ScePhotoReviewDialogResult {
	SceInt32 result;
	SceInt32 unk_0x04;
	SceChar8 reserved[0x1C];
} ScePhotoReviewDialogResult;
VITASDK_BUILD_ASSERT_EQ(0x24, ScePhotoReviewDialogResult);

static inline void scePhotoReviewDialogParamInit(ScePhotoReviewDialogParam *param)
{
	sceClibMemset(param, 0, sizeof(*param));
	_sceCommonDialogSetMagicNumber(&(param->commonParam));
	param->sdkVersion = PSP2_SDK_VERSION;
}

int scePhotoReviewDialogInit(ScePhotoReviewDialogParam *param);
int scePhotoReviewDialogTerm(void);
int scePhotoReviewDialogGetResult(ScePhotoReviewDialogResult *result);
int scePhotoReviewDialogGetStatus(void);
int scePhotoReviewDialogAbort(void);


#ifdef __cplusplus
}
#endif

#endif
