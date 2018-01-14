/**
 * \usergroup{SceFcntl}
 * \usage{psp2/io/fcntl.h,SceIofilemgr_stub}
 */


#ifndef _PSP2_IO_FCNTL_H_
#define _PSP2_IO_FCNTL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Note: Not all of these sceIoOpen() flags are not compatible with the
   open() flags found in sys/unistd.h. */
typedef enum SceIoMode {
	SCE_O_RDONLY    = 0x0001,                         //!< Read-only
	SCE_O_WRONLY    = 0x0002,                         //!< Write-only
	SCE_O_RDWR      = (SCE_O_RDONLY | SCE_O_WRONLY),  //!< Read/Write
	SCE_O_NBLOCK    = 0x0004,                         //!< Non blocking
	SCE_O_DIROPEN   = 0x0008,                         //!< Internal use for ::sceIoDopen
	SCE_O_RDLOCK    = 0x0010,                         //!< Read locked (non-shared)
	SCE_O_WRLOCK    = 0x0020,                         //!< Write locked (non-shared)
	SCE_O_APPEND    = 0x0100,                         //!< Append
	SCE_O_CREAT     = 0x0200,                         //!< Create
	SCE_O_TRUNC     = 0x0400,                         //!< Truncate
	SCE_O_EXCL      = 0x0800,                         //!< Exclusive create
	SCE_O_SCAN      = 0x1000,                         //!< Scan type
	SCE_O_RCOM      = 0x2000,                         //!< Remote command entry
	SCE_O_NOBUF     = 0x4000,                         //!< Number device buffer
	SCE_O_NOWAIT    = 0x8000,                         //!< Asynchronous I/O
	SCE_O_FDEXCL    = 0x01000000,                     //!< Exclusive access
	SCE_O_PWLOCK    = 0x02000000,                     //!< Power control lock
	SCE_O_FGAMEDATA = 0x40000000                      //!< Gamedata access
} SceIoMode;

typedef enum SceIoSeekMode {
	SCE_SEEK_SET,   //!< Starts from the begin of the file
	SCE_SEEK_CUR,   //!< Starts from current position
	SCE_SEEK_END    //!< Starts from the end of the file
} SceIoSeekMode;

typedef enum SceIoDevType {
	SCE_DEV_TYPE_NULL     = 0x00, //!< Dummy device
	SCE_DEV_TYPE_CHAR     = 0x01, //!< Character device
	SCE_DEV_TYPE_BLOCK    = 0x04, //!< Block device
	SCE_DEV_TYPE_FS       = 0x10, //!< File system device
	SCE_DEV_TYPE_ALIAS    = 0x20, //!< Alias name
	SCE_DEV_TYPE_MOUNTPT  = 0x40  //!< Mount point
} SceIoDevType;

/**
 * Open or create a file for reading or writing
 *
 * @par Example1: Open a file for reading
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", SCE_O_RDONLY, 0777)) {
 *	// error
 * }
 * @endcode
 * @par Example2: Open a file for writing, creating it if it doesn't exist
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", SCE_O_WRONLY|SCE_O_CREAT, 0777)) {
 *	// error
 * }
 * @endcode
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode (One or more ::SceIoMode).
 * @return A non-negative integer is a valid fd, anything else an error
 */
SceUID sceIoOpen(const char *file, int flags, SceMode mode);

/**
 * Open or create a file for reading or writing (asynchronous)
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode (One or more ::SceIoMode).
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
 * Reposition read/write file descriptor offset (asynchronous)
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 *
 * @return < 0 on error. Actual value should be passed returned by the ::sceIoWaitAsync call.
 */
int sceIoLseekAsync(SceUID fd, SceOff offset, int whence);

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
int sceIoLseek32(SceUID fd, int offset, int whence);

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
 * @param fd - Opened file descriptor to sync
 *
 * @return < 0 on error.
 */
int sceIoSyncByFd(SceUID fd);

/**
  * Cancel an asynchronous operation on a file descriptor.
  *
  * @param fd - The file descriptor to perform cancel on.
  *
  * @return < 0 on error.
  */
int sceIoCancel(SceUID fd);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_FCNTL_H_ */

