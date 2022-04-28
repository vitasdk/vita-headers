/**
 * \usergroup{SceFcntl}
 * \usage{psp2/io/fcntl.h,SceIofilemgr_stub}
 */


#ifndef _PSP2_IO_FCNTL_H_
#define _PSP2_IO_FCNTL_H_

#include <psp2/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Open or create a file for reading or writing
 *
 * @par Example1: Open a file for reading
 * @code
 * if((fd = sceIoOpen("device:/path/to/file", SCE_O_RDONLY, 0777) < 0) {
 * // error code in fd, for example no open filehandle left (0x80010018)
 * }
 * @endcode
 * @par Example2: Open a file for writing, creating it if it doesn't exist
 * @code
 * if((fd = sceIoOpen("device:/path/to/file", SCE_O_WRONLY|SCE_O_CREAT, 0777) < 0) {
 * // error code in fd, for example no open filehandle left (0x80010018)
 * }
 * @endcode
 *
 * @param file - Pointer to a string holding the name of the file to open.
 * @param flags - Libc styled flags that are or'ed together (One or more ::SceIoMode).
 * @param mode - One or more ::SceIoAccessMode flags or'ed together. Can also use Unix absolute permissions.
 * @return > 0 is a valid file handle, < 0 on error.
 */
SceUID sceIoOpen(const char *file, int flags, SceMode mode);

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
 * Read input
 *
 * @par Example:
 * @code
 * bytes_read = sceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd    - Opened file descriptor to read from
 * @param buf   - Pointer to the buffer where the read data will be placed
 * @param nbyte - Size of the read in bytes
 *
 * @return The number of bytes read
 */
SceSSize sceIoRead(SceUID fd, void *buf, SceSize nbyte);

/**
 * Read input at offset
 *
 * @par Example:
 * @code
 * bytes_read = sceIoPread(fd, data, 100, 0x1000);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * @param offset - Offset to read
 *
 * @return < 0 on error.
 */
int sceIoPread(SceUID fd, void *data, SceSize size, SceOff offset);

/**
 * Write output
 *
 * @par Example:
 * @code
 * bytes_written = sceIoWrite(fd, data, 100);
 * @endcode
 *
 * @param fd    - Opened file descriptor to write to
 * @param buf   - Pointer to the data to write
 * @param nbyte - Size of data to write
 *
 * @return The number of bytes written
 */
SceSSize sceIoWrite(SceUID fd, const void *buf, SceSize nbyte);

/**
 * Write output at offset
 *
 * @par Example:
 * @code
 * bytes_written = sceIoPwrite(fd, data, 100, 0x1000);
 * @endcode
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 * @param offset - Offset to write
 *
 * @return The number of bytes written
 */
int sceIoPwrite(SceUID fd, const void *data, SceSize size, SceOff offset);

/**
 * Reposition read/write file descriptor offset
 *
 * @par Example:
 * @code
 * pos = sceIoLseek(fd, -10, SCE_SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 *
 * @return The position in the file after the seek.
 */
SceOff sceIoLseek(SceUID fd, SceOff offset, int whence);

/**
 * Reposition read/write file descriptor offset (32bit mode)
 *
 * @par Example:
 * @code
 * pos = sceIoLseek32(fd, -10, SCE_SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 *
 * @return The position in the file after the seek.
 */
long sceIoLseek32(SceUID fd, long offset, int whence);

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
  * Synchronize the file data on the device.
  *
  * @param device - The device to synchronize (e.g. msfat0:)
  * @param unk - Unknown
  */
int sceIoSync(const char *device, unsigned int unk);

/**
 * Synchronize the file data for one file
 *
 * @param fd   - Opened file descriptor to sync
 * @param flag - unknown
 *
 * @return < 0 on error.
 */
int sceIoSyncByFd(SceUID fd, int flag);

/**
  * Cancel an asynchronous operation on a file descriptor.
  *
  * @param fd - The file descriptor to perform cancel on.
  *
  * @return < 0 on error.
  */
int sceIoCancel(SceUID fd);

int sceIoGetPriority(SceUID fd);
int sceIoGetProcessDefaultPriority(void);
int sceIoGetThreadDefaultPriority(void);
int sceIoSetPriority(SceUID fd, int priority);
int sceIoSetProcessDefaultPriority(int priority);
int sceIoSetThreadDefaultPriority(int priority);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_FCNTL_H_ */

