/**
 * \usergroup{SceAudioenc}
 * \usage{psp2/audioenc.h,SceAudioenc_stub}
 */


#ifndef _PSP2_AUDIOENC_H_
#define _PSP2_AUDIOENC_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAudioencErrorCode {
	SCE_AUDIOENC_ERROR_API_FAIL             = 0x80860000,
	SCE_AUDIOENC_ERROR_INVALID_TYPE         = 0x80860001,
	SCE_AUDIOENC_ERROR_INVALID_INIT_PARAM   = 0x80860002,
	SCE_AUDIOENC_ERROR_ALREADY_INITIALIZED  = 0x80860003,
	SCE_AUDIOENC_ERROR_OUT_OF_MEMORY        = 0x80860004,
	SCE_AUDIOENC_ERROR_NOT_INITIALIZED      = 0x80860005,
	SCE_AUDIOENC_ERROR_A_HANDLE_IN_USE      = 0x80860006,
	SCE_AUDIOENC_ERROR_ALL_HANDLES_IN_USE   = 0x80860007,
	SCE_AUDIOENC_ERROR_INVALID_PTR          = 0x80860008,
	SCE_AUDIOENC_ERROR_INVALID_HANDLE       = 0x80860009,
	SCE_AUDIOENC_ERROR_NOT_HANDLE_IN_USE    = 0x8086000A,
	SCE_AUDIOENC_ERROR_CH_SHORTAGE          = 0x8086000B,
	SCE_AUDIOENC_ERROR_INVALID_WORD_LENGTH  = 0x8086000C,
	SCE_AUDIOENC_ERROR_INVALID_SIZE         = 0x8086000D,
	SCE_AUDIOENC_ERROR_INVALID_ALIGNMENT    = 0x8086000E,
	SCE_AUDIOENC_ERROR_UNSUPPORTED          = 0x8086000F
} SceAudioencErrorCode;

typedef enum SceAudioencCelpErrorCode {
	SCE_AUDIOENC_CELP_ERROR_INVALID_CONFIG  = 0x80861001
} SceAudioencCelpErrorCode;

#define SCE_AUDIOENC_WORD_LENGTH_16BITS         16      //!< Definition of wordlength
#define SCE_AUDIOENC_TYPE_CELP                  0x2006U //!< Audio encoder type
#define SCE_AUDIOENC_CELP_MAX_STREAMS           1       //!< Max number of streams
#define SCE_AUDIOENC_CELP_MAX_SAMPLES           320     //!< Max number of samples
#define SCE_AUDIOENC_CELP_MAX_ES_SIZE           24      //!< Max elementary stream size
#define SCE_AUDIOENC_CELP_MPE                   (0)     //!< CELP encoder default excitation mode
#define SCE_AUDIOENC_CELP_SAMPLING_RATE_8KHZ    (8000)  //!< CELP encoder default sampling rate

typedef enum SceAudioencCelpBitrate {
	SCE_AUDIOENC_CELP_BIT_RATE_3850BPS  = 3850,
	SCE_AUDIOENC_CELP_BIT_RATE_4650BPS  = 4650,
	SCE_AUDIOENC_CELP_BIT_RATE_5700BPS  = 5700,
	SCE_AUDIOENC_CELP_BIT_RATE_6600BPS  = 6600,
	SCE_AUDIOENC_CELP_BIT_RATE_7300BPS  = 7300,
	SCE_AUDIOENC_CELP_BIT_RATE_8700BPS  = 8700,
	SCE_AUDIOENC_CELP_BIT_RATE_9900BPS  = 9900,
	SCE_AUDIOENC_CELP_BIT_RATE_10700BPS = 10700,
	SCE_AUDIOENC_CELP_BIT_RATE_11800BPS = 11800,
	SCE_AUDIOENC_CELP_BIT_RATE_12200BPS = 12200
} SceAudioencCelpBitrate;

/** Initialization structure to provide to ::SceAudioencInitParam */
typedef struct SceAudioencInitStreamParam {
	SceSize size;               //!< sizeof(SceAudioencInitStreamParam)
	unsigned int totalStreams;  //!< Total number of audio streams
} SceAudioencInitStreamParam;

/** Information structure for CELP */
typedef struct SceAudioencInfoCelp {
	SceSize size;                    //!< sizeof(SceAudioencInfoCelp)
	unsigned int excitationMode;     //!< Excitation mode
	unsigned int samplingRate;       //!< Sampling rate
	unsigned int bitRate;            //!< Bit rate (one of ::SceAudioencCelpBitrate)
} SceAudioencInfoCelp;

/** Optional information structure for CELP */
typedef struct SceAudioencOptInfoCelp {
	SceSize size;                  //!< sizeof(SceAudioencOptInfoCelp)
	uint8_t header[32];            //!< Header buffer
	SceSize headerSize;            //!< Header size
	unsigned int encoderVersion;   //!< Encoder version
} SceAudioencOptInfoCelp;

/** Initialization structure to pass as argument to ::sceAudioencInitLibrary */
typedef union SceAudioencInitParam {
	SceSize size;                     //!< sizeof(SceAudioencInitParam)
	SceAudioencInitStreamParam celp;  //!< See ::SceAudioencInitStreamParam
} SceAudioencInitParam;

/** Audio encoder info */
typedef union SceAudioencInfo {
	SceSize size;              //!< sizeof(SceAudioencInfo)
	SceAudioencInfoCelp celp;  //!< Information structure for CELP
} SceAudioencInfo;

/** Audio encoder optional info */
typedef union SceAudioencOptInfo {
	SceSize size;                 //!< sizeof(SceAudioencOptInfo)
	SceAudioencOptInfoCelp celp;  //!< Optional information structure for CELP
} SceAudioencOptInfo;

typedef struct SceAudioencCtrl {
	SceSize size;                   //!< sizeof(SceAudioencCtrl)
	int handle;                     //!< Encoder handle
	void *pInputPcm;                //!< Pointer to elementary stream
	SceSize inputPcmSize;           //!< Size of elementary stream used actually (in byte)
	SceSize maxPcmSize;             //!< Max size of elementary stream used (in byte)
	void *pOutputEs;                //!< Pointer to PCM
	SceSize outputEsSize;           //!< Size of PCM output actually (in byte)
	SceSize maxEsSize;              //!< Max size of PCM output (in byte)
	SceSize wordLength;             //!< PCM bit depth
	SceAudioencInfo *pInfo;         //!< Pointer to ::SceAudioencInfo
	SceAudioencOptInfo *pOptInfo;   //!< Pointer to ::SceAudioencOptInfo
} SceAudioencCtrl;

int sceAudioencInitLibrary(int codecType, SceAudioencInitParam *pInitParam);
int sceAudioencTermLibrary(unsigned int codecType);
int sceAudioencCreateEncoder(SceAudioencCtrl *pCtrl, int codecType);
int sceAudioencDeleteEncoder(SceAudioencCtrl *pCtrl);
int sceAudioencEncode(SceAudioencCtrl *pCtrl);
int sceAudioencClearContext(SceAudioencCtrl *pCtrl);
int sceAudioencGetOptInfo(SceAudioencCtrl *pCtrl);
int sceAudioencGetInternalError(SceAudioencCtrl *pCtrl, int *pInternalError);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_AUDIOENC_H_ */