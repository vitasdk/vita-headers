/**
 * \usergroup{SceCamera}
 * \usage{psp2/camera.h,SceCamera_stub}
 */


#ifndef _PSP2_CAMERA_H_
#define _PSP2_CAMERA_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Camera error codes. */
typedef enum SceCameraErrorCode {
	SCE_CAMERA_ERROR_PARAM               = 0x802E0000,
	SCE_CAMERA_ERROR_ALREADY_INIT        = 0x802E0001,
	SCE_CAMERA_ERROR_NOT_INIT            = 0x802E0002,
	SCE_CAMERA_ERROR_ALREADY_OPEN        = 0x802E0003,
	SCE_CAMERA_ERROR_NOT_OPEN            = 0x802E0004,
	SCE_CAMERA_ERROR_ALREADY_START       = 0x802E0005,
	SCE_CAMERA_ERROR_NOT_START           = 0x802E0006,
	SCE_CAMERA_ERROR_FORMAT_UNKNOWN      = 0x802E0007,
	SCE_CAMERA_ERROR_RESOLUTION_UNKNOWN  = 0x802E0008,
	SCE_CAMERA_ERROR_BAD_FRAMERATE       = 0x802E0009,
	SCE_CAMERA_ERROR_TIMEOUT             = 0x802E000A,
	SCE_CAMERA_ERROR_EXCLUSIVE           = 0x802E000B,
	SCE_CAMERA_ERROR_ATTRIBUTE_UNKNOWN   = 0x802E000C,
	SCE_CAMERA_ERROR_MAX_PROCESS         = 0x802E000D,
	SCE_CAMERA_ERROR_NOT_ACTIVE          = 0x802E000E,
	SCE_CAMERA_ERROR_ALREADY_READ        = 0x802E000F,
	SCE_CAMERA_ERROR_NOT_MOUNTED         = 0x802E0010,
	SCE_CAMERA_ERROR_DATA_RANGE_UNKNOWN  = 0x802E0011,
	SCE_CAMERA_ERROR_OTHER_ALREADY_START = 0x802E0012,
	SCE_CAMERA_ERROR_FATAL               = 0x802E00FF
} SceCameraErrorCode;

/** Enumeration for the camera device types. */
typedef enum SceCameraDevice {
	SCE_CAMERA_DEVICE_FRONT = 0, //!< Front camera
	SCE_CAMERA_DEVICE_BACK  = 1  //!< Retro camera
} SceCameraDevice;

/** Enumeration for the camera process priorities. */
typedef enum SceCameraPriority {
	SCE_CAMERA_PRIORITY_SHARE      = 0, //!< Share mode
	SCE_CAMERA_PRIORITY_EXCLUSIVE  = 1  //!< Exclusive mode
} SceCameraPriority;

/** Enumeration for the camera output formats. */
typedef enum SceCameraFormat {
	SCE_CAMERA_FORMAT_INVALID        = 0, //!< Invalid format
	SCE_CAMERA_FORMAT_YUV422_PLANE   = 1, //!< YUV422 planes
	SCE_CAMERA_FORMAT_YUV422_PACKED  = 2, //!< YUV422 pixels packed
	SCE_CAMERA_FORMAT_YUV420_PLANE   = 3, //!< YUV420 planes
	SCE_CAMERA_FORMAT_ARGB           = 4, //!< ARGB pixels
	SCE_CAMERA_FORMAT_ABGR           = 5, //!< ABGR pixels
	SCE_CAMERA_FORMAT_RAW8           = 6  //!< 8 bit raw data
} SceCameraFormat;

