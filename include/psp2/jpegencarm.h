/**
 * \usergroup{SceJpegEncArm}
 * \internalusage{psp2/jpegencarm.h,SceJpegEncArm_stub,SCE_SYSMODULE_INTERNAL_JPEG_ENC_ARM}
 */

#ifndef _PSP2_JPEGENCARM_H_
#define _PSP2_JPEGENCARM_H_

#include <psp2/types.h>
#include <psp2/jpegenc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* SceJpegArmEncoderContext;

/**
 * Initialize a jpeg encoder
 *
 * @param[in] context - A pointer to a big enough allocated memory block
 * @param[in] inWidth - Input width in pixels
 * @param[in] inHeight - Input height in pixels
 * @param[in] pixelformat - A valid ::SceJpegEncoderPixelFormat set of values
 * @param[in] outBuffer - A physically continuous memory block 256 bytes aligned
 * @param[in] outSize - Output size in bytes
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderInit(SceJpegArmEncoderContext context, int inWidth, int inHeight, SceJpegEncoderPixelFormat pixelformat, void *outBuffer, SceSize outSize);

/**
 * Terminate a jpeg encoder
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegArmEncoderContext
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderEnd(SceJpegArmEncoderContext context);

/**
 * Execute a jpeg encode
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegArmEncoderContext
 * @param[in] inBuffer - A physically continuous memory block 256 bytes aligned
 *
 * @return encoded jpeg size on success, < 0 on error.
 */
int sceJpegArmEncoderEncode(SceJpegArmEncoderContext context, const void *inBuffer);

/**
 * Set encoder compression ratio
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegArmEncoderContext
 * @param[in] ratio - A value between 0 and 255 (higher = better compression, lower = better speed)
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetCompressionRatio(SceJpegArmEncoderContext context, int ratio);

/**
 * Set encoder output address
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegArmEncoderContext
 * @param[in] outBuffer - A physically continuous memory block 256 bytes aligned
 * @param[in] outSize - Output buffer size in bytes
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetOutputAddr(SceJpegArmEncoderContext context, void *outBuffer, SceSize outSize);

/**
 * Return required free size to allocate a jpeg encoder
 *
 * @return Required free memory size in bytes, < 0 on error.
 */
int sceJpegArmEncoderGetContextSize(void);

/**
 * Set encoder valid region (?)
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegArmEncoderContext
 * @param[in] inWidth - Input width in pixels
 * @param[in] inHeight - Input height in pixels
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetValidRegion(SceJpegArmEncoderContext context, int inWidth, int inHeight);

/**
 * Set header used for output file
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegArmEncoderContext
 * @param[in] mode - One of ::SceJpegEncoderHeaderMode
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetHeaderMode(SceJpegArmEncoderContext context, int mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_JPEGENCARM_H_ */
