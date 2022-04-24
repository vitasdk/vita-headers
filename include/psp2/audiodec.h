/**
 * \usergroup{SceAudiodec}
 * \usage{psp2/audiodec.h,SceAudiodec_stub}
 */


#ifndef _PSP2_AUDIODEC_H_
#define _PSP2_AUDIODEC_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAudiodecErrorCode {
	SCE_AUDIODEC_ERROR_API_FAIL                  = 0x807F0000,
	SCE_AUDIODEC_ERROR_INVALID_TYPE              = 0x807F0001,
	SCE_AUDIODEC_ERROR_INVALID_INIT_PARAM        = 0x807F0002,
	SCE_AUDIODEC_ERROR_ALREADY_INITIALIZED       = 0x807F0003,
	SCE_AUDIODEC_ERROR_OUT_OF_MEMORY             = 0x807F0004,
	SCE_AUDIODEC_ERROR_NOT_INITIALIZED           = 0x807F0005,
	SCE_AUDIODEC_ERROR_A_HANDLE_IN_USE           = 0x807F0006,
	SCE_AUDIODEC_ERROR_ALL_HANDLES_IN_USE        = 0x807F0007,
	SCE_AUDIODEC_ERROR_INVALID_PTR               = 0x807F0008,
	SCE_AUDIODEC_ERROR_INVALID_HANDLE            = 0x807F0009,
	SCE_AUDIODEC_ERROR_NOT_HANDLE_IN_USE         = 0x807F000A,
	SCE_AUDIODEC_ERROR_CH_SHORTAGE               = 0x807F000B,
	SCE_AUDIODEC_ERROR_INVALID_WORD_LENGTH       = 0x807F000C,
	SCE_AUDIODEC_ERROR_INVALID_SIZE              = 0x807F000D,
	SCE_AUDIODEC_ERROR_UNSUPPORTED               = 0x807F000E,
	SCE_AUDIODEC_ERROR_INVALID_NFRAMES           = 0x807F000F,
	SCE_AUDIODEC_ERROR_INVALID_NSTREAMS          = 0x807F0010,
	SCE_AUDIODEC_ERROR_DIFFERENT_TYPES           = 0x807F0011,
	SCE_AUDIODEC_ERROR_SAME_HANDLES              = 0x807F0012,
	SCE_AUDIODEC_ERROR_BUSY                      = 0x807F0013,
	SCE_AUDIODEC_AT9_ERROR_INVALID_CONFIG        = 0x807F2000,
	SCE_AUDIODEC_MP3_ERROR_INVALID_CH            = 0x807F2800,
	SCE_AUDIODEC_MP3_ERROR_INVALID_MPEG_VERSION  = 0x807F2801,
	SCE_AUDIODEC_AAC_ERROR_INVALID_CH            = 0x807F3000,
	SCE_AUDIODEC_CELP_ERROR_INVALID_CONFIG       = 0x807F3800
} SceAudiodecErrorCode;

#define SCE_AUDIODEC_ALIGNMENT_SIZE 0x100U
#define SCE_AUDIODEC_ROUND_UP(size) ((size + SCE_AUDIODEC_ALIGNMENT_SIZE - 1) & ~(SCE_AUDIODEC_ALIGNMENT_SIZE - 1))

#define SCE_AUDIODEC_WORD_LENGTH_16BITS 16

typedef enum SceAudiodecType {
	SCE_AUDIODEC_TYPE_AT9  = 0x1003U,
	SCE_AUDIODEC_TYPE_MP3  = 0x1004U,
	SCE_AUDIODEC_TYPE_AAC  = 0x1005U,
	SCE_AUDIODEC_TYPE_CELP = 0x1006U
} SceAudiodecType;

#define SCE_AUDIODEC_AT9_MAX_CH_IN_LIBRARY 16
#define SCE_AUDIODEC_MP3_MAX_STREAMS       8
#define SCE_AUDIODEC_AAC_MAX_STREAMS       8
#define SCE_AUDIODEC_CELP_MAX_STREAMS      8

