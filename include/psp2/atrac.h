/**
 * \usergroup{SceAtrac}
 * \usage{psp2/atrac.h,SceAtrac_stub,SCE_SYSMODULE_ATRAC}
 */


#ifndef _PSP2_ATRAC_H_
#define _PSP2_ATRAC_H_

#include <psp2/types.h>
#include <psp2/audiodec.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAtracErrorCode {
	SCE_ATRAC_ERROR_INVALID_POINTER               = 0x80630000,
	SCE_ATRAC_ERROR_INVALID_SIZE                  = 0x80630001,
	SCE_ATRAC_ERROR_INVALID_WORD_LENGTH           = 0x80630002,
	SCE_ATRAC_ERROR_INVALID_TYPE                  = 0x80630003,
	SCE_ATRAC_ERROR_INVALID_TOTAL_CH              = 0x80630004,
	SCE_ATRAC_ERROR_INVALID_ALIGNMENT             = 0x80630005,
	SCE_ATRAC_ERROR_ALREADY_CREATED               = 0x80630006,
	SCE_ATRAC_ERROR_NOT_CREATED                   = 0x80630007,
	SCE_ATRAC_ERROR_SHORTAGE_OF_CH                = 0x80630008,
	SCE_ATRAC_ERROR_UNSUPPORTED_DATA              = 0x80630009,
	SCE_ATRAC_ERROR_INVALID_DATA                  = 0x8063000A,
	SCE_ATRAC_ERROR_READ_SIZE_IS_TOO_SMALL        = 0x8063000B,
	SCE_ATRAC_ERROR_INVALID_HANDLE                = 0x8063000C,
	SCE_ATRAC_ERROR_READ_SIZE_OVER_BUFFER         = 0x8063000D,
	SCE_ATRAC_ERROR_MAIN_BUFFER_SIZE_IS_TOO_SMALL = 0x8063000E,
	SCE_ATRAC_ERROR_SUB_BUFFER_SIZE_IS_TOO_SMALL  = 0x8063000F,
	SCE_ATRAC_ERROR_DATA_SHORTAGE_IN_BUFFER       = 0x80630010,
	SCE_ATRAC_ERROR_ALL_DATA_WAS_DECODED          = 0x80630011,
	SCE_ATRAC_ERROR_INVALID_MAX_OUTPUT_SAMPLES    = 0x80630012,
	SCE_ATRAC_ERROR_ADDED_DATA_IS_TOO_BIG         = 0x80630013,
	SCE_ATRAC_ERROR_NEED_SUB_BUFFER               = 0x80630014,
	SCE_ATRAC_ERROR_INVALID_SAMPLE                = 0x80630015,
	SCE_ATRAC_ERROR_NO_NEED_SUB_BUFFER            = 0x80630016,
	SCE_ATRAC_ERROR_INVALID_LOOP_STATUS           = 0x80630017,
	SCE_ATRAC_ERROR_REMAIN_VALID_HANDLE           = 0x80630018,
	SCE_ATRAC_ERROR_INVALID_LOOP_NUM              = 0x80630030
} SceAtracErrorCode;

/* Memory alignment size */
#define SCE_ATRAC_ALIGNMENT_SIZE (SCE_AUDIODEC_ALIGNMENT_SIZE)

/* The macro of rounding up the memory size */
#define SCE_ATRAC_ROUND_UP(size) ((size + SCE_ATRAC_ALIGNMENT_SIZE - 1) & ~(SCE_ATRAC_ALIGNMENT_SIZE - 1))

/* The definition of ATRAC(TM) type */
#define SCE_ATRAC_TYPE_AT9           (0x2003U)

/* Maximum number of total total channels */
#define SCE_ATRAC_AT9_MAX_TOTAL_CH (SCE_AUDIODEC_AT9_MAX_CH_IN_LIBRARY)

/* The definition of wordLength */
#define SCE_ATRAC_WORD_LENGTH_16BITS (SCE_AUDIODEC_WORD_LENGTH_16BITS)

/* Maximum number of channels per stream */
#define SCE_ATRAC_AT9_MAX_CH_IN_DECODER (SCE_AUDIODEC_AT9_MAX_CH_IN_DECODER)

/* Maximum number of samples */
#define SCE_ATRAC_AT9_MAX_FRAME_SAMPLES (SCE_AUDIODEC_AT9_MAX_SAMPLES)

/* Maximum number of output samples */
#define SCE_ATRAC_MAX_OUTPUT_SAMPLES (2048)

/* Maximum number of output frames */
#define SCE_ATRAC_AT9_MAX_OUTPUT_FRAMES  (8)

/* Minimum number of loop samples */
#define SCE_ATRAC_AT9_MIN_LOOP_SAMPLES (3072)

/* The definition of ATRAC infinite loop */
#define SCE_ATRAC_INFINITE_LOOP_NUM    (-1)

