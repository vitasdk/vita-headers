/**
 * \kernelgroup{SceOled}
 * \usage{psp2kern/oled.h,SceOledForDriver_stub}
 */

#ifndef _PSP2KERN_OLED_H_
#define _PSP2KERN_OLED_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceOledDisplayOff(void);
int ksceOledDisplayOn(void);
int ksceOledGetBrightness(void);
int ksceOledGetDDB(unsigned short *supplier_id, unsigned short *supplier_elective_data);
int ksceOledGetDisplayColorSpaceMode(void);
int ksceOledSetBrightness(SceUInt32 brightness);
int ksceOledSetDisplayColorSpaceMode(int mode);
int ksceOledWaitReady(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_OLED_H_ */