#define SCE_AUDIODEC_AT9_MAX_CH_IN_DECODER  2
#define SCE_AUDIODEC_MP3_MAX_CH_IN_DECODER  2
#define SCE_AUDIODEC_AAC_MAX_CH_IN_DECODER  2
#define SCE_AUDIODEC_CELP_MAX_CH_IN_DECODER 1

#define SCE_AUDIODEC_AT9_MAX_SAMPLES  256
#define SCE_AUDIODEC_MP3_MAX_SAMPLES  1152
#define SCE_AUDIODEC_AAC_MAX_SAMPLES  2048
#define SCE_AUDIODEC_CELP_MAX_SAMPLES 320

#define SCE_AUDIODEC_AT9_MAX_ES_SIZE  1024
#define SCE_AUDIODEC_MP3_MAX_ES_SIZE  1441
#define SCE_AUDIODEC_AAC_MAX_ES_SIZE  1536
#define SCE_AUDIODEC_CELP_MAX_ES_SIZE 24

#define SCE_AUDIODEC_AT9_EXTRA_ACCESS_SIZE  0
#define SCE_AUDIODEC_MP3_EXTRA_ACCESS_SIZE  0
#define SCE_AUDIODEC_AAC_EXTRA_ACCESS_SIZE  0
#define SCE_AUDIODEC_CELP_EXTRA_ACCESS_SIZE 0

#define SCE_AUDIODEC_AT9_MAX_NFRAMES  8
#define SCE_AUDIODEC_MP3_MAX_NFRAMES  1
#define SCE_AUDIODEC_AAC_MAX_NFRAMES  1
#define SCE_AUDIODEC_CELP_MAX_NFRAMES 1

#define SCE_AUDIODEC_AT9_MAX_NSTREAMS  6
#define SCE_AUDIODEC_MP3_MAX_NSTREAMS  6
#define SCE_AUDIODEC_AAC_MAX_NSTREAMS  6
#define SCE_AUDIODEC_CELP_MAX_NSTREAMS 7

typedef enum SceAudiodecMpegVersion {
	SCE_AUDIODEC_MP3_MPEG_VERSION_2_5      = 0,
	SCE_AUDIODEC_MP3_MPEG_VERSION_RESERVED = 1,
	SCE_AUDIODEC_MP3_MPEG_VERSION_2        = 2,
	SCE_AUDIODEC_MP3_MPEG_VERSION_1        = 3
} SceAudiodecMpegVersion;

#define SCE_AUDIODEC_CELP_MPE 0

#define SCE_AUDIODEC_CELP_SAMPLING_RATE_8KHZ 8000

typedef enum SceAudiodecCelpBitrate {
	SCE_AUDIODEC_CELP_BIT_RATE_3850BPS  = 3850,
	SCE_AUDIODEC_CELP_BIT_RATE_4650BPS  = 4650,
	SCE_AUDIODEC_CELP_BIT_RATE_5700BPS  = 5700,
	SCE_AUDIODEC_CELP_BIT_RATE_6600BPS  = 6600,
	SCE_AUDIODEC_CELP_BIT_RATE_7300BPS  = 7300,
	SCE_AUDIODEC_CELP_BIT_RATE_8700BPS  = 8700,
	SCE_AUDIODEC_CELP_BIT_RATE_9900BPS  = 9900,
	SCE_AUDIODEC_CELP_BIT_RATE_10700BPS = 10700,
	SCE_AUDIODEC_CELP_BIT_RATE_11800BPS = 11800,
	SCE_AUDIODEC_CELP_BIT_RATE_12200BPS = 12200
} SceAudiodecCelpBitrate;

typedef struct SceAudiodecInitStreamParam {
	SceUInt32 size;
	SceUInt32 totalStreams;
} SceAudiodecInitStreamParam;

typedef struct SceAudiodecInitChParam {
	SceUInt32 size;
	SceUInt32 totalCh;
} SceAudiodecInitChParam;

typedef union SceAudiodecInitParam {
	SceUInt32                  size;
	SceAudiodecInitChParam     at9;
	SceAudiodecInitStreamParam mp3;
	SceAudiodecInitStreamParam aac;
	SceAudiodecInitStreamParam celp;
} SceAudiodecInitParam;

