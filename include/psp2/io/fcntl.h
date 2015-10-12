/**
 * \file
 * \brief Header file which defines file control options
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_IO_FCNTL_H_
#define _PSP2_IO_FCNTL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Note: Not all of these sceIoOpen() flags are not compatible with the
   open() flags found in sys/unistd.h. */
enum {
	SCE_O_RDONLY   = 0x0001,
	SCE_O_WRONLY   = 0x0002,
	SCE_O_RDWR     = (SCE_O_RDONLY | SCE_O_WRONLY),
	SCE_O_NBLOCK   = 0x0004,
	SCE_O_DIROPEN  = 0x0008,  // Internal use for dopen
	SCE_O_APPEND   = 0x0100,
	SCE_O_CREAT    = 0x0200,
	SCE_O_TRUNC    = 0x0400,
	SCE_O_EXCL     = 0x0800,
	SCE_O_NOWAIT   = 0x8000
};

enum {
	SCE_SEEK_SET,
	SCE_SEEK_CUR,
	SCE_SEEK_END
};

/**
 * Open or create a file for reading or writing
 *
 * @par Example1: Open a file for reading
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", SCE_O_RDONLY, 0777)) {
 *	// error
 * }
 * @endcode
 * @par Example2: Open a file for writing, creating it if it doesnt exist
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", SCE_O_WRONLY|SCE_O_CREAT, 0777)) {
 *	// error
 * }
 * @endcode
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode.
 * @return A non-negative integer is a valid fd, anything else an error
 */
SceUID sceIoOpen(const char *file, int flags, SceMode mode);

/**
 * Open or create a file for reading or writing (asynchronous)
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode.
 * @return A non-negative integer is a valid fd, anything else an error
 */
SceUID sceIoOpenAsync(const char *file, int flags, SceMode mode);

/**
 * Delete a descriptor
 *
 * @code
 * sceIoClose(fd);
 * @endcode
 *
 * @param fd - File descriptor to close
 * @return < 0 on error
 */
int sceIoClose(SceUID fd);

/**
 * Delete a descriptor (asynchronous)
 *
 * @param fd - File descriptor to close
 * @return < 0 on error
 */
int sceIoCloseAsync(SceUID fd);

/**
 * Read input
 *
 * @par Example:
 * @code
 * bytes_read = sceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 *
 * @return The number of bytes read
 */
int sceIoRead(SceUID fd, void *data, SceSize size);

/**
 * Read input (asynchronous)
 *
 * @par Example:
 * @code
 * bytes_read = sceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 *
 * @return < 0 on error.
 */
int sceIoReadAsync(SceUID fd, void *data, SceSize size);

/**
 * Write output
 *
 * @par Example:
 * @code
 * bytes_written = sceIoWrite(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 *
 * @return The number of bytes written
 */
int sceIoWrite(SceUID fd, const void *data, SceSize size);

/**
 * Write output (asynchronous)
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 *
 * @return < 0 on error.
 */
int sceIoWriteAsync(SceUID fd, const void *data, SceSize size);

/**
 * Reposition read/write file descriptor offset
 *
 * @par Example:
 * @code
 * pos = sceIoLseek(fd, -10, SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - Set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return The position in the file after the seek.
 */
SceOff sceIoLseek(SceUID fd, SceOff offset, int whence);

/**
 * Reposition read/write file descriptor offset (asynchronous)
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - Set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return < 0 on error. Actual value should be passed returned by the ::sceIoWaitAsync call.
 */
int sceIoLseekAsync(SceUID fd, SceOff offset, int whence);

/**
 * Reposition read/write file descriptor offset (32bit mode)
 *
 * @par Example:
 * @code
 * pos = sceIoLseek32(fd, -10, SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - Set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return The position in the file after the seek.
 */
int sceIoLseek32(SceUID fd, int offset, int whence);

/**
 * Reposition read/write file descriptor offset (32bit mode, asynchronous)
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - Set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return < 0 on error.
 */
int sceIoLseek32Async(SceUID fd, int offset, int whence);

/**
 * Remove directory entry
 *
 * @param file - Path to the file to remove
 * @return < 0 on error
 */
int sceIoRemove(const char *file);

/**
 * Change the name of a file
 *
 * @param oldname - The old filename
 * @param newname - The new filename
 * @return < 0 on error.
 */
int sceIoRename(const char *oldname, const char *newname);

/**
  * Synchronise the file data on the device.
  *
  * @param device - The device to synchronise (e.g. msfat0:)
  * @param unk - Unknown
  */
int sceIoSync(const char *device, unsigned int unk);

/**
  * Wait for asyncronous completion.
  *
  * @param fd - The file descriptor which is current performing an asynchronous action.
  * @param res - The result of the async action.
  *
  * @return < 0 on error.
  */
int sceIoWaitAsync(SceUID fd, SceInt64 *res);

/**
  * Wait for asyncronous completion (with callbacks).
  *
  * @param fd - The file descriptor which is current performing an asynchronous action.
  * @param res - The result of the async action.
  *
  * @return < 0 on error.
  */
int sceIoWaitAsyncCB(SceUID fd, SceInt64 *res);

/**
  * Poll for asyncronous completion.
  *
  * @param fd - The file descriptor which is current performing an asynchronous action.
  * @param res - The result of the async action.
  *
  * @return < 0 on error.
  */
int sceIoPollAsync(SceUID fd, SceInt64 *res);

/**
  * Get the asyncronous completion status.
  *
  * @param fd - The file descriptor which is current performing an asynchronous action.
  * @param poll - If 0 then waits for the status, otherwise it polls the fd.
  * @param res - The result of the async action.
  *
  * @return < 0 on error.
  */
int sceIoGetAsyncStat(SceUID fd, int poll, SceInt64 *res);

/**
  * Cancel an asynchronous operation on a file descriptor.
  *
  * @param fd - The file descriptor to perform cancel on.
  *
  * @return < 0 on error.
  */
int sceIoCancel(SceUID fd);

/**
  * Get the device type of the currently opened file descriptor.
  *
  * @param fd - The opened file descriptor.
  *
  * @return < 0 on error. Otherwise the device type?
  */
int sceIoGetDevType(SceUID fd);

/**
  * Change the priority of the asynchronous thread.
  *
  * @param fd - The opened fd on which the priority should be changed.
  * @param pri - The priority of the thread.
  *
  * @return < 0 on error.
  */
int sceIoChangeAsyncPriority(SceUID fd, int pri);

/**
  * Sets a callback for the asynchronous action.
  *
  * @param fd - The filedescriptor currently performing an asynchronous action.
  * @param cb - The UID of the callback created with ::sceKernelCreateCallback
  * @param argp - Pointer to an argument to pass to the callback.
  *
  * @return < 0 on error.
  */
int sceIoSetAsyncCallback(SceUID fd, SceUID cb, void *argp);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_FCNTL_H_ */