/** Enumeration for the camera resolutions. */
typedef enum SceCameraResolution {
	SCE_CAMERA_RESOLUTION_0_0        = 0, //!< Invalid resolution
	SCE_CAMERA_RESOLUTION_640_480    = 1, //!< VGA resolution
	SCE_CAMERA_RESOLUTION_320_240    = 2, //!< QVGA resolution
	SCE_CAMERA_RESOLUTION_160_120    = 3, //!< QQVGA resolution
	SCE_CAMERA_RESOLUTION_352_288    = 4, //!< CIF resolution
	SCE_CAMERA_RESOLUTION_176_144    = 5, //!< QCIF resolution
	SCE_CAMERA_RESOLUTION_480_272    = 6, //!< PSP resolution
	SCE_CAMERA_RESOLUTION_640_360    = 8  //!< NGP resolution
} SceCameraResolution;

/** Enumeration for the camera framerates. */
typedef enum SceCameraFrameRate {
	SCE_CAMERA_FRAMERATE_3_FPS  = 3,   //!< 3.75 fps
	SCE_CAMERA_FRAMERATE_5_FPS  = 5,   //!< 5 fps
	SCE_CAMERA_FRAMERATE_7_FPS  = 7,   //!< 7.5 fps
	SCE_CAMERA_FRAMERATE_10_FPS = 10,  //!< 10 fps
	SCE_CAMERA_FRAMERATE_15_FPS = 15,  //!< 15 fps
	SCE_CAMERA_FRAMERATE_20_FPS = 20,  //!< 20 fps
	SCE_CAMERA_FRAMERATE_30_FPS = 30,  //!< 30 fps
	SCE_CAMERA_FRAMERATE_60_FPS = 60,  //!< 60 fps
	SCE_CAMERA_FRAMERATE_120_FPS = 120 //!< 120 fps (@note Resolution must be QVGA or lower)
} SceCameraFrameRate;

/** Enumeration for the camera exposure compensations. */
typedef enum SceCameraExposureCompensation {
	SCE_CAMERA_EV_NEGATIVE_20 = -20, //!< -2.0
	SCE_CAMERA_EV_NEGATIVE_17 = -17, //!< -1.7
	SCE_CAMERA_EV_NEGATIVE_15 = -15, //!< -1.5
	SCE_CAMERA_EV_NEGATIVE_13 = -13, //!< -1.3
	SCE_CAMERA_EV_NEGATIVE_10 = -10, //!< -1.0
	SCE_CAMERA_EV_NEGATIVE_7  = -7,  //!< -0.7
	SCE_CAMERA_EV_NEGATIVE_5  = -5,  //!< -0.5
	SCE_CAMERA_EV_NEGATIVE_3  = -3,  //!< -0.3
	SCE_CAMERA_EV_POSITIVE_0  = 0,   //!< +0.0
	SCE_CAMERA_EV_POSITIVE_3  = 3,   //!< +0.3
	SCE_CAMERA_EV_POSITIVE_5  = 5,   //!< +0.5
	SCE_CAMERA_EV_POSITIVE_7  = 7,   //!< +0.7
	SCE_CAMERA_EV_POSITIVE_10 = 10,  //!< +1.0
	SCE_CAMERA_EV_POSITIVE_13 = 13,  //!< +1.3
	SCE_CAMERA_EV_POSITIVE_15 = 15,  //!< +1.5
	SCE_CAMERA_EV_POSITIVE_17 = 17,  //!< +1.7
	SCE_CAMERA_EV_POSITIVE_20 = 20   //!< +2.0
} SceCameraExposureCompensation;

/** Enumeration for the camera effects. */
typedef enum SceCameraEffect {
	SCE_CAMERA_EFFECT_NORMAL     = 0,
	SCE_CAMERA_EFFECT_NEGATIVE   = 1,
	SCE_CAMERA_EFFECT_BLACKWHITE = 2,
	SCE_CAMERA_EFFECT_SEPIA      = 3,
	SCE_CAMERA_EFFECT_BLUE       = 4,
	SCE_CAMERA_EFFECT_RED        = 5,
	SCE_CAMERA_EFFECT_GREEN      = 6
} SceCameraEffect;

