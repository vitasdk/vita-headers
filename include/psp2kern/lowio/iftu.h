/**
 * \kernelgroup{SceIftu}
 * \usage{psp2kern/lowio/iftu.h,SceIftuForDriver_stub}
 */

#ifndef _PSP2KERN_LOWIO_IFTU_H_
#define _PSP2KERN_LOWIO_IFTU_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceIftuErrorCode {
	SCE_IFTU_ERROR_INVALID_PLANE		= 0x803F0700,
	SCE_IFTU_ERROR_INVALID_PARAM		= 0x803F0701,
	SCE_IFTU_ERROR_INVALID_PIXELFORMAT	= 0x803F0703,
	SCE_IFTU_ERROR_PLANE_BUSY		= 0x803F0704,
} SceIftuErrorCode;

typedef enum SceIftuPixelformat {
	SCE_IFTU_PIXELFORMAT_BGR565		= 0x01,
	SCE_IFTU_PIXELFORMAT_RGB565		= 0x02,
	SCE_IFTU_PIXELFORMAT_BGRA5551		= 0x04,
	SCE_IFTU_PIXELFORMAT_RGBA5551		= 0x08,
	SCE_IFTU_PIXELFORMAT_BGRX8888		= 0x10,
	SCE_IFTU_PIXELFORMAT_RGBX8888		= 0x20,
	SCE_IFTU_PIXELFORMAT_BGRA1010102	= 0x40,
	SCE_IFTU_PIXELFORMAT_RGBA1010102	= 0x80,
	SCE_IFTU_PIXELFORMAT_BGRP		= 0x100,	/* 3 planes - R, G, B */
	SCE_IFTU_PIXELFORMAT_RGBX8888_MULT	= 0x1000,
	SCE_IFTU_PIXELFORMAT_BGRX8888_MULT	= 0x2000,
	SCE_IFTU_PIXELFORMAT_RGBA1010102_MULT	= 0x4000,
	SCE_IFTU_PIXELFORMAT_BGRA1010102_MULT	= 0x8000,
	SCE_IFTU_PIXELFORMAT_NV12		= 0x10000,	/* 2 planes - Y, Cb + Cr interleaved */
	SCE_IFTU_PIXELFORMAT_YUV420		= 0x20000,	/* 3 planes - Y, Cb, Cr */
	SCE_IFTU_PIXELFORMAT_YUV422		= 0x200000,	/* 3 planes - Y, Cb, Cr */
} SceIftuPixelformat;

typedef enum SceIftuFilterMode {
	SCE_IFTU_FILTER_MODE_NEAREST  = 0,
	SCE_IFTU_FILTER_MODE_BILINEAR = 1
} SceIftuFilterMode;
VITASDK_BUILD_ASSERT_EQ(1, SceIftuFilterMode);

typedef enum SceIftuFieldMode {
	SCE_IFTU_FIELD_MODE_PROGRESSIVE        = 0,
	SCE_IFTU_FIELD_MODE_UNK_1              = 1,
	SCE_IFTU_FIELD_MODE_INTERLACED_FIELD_0 = 2,
	SCE_IFTU_FIELD_MODE_INTERLACED_FIELD_1 = 3
} SceIftuFieldMode;
VITASDK_BUILD_ASSERT_EQ(1, SceIftuFieldMode);

typedef struct SceIftuCscParams {
	unsigned int post_add_0;		//!< 10-bit post-add offset for component 0.
	unsigned int post_add_1_2;		//!< 10-bit post-add value shared by components 1 and 2.
	unsigned int post_clamp_max_0;		//!< 10-bit upper clamp limit for component 0.
	unsigned int post_clamp_min_0;		//!< 10-bit lower clamp limit for component 0.
	unsigned int post_clamp_max_1_2;	//!< 10-bit upper clamp limit shared by components 1 and 2.
	unsigned int post_clamp_min_1_2;	//!< 10-bit lower clamp limit shared by components 1 and 2.
	unsigned int ctm[3][3];			//!< Signed S3.9 fixed-point values stored as 12-bit two's-complement register fields.
} SceIftuCscParams;
VITASDK_BUILD_ASSERT_EQ(0x3C, SceIftuCscParams);

