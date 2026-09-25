/**
 * \kernelgroup{SceClockgen}
 * \usage{psp2kern/clockgen.h,SceClockgenForDriver_stub}
 */

#ifndef _PSP2KERN_CLOCKGEN_H_
#define _PSP2KERN_CLOCKGEN_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Disable the WLAN/Bluetooth clock-generator output.
 *
 * On FW 3.60 this operation is implemented only when clock-generator register
 * 0x80 contains 0x2F. If bit 7 of cached register 0x81 is set, the function
 * clears it and writes the updated register to I2C device 0xD2 on bus 0.
 *
 * @return 1 if the clock-enable bit was cleared, 0 if no change was required,
 *         or a negative mutex error. An I2C write failure is not reported.
 */
int ksceClockgenWlanBtClkDisable(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_CLOCKGEN_H_ */
