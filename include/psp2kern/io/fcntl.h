/**
 * \kernelgroup{SceFcntl}
 * \usage{psp2kern/io/fcntl.h,SceIofilemgrForDriver_stub}
 */


#ifndef _PSP2KERN_IO_FCNTL_H_
#define _PSP2KERN_IO_FCNTL_H_

#include <psp2kern/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Open or create a file for reading or writing
 *
 * @par Example1: Open a file for reading
 * @code
 * if(!(fd = ksceIoOpen("device:/path/to/file", SCE_O_RDONLY, 0777)) {
 *	// error
 * }
 * @endcode
 * @par Example2: Open a file for writing, creating it if it doesn't exist
 * @code
 * if(!(fd = ksceIoOpen("device:/path/to/file", SCE_O_WRONLY|SCE_O_CREAT, 0777)) {
 *	// error
 * }
 * @endcode
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode (One or more ::SceIoMode).
 * @return A non-negative integer is a valid fd, anything else an error
 */
SceUID ksceIoOpen(const char *file, int flags, SceMode mode);

/**
 * Delete a descriptor
 *
 * @code
 * ksceIoClose(fd);
 * @endcode
 *
 * @param fd - File descriptor to close
 * @return < 0 on error
 */
int ksceIoClose(SceUID fd);

/**
 * Read input
 *
 * @par Example:
 * @code
 * bytes_read = ksceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 *
 * @return The number of bytes read
 */
int ksceIoRead(SceUID fd, void *data, SceSize size);

/**
 * Read input at offset
 *
 * @par Example:
 * @code
 * bytes_read = ksceIoPread(fd, data, 100, 0x1000);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * @param offset - Offset to read
 *
 * @return < 0 on error.
 */
int ksceIoPread(SceUID fd, void *data, SceSize size, SceOff offset);

/**
 * Write output
 *
 * @par Example:
 * @code
 * bytes_written = ksceIoWrite(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 *
 * @return The number of bytes written
 */
int ksceIoWrite(SceUID fd, const void *data, SceSize size);

/**
 * Write output at offset
 *
 * @par Example:
 * @code
 * bytes_written = ksceIoPwrite(fd, data, 100, 0x1000);
 * @endcode
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 * @param offset - Offset to write
 *
 * @return The number of bytes written
 */
int ksceIoPwrite(SceUID fd, const void *data, SceSize size, SceOff offset);

/**
 * Reposition read/write file descriptor offset
 *
 * @par Example:
 * @code
 * pos = ksceIoLseek(fd, -10, SCE_SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 *
 * @return The position in the file after the seek.
 */
SceOff ksceIoLseek(SceUID fd, SceOff offset, int whence);

/**
 * Remove directory entry
 *
 * @param file - Path to the file to remove
 * @return < 0 on error
 */
int ksceIoRemove(const char *file);

/**
 * Change the name of a file
 *
 * @param oldname - The old filename
 * @param newname - The new filename
 * @return < 0 on error.
 */
int ksceIoRename(const char *oldname, const char *newname);

/**
  * Synchronize the file data on the device.
  *
  * @param device - The device to synchronize (e.g. msfat0:)
  * @param unk - Unknown
  */
int ksceIoSync(const char *device, unsigned int unk);

/**
 * Synchronize the file data for one file
 *
 * @param fd - Opened file descriptor to sync
 *
 * @return < 0 on error.
 */
int ksceIoSyncByFd(SceUID fd);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_IO_FCNTL_H_ */

