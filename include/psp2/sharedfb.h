/**
 * \usergroup{SceSharedFb}
 * \usage{psp2/sharedfb.h,SceAppMgr_stub}
 */


#ifndef _PSP2_SHAREDFB_H_
#define _PSP2_SHAREDFB_H_

#include <vitasdk/build_utils.h>
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
VITASDK_BUILD_ASSERT_EQ(0x58, SceSharedFbInfo);

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

typedef struct SceSharedFbCreate {
	SceSize AllocMemSize; //!< Size in bytes of the CDRAM allocation.
	int reserved0; //!< Retained by the object but actually unused on FW 3.60.
	int reserved[4]; //!< Copied from user memory but actually unused on FW 3.60.
} SceSharedFbCreate;
VITASDK_BUILD_ASSERT_EQ(0x18, SceSharedFbCreate); // size is from FW 3.60

/**
 * Creates a shared-framebuffer object.
 *
 * @param[in] index Shared-framebuffer index.
 * @param[in] createParam A 0x18-byte ::SceSharedFbCreate structure.
 *
 * @return The shared-framebuffer ID on success, or a negative error code.
 */
SceUID sceSharedFbCreate(int index, SceSharedFbCreate *createParam);

/**
 * Gets the current shell render port.
 *
 * @return The shell render port on success, or a negative error code.
 */
int sceSharedFbGetShellRenderPort(void);

/**
 * Performs one process handoff after ::sceSharedFbUpdateProcessBegin.
 *
 * @return 1 when the selected process is marked for rendering, 0 otherwise,
 * or a negative error code.
 */
int sceSharedFbUpdateProcess(void);

/**
 * Begins a shared-framebuffer update.
 *
 * @param[in] sharedFbId Shared-framebuffer ID.
 * @param[in] renderInfo A pointer to a 0x40-byte rendering-information block.
 * @param[out] updateCount A pointer to the 32-bit number of subsequent
 * ::sceSharedFbUpdateProcess calls required.
 *
 * @return 0 on success, or a negative error code.
 */
int sceSharedFbUpdateProcessBegin(SceUID sharedFbId, void *renderInfo, void *updateCount);

/**
 * Completes a process handoff sequence begun by
 * ::sceSharedFbUpdateProcessBegin.
 *
 * @return 0 on success, or a negative error code.
 */
int sceSharedFbUpdateProcessEnd(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SHAREDFB_H_ */
