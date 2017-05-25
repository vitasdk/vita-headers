/**
 * \usergroup{SceJpegEnc}
 * \usage{psp2/jpegenc.h,SceJpegEnc_stub}
 */


 
#ifndef _JPEGENC_H_
#define _JPEGENC_H_
 
#define SceJpegEncoderContext void*
 
typedef enum SceJpegEncoderPixelFormat{
	PIXELFORMAT_ARGB8888 = 0,       //!< ARGB8888 format
	PIXELFORMAT_YCBCR420 = 8,       //!< YCbCr420 format
	PIXELFORMAT_YCBCR422 = 9,       //!< YCbCr422 format
	PIXELFORMAT_CSC_ARGB_YCBCR = 16 //!< ARGB to YCbCr color conversion flag
}SceJpegEncoderPixelFormat;

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
SceUID sceJpegEncoderInit(SceJpegEncoderContext context, int inWidth,int inHeight, SceJpegEncoderPixelFormat pixelformat, void* outBuffer, int outSize);

/**
 * Terminate a jpeg encoder
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderEnd(SceJpegEncoderContext context);

/**
 * Execute a jpeg encode
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] inBuffer - A physically continuous memory block 256 bytes aligned
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderEncode(SceJpegEncoderContext context, void* inBuffer);

/**
 * Set encoder compression ratio
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] ratio - A value between 0 and 255 (higher = better compression, lower = better speed)
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderSetCompressionRatio(SceJpegEncoderContext context,int ratio);


/**
 * Set encoder output address
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] outBuffer - A physically continuous memory block 256 bytes aligned
 * @param[in] outSize - Output buffer size in bytes
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderSetOutputAddr(SceJpegEncoderContext context,void* outBuffer,int outSize);

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
SceUID sceJpegEncoderCsc(SceJpegEncoderContext context,void* outBuffer,void* inBuffer,int inPitch,SceJpegEncoderPixelFormat inPixelFormat);

/**
 * Return required free size to allocate a jpeg encoder
 *
 * @return Required free memory size in bytes, < 0 on error.
 */
SceUID sceJpegEncoderGetContextSize(void);

/**
 * Set encoder valid region (?)
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] inWidth - Input width in pixels
 * @param[in] inHeight - Input height in pixels
 *
 * @return 0 on success, < 0 on error.
 */
SceUID sceJpegEncoderSetValidRegion(SceJpegEncoderContext context, int inWidth, int inHeight);

#endif

