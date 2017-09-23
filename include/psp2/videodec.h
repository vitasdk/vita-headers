/**
 * \usergroup{SceVideoDec}
 * \usage{psp2/videodec.h,SceVideodec_stub}
 */


#ifndef _PSP2_VIDEODEC_H_
#define _PSP2_VIDEODEC_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceVideodecType {
	SCE_VIDEODEC_TYPE_HW_AVCDEC = 0x1001
} SceVideodecType;

typedef struct SceVideodecQueryInitInfoHwAvcdec {
	uint32_t size;				//!< sizeof(SceVideodecQueryInitInfoHwAvcdec)
	uint32_t horizontal;
	uint32_t vertical;
	uint32_t numOfRefFrames;
	uint32_t numOfStreams;
} SceVideodecQueryInitInfoHwAvcdec;

typedef union SceVideodecQueryInitInfo {
	uint8_t reserved[32];
	SceVideodecQueryInitInfoHwAvcdec hwAvc;
} SceVideodecQueryInitInfo;

typedef struct SceVideodecTimeStamp {
	uint32_t upper;
	uint32_t lower;
} SceVideodecTimeStamp;

typedef struct SceAvcdecQueryDecoderInfo {
	uint32_t horizontal;
	uint32_t vertical;
	uint32_t numOfRefFrames;
} SceAvcdecQueryDecoderInfo;

typedef struct SceAvcdecDecoderInfo {
	uint32_t frameMemSize;
} SceAvcdecDecoderInfo;

typedef struct SceAvcdecBuf {
	void *pBuf;
	uint32_t size;
} SceAvcdecBuf;

typedef struct SceAvcdecCtrl {
	uint32_t handle;
	SceAvcdecBuf frameBuf;
} SceAvcdecCtrl;

typedef struct SceAvcdecAu {
	SceVideodecTimeStamp pts;
	SceVideodecTimeStamp dts;
	SceAvcdecBuf es;
} SceAvcdecAu;

typedef struct SceAvcdecInfo {
	uint32_t numUnitsInTick;
	uint32_t timeScale;
	uint8_t fixedFrameRateFlag;

	uint8_t aspectRatioIdc;
	uint16_t sarWidth;
	uint16_t sarHeight;

	uint8_t colourPrimaries;
	uint8_t transferCharacteristics;
	uint8_t matrixCoefficients;

	uint8_t videoFullRangeFlag;

	uint8_t unknown[3]; // maybe picStruct & ctType

	SceVideodecTimeStamp pts;
} SceAvcdecInfo;

typedef struct SceAvcdecFrameOptionRGBA {
	uint8_t alpha;
	uint8_t cscCoefficient;
	uint8_t reserved[14];
} SceAvcdecFrameOptionRGBA;

typedef union SceAvcdecFrameOption {
	uint8_t reserved[16];
	SceAvcdecFrameOptionRGBA rgba;
} SceAvcdecFrameOption;

typedef struct SceAvcdecFrame {
	uint32_t pixelType;		//!< display pixel format
	uint32_t framePitch;
	uint32_t frameWidth;
	uint32_t frameHeight;

	uint32_t horizontalSize;
	uint32_t verticalSize;

	uint32_t frameCropLeftOffset;
	uint32_t frameCropRightOffset;
	uint32_t frameCropTopOffset;
	uint32_t frameCropBottomOffset;

	SceAvcdecFrameOption opt;

	void *pPicture[2];		//!< address of picture buffer
} SceAvcdecFrame;

typedef struct SceAvcdecPicture {
	uint32_t size;
	SceAvcdecFrame frame;
	SceAvcdecInfo info;
} SceAvcdecPicture;

typedef struct SceAvcdecArrayPicture {
	uint32_t numOfOutput;
	uint32_t numOfElm;
	SceAvcdecPicture **pPicture;
} SceAvcdecArrayPicture;

/***
 * @param[in] codec - See ::SceVideodecType
 * @param[in] initInfo - See ::SceVideodecQueryInitInfoHwAvcdec
 *
 * @return 0 on success, < 0 on error.
 */
int sceVideodecInitLibrary(SceVideodecType codec, const SceVideodecQueryInitInfoHwAvcdec *initInfo);

/***
 * @param[in] codec - See ::SceVideodecType
 *
 * @return 0 on success, < 0 on error.
 */
int sceVideodecTermLibrary(SceVideodecType codec);

/***
 * @param[in] codec - See ::SceVideodecType
 * @param[in] query - Should be copy from ::SceVideodecQueryInitInfoHwAvcdec.
 * @param[out] decoderInfo - Must be initialized with zeros.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvcdecQueryDecoderMemSize(SceVideodecType codec, const SceAvcdecQueryDecoderInfo *query, SceAvcdecDecoderInfo *decoderInfo);

/***
 * @param[in] codec - See ::SceVideodecType
 * @param[out] decoder - Must be initialized frameBuf.size and frameBuf.pBuf
 * @param[in] query - Should be copy from ::SceVideodecQueryInitInfoHwAvcdec.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvcdecCreateDecoder(SceVideodecType codec, SceAvcdecCtrl *decoder, const SceAvcdecQueryDecoderInfo *query);

/***
 * @param[in] decoder - A ::SceAvcdecCtrl decoder initialized with ::sceAvcdecCreateDecoder
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvcdecDeleteDecoder(SceAvcdecCtrl *decoder);

/***
 * @param[in] decoder
 * @param[in] au - Must set buffer information(es) and be initialized timestamps with 0xFFFFFFFF
 * @param[out] array_picture - Must set numOfElm and pPicture. See ::SceAvcdecArrayPicture
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvcdecDecode(const SceAvcdecCtrl *decoder, const SceAvcdecAu *au, SceAvcdecArrayPicture *array_picture);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_VIDEODEC_H_ */