/** Enumeration for the camera reverse modes. */
typedef enum SceCameraReverse {
	SCE_CAMERA_REVERSE_OFF          = 0,                                                    //!< Reverse mode off
	SCE_CAMERA_REVERSE_MIRROR       = 1,                                                    //!< Mirror mode
	SCE_CAMERA_REVERSE_FLIP         = 2,                                                    //!< Flip mode
	SCE_CAMERA_REVERSE_MIRROR_FLIP  = (SCE_CAMERA_REVERSE_MIRROR | SCE_CAMERA_REVERSE_FLIP) //!< Mirror + Flip mode
} SceCameraReverse;

/** Enumeration for the camera saturations. */
typedef enum SceCameraSaturation {
	SCE_CAMERA_SATURATION_0  = 0,  //!< 0.0
	SCE_CAMERA_SATURATION_5  = 5,  //!< 0.5
	SCE_CAMERA_SATURATION_10 = 10, //!< 1.0
	SCE_CAMERA_SATURATION_20 = 20, //!< 2.0
	SCE_CAMERA_SATURATION_30 = 30, //!< 3.0
	SCE_CAMERA_SATURATION_40 = 40  //!< 4.0
} SceCameraSaturation;

/** Enumeration for the camera sharpnesses. */
typedef enum SceCameraSharpness {
	SCE_CAMERA_SHARPNESS_100 = 1, //!< 100%
	SCE_CAMERA_SHARPNESS_200 = 2, //!< 200%
	SCE_CAMERA_SHARPNESS_300 = 3, //!< 300%
	SCE_CAMERA_SHARPNESS_400 = 4  //!< 400%
} SceCameraSharpness;

/** Enumeration for the camera anti-flickering modes. */
typedef enum SceCameraAntiFlicker {
	SCE_CAMERA_ANTIFLICKER_AUTO = 1, //!< Automatic mode
	SCE_CAMERA_ANTIFLICKER_50HZ = 2, //!< 50 Hz mode
	SCE_CAMERA_ANTIFLICKER_60HZ = 3  //!< 50 Hz mode
} SceCameraAntiFlicker;

/** Enumeration for the camera ISO speed modes. */
typedef enum SceCameraISO {
	SCE_CAMERA_ISO_AUTO = 1,  //!< Automatic mode
	SCE_CAMERA_ISO_100 = 100, //!< ISO100/21�
	SCE_CAMERA_ISO_200 = 200, //!< ISO200/24�
	SCE_CAMERA_ISO_400 = 400  //!< ISO400/27�
} SceCameraISO;

/** Enumeration for the camera gain modes. */
typedef enum SceCameraGain {
	SCE_CAMERA_GAIN_AUTO = 0,
	SCE_CAMERA_GAIN_1    = 1,
	SCE_CAMERA_GAIN_2    = 2,
	SCE_CAMERA_GAIN_3    = 3,
	SCE_CAMERA_GAIN_4    = 4,
	SCE_CAMERA_GAIN_5    = 5,
	SCE_CAMERA_GAIN_6    = 6,
	SCE_CAMERA_GAIN_7    = 7,
	SCE_CAMERA_GAIN_8    = 8,
	SCE_CAMERA_GAIN_9    = 9,
	SCE_CAMERA_GAIN_10   = 10,
	SCE_CAMERA_GAIN_11   = 11,
	SCE_CAMERA_GAIN_12   = 12,
	SCE_CAMERA_GAIN_13   = 13,
	SCE_CAMERA_GAIN_14   = 14,
	SCE_CAMERA_GAIN_15   = 15,
	SCE_CAMERA_GAIN_16   = 16
} SceCameraGain;

/** Enumeration for the camera white balance modes. */
typedef enum SceCameraWhiteBalance {
	SCE_CAMERA_WB_AUTO = 0,  //!< Automatic mode
	SCE_CAMERA_WB_DAY  = 1,  //!< Daylight mode
	SCE_CAMERA_WB_CWF  = 2,  //!< Cool White Fluorescent mode
	SCE_CAMERA_WB_SLSA = 4   //!< Standard Light Source A mode
} SceCameraWhiteBalance;

