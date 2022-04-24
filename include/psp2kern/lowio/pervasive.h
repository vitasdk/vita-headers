/**
 * \kernelgroup{ScePervasive}
 * \usage{psp2kern/lowio/pervasive.h,ScePervasiveForDriver_stub}
 */

#ifndef _PSP2KERN_LOWIO_PERVASIVE_H_
#define _PSP2KERN_LOWIO_PERVASIVE_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int kscePervasiveUartClockDisable(int port);
int kscePervasiveUartResetEnable(int port);
int kscePervasiveUartResetDisable(int port);
int kscePervasiveUartClockEnable(int port);
int kscePervasiveUartSetBaudrate(int port, unsigned int baudrate);

int kscePervasiveGpioResetEnable(void);
int kscePervasiveGpioResetDisable(void);
int kscePervasiveGpioClockEnable(void);
int kscePervasiveGpioClockDisable(void);

int kscePervasiveSpiResetEnable(int port);
int kscePervasiveSpiResetDisable(int port);
int kscePervasiveSpiClockDisable(int port);
int kscePervasiveSpiClockEnable(int port);

int kscePervasiveDsiResetEnable(int port, unsigned int mask);
int kscePervasiveDsiResetDisable(int port, unsigned int mask);
int kscePervasiveDsiClockEnable(int port, unsigned int mask);
int kscePervasiveDsiClockDisable(int port, unsigned int mask);
int kscePervasiveDsiSetPixelClock(int port, int pixelclock);

int kscePervasiveMsifResetEnable(void);
int kscePervasiveMsifResetDisable(void);
int kscePervasiveMsifClockEnable(void);
int kscePervasiveMsifClockDisable(void);
int kscePervasiveMsifSetClock(unsigned int clock);

int kscePervasiveRemovableMemoryGetCardInsertState(void);

SceUInt32 kscePervasiveGetSoCRevision(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_PERVASIVE_H_ */

