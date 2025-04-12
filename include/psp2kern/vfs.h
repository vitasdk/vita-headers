/**
 * \kernelgroup{SceVfs}
 * \usage{psp2kern/vfs.h,SceIofilemgrForDriver_stub}
 */

#ifndef _PSP2KERN_VFS_H_
#define _PSP2KERN_VFS_H_

#include <vitasdk/build_utils.h>
#include <psp2common/kernel/iofilemgr.h>
#include <psp2kern/kernel/threadmgr/fast_mutex.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct SceVfsMount SceVfsMount;
typedef struct SceVfsVnode SceVfsVnode;
typedef struct SceVfsFile SceVfsFile;
typedef struct SceVfsOpTable SceVfsOpTable;
typedef struct SceVopTable SceVopTable;

/**
 * @name VFS Data Types
 */
/** @{ */
#define SCE_VFS_TYPE_FS    (0x00000000)
#define SCE_VFS_TYPE_DEVFS (0x00000010)

/**
 * VFS Info defining a VFS Implementation
 */
typedef struct SceVfsInfo {
	const SceVfsOpTable *vfs_ops;    //!< VFS Implementation operations for mountpoint actions.
	const char *vfs_name;            //!< Name of the VFS implementation (Must be unique, used to identify the VFS)
	SceSize vfs_name_len;            //!< Length of vfs_name plus null-terminator

	SceUInt32 ref_count;             //!< Internal use only
	SceUInt32 type;                  //!< One of SCE_VFS_TYPE_*

	const SceVopTable *default_vops; //!< Default vop table for the vnodes
	void *vfs_data;                  //!< Optional data that can be passed to the vfs_init callback

	struct SceVfsInfo *next;         //!< Internal use only
} SceVfsInfo;
VITASDK_BUILD_ASSERT_EQ(0x20, SceVfsInfo);

/**
 * VFS Path for vnode
 * 
 * @note These paths used internally are root based paths, not mountpoint based.
 */
typedef struct SceVfsPath {
	const char *name;    //!< Name of vnode
	SceSize name_length; //!< Length of name
	const char *path;    //!< Full path name is from
} SceVfsPath;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVfsPath);

/**
 * Mountpoint Data
 */
typedef struct SceVfsMountData {
	const char *assign_name;           //!< Assigned name for the mount point. Must end with ':', typically in format `<mnt>0:`
	const char *fs_name;               //!< Name of the FS being mounted.
	const char *blockdev_name;         //!< Path to the block device
	const char *blockdev_name_no_part; //!< Path to the block device without a partition specified (used as a fallback if blockdev_name isn't found)
	SceUInt32 mnt_id;                  //!< Mountpoint ID (example: 0xF00 for uma0:)
} SceVfsMountData;
VITASDK_BUILD_ASSERT_EQ(0x14, SceVfsMountData);

#define SCE_VFS_FS_TYPE_FS      (0x01) //!< All exfat mounts
#define SCE_VFS_FS_TYPE_PFS     (0x03) //!< PFS mounts
#define SCE_VFS_FS_TYPE_HOSTFS  (0x04) //!< host0:
#define SCE_VFS_FS_TYPE_BLKDEV  (0x10) //!< sdstor0:, md0:
#define SCE_VFS_FS_TYPE_CHRDEV  (0x20) //!< tty0:

#define SCE_VFS_MOUNT_TYPE_PFS          (0x00000001) //!< PFS mounts
#define SCE_VFS_MOUNT_TYPE_FSROOT       (0x00000002) //!< Standard Root File System
#define SCE_VFS_MOUNT_TYPE_DEVFS        (0x00000003) //!< Device File System
#define SCE_VFS_MOUNT_TYPE_STACKFS      (0x00000005) //!< Loop File System (File system mounted from a file)
#define SCE_VFS_MOUNT_TYPE_HOSTFS       (0x00000006) //!< Hostfs
#define SCE_VFS_MOUNT_FLAG_TYPE_MASK    (0x000000FF)
#define SCE_VFS_MOUNT_FLAG_RDONLY       (0x00001000) //!< Read-only mount
#define SCE_VFS_MOUNT_FLAG_NOBUF        (0x00002000) //!< Disables VFS Buffer Cache
/**
 * Files for this mountpoint are treated as numbered extensions of the assignName.
 *
 * Example: tty mountpoint devices (tty0:, tty1:) internally are handled /tty/tty0:
 */