/** Enumeration for the camera backlight modes. */
typedef enum SceCameraBacklight {
	SCE_CAMERA_BACKLIGHT_OFF = 0,  //!< Disabled
	SCE_CAMERA_BACKLIGHT_ON  = 1   //!< Enabled
} SceCameraBacklight;

/** Enumeration for the camera nightmode modes. */
typedef enum SceCameraNightmode {
	SCE_CAMERA_NIGHTMODE_OFF     = 0,  //!< Disabled
	SCE_CAMERA_NIGHTMODE_LESS10  = 1,  //!< 10 lux or below
	SCE_CAMERA_NIGHTMODE_LESS100 = 2,  //!< 100 lux or below
	SCE_CAMERA_NIGHTMODE_OVER100 = 3   //!< 100 lux or over
} SceCameraNightmode;

typedef struct SceCameraInfo {
	SceSize size;        //!< sizeof(SceCameraInfo)
	uint16_t priority;   //!< Process priority (one of ::SceCameraPriority)
	uint16_t format;     //!< Output format (One or more ::SceCameraFormat)
	uint16_t resolution; //!< Resolution (one of ::SceCameraResolution)
	uint16_t framerate;  //!< Framerate (one of ::SceCameraFrameRate)
	uint16_t width;
	uint16_t height;
	uint16_t range;
	uint16_t pad;        //!< Structure padding
	SceSize sizeIBase;
	SceSize sizeUBase;
	SceSize sizeVBase;
	void *pIBase;
	void *pUBase;
	void *pVBase;
	uint16_t pitch;
	uint16_t buffer;
} SceCameraInfo;

typedef struct SceCameraRead {
	SceSize size;         //!< sizeof(SceCameraRead)
	int mode;
	int pad;
	int status;
	uint64_t frame;
	uint64_t timestamp;
	SceSize sizeIBase;
	SceSize sizeUBase;
	SceSize sizeVBase;
	void *pIBase;
	void *pUBase;
	void *pVBase;
} SceCameraRead;

/**
 * Open a camera device.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] pInfo - Pointer to an already set ::SceCameraInfo struct.
 *
 * @return SCE_OK, <0 on error.
 */
int sceCameraOpen(int devnum, SceCameraInfo *pInfo);

/**
 * Close a camera device.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 *
 * @return SCE_OK, <0 on error.
 */
int sceCameraClose(int devnum);

/**
 * Start camera streaming.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 *
 * @return SCE_OK, <0 on error.
 */
int sceCameraStart(int devnum);

/**
 * Stop camera streaming.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 *
 * @return SCE_OK, <0 on error.
 */
int sceCameraStop(int devnum);

/**
 * Read image data from current streaming.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] pRead - Pointer to an already set ::SceCameraRead.
 *
 * @return SCE_OK, <0 on error.
 */
int sceCameraRead(int devnum, SceCameraRead *pRead);

/**
 * Check if camera device is active.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 *
 * @return 1 if camera is active, 0 if inactive , <0 on error.
 */
int sceCameraIsActive(int devnum);

/**
 * Get camera saturation value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pLevel - Pointer to a variable where to save the result. (See ::SceCameraSaturation)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetSaturation(int devnum, int *pLevel);

/**
 * Set camera saturation value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] level - One of ::SceCameraSaturation.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetSaturation(int devnum, int level);

/**
 * Get camera brightness value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pLevel - Pointer to a variable where to save the result.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetBrightness(int devnum, int *pLevel);

/**
 * Set camera brightness value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] level - Brightness value.
 *
 * @return SCE_OK , <0 on error.
 *
 * @note Brightness value must be between 0 and 255.
 */
int sceCameraSetBrightness(int devnum, int level);

/**
 * Get camera contrast value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pLevel - Pointer to a variable where to save the result.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetContrast(int devnum, int *pLevel);

/**
 * Set camera contrast value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] level - Contrast value.
 *
 * @return SCE_OK , <0 on error.
 *
 * @note Contrast value must be between 0 and 255.
 */
int sceCameraSetContrast(int devnum, int level);

