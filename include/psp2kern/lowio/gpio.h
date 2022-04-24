/**
 * \kernelgroup{SceGpio}
 * \usage{psp2kern/lowio/gpio.h,SceGpioForDriver_stub}
 */

#ifndef _PSP2KERN_LOWIO_GPIO_H_
#define _PSP2KERN_LOWIO_GPIO_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceGpioErrorCode {
	SCE_GPIO_ERROR_INVALID_BUS	= 0x803F0100,
	SCE_GPIO_ERROR_INVALID_PORT	= 0x803F0101,
	SCE_GPIO_ERROR_INVALID_MODE	= 0x803F0102
} SceGpioErrorCode;

typedef enum SceGpioPortMasks {
	SCE_GPIO_PORT_MASK_LED_GAMECARD		= 1 << 6,
	SCE_GPIO_PORT_MASK_LED_PS_BUTTON	= 1 << 7
} SceGpioPortMasks;

typedef enum SceGpioPortMode {
	SCE_GPIO_PORT_MODE_OUTPUT	= 0,
	SCE_GPIO_PORT_MODE_INPUT	= 1
} SceGpioPortMode;

int ksceGpioPortRead(int bus, int port);
int ksceGpioPortSet(int bus, int port);
int ksceGpioPortClear(int bus, int port);
int ksceGpioPortReset(int bus, int port);
int ksceGpioSetPortMode(int bus, int port, int mode);
int ksceGpioGetPortMode(int bus, int port);
int ksceGpioSetIntrMode(int bus, int port, int intr_mode);
int ksceGpioGetIntrMode(int bus, int port);
int ksceGpioAcquireIntr(int bus, int port);
int ksceGpioQueryIntr(int bus, int port);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_GPIO_H_ */

