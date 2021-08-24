/**
 * \usergroup{SceMotionDev}
 * \usage{psp2/motion_dev.h,SceMotionDev_stub}
 */


#ifndef _PSP2_MOTION_DEV_H_
#define _PSP2_MOTION_DEV_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// missing structs
typedef struct SceMotionDevAccCalibData SceMotionDevAccCalibData;
typedef struct SceMotionDevCalibrationData SceMotionDevCalibrationData;
typedef struct SceMotionDevCalibrationHeader SceMotionDevCalibrationHeader;
typedef struct SceMotionDevMagnCalibData SceMotionDevMagnCalibData;
typedef struct SceMotionDevDeviceInfo SceMotionDevDeviceInfo;
typedef struct SceMotionDevDeviceLocation SceMotionDevDeviceLocation;
typedef struct SceMotionDevGyroBiasData SceMotionDevGyroBiasData;
typedef struct SceMotionDevGyroCalibData SceMotionDevGyroCalibData;
typedef struct SceMotionDevModeInfo SceMotionDevModeInfo;
typedef struct SceMotionDevData SceMotionDevData;

int sceMotionDevGetAccCalibData(SceMotionDevAccCalibData *data);
int sceMotionDevGetAccCalibData2(int port, SceMotionDevAccCalibData *data);
int sceMotionDevGetCalibrationData(SceUInt32 block_id, SceMotionDevCalibrationData* data, SceUInt32 data_num);
int sceMotionDevGetCalibrationHeader(SceUInt32 block_id, SceMotionDevCalibrationHeader* calib_header);
int sceMotionDevGetCurrentMagnCalibData(SceMotionDevMagnCalibData *data);
int sceMotionDevGetCurrentMagnStabilityLevel(SceUInt32* level);
int sceMotionDevGetDeviceInfo(SceMotionDevDeviceInfo *device_info);
int sceMotionDevGetDeviceLocation(SceMotionDevDeviceLocation *location);
int sceMotionDevGetFactoryMagnCalibData(SceMotionDevMagnCalibData *data);
int sceMotionDevGetGyroBias(SceMotionDevGyroBiasData *bias);
int sceMotionDevGetGyroBias2(int port, SceMotionDevGyroBiasData *bias);
int sceMotionDevGetGyroCalibData(SceMotionDevGyroCalibData *data);
int sceMotionDevGetGyroCalibData2(int port, SceMotionDevGyroCalibData *data);
int sceMotionDevGetMeasMode(SceMotionDevModeInfo *mode_info);
int sceMotionDevIsReady(void);
int sceMotionDevMagnSamplingStart(void);
int sceMotionDevMagnSamplingStop(void);
int sceMotionDevRead(SceMotionDevData* data, int data_num, SceUInt32 *info);
int sceMotionDevRead2(int port, SceMotionDevData *data, int data_num, SceUInt32 *info);
int sceMotionDevReadForMagnCalib(SceMotionDevData* data, int data_num);
int sceMotionDevSamplingStart(void);
int sceMotionDevSamplingStart2(int port);
int sceMotionDevSamplingStop(void);
int sceMotionDevSamplingStop2(int port);
int sceMotionDevSetSamplingMode(SceUInt32 mode);
int sceMotionDevUpdateMagnCalibData(const SceMotionDevMagnCalibData *data, SceUInt32* tag);
int sceMotionDevUpdateMagnStabilityLevel(SceUInt32 level);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MOTION_DEV_H_ */
