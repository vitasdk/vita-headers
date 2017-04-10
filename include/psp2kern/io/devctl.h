/**
 * \kernelgroup{SceDevCtl}
 * \usage{psp2kern/io/devctl.h,-lSceIofilemgrForDriver_stub}
 */


#ifndef _PSP2_IO_DEVCTRL_H_
#define _PSP2_IO_DEVCTRL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * Send a devctl command to a device.
  *
  * @par Example: Sending a simple command to a device
  * @code
  * ksceIoDevctl("ux0:", 0x3001, NULL, 0, outdata, 0x18);
  * @endcode
  *
  * @param dev - String for the device to send the devctl to (e.g. "ux0:")
  * @param cmd - The command to send to the device
  * @param indata - A data block to send to the device, if NULL sends no data
  * @param inlen - Length of indata, if 0 sends no data
  * @param outdata - A data block to receive the result of a command, if NULL receives no data
  * @param outlen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int ksceIoDevctl(const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_DEVCTRL_H_ */

