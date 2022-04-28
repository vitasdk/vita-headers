/**
 * \usergroup{SceStat}
 * \usage{psp2/io/stat.h}
 */


#ifndef _PSP2_IO_STAT_H_
#define _PSP2_IO_STAT_H_

#include <psp2/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Make a directory file
 *
 * @param dir - The path to the directory
 * @param mode - Access mode (One or more ::SceIoAccessMode).
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceIoMkdir(const char *dir, SceMode mode);

/**
 * Remove a directory file
 *
 * @param path - Removes a directory file pointed by the string path
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceIoRmdir(const char *path);

/**
  * Get the status of a file.
  *
  * @param file - The path to the file.
  * @param stat - A pointer to a ::SceIoStat structure.
  *
  * @return < 0 on error.
  */
int sceIoGetstat(const char *file, SceIoStat *stat);

/**
  * Get the status of a file descriptor.
  *
  * @param fd - The file descriptor.
  * @param stat - A pointer to a ::SceIoStat structure.
  *
  * @return < 0 on error.
  */
int sceIoGetstatByFd(SceUID fd, SceIoStat *stat);

/**
  * Change the status of a file.
  *
  * @param file - The path to the file.
  * @param stat - A pointer to a ::SceIoStat structure.
  * @param bits - Bitmask defining which bits to change.
  *
  * @return < 0 on error.
  */
int sceIoChstat(const char *file, SceIoStat *stat, int bits);

/**
  * Change the status of a file descriptor.
  *
  * @param fd - The file descriptor.
  * @param stat - A pointer to an io_stat_t structure.
  * @param bits - Bitmask defining which bits to change.
  *
  * @return < 0 on error.
  */
int sceIoChstatByFd(SceUID fd, const SceIoStat *buf, unsigned int cbit);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_STAT_H_ */

