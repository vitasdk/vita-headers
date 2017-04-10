/**
 * \kernelgroup{SceDirEnt}
 * \usage{psp2kern/io/dirent.h,-lSceIofilemgrForDriver_stub}
 */


#ifndef _PSP2_IO_DRENT_H_
#define _PSP2_IO_DRENT_H_

#include <psp2/types.h>
#include <psp2kern/io/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Describes a single directory entry */
typedef struct SceIoDirent {
	/** File status. */
	SceIoStat	d_stat;
	/** File name. */
	char	d_name[256];
	/** Device-specific data. */
	void	*d_private;
	int	dummy;
} SceIoDirent;

/**
  * Open a directory
  *
  * @par Example:
  * @code
  * int dfd;
  * dfd = ksceIoDopen("device:/");
  * if(dfd >= 0)
  * { Do something with the file descriptor }
  * @endcode
  * @param dirname - The directory to open for reading.
  * @return If >= 0 then a valid file descriptor, otherwise a Sony error code.
  */
SceUID ksceIoDopen(const char *dirname);

/**
  * Reads an entry from an opened file descriptor.
  *
  * @param fd - Already opened file descriptor (using ksceIoDopen)
  * @param dir - Pointer to an io_dirent_t structure to hold the file information
  *
  * @return Read status
  * -   0 - No more directory entries left
  * - > 0 - More directory entries to go
  * - < 0 - Error
  */
int ksceIoDread(SceUID fd, SceIoDirent *dir);

/**
  * Close an opened directory file descriptor
  *
  * @param fd - Already opened file descriptor (using ksceIoDopen)
  * @return < 0 on error
  */
int ksceIoDclose(SceUID fd);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_DRENT_H_ */