#define SCE_VFS_MOUNT_FLAG_NUMBERED     (0x00004000)
#define SCE_VFS_MOUNT_FLAG_REMOTE       (0x00008000) //!< Prevents ncache entry of failed lookups. Used on host0:
#define SCE_VFS_MOUNT_FLAG_INTERNAL     (0x00010000)
#define SCE_VFS_MOUNT_FLAG_EXTERNAL     (0x00020000)
#define SCE_VFS_MOUNT_FLAG_WRITE_CACHE  (0x00040000) //!< Allow write-caching. Default behavior is to flush buffer cache after write.
#define SCE_VFS_MOUNT_FLAG_NO_RECLAIM   (0x00100000) //!< Prevents Vnodes from being reclaimed. Only set internally for devfs 

typedef struct SceVfsMount {
	SceKernelFastMutex fast_mutex;

	SceVfsVnode *mnt_vnode;

	SceUID allocator;

	SceUInt32 state;
	SceUInt8 fs_type;    //!< One of SCE_VFS_FS_TYPE_*
	SceUInt16 opt;
	SceUInt32 mnt_flags; //!< ORed together SCE_VFS_MOUNT_FLAG_* flags

	SceVfsVnode *vnode_list;
	SceUInt32 vnode_num;

	SceVfsInfo *mnt_vfs_inf;
	SceUInt32 mnt_ref_count;

	SceUInt32 opened_entry_num;
	SceUInt32 available_entry_num;

	SceUID pid;

	SceVfsMount *mnted_on_list;
	SceVfsMount *mnted_on_list_prev;
	SceVfsMount *mnt_list_next;

	SceVfsMountData *mnt_data;
	char path[64];

	SceUInt32 default_io_cache_size;

	void *data;  //!< VFS Implementation defined mount point data.

	struct FdLock *fd_lock;
	struct Fumount *fumount;

	SceUInt32 opaque[4];  // Backing storage for pFdLock
	SceUInt32 opaque2[4]; // Backing storage for pFumount

	SceUInt8 padding[16];
} SceVfsMount;
VITASDK_BUILD_ASSERT_EQ(0x100, SceVfsMount);

#define SCE_VNODE_TYPE_REG     (0x00000001) //!< Regular file
#define SCE_VNODE_TYPE_DIR     (0x00000002) //!< Regular directory
#define SCE_VNODE_TYPE_CHR     (0x00000010) //!< Character file
#define SCE_VNODE_TYPE_ROOT    (0x00001000) //!< Root vnode
#define SCE_VNODE_TYPE_DEV     (0x00002000) //!< Device vnode
#define SCE_VNODE_TYPE_MOUNTED (0x00004000) //!< Vnode used as a backing for a mountpoint

#define SCE_VNODE_TYPE_CHRDEV        (SCE_VNODE_TYPE_DEV | SCE_VNODE_TYPE_CHR)
#define SCE_VNODE_TYPE_ROOTDIR       (SCE_VNODE_TYPE_ROOT | SCE_VNODE_TYPE_DIR) //!< Root directory
#define SCE_VNODE_TYPE_ROOTDIR_DEVFS (0x10000 | 0x20) //!< Root directory on devfs mountpoints

#define SCE_VNODE_STATE_ACTIVE    (0x00000001) //!< Vnode is active and valid for all operations
#define SCE_VNODE_STATE_INACTIVE  (0x00000100) //!< Vnode is inactive and may be pending deletion or otherwise.
#define SCE_VNODE_STATE_UNMOUNTED (0x00000200)
#define SCE_VNODE_STATE_DELETED   (0x00000400)
#define SCE_VNODE_STATE_RECLAIMED (0x00002000)
#define SCE_VNODE_STATE_NEW       (0x00008000)