/* The definition of ATRAC infinite samples */
#define SCE_ATRAC_INFINITE_SAMPLES  (-1)

/* The definition of ATRAC decoder status */
typedef enum SceAtracDecoderStatus {
	SCE_ATRAC_DECODER_STATUS_ALL_DATA_WAS_DECODED       = 0x00000001,
	SCE_ATRAC_DECODER_STATUS_ALL_DATA_IS_ON_MEMORY      = 0x00000002,
	SCE_ATRAC_DECODER_STATUS_NONLOOP_PART_IS_ON_MEMORY  = 0x00000004,
	SCE_ATRAC_DECODER_STATUS_LOOP_PART_IS_ON_MEMORY     = 0x00000008
} SceAtracDecoderStatus;

/* The definition of loop status */
typedef enum SceAtracLoopStatus {
	SCE_ATRAC_LOOP_STATUS_NON_RESETABLE_PART          = 0x00000000,
	SCE_ATRAC_LOOP_STATUS_RESETABLE_PART              = 0x00000001
} SceAtracLoopStatus;

/* The structure for decoder group */
typedef struct {
	SceUInt32 size;
	SceUInt32 wordLength;
	SceUInt32 totalCh;
} SceAtracDecoderGroup;

/* Content information structure */
typedef struct {
	SceUInt32 size;
	SceUInt32 atracType;
	SceUInt32 channel;
	SceUInt32 samplingRate;
	SceInt32  endSample;
	SceInt32  loopStartSample;
	SceInt32  loopEndSample;
	SceUInt32 bitRate;
	SceUInt32 fixedEncBlockSize;
	SceUInt32 fixedEncBlockSample;
	SceUInt32 frameSample;
	SceUInt32 loopBlockOffset;
	SceUInt32 loopBlockSize;
} SceAtracContentInfo;

/* Stream information structure */
typedef struct {
	SceUInt32 size;
	SceUChar8 *pWritePosition;
	SceUInt32 readPosition;
	SceUInt32 writableSize;
} SceAtracStreamInfo;

int sceAtracQueryDecoderGroupMemSize(SceUInt32 atracType, const SceAtracDecoderGroup *pDecoderGroup);

int sceAtracCreateDecoderGroup(SceUInt32 atracType, const SceAtracDecoderGroup *pDecoderGroup, void *pvWorkMem, int initAudiodecFlag);

int sceAtracDeleteDecoderGroup(SceUInt32 atracType, int termAudiodecFlag);

int sceAtracGetDecoderGroupInfo(SceUInt32 atracType, SceAtracDecoderGroup *pCreatedDecoder, SceAtracDecoderGroup *pAvailableDecoder);

int sceAtracSetDataAndAcquireHandle(SceUChar8 *pucBuffer, SceUInt32 uiReadSize, SceUInt32 uiBufferSize);

int sceAtracReleaseHandle(int atracHandle);

int sceAtracDecode(int atracHandle, void *pOutputBuffer, SceUInt32 *pOutputSamples, SceUInt32 *pDecoderStatus);

int sceAtracGetStreamInfo(int atracHandle, SceAtracStreamInfo *pStreamInfo);

int sceAtracAddStreamData(int atracHandle, SceUInt32 addSize);

int sceAtracIsSubBufferNeeded(int atracHandle);

int sceAtracGetSubBufferInfo(int atracHandle, SceUInt32 *pReadPosition, SceUInt32 *pMinSubBufferSize, SceUInt32 *pDataSize);

int sceAtracSetSubBuffer(int atracHandle, SceUChar8 *pSubBuffer, SceUInt32 subBufferSize);

int sceAtracSetLoopNum(int atracHandle, int loopNum);

int sceAtracSetOutputSamples(int atracHandle, SceUInt32 outputSamples);

int sceAtracResetNextOutputPosition(int atracHandle, SceUInt32 resetSample);

int sceAtracGetContentInfo(int atracHandle, SceAtracContentInfo *pContentInfo);

int sceAtracGetLoopInfo(int atracHandle, int *pLoopNum, SceUInt32 *pLoopStatus);

int sceAtracGetOutputSamples(int atracHandle, SceUInt32 *pOutputSamples);

int sceAtracGetNextOutputPosition(int atracHandle, SceUInt32 *pNextOutputSample);

int sceAtracGetRemainSamples(int atracHandle, SceLong64 *pRemainSamples);

int sceAtracGetOutputableSamples(int atracHandle, SceLong64 *pOutputableSamples);

int sceAtracGetDecoderStatus(int atracHandle, SceUInt32 *pDecoderStatus);

int sceAtracGetVacantSize(int atracHandle, SceUInt32 *pVacantSize);

int sceAtracGetInternalError(int atracHandle, int *pInternalError);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_ATRAC_H_ */

