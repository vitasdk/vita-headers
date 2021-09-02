/**
 * \kernelgroup{SceGps}
 * \usage{psp2/gps.h,SceGps_stub}
 */


#ifndef _PSP2_GPS_H_
#define _PSP2_GPS_H_

#include <psp2/types.h>
#include <psp2/rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

// missing structs
typedef struct SceGpsDeviceInfo SceGpsDeviceInfo;
typedef struct SceGpsSatelliteData SceGpsSatelliteData;
typedef struct SceGpsPositionData SceGpsPositionData;
typedef struct SceGpsStatus SceGpsStatus;

int _sceGpsClose(void);
int _sceGpsGetData(SceGpsPositionData *pos, SceGpsSatelliteData *sat);
int _sceGpsGetDeviceInfo(SceGpsDeviceInfo *dev_info);
int _sceGpsGetState(SceGpsStatus *state);
int _sceGpsIoctl(SceUInt32 ioctl_command, SceVoid *arg, SceSize arg_size, SceSize *a4);
int _sceGpsIsDevice(void);
int _sceGpsOpen(SceUID cbid);
int _sceGpsResumeCallback(void);
int _sceGpsSelectDevice(SceUInt32 device_type);
int _sceGpsStart(unsigned int mode);
int _sceGpsStop(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_GPS_H_ */
