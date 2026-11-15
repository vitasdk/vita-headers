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
	SceSize alloc_mem_size; //!< Size in bytes of the CDRAM allocation.
	SceUInt32 reserved0; //!< Stored in the object but otherwise ignored on FW 3.60.
	SceUInt32 reserved[4]; //!< Ignored on FW 3.60.
} SceSharedFbCreate;
VITASDK_BUILD_ASSERT_EQ(0x18, SceSharedFbCreate); // size is from FW 3.60

/** Rendering information supplied by PAF during a shared-framebuffer handoff. */
typedef struct SceSharedFbRenderInfo {
	void *frame_buffer_base; //!< Base address of the selected color buffer.
	SceUInt32 reserved04; //!< Set to 0 by PAF on FW 3.60.
	void *depth_stencil_buffer; //!< Opaque PAF depth/stencil buffer; NULL disables the depth/stencil surface.
	SceUInt32 reserved_0C[4]; //!< Set to 0 by PAF on FW 3.60.
	SceUInt32 stride; //!< Color-buffer stride in pixels.
	SceUInt32 width;
	SceUInt32 height;
	SceUInt32 pixel_format; //!< One of ::SceGxmColorFormat.
	SceInt32 buffer_index; //!< One-based render-buffer index used by PAF.
	SceUInt32 reserved30[4]; //!< Set to 0 by PAF on FW 3.60.
} SceSharedFbRenderInfo;
VITASDK_BUILD_ASSERT_EQ(0x40, SceSharedFbRenderInfo); // size is from FW 3.60

/**
 * Create a shared-framebuffer object.
 *
 * FW 3.60 supports two objects at a time. PAF creates index 1.
 * The calling process must be a system program.
 *
 * @param[in] index Non-negative shared-framebuffer index.
 * @param[in] create_param Required 0x18-byte ::SceSharedFbCreate structure.
 *
 * @return The shared-framebuffer ID on success, or a negative error code.
 */
SceUID sceSharedFbCreate(int index, const SceSharedFbCreate *create_param);

/**
 * Get the current shell render port.
 *
 * @return 0 or 1 on success, or a negative error code.
 */
int sceSharedFbGetShellRenderPort(void);

/**
 * Perform one process handoff after ::sceSharedFbUpdateProcessBegin.
 *
 * Call this function exactly the number of times specified by the
 * `update_count` output of ::sceSharedFbUpdateProcessBegin, then call
 * ::sceSharedFbUpdateProcessEnd.
 *
 * @return 1 when the selected process is marked for rendering, 0 otherwise,
 * or a negative error code.
 */
int sceSharedFbUpdateProcess(void);

/**
 * Begin a shared-framebuffer update.
 *
 * Both pointers must be non-NULL on FW 3.60. The calling process must be a
 * system program and \a shared_fb_id must identify one of the two created shared
 * framebuffers.
 *
 * @param[in] shared_fb_id Shared-framebuffer ID.
 * @param[in] render_info Rendering information copied into the shared framebuffer.
 * @param[out] update_count Receives the 32-bit number of required
 *                         ::sceSharedFbUpdateProcess calls.
 *
 * @return 0 on success, or a negative error code.
 */
int sceSharedFbUpdateProcessBegin(SceUID shared_fb_id, const SceSharedFbRenderInfo *render_info, SceUInt32 *update_count);

/**
 * Complete a process handoff sequence begun by
 * ::sceSharedFbUpdateProcessBegin.
 *
 * This function takes no arguments and must be called after the corresponding
 * update-process loop.
 *
 * @return 0 on success, or a negative error code.
 */
int sceSharedFbUpdateProcessEnd(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SHAREDFB_H_ */