/**
 * VFS Vnode 
 * 
 * The most fundamental aspect of the VFS. Vnodes represent every individual file or
 * directory which has been looked-up or accessed.
 */
typedef struct SceVfsVnode {
	struct {
		SceUInt32 waiter;
		SceUID owner_id;
		SceUInt32 recursive_count;
		SceUID wait_id;
		SceUInt32 wait_pattern;
	} vdlock;

	SceUInt8 padding[44];

	struct {  
		SceVopTable *ops;

		SceUInt32 node_inf; //!< Field for private VFS vnode info
		void *node_data;    //!< Pointer for private VFS data

		SceVfsMount *mnt;

		SceVfsVnode *dd;   //!<  Parent vnode
		SceVfsVnode *next;

		SceUInt32 ref_count;

		struct BuffCache *bc;

		SceUInt32 fid[2];
		struct Flock *flock;

		SceUID allocator;

		struct Ncache *ncache;

		SceUInt32 state; //!< One of SCE_VNODE_STATE_*
		SceUInt32 type;  //!< ORed together SCE_VNODE_TYPE_* flags

		SceVopTable *vop_tbl; //!< Internal use only

		SceUInt64 size;
		SceUInt32 acl_data[2]; //!< Typically holds st_attr in acl_data[0]

		SceVfsFile *fd_list;
		SceUInt32 fd_num;

		SceVfsVnode *link_to;
		SceUInt32 linked_num;

		SceUInt8 unused[48];

		SceUInt32 mnt_opt;
		SceUInt32 unk_0xd4;
	} core;

	SceUInt8 padding2[40];
} SceVfsVnode;
VITASDK_BUILD_ASSERT_EQ(0x100, SceVfsVnode);

#define SCE_VFS_FILE_STATE_OPEN   (0x00000001) //!< File is open
#define SCE_VFS_FILE_STATE_CLOSED (0x00000200) //!< File is closed
#define SCE_VFS_FILE_STATE_UNK    (0x00000800) //!< Unknown status
#define SCE_VFS_FILE_STATE_DUMMY  (0x00010000) //!< Dummy file

/**
 * VFS File
 * 
 * The file structure is contained within the SceUIDVfsFileObject structure, and represents file handles in the VFS.
 */
typedef struct SceVfsFile {
	SceUInt32 is_dir;
	SceUInt32 flags;

	SceOff position;

	SceUInt32 state;
	SceUID pid;

	SceVfsVnode *vp;
	SceVfsFile *next;

	SceUInt32 fd; //!< File descriptor provided and used by VFS implementation
	SceUInt16 flock_busy_count;

	SceUInt8 is_locked;
	SceUInt8 has_flock_ent;

	struct FdLock *fd_lock;

	SceUInt32 idata;

	struct DebugPath *debug_path; 

	SceUInt32 ioSchedData[3];
} SceVfsFile;
VITASDK_BUILD_ASSERT_EQ(0x40, SceVfsFile);
/** @} */

/**
 * @name VFS Operation Arguments and Callback Table
 */
/** @{ */
typedef struct SceVfsOpMountArgs {
	SceVfsMount *mnt;
	SceVfsPath *dev_file_path; //!< Path to the device file.
} SceVfsOpMountArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVfsOpMountArgs);

typedef struct SceVfsOpUmountArgs {
	SceVfsMount *mnt;
	int flags;
} SceVfsOpUmountArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVfsOpUmountArgs);

typedef struct SceVfsOpSetRootArgs {
	SceVfsMount *mnt;
	int unk;
	struct SceVfsVnode *vp;
} SceVfsOpSetRootArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVfsOpSetRootArgs);

