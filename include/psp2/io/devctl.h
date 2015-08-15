/**
 * \file
 * \brief Header file which defines device control options
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
  * @par Example: Sending a simple command to a device (not a real devctl)
  * @code
  * sceIoDevctl("ms0:", 0x200000, indata, 4, NULL, NULL);
  * @endcode
  *
  * @param dev - String for the device to send the devctl to (e.g. "ms0:")
  * @param cmd - The command to send to the device
  * @param indata - A data block to send to the device, if NULL sends no data
  * @param inlen - Length of indata, if 0 sends no data
  * @param outdata - A data block to receive the result of a command, if NULL receives no data
  * @param outlen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int sceIoDevctl(const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

/**
  * Assigns one IO device to another (I guess)
  * @param dev1 - The device name to assign.
  * @param dev2 - The block device to assign from.
  * @param dev3 - The filesystem device to mape the block device to dev1
  * @param mode - Read/Write mode. One of IoAssignPerms.
  * @param unk1 - Unknown, set to NULL.
  * @param unk2 - Unknown, set to 0.
  * @return < 0 on error.
  *
  * @par Example: Reassign flash0 in read/write mode.
  * @code
  *	sceIoUnassign("flash0");
  * sceIoAssign("flash0", "lflash0:0,0", "flashfat0:", IOASSIGN_RDWR, NULL, 0);
  * @endcode
  *
  */
int sceIoAssign(const char *dev1, const char *dev2, const char *dev3, int mode, void* unk1, long unk2);

/**
  * Unassign an IO device.
  * @param dev - The device to unassign.
  * @return < 0 on error
  *
  * @par Example: See ::sceIoAssign
  */
int sceIoUnassign(const char *dev);

/**
  * Perform an ioctl on a device.
  *
  * @param fd - Opened file descriptor to ioctl to
  * @param cmd - The command to send to the device
  * @param indata - A data block to send to the device, if NULL sends no data
  * @param inlen - Length of indata, if 0 sends no data
  * @param outdata - A data block to receive the result of a command, if NULL receives no data
  * @param outlen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int sceIoIoctl(SceUID fd, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

/**
  * Perform an ioctl on a device. (asynchronous)
  *
  * @param fd - Opened file descriptor to ioctl to
  * @param cmd - The command to send to the device
  * @param indata - A data block to send to the device, if NULL sends no data
  * @param inlen - Length of indata, if 0 sends no data
  * @param outdata - A data block to receive the result of a command, if NULL receives no data
  * @param outlen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int sceIoIoctlAsync(SceUID fd, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_DEVCTRL_H_ */
