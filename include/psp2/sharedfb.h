/**
 * \usergroup{SceSharedFb}
 * \usage{psp2/sharedfb.h,SceAppMgr_stub}
 */


#ifndef _PSP2_SHAREDFB_H_
#define _PSP2_SHAREDFB_H_

#include <psp2/types.h>
#include <psp2common/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceSharedFbInfo {
	void *fb_base;
	int fb_size;
	void *fb_base2;
	int unk0[6];
	int stride;
	int width;
	int height;
	int unk1;
	int index;
	int unk2[4];
	int vsync;
	int unk3[3];
} SceSharedFbInfo;

SceUID _sceSharedFbOpen(int index, int sysver);
int sceSharedFbClose(SceUID fb_id);
int sceSharedFbBegin(SceUID fb_id, SceSharedFbInfo *info);
int sceSharedFbEnd(SceUID fb_id);
int sceSharedFbGetInfo(SceUID fb_id, SceSharedFbInfo *info);

static inline
SceUID sceSharedFbOpen(int index)
{
	return _sceSharedFbOpen(index, PSP2_SDK_VERSION);
};

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SHAREDFB_H_ */