typedef struct SceVfsOpGetRootArgs {
	SceVfsMount *mnt;
	int unk;
	struct SceVfsVnode **vpp;
} SceVfsOpGetRootArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVfsOpGetRootArgs);

typedef struct SceVfsOpSyncArgs {
	SceVfsMount *mnt;
	int flags;
} SceVfsOpSyncArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVfsOpSyncArgs);

typedef struct SceVfsOpInitArgs {
	SceVfsInfo *vfs_inf;
} SceVfsOpInitArgs;
VITASDK_BUILD_ASSERT_EQ(0x4, SceVfsOpInitArgs);

typedef struct SceVfsOpFiniArgs {
	SceVfsInfo *vfs_inf;
} SceVfsOpFiniArgs;
VITASDK_BUILD_ASSERT_EQ(0x4, SceVfsOpFiniArgs);

typedef struct SceVfsOpDevctlArg {
	SceVfsMount *mnt;
	const char *dev;
	unsigned int cmd;
	const void *arg;
	SceSize arg_len;
	void *buf;
	SceSize buf_len;
} SceVfsOpDevctlArg;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceVfsOpDevctlArg);

typedef struct SceVfsOpDecodePathElemArgs { 
	SceVfsMount *mnt;
	const char *path;
	const char **path2;  // path + something
	const char **path3;  // path3 + *decodeLen
	char *buf;
	SceSize buf_len;
	SceSize *decode_len; // out
} SceVfsOpDecodePathElemArgs;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceVfsOpDecodePathElemArgs);

typedef struct SceVfsOpTable {
	int (*vfs_mount)(SceVfsOpMountArgs *argp);
	int (*vfs_umount)(SceVfsOpUmountArgs *argp);
	int (*vfs_set_root)(SceVfsOpSetRootArgs *argp);
	int (*vfs_get_root)(SceVfsOpGetRootArgs *argp);

	void *reserved[2]; // Unused

	int (*vfs_sync)(SceVfsOpSyncArgs *argp);

	void *reserved2; // Unused

	int (*vfs_init)(SceVfsOpInitArgs *argp);
	int (*vfs_fini)(SceVfsOpFiniArgs *argp);

	void *reserved3; // Unused

	int (*vfs_devctl)(SceVfsOpDevctlArg *arg);
	int (*vfs_decode_path_elem)(SceVfsOpDecodePathElemArgs *argp);
} SceVfsOpTable;
VITASDK_BUILD_ASSERT_EQ(0x34, SceVfsOpTable);
/** @} */

/**
 * @name VFS Vnode Operation Arguments and Callback Table
 */
/** @{ */
typedef struct SceVopOpenArgs {
	SceVfsVnode *vp;
	SceVfsPath *path;
	int flags;
	SceVfsFile *file;
} SceVopOpenArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopOpenArgs);

typedef struct SceVopCreateArgs {
	SceVfsVnode *dvp;
	SceVfsVnode **vpp;
	SceVfsPath *path;
	int flags;
	int mode;
} SceVopCreateArgs;
VITASDK_BUILD_ASSERT_EQ(0x14, SceVopCreateArgs);

typedef struct SceVopCloseArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
} SceVopCloseArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVopCloseArgs);

typedef struct SceVopLookupArgs {
	SceVfsVnode  *dvp;
	SceVfsVnode **vpp;
	SceVfsPath *path;
	SceUInt32 flags;
} SceVopLookupArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopLookupArgs);

typedef struct SceVopReadArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	void *buf;
	SceSize nbyte;
} SceVopReadArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopReadArgs);

typedef struct SceVopWriteArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	const void *buf;
	SceSize nbyte;
} SceVopWriteArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopWriteArgs);

typedef struct SceVopLseekArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	SceOff offset;
	int whence;
} SceVopLseekArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceVopLseekArgs); // really 0x18 by SceOff align 8?

typedef struct SceVopIoctlArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	int cmd;
	const void *in_data;
	SceSize in_len;
	void *out_data;
	SceSize out_len;
} SceVopIoctlArgs;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceVopIoctlArgs);