typedef struct SceIftuConvParams {
	unsigned int size;               //!< Structure size; FW 3.60 does not validate it.
	unsigned int bilinear;           //!< One of ::SceIftuFilterMode.
	SceIftuCscParams *csc_params1;   //!< Optional read-only parameters for the CSC register block starting at 0x130.
	SceIftuCscParams *csc_params2;   //!< Optional read-only parameters for the CSC register block starting at 0x104.
	unsigned int csc_control;        //!< Raw CSC control-register value.
	unsigned int background_color_0; //!< 10-bit background component 0 in the input color space.
	unsigned int background_color_1; //!< 10-bit background component 1 in the input color space.
	unsigned int background_color_2; //!< 10-bit background component 2 in the input color space.
	unsigned int alpha;              //!< Alpha value. The default is 0xFF.
	unsigned int field_mode;         //!< One of ::SceIftuFieldMode; only the low two bits are used.
} SceIftuConvParams;
VITASDK_BUILD_ASSERT_EQ(0x28, SceIftuConvParams);

typedef struct SceIftuFrameBuf {
	unsigned int pixelformat;              //!< One of ::SceIftuPixelformat or a documented extended format.
	unsigned int width;                    //!< Frame width in pixels; known FW 3.60 callers align it to 16 pixels.
	unsigned int height;                   //!< Frame height in pixels; known FW 3.60 callers align it to 8 pixels.
	unsigned int leftover_stride;          //!< Additional bytes after each luma or packed-pixel row.
	unsigned int plane1_2_leftover_stride; //!< Additional bytes after each chroma row.
	unsigned int paddr0;                   //!< Physical address of plane 0.
	unsigned int paddr1;                   //!< Physical address of plane 1, or zero when unused.
	unsigned int paddr2;                   //!< Physical address of plane 2, or zero when unused.
} SceIftuFrameBuf;
VITASDK_BUILD_ASSERT_EQ(0x20, SceIftuFrameBuf);

typedef struct SceIftuPlaneState {
	SceIftuFrameBuf fb;
	unsigned int reserved[3]; //!< Values written to undocumented IFTU registers; their purpose is unknown.
	unsigned int src_w;       //!< Horizontal source-sampling step per destination pixel in 16.16 fixed-point format.
	unsigned int src_h;       //!< Vertical source-sampling step per destination pixel in 16.16 fixed-point format.
	unsigned int dst_x;       //!< Destination X coordinate in pixels.
	unsigned int dst_y;       //!< Destination Y coordinate in pixels.
	unsigned int src_x;       //!< Horizontal source-sampling offset in unsigned 8.8 fixed-point format.
	unsigned int src_y;       //!< Vertical source-sampling offset in unsigned 8.8 fixed-point format.
	unsigned int crop_top;    //!< Number of source pixels cropped from the top.
	unsigned int crop_bottom; //!< Number of source pixels cropped from the bottom.
	unsigned int crop_left;   //!< Number of source pixels cropped from the left.
	unsigned int crop_right;  //!< Number of source pixels cropped from the right.
} SceIftuPlaneState;
VITASDK_BUILD_ASSERT_EQ(0x54, SceIftuPlaneState);

/**
 * Convert a frame with the standalone IFTU2 engine and wait for completion.
 *
 * \a dst and \a src must be non-NULL; FW 3.60 dereferences them without
 * checking for NULL. The structures they point to are read-only. \a params
 * may be NULL, which selects bilinear filtering, no CSC control, a zero
 * background, alpha 0xFF, and progressive field mode.
 *
 * FW 3.60 does not read or validate ::SceIftuConvParams::size. Interlaced
 * callers perform one conversion with field mode 2 or 3 and a second
 * conversion with the other mode. How these modes correspond to the top and
 * bottom fields depends on the source description and is not established.
 *
 * The source accepts every ::SceIftuPixelformat value, zero, 0x80020000,
 * 0x80140000, and 0x80180000. The purpose of these three extended
 * formats is unknown. The destination accepts every ::SceIftuPixelformat
 * value and ignores bit 31 while validating it.
 *
 * @param[in] dst - Destination frame-buffer description.
 * @param[in] src - Source plane state.
 * @param[in] params - Optional conversion parameters.
 *
 * @return 0 on success, ::SCE_IFTU_ERROR_INVALID_PIXELFORMAT for an
 * unsupported source or destination pixel format, or a negative fast-mutex
 * error.
 */
