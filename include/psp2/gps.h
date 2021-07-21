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
int _sceGpsGetData(SceGpsPositionData *pPos, SceGpsSatelliteData *pSat);
int _sceGpsGetDeviceInfo(SceGpsDeviceInfo *pDevInfo);
int _sceGpsGetState(SceGpsStatus *pState);
int _sceGpsIoctl(SceUInt32 ioctlCommand, SceVoid *pArg, SceSize argSize);
int _sceGpsIsDevice(void);
int _sceGpsOpen(SceUID cbid);
int _sceGpsResumeCallback(void);
int _sceGpsSelectDevice(SceUInt32 deviceType);
int _sceGpsStart(unsigned int mode);
int _sceGpsStop(void);

// Maybe not present in 3.60
//SceInt32 _sceGpsSetCurrentTick(const SceRtcTick *pTick);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_GPS_H_ */
