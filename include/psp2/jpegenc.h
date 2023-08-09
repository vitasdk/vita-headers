/**
 * \usergroup{SceJpegEnc}
 * \usage{psp2/jpegenc.h,SceJpegEnc_stub}
 */

#ifndef _PSP2_JPEGENC_H_
#define _PSP2_JPEGENC_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/jpegenc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceJpegEncoderInitParamOption {
	SCE_JPEGENC_INIT_PARAM_OPTION_NONE          = 0,  //!< Default option
	SCE_JPEGENC_INIT_PARAM_OPTION_LPDDR2_MEMORY = 1   //!< LPDDR2 memory will be used instead of CDRAM
} SceJpegEncoderInitParamOption;

typedef struct SceJpegEncoderInitParam {
	SceSize	size;        //!< Size of this structure
	int     inWidth;     //!< Input width in pixels
	int     inHeight;    //!< Input height in pixels
	int     pixelFormat; //!< A valid ::SceJpegEncoderPixelFormat set of values
	void    *outBuffer;  //!< A physically continuous memory block 256 bytes aligned
	SceSize outSize;     //!< Output size in bytes
	int     option;      //!< Additional options, OR of ::SceJpegEncoderInitParamOption
} SceJpegEncoderInitParam;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceJpegEncoderInitParam);

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
int sceJpegEncoderInit(SceJpegEncoderContext context, int inWidth, int inHeight, SceJpegEncoderPixelFormat pixelformat, void *outBuffer, SceSize outSize);

/**
 * Initialize a jpeg encoder with param
 *
 * @param[in] initParam - A pointer to the initialization parameters
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegEncoderInitWithParam(SceJpegEncoderContext context, const SceJpegEncoderInitParam *initParam);

/**
 * Terminate a jpeg encoder
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegEncoderEnd(SceJpegEncoderContext context);

/**
 * Execute a jpeg encode
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] inBuffer - A physically continuous memory block 256 bytes aligned
 *
 * @return encoded jpeg size on success, < 0 on error.
 */
int sceJpegEncoderEncode(SceJpegEncoderContext context, const void *inBuffer);

/**
 * Set encoder compression ratio
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] ratio - A value between 0 and 255 (higher = better compression, lower = better speed)
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegEncoderSetCompressionRatio(SceJpegEncoderContext context, int ratio);


/**
 * Set encoder output address
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] outBuffer - A physically continuous memory block 256 bytes aligned
 * @param[in] outSize - Output buffer size in bytes
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegEncoderSetOutputAddr(SceJpegEncoderContext context, void *outBuffer, SceSize outSize);

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
int sceJpegEncoderCsc(SceJpegEncoderContext context, void *outBuffer, const void *inBuffer, int inPitch, SceJpegEncoderPixelFormat inPixelFormat);

/**
 * Return required free size to allocate a jpeg encoder
 *
 * @return Required free memory size in bytes, < 0 on error.
 */
int sceJpegEncoderGetContextSize(void);

/**
 * Set encoder valid region (?)
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] inWidth - Input width in pixels
 * @param[in] inHeight - Input height in pixels
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegEncoderSetValidRegion(SceJpegEncoderContext context, int inWidth, int inHeight);

/**
 * Set header used for output file
 *
 * @param[in] context - A pointer to an already initialized ::SceJpegEncoderContext
 * @param[in] mode - One of ::SceJpegEncoderHeaderMode
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegEncoderSetHeaderMode(SceJpegEncoderContext context, int mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_JPEGENC_H_ */

