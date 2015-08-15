/**
 * \file
 * \brief Header file which describes file structures
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_IO_STAT_H_
#define _PSP2_IO_STAT_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Access modes for st_mode in SceIoStat (confirm?). */
enum {
	/** Format bits mask */
	PSP2_S_IFMT		= 0xF000,
	/** Symbolic link */
	PSP2_S_IFLNK		= 0x4000,
	/** Directory */
	PSP2_S_IFDIR		= 0x1000,
	/** Regular file */
	PSP2_S_IFREG		= 0x2000,

	/** Set UID */
	PSP2_S_ISUID		= 0x0800,
	/** Set GID */
	PSP2_S_ISGID		= 0x0400,
	/** Sticky */
	PSP2_S_ISVTX		= 0x0200,

	/** User access rights mask */
	PSP2_S_IRWXU		= 0x01C0,
	/** Read user permission */
	PSP2_S_IRUSR		= 0x0100,
	/** Write user permission */
	PSP2_S_IWUSR		= 0x0080,
	/** Execute user permission */
	PSP2_S_IXUSR		= 0x0040,

	/** Group access rights mask */
	PSP2_S_IRWXG		= 0x0038,
	/** Group read permission */
	PSP2_S_IRGRP		= 0x0020,
	/** Group write permission */
	PSP2_S_IWGRP		= 0x0010,
	/** Group execute permission */
	PSP2_S_IXGRP		= 0x0008,

	/** Others access rights mask */
	PSP2_S_IRWXO		= 0x0007,
	/** Others read permission */
	PSP2_S_IROTH		= 0x0004,
	/** Others write permission */
	PSP2_S_IWOTH		= 0x0002,
	/** Others execute permission */
	PSP2_S_IXOTH		= 0x0001,
};

// File mode checking macros
#define PSP2_S_ISLNK(m)	(((m) & PSP2_S_IFMT) == PSP2_S_IFLNK)
#define PSP2_S_ISREG(m)	(((m) & PSP2_S_IFMT) == PSP2_S_IFREG)
#define PSP2_S_ISDIR(m)	(((m) & PSP2_S_IFMT) == PSP2_S_IFDIR)

/** File modes, used for the st_attr parameter in SceIoStat (confirm?). */
enum {
	/** Format mask */
	PSP2_SO_IFMT             = 0x0038,               // Format mask
	/** Symlink */
	PSP2_SO_IFLNK            = 0x0008,               // Symbolic link
	/** Directory */
	PSP2_SO_IFDIR            = 0x0010,               // Directory
	/** Regular file */
	PSP2_SO_IFREG            = 0x0020,               // Regular file

	/** Hidden read permission */
	PSP2_SO_IROTH            = 0x0004,               // read
	/** Hidden write permission */
	PSP2_SO_IWOTH            = 0x0002,               // write
	/** Hidden execute permission */
	PSP2_SO_IXOTH            = 0x0001,               // execute
};

// File mode checking macros
#define PSP2_SO_ISLNK(m)	(((m) & PSP2_SO_IFMT) == PSP2_SO_IFLNK)
#define PSP2_SO_ISREG(m)	(((m) & PSP2_SO_IFMT) == PSP2_SO_IFREG)
#define PSP2_SO_ISDIR(m)	(((m) & PSP2_SO_IFMT) == PSP2_SO_IFDIR)

/** Structure to hold the status information about a file */
typedef struct SceIoStat {
	SceMode	st_mode;
	unsigned int	st_attr;
	/** Size of the file in bytes. */
	SceOff	st_size;
	/** Creation time. */
	SceDateTime	st_ctime;
	/** Access time. */
	SceDateTime	st_atime;
	/** Modification time. */
	SceDateTime	st_mtime;
	/** Device-specific data. */
	unsigned int	st_private[6];
} SceIoStat;

/**
 * Make a directory file
 *
 * @param dir
 * @param mode - Access mode.
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoMkdir(const char *dir, SceMode mode);

/**
 * Remove a directory file
 *
 * @param path - Removes a directory file pointed by the string path
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoRmdir(const char *path);

/**
  * Change the current directory.
  *
  * @param path - The path to change to.
  * @return < 0 on error.
  */
int sceIoChdir(const char *path);

/**
  * Get the status of a file.
  *
  * @param file - The path to the file.
  * @param stat - A pointer to an io_stat_t structure.
  *
  * @return < 0 on error.
  */
int sceIoGetstat(const char *file, SceIoStat *stat);

/**
  * Change the status of a file.
  *
  * @param file - The path to the file.
  * @param stat - A pointer to an io_stat_t structure.
  * @param bits - Bitmask defining which bits to change.
  *
  * @return < 0 on error.
  */
int sceIoChstat(const char *file, SceIoStat *stat, int bits);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_STAT_H_ */
