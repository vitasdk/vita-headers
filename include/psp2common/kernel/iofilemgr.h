/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2common/kernel/iofilemgr.h}
 */

#ifndef _PSP2COMMON_KERNEL_IOFILEMGR_H_
#define _PSP2COMMON_KERNEL_IOFILEMGR_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceIoDevInfo {
	SceOff max_size;
	SceOff free_size;
	SceSize cluster_size;
	void *unk;
} SceIoDevInfo;


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
  * Access modes for st_mode in ::SceIoStat.
  *
  * @note
  * System always requires RW access.
  * For safe homebrew system software will force system permission field to RW.
  * For unsafe homebrew, you need to set it yourself `( mode | SCE_S_IWSYS | SCE_S_IRSYS)`
  *
  */
typedef enum SceIoAccessMode {
	SCE_S_IXUSR		= 000100, //!< User execute permission
	SCE_S_IWUSR		= 000200, //!< User write permission
	SCE_S_IRUSR		= 000400, //!< User read permission
	SCE_S_IRWXU		= 000700, //!< User access rights mask

	SCE_S_IXGRP		= 000000, //!< Group execute permission. Ignored and reset to 0 by system
	SCE_S_IWGRP		= 000000, //!< Group write permission. Ignored and reset to 0 by system
	SCE_S_IRGRP		= 000000, //!< Group read permission. Ignored and reset to 0 by system
	SCE_S_IRWXG		= 000000, //!< Group access rights mask. Ignored and reset to 0 by system

	SCE_S_IXSYS		= 000001, //!< System execute permission
	SCE_S_IWSYS		= 000002, //!< System write permission
	SCE_S_IRSYS		= 000004, //!< System read permission
	SCE_S_IRWXS		= 000007, //!< System access rights mask

	SCE_DEPRECATED(SCE_S_IXOTH)		= 000001, //!< Others execute permission. Deprecated, use ::SCE_S_IXSYS
	SCE_DEPRECATED(SCE_S_IWOTH)		= 000002, //!< Others write permission. Deprecated, use ::SCE_S_IXSYS
	SCE_DEPRECATED(SCE_S_IROTH)		= 000004, //!< Others read permission. Deprecated, use ::SCE_S_IXSYS
	SCE_DEPRECATED(SCE_S_IRWXO)		= 000007, //!< Others access rights mask. Deprecated, use ::SCE_S_IRWXS

	SCE_DEPRECATED(SCE_S_ISVTX)		= 000000, //!< Sticky. Deprecated
	SCE_DEPRECATED(SCE_S_ISGID)		= 000000, //!< Set GID. Deprecated
	SCE_DEPRECATED(SCE_S_ISUID)		= 000000, //!< Set UID. Deprecated

	SCE_S_IFDIR		= 0010000, //!< Directory
	SCE_S_IFREG		= 0020000, //!< Regular file
	SCE_S_IFLNK		= 0040000, //!< Symbolic link
	SCE_S_IFMT		= 0170000, //!< Format bits mask
} SceIoAccessMode;

// File mode checking macros
#define SCE_S_ISLNK(m)	(((m) & SCE_S_IFMT) == SCE_S_IFLNK)
#define SCE_S_ISREG(m)	(((m) & SCE_S_IFMT) == SCE_S_IFREG)
#define SCE_S_ISDIR(m)	(((m) & SCE_S_IFMT) == SCE_S_IFDIR)

/** File modes, used for the st_attr parameter in ::SceIoStat. */
typedef enum SceIoFileMode {
	SCE_SO_IXOTH            = 0x0001,               //!< Hidden execute permission
	SCE_SO_IWOTH            = 0x0002,               //!< Hidden write permission
	SCE_SO_IROTH            = 0x0004,               //!< Hidden read permission
	SCE_SO_IFLNK            = 0x0008,               //!< Symbolic link
	SCE_SO_IFDIR            = 0x0010,               //!< Directory
	SCE_SO_IFREG            = 0x0020,               //!< Regular file
	SCE_SO_IFMT             = 0x0038,               //!< Format mask
} SceIoFileMode;

// File mode checking macros
#define SCE_SO_ISLNK(m)	(((m) & SCE_SO_IFMT) == SCE_SO_IFLNK)
#define SCE_SO_ISREG(m)	(((m) & SCE_SO_IFMT) == SCE_SO_IFREG)
#define SCE_SO_ISDIR(m)	(((m) & SCE_SO_IFMT) == SCE_SO_IFDIR)

/** Structure to hold the status information about a file */
typedef struct SceIoStat {
	SceMode st_mode;             //!< One or more ::SceIoAccessMode
	unsigned int st_attr;        //!< One or more ::SceIoFileMode
	SceOff st_size;              //!< Size of the file in bytes
	SceDateTime st_ctime;        //!< Creation time
	SceDateTime st_atime;        //!< Last access time
	SceDateTime st_mtime;        //!< Last modification time
	unsigned int st_private[6];  //!< Device-specific data
} SceIoStat;

/** Defines for `sceIoChstat` and `sceIoChstatByFd` **/
#define SCE_CST_MODE        0x0001
#define SCE_CST_SIZE        0x0004
#define SCE_CST_CT          0x0008
#define SCE_CST_AT          0x0010
#define SCE_CST_MT          0x0020


/** Describes a single directory entry */
typedef struct SceIoDirent {
	SceIoStat d_stat; //!< File status
	char d_name[256]; //!< File name
	void *d_private;  //!< Device-specific data
	int dummy;        //!< Dummy data
} SceIoDirent;


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_IOFILEMGR_H_ */