typedef struct SceVopRemoveArgs {
	SceVfsVnode *dvp;
	SceVfsVnode *vp;
	SceVfsPath *path;
	SceUInt32 flags;
} SceVopRemoveArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopRemoveArgs);

typedef struct SceVopMkdirArgs {
	SceVfsVnode  *dvp;
	SceVfsVnode **vpp;
	SceVfsPath *path;
	int mode;
} SceVopMkdirArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopMkdirArgs);

typedef struct SceVopRmdirArgs {
	SceVfsVnode *dvp;
	SceVfsVnode *vp;
	SceVfsPath *path;
} SceVopRmdirArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVopRmdirArgs);

typedef struct SceVopDopenAgrs {
	SceVfsVnode *vp;
	SceVfsPath *path;
	SceVfsFile *file;
} SceVopDopenAgrs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVopDopenAgrs);

typedef struct SceVopDcloseArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
} SceVopDcloseArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVopDcloseArgs);

typedef struct SceVopDreadArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	SceIoDirent *dir;
} SceVopDreadArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVopDreadArgs);

typedef struct SceVopGetstatArgs {
	SceVfsVnode *vp;
	SceVfsPath *path;
	SceIoStat *stat;
} SceVopGetstatArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVopGetstatArgs);

typedef struct SceVopChstatArgs {
	SceVfsVnode *vp;
	SceVfsPath *path;
	SceIoStat *stat;
	int bit;
} SceVopChstatArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopChstatArgs);

typedef struct SceVopFchstatArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	SceIoStat *stat;
	SceUInt32 bit;
} SceVopFchstatArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopFchstatArgs);

typedef struct SceVopFgetstatArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	SceIoStat *stat;
} SceVopFgetstatArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVopFgetstatArgs);

typedef struct SceVopInactiveArgs {
	SceVfsVnode *vp;
} SceVopInactiveArgs;
VITASDK_BUILD_ASSERT_EQ(0x4, SceVopInactiveArgs);

typedef struct SceVopLinkArgs {
	SceVfsVnode *fvp;
	SceVfsVnode *tvp;
} SceVopLinkArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVopLinkArgs);

typedef struct SceVopUnlinkArgs {
	SceVfsVnode *fvp;
	SceVfsVnode *tvp;
} SceVopUnlinkArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVopUnlinkArgs);

typedef struct SceVopSyncArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	int flags;
} SceVopSyncArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVopSyncArgs);

typedef struct SceVopRenameArgs {
	SceVfsVnode *odvp;
	SceVfsVnode *ovp;
	SceVfsPath *old_path;
	SceVfsVnode *ndvp;
	SceVfsVnode **nvpp;
	SceVfsPath *new_path;
} SceVopRenameArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceVopRenameArgs);

typedef struct SceVopPreadArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	void *buf;
	SceSize nbyte;
	SceOff offset;
} SceVopPreadArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceVopPreadArgs);

typedef struct SceVopPwriteArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
	const void *buf;
	SceSize nbyte;
	SceOff offset;
} SceVopPwriteArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceVopPwriteArgs);

typedef struct SceVopWhiteoutArgs {
	SceVfsVnode *dvp;
	SceVfsVnode *vp;
	SceVfsPath *old_path;
	SceVfsPath *new_path;
} SceVopWhiteoutArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVopWhiteoutArgs);

typedef struct SceVopCleanupArgs {
	SceVfsVnode *vp;
	SceVfsFile *file;
} SceVopCleanupArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVopCleanupArgs);

typedef struct SceVopZerofillArgs {
	SceVfsVnode *vp;
	SceUInt64 unk;
	SceUInt64 unk1;
	SceUInt64 unk2;
} SceVopZerofillArgs;
VITASDK_BUILD_ASSERT_EQ(0x20, SceVopZerofillArgs);