/**
 * Get camera sharpness value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pLevel - Pointer to a variable where to save the result. (See ::SceCameraSharpness)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetSharpness(int devnum, int *pLevel);

/**
 * Set camera sharpness value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] level - One of ::SceCameraSharpness.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetSharpness(int devnum, int level);

/**
 * Get camera reverse mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result. (See ::SceCameraReverse)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetReverse(int devnum, int *pMode);

/**
 * Set camera reverse mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraReverse.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetReverse(int devnum, int mode);

/**
 * Get active camera effects.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetEffect(int devnum, int *pMode);

/**
 * Active a camera effect.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraEffect.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetEffect(int devnum, int mode);

/**
 * Get camera exposure compensation value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pLevel - Pointer to a variable where to save the result (See ::SceCameraExposureCompensation).
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetEV(int devnum, int *pLevel);

/**
 * Set camera exposure compensation value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] level - One of ::SceCameraExposureCompensation.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetEV(int devnum, int level);

/**
 * Get camera zoom value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pLevel - Pointer to a variable where to save the result.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetZoom(int devnum, int *pLevel);

/**
 * Set camera zoom value.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] level - Camera zoom value.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetZoom(int devnum, int level);

/**
 * Get camera anti-flickering mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result. (See ::SceCameraAntiFlicker)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetAntiFlicker(int devnum, int *pMode);

/**
 * Set camera exposure anti-flickering mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraAntiFlicker.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetAntiFlicker(int devnum, int mode);

/**
 * Get camera ISO speed mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result. (See ::SceCameraISO)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetISO(int devnum, int *pMode);

/**
 * Set camera ISO speed mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraISO.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetISO(int devnum, int mode);

/**
 * Get camera gain mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result. (See ::SceCameraGain)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetGain(int devnum, int *pMode);

/**
 * Set camera gain mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraGain.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetGain(int devnum, int mode);

/**
 * Get camera white balance mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result. (See ::SceCameraWhiteBalance)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetWhiteBalance(int devnum, int *pMode);

/**
 * Set camera white balance mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraWhiteBalance.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetWhiteBalance(int devnum, int mode);

/**
 * Get camera backlight compensation mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result. (See ::SceCameraBacklight)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetBacklight(int devnum, int *pMode);

/**
 * Set camera backlight mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraBacklight.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetBacklight(int devnum, int mode);

/**
 * Get nightmode mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result. (See ::SceCameraNightmode)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetNightmode(int devnum, int *pMode);

/**
 * Set camera nightmoge mode.
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - One of ::SceCameraNightmode.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetNightmode(int devnum, int mode);

/**
 * Get exposure ceiling mode. (?)
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetExposureCeiling(int devnum, int *pMode);

/**
 * Set exposure ceiling mode. (?)
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - Exposure ceiling mode value. (?)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetExposureCeiling(int devnum, int mode);

/**
 * Get auto control hold mode. (?)
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pMode - Pointer to a variable where to save the result.
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraGetAutoControlHold(int devnum, int *pMode);

/**
 * Set auto control hold mode. (?)
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[in] mode - Auto control hold mode value. (?)
 *
 * @return SCE_OK , <0 on error.
 */
int sceCameraSetAutoControlHold(int devnum, int mode);

/**
 * Get camera device location. (?)
 *
 * @param[in] devnum - One of ::SceCameraDevice.
 * @param[out] pLocation - Pointer to a variable where to save the result.
 *
 * @return SCE_OK , <0 on error.
 */

int sceCameraGetDeviceLocation(int devnum, SceFVector3 *pLocation);

int sceCameraGetImageQuality(int devnum, int* pLevel);
int sceCameraSetImageQuality(int devnum, int level);
int sceCameraGetNoiseReduction(int devnum, int* pLevel);
int sceCameraSetNoiseReduction(int devnum, int level);
int sceCameraGetSharpnessOff(int devnum, int* pLevel);
int sceCameraSetSharpnessOff(int devnum, int level);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_CAMERA_H_ */

