/**
 * \kernelgroup{SceDisplay}
 * \usage{psp2kern/display.h,SceDisplayForDriver_stub}
 */


#ifndef _PSP2_KERNEL_DISPLAY_H_
#define _PSP2_KERNEL_DISPLAY_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_DISPLAY_ERROR_OK			= 0,
	SCE_DISPLAY_ERROR_INVALID_HEAD		= 0x80290000,
	SCE_DISPLAY_ERROR_INVALID_VALUE		= 0x80290001,
	SCE_DISPLAY_ERROR_INVALID_ADDR		= 0x80290002,
	SCE_DISPLAY_ERROR_INVALID_PIXELFORMAT	= 0x80290003,
	SCE_DISPLAY_ERROR_INVALID_PITCH		= 0x80290004,
	SCE_DISPLAY_ERROR_INVALID_RESOLUTION	= 0x80290005,
	SCE_DISPLAY_ERROR_INVALID_UPDATETIMING	= 0x80290006,
	SCE_DISPLAY_ERROR_NO_FRAME_BUFFER	= 0x80290007,
	SCE_DISPLAY_ERROR_NO_PIXEL_DATA		= 0x80290008
};

#define SCE_DISPLAY_PIXELFORMAT_A8B8G8R8 0x00000000U

enum {
	/** Buffer change effective immediately */
	SCE_DISPLAY_SETBUF_IMMEDIATE = 0,
	/** Buffer change effective next frame */
	SCE_DISPLAY_SETBUF_NEXTFRAME = 1
};

/**
 * Structure used with sceDisplaySetFrameBuf to set/update framebuffer.
 * Original screen resolution is 960x544, but the following resolutions
 * can also be supplied as width and height :
 * 480x272, 640x368, 720x408
 *
 * @note - This structure is returned by sceDisplayGetFrameBuf
*/
typedef struct SceDisplayFrameBuf {
	SceSize size;	//!< sizeof(SceDisplayFrameBuf)
	void *base;	//!< Pointer to framebuffer
	unsigned int pitch;	//!< pitch pixels
	unsigned int pixelformat;	//!< use SCE_DISPLAY_PIXELFORMAT_A8B8G8R8
	unsigned int width;	//!< framebuffer width
	unsigned int height;	//!< framebuffer height
} SceDisplayFrameBuf;

/**
 * Set/Update framebuffer parameters
 *
 * @param[in] pParam - Pointer to a ::SceDisplayFrameBuf structure.
 * @param[in] sync - One of ::DisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as pParam pointer, output is blacked out.
*/
int ksceDisplaySetFrameBuf(const SceDisplayFrameBuf *pParam, int sync);

/**
 * Get current framebuffer parameters
 *
 * @param[out] pParam - Pointer to a ::SceDisplayFrameBuf structure
 * which will receive framebuffer parameters.
 *
 * @param[in] sync - One of ::DisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
*/
int ksceDisplayGetFrameBuf(SceDisplayFrameBuf *pParam, int sync);

/**
 * Get current framebuffer dimensions
 *
 * @param[out] width - Framebuffer width
 * @param[out] height - Framebuffer height
 *
 * @return 0 on success, < 0 on error.
*/
int ksceDisplayGetFrameBufDimensions(int *width, int *height);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_DISPLAY_H_ */