typedef struct SceVopTable {
	int (*vop_open)(SceVopOpenArgs *argp);
	int (*vop_create)(SceVopCreateArgs *argp);
	int (*vop_close)(SceVopCloseArgs *argp);
	int (*vop_lookup)(SceVopLookupArgs *argp);

	SceSSize (*vop_read)(SceVopReadArgs *argp);
	SceSSize (*vop_write)(SceVopWriteArgs *argp);
	SceOff (*vop_lseek)(SceVopLseekArgs *argp);

	int (*vop_ioctl)(SceVopIoctlArgs *argp);

	int (*vop_remove)(SceVopRemoveArgs *argp);

	int (*vop_mkdir)(SceVopMkdirArgs *argp);
	int (*vop_rmdir)(SceVopRmdirArgs *argp);

	int (*vop_dopen)(SceVopDopenAgrs *argp);
	int (*vop_dclose)(SceVopDcloseArgs *argp);
	int (*vop_dread)(SceVopDreadArgs *argp);

	int (*vop_getstat)(SceVopGetstatArgs *argp);
	int (*vop_chstat)(SceVopChstatArgs *argp);

	int (*vop_rename)(SceVopRenameArgs *argp);

	const void *reserved; // Unused

	SceSSize (*vop_pread)(SceVopPreadArgs *argp);
	SceSSize (*vop_pwrite)(SceVopPwriteArgs *argp);

	int (*vop_inactive)(SceVopInactiveArgs *argp);
	int (*vop_link)(SceVopLinkArgs *argp);
	int (*vop_unlink)(SceVopUnlinkArgs *argp);

	int (*vop_sync)(SceVopSyncArgs *argp);

	int (*vop_fgetstat)(SceVopFgetstatArgs *argp);
	int (*vop_fchstat)(SceVopFchstatArgs *argp);

	int (*vop_whiteout)(SceVopWhiteoutArgs *argp);
	int (*vop_cleanup)(SceVopCleanupArgs *argp);
	int (*vop_verofill)(SceVopZerofillArgs *argp);
} SceVopTable;
VITASDK_BUILD_ASSERT_EQ(0x74, SceVopTable);
/** @} */

/**
 * @name VFS Core API
 */
/** @{ */
/**
 * Parameters for vfsMount and vfsMountForPFS
 */
typedef struct SceVfsMountParam {
	const char *root_path;       //!< This is the internal root path of the mountpoint. (example: /ux/exfat for ux0:)
	const char *blockdev_name;   //!< Overrides blockdevName in misc->blockdevName

	SceUInt8 fs_type;      //!< One of SCE_VFS_FS_TYPE_*
	SceUInt16 opt;         //!< Used to identify the IO Scheduler queue to use for the mountpoint
	SceUInt32 mnt_flags;   //!< ORed together SCE_VFS_MOUNT_FLAG_* flags

	const char *vfs_name;        //!< Name of the VFS to use for the mountpoint

	void *data;            //!< To be passed to the created mountpoint

	SceVfsMountData *misc;

	SceVopTable *vops;     //!< Overrides defaultVops in the VFS Info for the root vnode of the VFS
} SceVfsMountParam;
VITASDK_BUILD_ASSERT_EQ(0x20, SceVfsMountParam);

#define SCE_VFS_UMOUNT_FLAG_FORCE (0x1) //!< Force unmount

/**
 * Parameters for vfsUmount and vfsUmountForPFS
 */
typedef struct SceVfsUmountParam {
	const char *assign_name; //!< Assigned name of the mountpoint to unmount
	int flag;         //!< One of SCE_VFS_UMOUNT_FLAG_*
} SceVfsUmountParam;
VITASDK_BUILD_ASSERT_EQ(0x8, SceVfsUmountParam);

/**
 * Register a VFS implementation
 *
 * @param vfs_info - The VFS Info structure for the VFS. (This pointer should remain persistent until the VFS is deleted)
 * 
 * @return 0 on success, < 0 on error
 */
