/**
 * \kernelgroup{SceDirEnt}
 * \usage{psp2kern/io/dirent.h,SceIofilemgrForDriver_stub}
 */


#ifndef _PSP2_IO_DRENT_H_
#define _PSP2_IO_DRENT_H_

#include <psp2kern/types.h>
#include <psp2kern/io/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Describes a single directory entry */
typedef struct SceIoDirent {
	SceIoStat d_stat; //!< File status
	char d_name[256]; //!< File name
	void *d_private;  //!< Device-specific data
	int dummy;        //!< Dummy data
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
  * @param fd - Already opened file descriptor (using ::ksceIoDopen)
  * @param dir - Pointer to an ::SceIoDirent structure to hold the file information
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
  * @param fd - Already opened file descriptor (using ::ksceIoDopen)
  * @return < 0 on error
  */
int ksceIoDclose(SceUID fd);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_DRENT_H_ */