int ksceIftuCsc(SceIftuFrameBuf *dst, SceIftuPlaneState *src, SceIftuConvParams *params);

/**
 * Disable a display-plane IFTU context and its interrupt.
 *
 * @param[in] plane_index - Display-plane index in the range 0 to 3.
 *
 * @return 0 on success, ::SCE_IFTU_ERROR_INVALID_PLANE for an invalid plane.
 */
int ksceIftuDisable(unsigned int plane_index);

/**
 * Enable a display-plane IFTU context using its cached configuration.
 *
 * @param[in] plane_index - Display-plane index in the range 0 to 3.
 *
 * @return 0 on success, ::SCE_IFTU_ERROR_INVALID_PLANE for an invalid plane.
 */
int ksceIftuEnable(unsigned int plane_index);

/**
 * Store an IFTU input-plane state in the cache and submit it.
 *
 * FW 3.60 copies all 0x54 bytes when \a plane_state is non-NULL. A zero pixel
 * format disables the input. When the plane is enabled, a zero \a sync updates
 * only the physical addresses and the three reserved register words in both
 * configuration banks. A nonzero value submits the complete cached state.
 * In addition to ::SceIftuPixelformat, FW 3.60 accepts input formats
 * 0x80020000, 0x80140000, and 0x80180000; their purpose is unknown.
 *
 * @param[in] plane_index - Global IFTU plane index in the range 0 to 4.
 * @param[in] plane_state - New complete state, or NULL to reuse the cached
 * state. The structure is read-only.
 * @param[in] bilinear - A nonnegative value replaces the cached filter
 * setting; a negative value preserves it. Known FW 3.60 callers use
 * ::SCE_IFTU_FILTER_MODE_NEAREST or ::SCE_IFTU_FILTER_MODE_BILINEAR.
 * @param[in] sync - Zero to update only addresses and reserved register words
 * when the plane is enabled, or nonzero to submit the complete state.
 *
 * @return 0 on success, ::SCE_IFTU_ERROR_INVALID_PLANE for an invalid plane,
 * or ::SCE_IFTU_ERROR_INVALID_PIXELFORMAT for an unsupported input format.
 */
int ksceIftuSetInputFrameBuffer(unsigned int plane_index, const SceIftuPlaneState *plane_state, int bilinear, int sync);

/**
 * Set an overlay plane's merge/blending control.
 *
 * @param[in] plane_index - Overlay plane index; only 1 and 3 are accepted.
 * @param[in] control - Raw merge-control value. 0x80 disables the associated blend-enable bit.
 *
 * @return 0 on success, ::SCE_IFTU_ERROR_INVALID_PLANE for an invalid plane.
 */
int ksceIftuSetMergeSetting(unsigned int plane_index, int control);

/**
 * Configure an IFTU display plane's output size and format.
 *
 * @param[in] plane_index - Display-plane index in the range 0 to 3.
 * @param[in] width - Output width in pixels; must be a multiple of 16.
 * @param[in] height - Output height in pixels; must be a multiple of 8.
 * @param[in] pixel_format - One of ::SceIftuPixelformat. FW 3.60 accepts values
 * 0x10, 0x20, 0x40, 0x80, 0x1000, 0x2000, 0x4000, and 0x8000.
 * @param[in] interlaced - Set to 1 to enable interlaced output handling. All
 *                         other values select progressive handling.
 *
 * @return 0 on success, ::SCE_IFTU_ERROR_INVALID_PLANE for an invalid plane,
 * ::SCE_IFTU_ERROR_INVALID_PARAM for a misaligned width or height,
 * ::SCE_IFTU_ERROR_INVALID_PIXELFORMAT for an unsupported output format, or
 * ::SCE_IFTU_ERROR_PLANE_BUSY if the plane is enabled.
 */
int ksceIftuSetOutputFormat(unsigned int plane_index, unsigned int width, unsigned int height, unsigned int pixel_format, unsigned int interlaced);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_IFTU_H_ */