int ksceVfsAddVfs(SceVfsInfo *vfs_info);
/**
 * Unegister a VFS implementation
 *
 * @param name    - The name of the VFS implementation to unregister
 * @param vfs_info - The VFS Info structure for the VFS. (This pointer should remain persistent until the VFS is deleted)
 *
 * @return 0 on success, < 0 on error
 */
int ksceVfsDeleteVfs(const char *name, SceVfsInfo **vfs_info);

/**
 * Mount a drive
 *
 * @param param - The mount parameters
 *
 * @return 0 on success, < 0 on error
 */
int vfsMount(SceVfsMountParam *param);
/**
 * Unmount a drive
 *
 * @param param - The unmount parameters
 *
 * @return 0 on success, < 0 on error
 */
int vfsUmount(SceVfsUmountParam *param);

/**
 * Mount a drive via the mount daemon
 * 
 * @param param - The mount parameters
 * 
 * @return 0 on success, < 0 on error
 */
int vfsMountForPFS(SceVfsMountParam *param);
/**
 * Unmount a drive via the mount daemon
 *
 * @param param - The unmount parameters
 *
 * @return 0 on success, < 0 on error
 */
int vfsUmountForPFS(SceVfsUmountParam *param, int unk, int unk2);

/**
 * Lock the mnt
 * 
 * @param mnt - The mountpoint to lock
 * 
 * @return 0 on success, < 0 on error
 */
int vfsLockMnt(SceVfsMount *mnt);
/**
 * Unlock the mnt
 *
 * @param mnt - The mountpoint to unlock
 *
 * @return 0 on success, < 0 on error
 */
int vfsUnlockMnt(SceVfsMount *mnt);
/**
 * Is the mnt lock held by the current thread ?
 * 
 * @param mnt - The mount point to query
 * 
 * @return SCE_TRUE if the lock is held, SCE_FALSE if it is not, and < 0 on error
 */
SceBool vfsIsLockedMnt(SceVfsMount *mnt);

/**
 * Allocate a new VFS file object
 * 
 * @param vp     - The vnode the file should be referencing
 * @param file - The pointer reference the file will be returned to
 * @param name   - The name of the file
 * 
 * @return The UID of the file object on success, < 0 on error
 */
SceUID vfsAllocateFile(SceVfsVnode *vp, SceVfsFile **file, const char *name);
/**
 * Free a File object
 * 
 * @param vp - Vnode for the file handle being freed
 * @param fd - UID of the file being freed
 * 
 * @return 0 on success, < 0 on error
 */
int vfsFreeFile(SceVfsVnode *vp, SceUID fd);

/**
 * Get a new vnode from the pool
 * 
 * @param mnt  - The mountpoint the vnode will be attached to
 * @param vops - The vnode vop table for executing VFS Vops
 * @param unk  - Must be 0
 * @param vpp  - The pointer reference to return the vnode to
 * 
 * @return 0 on success, < 0 on error 
 */
int vfsGetNewVnode(SceVfsMount *mnt, SceVopTable *vops, int unk, SceVfsVnode **vpp);
/**
 * Return a vnode to the pool
 *
 * @param vp - The vnode to return
 *
 * @return 0 on success, < 0 on error
 */
int vfsFreeVnode(SceVfsVnode *vp);

/**
 * Lock a vnode
 * 
 * @param vp - Target vnode
 * 
 * @return 0 on success, < 0 on error
 */
int vfsLockVnode(SceVfsVnode *vp);
/**
 * Unlock a vnode
 *
 * @param vp - Target vnode
 *
 * @return 0 on success, < 0 on error
 */
int vfsUnlockVnode(SceVfsVnode *vp);
/**
 * Does the current thread own the vnode lock
 *
 * @param vp - Target vnode
 *
 * @return SCE_TRUE if the lock is owned, SCE_FALSE if it is not, and < 0 on error
 */
SceBool vfsIsOwnerVnode(SceVfsVnode *vp);

