/**
 * \usergroup{SceAvPlayer}
 * \usage{psp2/avplayer.h,SceAvPlayer_stub,SCE_SYSMODULE_AVPLAYER}
 */
 
#ifndef _PSP2_AVPLAYER_H_
#define _PSP2_AVPLAYER_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceAvPlayerHandle;

typedef enum SceAvPlayerErrorCode {
	SCE_AVPLAYER_ERROR_INVALID_PARAM = 0x806A0001,
	SCE_AVPLAYER_ERROR_OUT_OF_MEMORY = 0x806A0003
} SceAvPlayerErrorCode;

typedef enum SceAvPlayerTrickSpeeds {
	SCE_AVPLAYER_TRICK_SPEED_REWIND_32X       = -3200, //!< Rewind 32x
	SCE_AVPLAYER_TRICK_SPEED_REWIND_16X       = -1600, //!< Rewind 16x
	SCE_AVPLAYER_TRICK_SPEED_REWIND_8X        = -800,  //!< Rewind 8x
	SCE_AVPLAYER_TRICK_SPEED_NORMAL           =  100,  //!< Normal Speed
	SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_2X  =  200,  //!< Fast Forward 2x
	SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_4X  =  400,  //!< Fast Forward 4x
	SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_8X  =  800,  //!< Fast Forward 8x
	SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_16X = 1600,  //!< Fast Forward 16x
	SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_32X = 3200   //!< Fast Forward 32x
} SceAvPlayerTrickSpeeds;

typedef enum SceAvPlayerStreamType {
	SCE_AVPLAYER_VIDEO,     //!< Video stream type
	SCE_AVPLAYER_AUDIO,     //!< Audio stream type
	SCE_AVPLAYER_TIMEDTEXT  //!< Timed text (subtitles) stream type
} SceAvPlayerStreamType;

typedef void* (*SceAvPlayerAlloc)(void *arg, uint32_t alignment, uint32_t size);
typedef void (*SceAvPlayerFree)(void *arg, void *ptr);
typedef void* (*SceAvPlayerAllocFrame)(void *arg, uint32_t alignment, uint32_t size);
typedef void (*SceAvPlayerFreeFrame)(void *arg, void *ptr);

typedef int (*SceAvPlayerOpenFile)(void *p, const char *filename);
typedef int (*SceAvPlayerCloseFile)(void *p);
typedef int (*SceAvPlayerReadOffsetFile)(void *p, uint8_t *buffer, uint64_t position, uint32_t length);
typedef uint64_t (*SceAvPlayerSizeFile)(void *p);

typedef void (*SceAvPlayerEventCallback)(void *p, int32_t argEventId, int32_t argSourceId, void *argEventData);

typedef struct SceAvPlayerMemReplacement {
	void *objectPointer;
	SceAvPlayerAlloc allocate;               //!< Memory allocator for generic data
	SceAvPlayerFree deallocate;              //!< Memory deallocator for generic data
	SceAvPlayerAllocFrame allocateTexture;   //!< Memory allocator for video frames
	SceAvPlayerFreeFrame deallocateTexture;  //!< Memory deallocator for video frames
} SceAvPlayerMemReplacement;

typedef struct SceAvPlayerFileReplacement {
	void* objectPointer;
	SceAvPlayerOpenFile open;                //!< File open
	SceAvPlayerCloseFile close;              //!< File close
	SceAvPlayerReadOffsetFile readOffset;    //!< File read from offset
	SceAvPlayerSizeFile size;                //!< File size
} SceAvPlayerFileReplacement;

typedef struct SceAvPlayerEventReplacement {
	void *objectPointer;
	SceAvPlayerEventCallback eventCallback;
} SceAvPlayerEventReplacement;

typedef struct SceAvPlayerInitData {
	SceAvPlayerMemReplacement memoryReplacement;  //!< Memory allocator replacement
	SceAvPlayerFileReplacement fileReplacement;   //!< File I/O replacement
	SceAvPlayerEventReplacement eventReplacement; //!< Event callback replacement
	int32_t debugLevel;
	uint32_t basePriority;                        //!< Base priority of the thread running the video player
	int32_t numOutputVideoFrameBuffers;
	SceBool autoStart;                            //!< Flag indicating whether the video player should start playback automatically
	uint8_t reserved[3];                          //!< Reserved data
	const char *defaultLanguage;
} SceAvPlayerInitData;

