/**
 * \file
 * \brief Header file which defines native jpeg encoder related variables and functions
 *
 * Copyright (C) 2016 vitasdk
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
 
#ifndef _JPEGENC_H_
#define _JPEGENC_H_
 
#define SceJpegEncoderContext void*
 
typedef enum sceJpegEncoderPixelFormat{
	PIXELFORMAT_ARGB8888 = 0,
	PIXELFORMAT_YCBCR420 = 8,
	PIXELFORMAT_YCBCR422 = 9,
	PIXELFORMAT_CSC_ARGB_YCBCR = 16 // ARGB to YCbCr color conversion flag
}sceJpegEncoderPixelFormat;

/**
 * Initialize a jpeg encoder
 *
 * @param[in] context - A pointer to a big enough allocated memory block
 * @param[in] inWidth - Input width in pixels
 * @param[in] inHeight - Input height in pixels
 * @param[in] pixelformat - A valid sceJpegEncoderPixelFormat set of values
 * @param[in] outBuffer - A physically continuous memory block 256 bytes aligned
 * @param[in] outSize - Output size in bytes
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderInit(SceJpegEncoderContext context, int inWidth,int inHeight, sceJpegEncoderPixelFormat pixelformat, void* outBuffer, int outSize);

/**
 * Terminate a jpeg encoder
 *
 * @param[in] context - A pointer to an already initialized sceJpegEncoderContext
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderEnd(SceJpegEncoderContext context);

/**
 * Execute a jpeg encode
 *
 * @param[in] context - A pointer to an already initialized sceJpegEncoderContext
 * @param[in] inBuffer - A physically continuous memory block 256 bytes aligned
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderEncode(SceJpegEncoderContext context, void* inBuffer);

/**
 * Set encoder compression ratio
 *
 * @param[in] context - A pointer to an already initialized sceJpegEncoderContext
 * @param[in] ratio - A value between 0 and 255 (higher = better compression, lower = better speed)
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderSetCompressionRatio(SceJpegEncoderContext context,int ratio);


/**
 * Set encoder output address
 *
 * @param[in] context - A pointer to an already initialized sceJpegEncoderContext
 * @param[in] outBuffer - A physically continuous memory block 256 bytes aligned
 * @param[in] outSize - Output buffer size in bytes
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderSetOutputAddr(SceJpegEncoderContext context,void* outBuffer,int outSize);

/**
 * Execute a color conversion from ARGB to YCbCr
 *
 * @param[in] context - A pointer to an already initialized sceJpegEncoderContext
 * @param[in] outBuffer - A physical continuous memory block 256 bytes aligned
 * @param[in] inBuffer - A pointer to a valid ARGB buffer
 * @param[in] inPitch - Input pitch value in pixels
 * @param[in] inPixelFormat - A valid sceJpegEncoderPixelFormat set of values
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderCsc(SceJpegEncoderContext context,void* outBuffer,void* inBuffer,int inPitch,sceJpegEncoderPixelFormat inPixelFormat);

/**
 * Return required free size to allocate a jpeg encoder
 *
 * @return Required free memory size in bytes, < 0 on error.
 */
SceUID sceJpegEncoderGetContextSize(void);

/**
 * Set encoder valid region (?)
 *
 * @param[in] context - A pointer to an already initialized sceJpegEncoderContext
 * @param[in] inWidth - Input width in pixels
 * @param[in] inHeight - Input height in pixels
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderSetValidRegion(SceJpegEncoderContext context, int inWidth, int inHeight);

#endif