typedef struct SceAudiodecInfoAt9 {
	SceUInt32 size;
	SceUInt8  configData[4];
	SceUInt32 ch;
	SceUInt32 bitRate;
	SceUInt32 samplingRate;
	SceUInt32 superFrameSize;
	SceUInt32 framesInSuperFrame;
} SceAudiodecInfoAt9;

typedef struct SceAudiodecInfoMp3 {
	SceUInt32 size;      //!< sizeof(SceAudiodecInfoMp3)
	SceUInt32 ch;        //!< number of channels (mono: 1, stereo/joint stereo/two mono: 2)
	SceUInt32 version;   //!< MPEG version (MPEG1: 3, MPEG2: 2, MPEG2.5: 0)
} SceAudiodecInfoMp3;

typedef struct SceAudiodecInfoAac {
	SceUInt32 size;
	SceUInt32 isAdts;
	SceUInt32 ch;
	SceUInt32 samplingRate;
	SceUInt32 isSbr;
} SceAudiodecInfoAac;

/** Information structure for CELP */
typedef struct SceAudiodecInfoCelp {
	SceUInt32 size;                  //!< sizeof(SceAudiodecInfoCelp)
	SceUInt32 excitationMode;        //!< Excitation mode
	SceUInt32 samplingRate;          //!< Sampling rate
	SceUInt32 bitRate;               //!< Bit rate (one of ::SceAudiodecCelpBitrate)
	SceUInt32 lostCount;
} SceAudiodecInfoCelp;

typedef union SceAudiodecInfo {
	SceUInt32           size;
	SceAudiodecInfoAt9  at9;
	SceAudiodecInfoMp3  mp3;
	SceAudiodecInfoAac  aac;
	SceAudiodecInfoCelp celp;
} SceAudiodecInfo;

typedef struct SceAudiodecCtrl {
	SceUInt32       size;
	SceInt32        handle;
	SceUInt8        *pEs;			//!< pointer to elementary stream
	SceUInt32       inputEsSize;	//!< size of elementary stream used actually (in byte)
	SceUInt32       maxEsSize;		//!< maximum size of elementary stream used (in byte)
	void            *pPcm;			//!< pointer to PCM
	SceUInt32       outputPcmSize;	//!< size of PCM output actually (in byte)
	SceUInt32       maxPcmSize;		//!< maximum size of PCM output (in byte)
	SceUInt32       wordLength;		//!< PCM bit depth
	SceAudiodecInfo *pInfo;			//!< pointer to SceAudiodecInfo
} SceAudiodecCtrl;

extern SceInt32 sceAudiodecInitLibrary(SceUInt32 codecType, SceAudiodecInitParam *pInitParam);
extern SceInt32 sceAudiodecTermLibrary(SceUInt32 codecType);
extern SceInt32 sceAudiodecCreateDecoder(SceAudiodecCtrl *pCtrl, SceUInt32 codecType);
extern SceInt32 sceAudiodecDeleteDecoder(SceAudiodecCtrl *pCtrl);
extern SceInt32 sceAudiodecDecode(SceAudiodecCtrl *pCtrl);
extern SceInt32 sceAudiodecDecodeNFrames(SceAudiodecCtrl *pCtrl, SceUInt32 nFrames);
extern SceInt32 sceAudiodecDecodeNStreams(SceAudiodecCtrl *pCtrls[], SceUInt32 nStreams);
extern SceInt32 sceAudiodecClearContext(SceAudiodecCtrl *pCtrl);
extern SceInt32 sceAudiodecGetInternalError(SceAudiodecCtrl *pCtrl, SceInt32 *pInternalError);

extern SceInt32 sceAudiodecGetContextSize(SceAudiodecCtrl *pCtrl, SceUInt32 codecType);
extern SceInt32 sceAudiodecCreateDecoderExternal(SceAudiodecCtrl *pCtrl, SceUInt32 codecType, SceUIntVAddr vaContext, SceUInt32 contextSize);
extern SceInt32 sceAudiodecDeleteDecoderExternal(SceAudiodecCtrl *pCtrl, SceUIntVAddr *pvaContext);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_AUDIODEC_H_ */
