/**
 * \usergroup{SceMp4Rec}
 * \usage{psp2/mp4rec.h,SceLibMp4Recorder_stub,SCE_SYSMODULE_MP4_RECORDER}
 */

#ifndef _PSP2_MP4REC_H_
#define _PSP2_MP4REC_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_MP4REC_COMMON_DENOM_TIMESCALE 240000 //!< Common denominator timescale between audio and video
#define SCE_MP4REC_VIDEO_TIMESCALE 30000 //!< Video timescale in hz
#define SCE_MP4REC_AUDIO_TIMESCALE 48000 //!< Audio timescale in hz

#define SCE_MP4REC_VIDEO_SAMPLE_DURATION 1001 //!< Duration of a single video sample in ms
#define SCE_MP4REC_AUDIO_SAMPLE_DURATION 1024 //!< Duration of a single audio sample in ms

#define SCE_MP4REC_AUDIO_BUFFER_SIZE 4096 //!< Size in bytes of the audio buffer used during recording

typedef enum {
	SCE_MP4REC_PIXELFORMAT_A8B8G8R8      = 0x00000000, //!< 32-bit ABGR format
	SCE_MP4REC_PIXELFORMAT_YUV420_PACKED = 0x00000020  //!< Packed YUV420 format
} SceMp4RecPixelFormat;

typedef enum {
	SCE_MP4REC_MODE_640_368_2MBPS, //!< 640x368 with 2mbps bitrate
	SCE_MP4REC_MODE_640_368_1MBPS, //!< 640x368 with 1mbps bitrate
	SCE_MP4REC_MODE_480_272_2MBPS, //!< 480x272 with 2mbps bitrate
	SCE_MP4REC_MODE_480_272_1MBPS, //!< 480x272 with 1mbps bitrate
	SCE_MP4REC_MODE_368_208_2MBPS, //!< 368x208 with 2mbps bitrate
	SCE_MP4REC_MODE_368_208_1MBPS  //!< 368x208 with 1mbps bitrate
} SceMp4RecMode;

typedef struct {
    SceSize size;       //!< sizeof(SceMp4RecRecorder)
    void *base;         //!< Pointer to the base address of the recorder memblock
    uint32_t base_size; //!< Size of the recorder memblock in bytes
    int unk;            //!< Unknown area
} SceMp4RecRecorder;

typedef struct {
    SceSize size;           //!< sizeof(SceMp4RecInitParam)
    uint32_t mode;          //!< One of ::SceMp4RecMode
    void *encoder_mem;      //!< Pointer to base address of a physically contiguous memory block to use for video encoding
    uint32_t encoder_size;  //!< Size of the memory block used for video encoding in bytes
    void *av_mem;           //!< Pointer to base address of a physically contiguous memory block to use for audio encoding
    uint32_t av_size;       //!< Size of the memory block used for audio encoding in bytes
    int affinity;           //!< CPU affinity mask for the recorder thread
    int priority;           //!< Priority for the recoreder thread
} SceMp4RecInitParam;

typedef struct {
    SceSize size;             //!< sizeof(SceMp4RecFrame)
    int pixelformat;          //!< Pixelformat (One of ::SceMp4RecPixelFormat)
    int stride;               //!< Frame stride in pixels
    int width;                //!< Frame width in pixels
    int height;               //!< Frame height in pixels
    char unk[16];             //!< Unknown area
    void *buffer;             //!< Pointer to the frame buffer
	uint32_t reserved;        //!< Reserved area
} SceMp4RecFrame;

typedef struct {
    SceSize size;           //!< sizeof(SceMp4RecTermParam)
    SceBool discard;        //!< Wether to save or discard the final video file
    uint32_t reserved[128]; //!< Reserved area
    void *metadata;         //!< Metadata of the final video file
} SceMp4RecTermParam;

/**
 * Create a new MP4 video recorder
 *
 *
 * @param[in] rec - Struct describing memory layout for the new recorder.
 *
 * @return 0 on success, < 0 on error.
*/
int sceMp4RecCreateRecorder(SceMp4RecRecorder *rec);

/**
 * Delete an existing MP4 video recorder
 *
 *
 * @param[in] rec - Struct describing memory layout for the recorder to delete.
 *
 * @return 0 on success, < 0 on error.
*/
int sceMp4RecDeleteRecorder(SceMp4RecRecorder *rec);

/**
 * Queries the required memory size for video and audio encoding.
 *
 *
 * @param[in] rec - Struct describing memory layout for the recorder to use.
 * @param[in] mode - The recorder mode to use (One of ::SceMp4RecMode).
 * @param[out] encoder_size - The required size in bytes for the video encoding memory block.
 * @param[out] av_size - The required size in bytes for the audio encoding memory block.
 *
 * @return 0 on success, < 0 on error.
*/
int sceMp4RecQueryPhysicalMemSize(SceMp4RecRecorder *rec, int mode, uint32_t *encoder_size, uint32_t *av_size);

/**
 * Init a new video recording session.
 *
 *
 * @param[in] rec - Struct describing memory layout for the recorder to use.
 * @param[in] params - Struct describing the recording session parameters to use.
 *
 * @return 0 on success, < 0 on error.
*/
int sceMp4RecInit(SceMp4RecRecorder *rec, SceMp4RecInitParam *params);

/**
 * Terminate an ongoing recording session.
 *
 *
 * @param[in] rec - Struct describing memory layout for the recorder to use.
 * @param[in] params - Struct describing the recording session parameters to use for the final video file.
 *
 * @return 0 on success, < 0 on error.
 * @note - If the video is not discarded, it will be auomatically saved in ux0:video.
*/
int sceMp4RecTerm(SceMp4RecRecorder *rec, SceMp4RecTermParam *params);

/**
 * Perform hardware accelerated rescaling and colorspace conversion.
 *
 *
 * @param[in] dst - Struct describing the desired frame output setup.
 * @param[in] src - Struct describing the frame input setup.
 *
 * @return 0 on success, < 0 on error.
*/
int sceMp4RecCsc(SceMp4RecFrame *dst, SceMp4RecFrame *src);

/**
 * Add a new video sample to the ongoing recording recording session.
 *
 *
 * @param[in] rec - Struct describing memory layout for the recorder to use.
 * @param[in] buffer - Buffer pointing to the frame buffer to add to the recording.
 * @param[in] size - Size in bytes of the passed frame buffer.
 *
 * @return 0 on success, < 0 on error.
*/
int sceMp4RecAddVideoSample(SceMp4RecRecorder *rec, void *buffer, int size);

/**
 * Add a new audio sample to the ongoing recording recording session.
 *
 *
 * @param[in] rec - Struct describing memory layout for the recorder to use.
 * @param[in] buffer - Buffer pointing to the audio buffer to add to the recording.
 * @param[in] size - Size in bytes of the passed audio buffer (Must be SCE_MP4REC_AUDIO_BUFFER_SIZE)
 *
 * @return 0 on success, < 0 on error.
*/
int sceMp4RecAddAudioSample(SceMp4RecRecorder *rec, void *buffer, int size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MP4REC_H_ */
