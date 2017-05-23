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

typedef enum SceCameraErrorCode {
	SCE_CAMERA_ERROR_PARAM              = 0x802e0000,
	SCE_CAMERA_ERROR_ALREADY_INIT       = 0x802e0001,
	SCE_CAMERA_ERROR_NOT_INIT           = 0x802e0002,
	SCE_CAMERA_ERROR_ALREADY_OPEN       = 0x802e0003,
	SCE_CAMERA_ERROR_NOT_OPEN           = 0x802e0004,
	SCE_CAMERA_ERROR_ALREADY_START      = 0x802e0005,
	SCE_CAMERA_ERROR_NOT_START          = 0x802e0006,
	SCE_CAMERA_ERROR_FORMAT_UNKNOWN     = 0x802e0007,
	SCE_CAMERA_ERROR_RESOLUTION_UNKNOWN = 0x802e0008,
	SCE_CAMERA_ERROR_BAD_FRAMERATE      = 0x802e0009,
	SCE_CAMERA_ERROR_TIMEOUT            = 0x802e000a,
	SCE_CAMERA_ERROR_EXCLUSIVE          = 0x802e000b,
	SCE_CAMERA_ERROR_ATTRIBUTE_UNKNOWN  = 0x802e000c,
	SCE_CAMERA_ERROR_MAX_PROCESS        = 0x802e000d,
	SCE_CAMERA_ERROR_NOT_ACTIVE         = 0x802e000e,
	SCE_CAMERA_ERROR_FATAL              = 0x802e00ff
} SceCameraErrorCode;

typedef enum SceCameraDevice {
	SCE_CAMERA_DEVICE_FRONT = 0,
	SCE_CAMERA_DEVICE_BACK  = 1
} SceCameraDevice;

typedef enum SceCameraResolution {
	SCE_CAMERA_RESOLUTION_0_0        = 0,
	SCE_CAMERA_RESOLUTION_640_480    = 1,
	SCE_CAMERA_RESOLUTION_320_240    = 2,
	SCE_CAMERA_RESOLUTION_160_120    = 3,
	SCE_CAMERA_RESOLUTION_352_288    = 4,
	SCE_CAMERA_RESOLUTION_176_144    = 5,
	SCE_CAMERA_RESOLUTION_480_272    = 6,
	SCE_CAMERA_RESOLUTION_640_360    = 7,
	SCE_CAMERA_RESOLUTION_640_360_1  = 8
} SceCameraResolution;

typedef enum SceCameraFrameRate {
	SCE_CAMERA_FRAMERATE_3_FPS  = 3,
	SCE_CAMERA_FRAMERATE_5_FPS  = 5,
	SCE_CAMERA_FRAMERATE_7_FPS  = 7,
	SCE_CAMERA_FRAMERATE_10_FPS = 10,
	SCE_CAMERA_FRAMERATE_15_FPS = 15,
	SCE_CAMERA_FRAMERATE_20_FPS = 20,
	SCE_CAMERA_FRAMERATE_30_FPS = 30,
	SCE_CAMERA_FRAMERATE_60_FPS = 60
} SceCameraFrameRate;

typedef enum SceCameraFxMode {
	SCE_CAMERA_FXMODE_NORMAL     = 0,
	SCE_CAMERA_FXMODE_NEGATIVE   = 1,
	SCE_CAMERA_FXMODE_BLACKWHITE = 2,
	SCE_CAMERA_FXMODE_SEPIA      = 3,
	SCE_CAMERA_FXMODE_BLUE       = 4,
	SCE_CAMERA_FXMODE_RED        = 5,
	SCE_CAMERA_FXMODE_GREEN      = 6
} SceCameraFxMode;

typedef struct SceCameraInfo {
	SceSize size;
	uint16_t priority;
	uint16_t format;
	uint16_t resolution; //!< Resolution (one of ::SceCameraResolution)
	uint16_t framerate;  //!< Framerate (one of ::SceCameraFrameRate)
	uint16_t width;
	uint16_t height;
	uint16_t range;
	uint16_t pad;
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
	SceSize size;
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

int sceCameraOpen(int devnum, SceCameraInfo *pInfo);
int sceCameraClose(int devnum);
int sceCameraStart(int devnum);
int sceCameraStop(int devnum);
int sceCameraRead(int devnum, SceCameraRead *pRead);
int sceCameraIsActive(int devnum);
int sceCameraGetSaturation(int devnum, int *pLevel);
int sceCameraSetSaturation(int devnum, int level);
int sceCameraGetBrightness(int devnum, int *pLevel);
int sceCameraSetBrightness(int devnum, int level);
int sceCameraGetContrast(int devnum, int *pLevel);
int sceCameraSetContrast(int devnum, int level);
int sceCameraGetSharpness(int devnum, int *pLevel);
int sceCameraSetSharpness(int devnum, int level);
int sceCameraGetReverse(int devnum, int *pMode);
int sceCameraSetReverse(int devnum, int mode);
int sceCameraGetEffect(int devnum, int *pMode);
int sceCameraSetEffect(int devnum, int mode);
int sceCameraGetEV(int devnum, int *pLevel);
int sceCameraSetEV(int devnum, int level);
int sceCameraGetZoom(int devnum, int *pLevel);
int sceCameraSetZoom(int devnum, int level);
int sceCameraGetAntiFlicker(int devnum, int *pMode);
int sceCameraSetAntiFlicker(int devnum, int mode);
int sceCameraGetISO(int devnum, int *pMode);
int sceCameraSetISO(int devnum, int mode);
int sceCameraGetGain(int devnum, int *pMode);
int sceCameraSetGain(int devnum, int mode);
int sceCameraGetWhiteBalance(int devnum, int *pMode);
int sceCameraSetWhiteBalance(int devnum, int mode);
int sceCameraGetBacklight(int devnum, int *pMode);
int sceCameraSetBacklight(int devnum, int mode);
int sceCameraGetNightmode(int devnum, int *pMode);
int sceCameraSetNightmode(int devnum, int mode);
int sceCameraGetExposureCeiling(int devnum, int *pMode);
int sceCameraSetExposureCeiling(int devnum, int mode);
int sceCameraGetAutoControlHold(int devnum, int *pMode);
int sceCameraSetAutoControlHold(int devnum, int mode);
int sceCameraGetEV(int devnum, int *pMode);
int sceCameraSetEV(int devnum, int mode);
int sceCameraGetDeviceLocation(int devnum, SceFVector3 *pLocation);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_CAMERA_H_ */

