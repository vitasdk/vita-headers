/**
 * \kernelgroup{SceJpegEnc}
 * \usage{psp2kern/avcodec/jpegenc.h,SceAvcodecForDriver_stub}
 */

#ifndef _PSP2KERN_AVCODEC_JPEGENC_H_
#define _PSP2KERN_AVCODEC_JPEGENC_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/jpegenc.h>

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
int ksceJpegEncoderInit(SceJpegEncoderContext context, int inWidth, int inHeight, SceJpegEncoderPixelFormat pixelformat, void *outBuffer, SceSize outSize);

/**
 * Terminate a jpeg encoder
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 *
 * @return 0 on success, < 0 on error.
 */
int ksceJpegEncoderEnd(SceJpegEncoderContext context);

/**
 * Execute a jpeg encode
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] inBuffer - A physically continuous memory block 256 bytes aligned
 *
 * @return 0 on success, < 0 on error.
 */
int ksceJpegEncoderEncode(SceJpegEncoderContext context, const void *inBuffer);

/**
 * Set encoder compression ratio
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] ratio - A value between 0 and 255 (higher = better compression, lower = better speed)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceJpegEncoderSetCompressionRatio(SceJpegEncoderContext context, int ratio);


/**
 * Set encoder output address
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] outBuffer - A physically continuous memory block 256 bytes aligned
 * @param[in] outSize - Output buffer size in bytes
 *
 * @return 0 on success, < 0 on error.
 */
int ksceJpegEncoderSetOutputAddr(SceJpegEncoderContext context, void *outBuffer, SceSize outSize);

/**
 * Execute a color conversion from ARGB to YCbCr
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] outBuffer - A physical continuous memory block 256 bytes aligned
 * @param[in] inBuffer - A pointer to a valid ARGB buffer
 * @param[in] inPitch - Input pitch value in pixels
 * @param[in] inPixelFormat - A valid ::SceJpegEncoderPixelFormat set of values
 *
 * @return 0 on success, < 0 on error.
 */
int ksceJpegEncoderCsc(SceJpegEncoderContext context, void *outBuffer, const void *inBuffer, int inPitch, SceJpegEncoderPixelFormat inPixelFormat);

/**
 * Return required free size to allocate a jpeg encoder
 *
 * @return Required free memory size in bytes, < 0 on error.
 */
int ksceJpegEncoderGetContextSize(void);

/**
 * Set encoder valid region (?)
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] inWidth - Input width in pixels
 * @param[in] inHeight - Input height in pixels
 *
 * @return 0 on success, < 0 on error.
 */
int ksceJpegEncoderSetValidRegion(SceJpegEncoderContext context, int inWidth, int inHeight);

/**
 * Set header used for output file
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] mode - One of ::SceJpegEncoderHeaderMode
 *
 * @return 0 on success, < 0 on error.
 */
int ksceJpegEncoderSetHeaderMode(SceJpegEncoderContext context, int mode);

#endif /* _PSP2KERN_AVCODEC_JPEGENC_H_ */