typedef struct SceAvPlayerAudio {
	uint16_t channelCount; //!< The number of audio channels of the audio frame.
	uint8_t reserved[2];   //!< Reserved data.
	uint32_t sampleRate;   //!< The samplerate of the audio frame in Hz.
	uint32_t size;         //!< The size of the audio frame in bytes.
	uint32_t languageCode; //!< The language code of the audio frame.
} SceAvPlayerAudio;

typedef struct SceAvPlayerVideo {
	uint32_t width;        //!< The width of the video frame in pixels.
	uint32_t height;       //!< The height of the video frame in pixels.
	float aspectRatio;     //!< The aspect ratio of the video frame.
	uint32_t languageCode; //!< The language code of the video frame.
} SceAvPlayerVideo;

typedef struct SceAvPlayerTextPosition{
	uint16_t top;
	uint16_t left;
	uint16_t bottom;
	uint16_t right;
} SceAvPlayerTextPosition;

typedef struct SceAvPlayerTimedText {
	uint32_t languageCode;            //!< The language code of the subtitles.
	uint16_t textSize;                //!< The size of the subtitles.
	uint16_t fontSize;                //!< The size of the subtitles.
	SceAvPlayerTextPosition position; //!< The position of the subtitles.
} SceAvPlayerTimedText;

typedef union SceAvPlayerStreamDetails {
	uint32_t reserved[4];      //!< Reserved data.
	SceAvPlayerAudio audio;    //!< Audio details.
	SceAvPlayerVideo video;    //!< Video details.
	SceAvPlayerTimedText subs; //!< Subtitles details.
} SceAvPlayerStreamDetails;

typedef struct SceAvPlayerFrameInfo {
	uint8_t *pData;                   //!< Pointer to the frame data.
	uint32_t reserved;                //!< Reserved data
	uint64_t timeStamp;               //!< Timestamp of the frame in milliseconds
	SceAvPlayerStreamDetails details; //!< The frame details.
} SceAvPlayerFrameInfo;

typedef struct SceAvPlayerStreamInfo {
	uint32_t type;                    //!< Type of the stream (One of ::SceAvPlayerStreamType)
	uint32_t reserved;                //!< Reserved data             
	SceAvPlayerStreamDetails details; //!< The stream details.
	uint64_t duration;                //!< Total duration of the stream in milliseconds.
	uint64_t startTime;               //!< Starting time of the stream in milliseconds.
} SceAvPlayerStreamInfo;

/**
 * @param[in] data - Init data for the video player
 *
 * @return The video player handle on success, < 0 on error.
 */
SceAvPlayerHandle sceAvPlayerInit(SceAvPlayerInitData *data);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerPause(SceAvPlayerHandle handle);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerResume(SceAvPlayerHandle handle);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerStart(SceAvPlayerHandle handle);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerStop(SceAvPlayerHandle handle);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 * @param[in] looping - A flag indicating whether the video playback should loop
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerSetLooping(SceAvPlayerHandle handle, SceBool looping);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 *
 * @return SCE_TRUE if the video playback is active, SCE_FALSE otherwise.
 */
SceBool sceAvPlayerIsActive(SceAvPlayerHandle handle);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 * @param[in] filename - Full path to the file to play
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerAddSource(SceAvPlayerHandle handle, const char *filename);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerClose(SceAvPlayerHandle handle);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 * @param[out] info - Descriptor for the received data
 *
 * @return SCE_TRUE if new data is available, SCE_FALSE otherwise.
 */
SceBool sceAvPlayerGetAudioData(SceAvPlayerHandle handle, SceAvPlayerFrameInfo *info);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 * @param[out] info - Descriptor for the received data
 *
 * @return SCE_TRUE if new data is available, SCE_FALSE otherwise.
 */
SceBool sceAvPlayerGetVideoData(SceAvPlayerHandle handle, SceAvPlayerFrameInfo *info);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 *
 * @return Current time on the video playback in milliseconds.
 */
uint64_t sceAvPlayerCurrentTime(SceAvPlayerHandle handle);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 * @param[in] offset - Offset to jump to on the video playback in milliseconds.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerJumpToTime(SceAvPlayerHandle handle, uint64_t offset);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 * @param[in] offset - One of ::SceAvPlayerTrickSpeeds.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerSetTrickSpeed(SceAvPlayerHandle handle, int speed);

/**
 * @param[in] handle - A player handle created with ::sceAvPlayerInit
 * @param[in] id - Stream ID to get info for.
 * @param[out] info - Info retrieved for the requested stream.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAvPlayerGetStreamInfo(SceAvPlayerHandle handle, uint32_t id, SceAvPlayerStreamInfo *info);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_AVPLAYER_H_ */
