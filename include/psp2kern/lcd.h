/**
 * \kernelgroup{SceLcd}
 * \usage{psp2kern/lcd.h,SceLcdForDriver_stub}
 */

#ifndef _PSP2KERN_LCD_H_
#define _PSP2KERN_LCD_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceLcdDisplayOff(void);
int ksceLcdDisplayOn(void);
int ksceLcdGetBrightness(void);
int ksceLcdGetDDB(unsigned short *supplier_id, unsigned short *supplier_elective_data);
int ksceLcdGetDisplayColorSpaceMode(void);
int ksceLcdSetBrightness(unsigned int brightness);
int ksceLcdSetDisplayColorSpaceMode(int mode);
int ksceLcdWaitReady(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LCD_H_ */