/**
 * Get the name of a vnode
 * 
 * @param vp     - Target vnode
 * @param name   - Buffer for the name
 * @param n      - Buffer size
 * @param result - Length of the returned name
 * 
 * @return 0 on success, < 0 on error 
 */
int vfsGetVnodeName(SceVfsVnode *vp, char *name, SceSize n, SceSize *result);
/** @} */

/**
 * @name VFS Vop APIs
 * 
 * These are relevant when doing operations on vnodes owned by other VFS implementations (block devices, etc.)
 */
/** @{ */
int ksceVopOpen(SceVfsVnode *vp, SceVfsPath *path, int flags, SceVfsFile *file);
int ksceVopCreate(SceVfsVnode *dvp, SceVfsVnode **vpp, SceVfsPath *path, int flags, int mode);
int ksceVopClose(SceVfsVnode *vp, SceVfsFile *file);
int ksceVopLookup(SceVfsVnode *dvp, SceVfsVnode **vpp, SceVfsPath *path, SceUInt32 flags);
int ksceVopRead(SceVfsVnode *vp, SceVfsFile *file, void *data, SceSize nbyte, SceSize *result);
int ksceVopWrite(SceVfsVnode *vp, SceVfsFile *file, const void *data, SceSize nbyte, SceSize *result);
SceOff ksceVopLseek(SceVfsVnode *vp, SceVfsFile *file, SceOff offset, int whence);

int ksceVopIoctl(SceVfsVnode *vp, SceVfsFile *file, int cmd, const void *in_data, SceSize in_len, void *out_data, SceSize out_len);
int ksceVopRemove(SceVfsVnode *dvp, SceVfsVnode *vp, SceVfsPath *path, SceUInt32 flags); 
int ksceVopMkdir(SceVfsVnode *dvp, SceVfsVnode **vpp, SceVfsPath *path, int mode);
int ksceVopRmdir(SceVfsVnode *dvp, SceVfsVnode *vp, SceVfsPath *path);

int ksceVopDopen(SceVfsVnode *vp, SceVfsPath *path, SceVfsFile *file);
int ksceVopDclose(SceVfsVnode *vp, SceVfsFile *file);
int ksceVopDread(SceVfsVnode *vp, SceVfsFile *file, SceIoDirent *dir);

int ksceVopGetstat(SceVfsVnode *vp, SceVfsPath *path, SceIoStat *stat);
int ksceVopChstat(SceVfsVnode *vp, SceVfsPath *path, SceIoStat *stat, int bit);

int ksceVopRename(SceVfsVnode *odvp, SceVfsVnode *ovp, SceVfsPath *old_path, SceVfsVnode *ndvp, SceVfsVnode **nvpp, SceVfsPath *new_path);
int ksceVopPread(SceVfsVnode *vp, SceVfsFile *file, void *data, SceSize nbyte, SceOff offset, SceSize *pResult);
int ksceVopPwrite(SceVfsVnode *vp, SceVfsFile *file, const void *data, SceSize nbyte, SceOff offset, SceSize *result);
int ksceVopInactive(SceVfsVnode *vp);
int ksceVopSync(SceVfsVnode *vp, SceVfsFile *file, int flags);
int ksceVopFgetstat(SceVfsVnode *vp, SceVfsFile *file, SceIoStat *stat);
int ksceVopFchstat(SceVfsVnode *vp, SceVfsFile *file, SceIoStat *stat, int bit);

int ksceVopLink(SceVfsVnode *fvp, SceVfsVnode *tvp);
int ksceVopUnlink(SceVfsVnode *fvp, SceVfsVnode *tvp);

int ksceVopWhiteout(SceVfsVnode *dvp, SceVfsVnode *vp, SceVfsPath *old_path, SceVfsPath *new_path);
int ksceVopCleanup(SceVfsVnode *vp, SceVfsFile *file);
int ksceVopZerofill(SceVfsVnode *vp, SceUInt64 unk, SceUInt64 unk1, SceUInt64 unk2);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_VFS_VNODE_H_ */