/**
 * \kernelgroup{SceDevCtl}
 * \usage{psp2kern/io/devctl.h,SceIofilemgrForDriver_stub}
 */


#ifndef _PSP2KERN_IO_DEVCTL_H_
#define _PSP2KERN_IO_DEVCTL_H_

#include <psp2kern/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
  * Send a devctl command to a device.
  *
  * @par Example: Sending a simple command to a device
  * @code
  * SceIoDevInfo info;
  * ksceIoDevctl("ux0:", 0x3001, NULL, 0, &info, sizeof(SceIoDevInfo));
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

#endif /* _PSP2KERN_IO_DEVCTL_H_ */

