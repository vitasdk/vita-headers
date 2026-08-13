/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr.h,SceIofilemgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_IOFILEMGR_H_
#define _PSP2KERN_KERNEL_IOFILEMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2kern/io/fcntl.h>
#include <psp2kern/io/devctl.h>
#include <psp2kern/io/stat.h>
#include <psp2kern/io/dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceIoFdInfo {
	SceUID fd;
	SceUID pid;
} SceIoFdInfo;
VITASDK_BUILD_ASSERT_EQ(8, SceIoFdInfo);

/**
  * Get global file descriptor
  *
  * @param[in]  vis_level - unknown, set 5
  * @param[out] dst       - fd list output
  * @param[in]  max_size  - dst array count
  * @param[out] res_size  - result array count output
  *
  * @return < 0 on error.
  */
int ksceIoGetGUIDFdListForDebugger(int vis_level, SceIoFdInfo *dst, SceSize max_size, SceSize *res_size);

#define ksceIoGetGUIDFdList ksceIoGetGUIDFdListForDebugger

/**
  * Get process file descriptor
  *
  * @param[in]  vis_level - unknown, set 5
  * @param[out] dst       - fd list output
  * @param[in]  max_size  - dst array count
  * @param[out] res_size  - result array count output
  *
  * @return < 0 on error.
  */
int ksceIoGetPUIDFdListForDebugger(int vis_level, SceIoFdInfo *dst, SceSize max_size, SceSize *res_size);

#define ksceIoGetPUIDFdList ksceIoGetPUIDFdListForDebugger

typedef struct SceIofileInfo { // size is 0x828
	char path[0x400];
	char path2[0x400];
	SceUID pid;
	int data_0x804;
	int data_0x808;
	int data_0x80C;
	int data_0x810;
	int data_0x814;
	int data_0x818;
	int data_0x81C;
	int data_0x820; // maybe media type
	int data_0x824;
} SceIofileInfo;
VITASDK_BUILD_ASSERT_EQ(0x828, SceIofileInfo);

/**
  * Get file info
  *
  * @param[in]  fd   - file descriptor
  * @param[in]  pid  - process id
  * @param[out] info - fd info output
  *
  * @return < 0 on error.
  */
int ksceIoGetFileInfo(SceUID fd, SceUID pid, SceIofileInfo *info);

/**
  * Mounts a device
  *
  * @param[in]  id          Device to mount
  * @param[in]  path        Where to mount to
  * @param[in]  permission  Permission flags
  * @param      a4          Unknown, set to 0
  * @param      a5          Unknown, set to 0
  * @param      a6          Unknown, set to 0
  *
  * @return < 0 on error.
  */
int ksceIoMount(int id, const char *path, int permission, int a4, int a5, int a6);

/**
  * Unmounts a device
  *
  * @param[in]  id    Device to unmount
  * @param[in]  a2    Unknown, set to 0
  * @param[in]  a3    Unknown, set to 0
  * @param[in]  a4    Unknown, set to 0
  *
  * @return < 0 on error.
  */
int ksceIoUmount(int id, int a2, int a3, int a4);

/**
  * Get Remote Kernel Process Local Storage Data
  *
  * @param[in]  pid - The target process id
  * @param[out] dst - The pointer of RemoteKPLS output buffer. size is 0x1C.
  *
  * @return < 0 on error.
  */
int ksceIoGetRemoteKPLSData(SceUID pid, void *dst);

typedef struct SceIoMount {
	void *mnt; //!< Pointer to the internal VFS mount.
	int mntId; //!< VSH mount ID.
	char assignName[0x20];
	SceUInt32 openedEntryNum; //!< Number of open entries.
	SceBool isPfsMount; //!< Non-zero for a PFS_GDSD_INF mount.
	int pfsContext; //!< Pointer to the internal PFS buffer-list context.
} SceIoMount;
VITASDK_BUILD_ASSERT_EQ(0x34, SceIoMount); // size is from FW 3.60

typedef struct SceIoMountInfo {
	void *mnt; //!< Pointer to the internal VFS mount.
	int mntId; //!< VSH mount ID.
	char assignName[0x20];
	SceUInt32 openedEntryNum; //!< Number of open entries.
	int stateFlags;
	int devMinor;
	int devMajor;
	int mountCopy; //!< Same internal VFS mount pointer as mnt.
	int mountpoint; //!< Pointer to the internal mountpoint node.
	int poolUid; //!< Value of type ::SceUID.
	int referenceCount;
	int vnodeCount;
	int vnodeListHead; //!< Pointer to the first internal VFS node.
	int childMountListHead; //!< Pointer to the first child mount.
	int nextSiblingMount; //!< Pointer to the next sibling mount.
	int maxIoSize;
	int pfsContext; //!< Pointer to the internal PFS buffer-list context.
	int fdLock; //!< Pointer to the internal file-descriptor lock.
	int fdLockMutex; //!< Value of type ::SceUID.
	int fdLockCond; //!< Value of type ::SceUID.
	int fdLockOperationState;
	int fdLockWaiterCount;
	int mountCc; //!< Pointer to the internal mount cache-control object.
	int mountCcDirty;
	int mountCcFlag;
	int mountCcEventFlag; //!< Value of type ::SceUID.
	int blockDevAddress; //!< Pointer to the mount's internal block-device pointer.
	char mountData[0x400]; //!< Raw internal mount data beginning with the Unix mount path.
	int blockDev; //!< Pointer to the internal block-device descriptor.
	char filesystem[0x40];
	char blockdevName[0x40]; //!< Primary block-device name.
	char blockDeviceSecondary[0x40];
} SceIoMountInfo;
VITASDK_BUILD_ASSERT_EQ(0x54C, SceIoMountInfo); // size is from FW 3.60

typedef int (SceIoPathMappingFunc)(const char *path, SceUID pid, char *result_path, SceSize size);

typedef struct SceVfsChstatArgs {
	const char *path;
	const SceIoStat *stat;
	unsigned int cbit;
	uint32_t store_attr;
} SceVfsChstatArgs;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVfsChstatArgs); // size is from FW 3.60

typedef struct SceVfsChstatByFdArgs {
	SceUID fd;
	const SceIoStat *buf; //!< Stat buffer.
	unsigned int cbit;
} SceVfsChstatByFdArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVfsChstatByFdArgs); // size is from FW 3.60

typedef struct SceVfsCloseArgs {
	SceUID fd;
} SceVfsCloseArgs;
VITASDK_BUILD_ASSERT_EQ(0x4, SceVfsCloseArgs); // size is from FW 3.60

typedef struct SceVfsIoctlArgs {
	SceUID fd;
	unsigned int cmd;
	void *indata; //!< Input buffer.
	int inlen; //!< Size of indata.
	void *outdata; //!< Output buffer.
	int outlen; //!< Size of outdata.
} SceVfsIoctlArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceVfsIoctlArgs); // size is from FW 3.60

typedef struct SceVfsOpenArgs {
	const char *filename;
	int flag;
	SceIoMode mode;
} SceVfsOpenArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVfsOpenArgs); // size is from FW 3.60

typedef struct SceVfsPreadArgs {
	SceUID uid; //!< File descriptor.
	void *data;
	SceSize size;
	int padding; //!< Unused padding.
	SceOff offset;
} SceVfsPreadArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceVfsPreadArgs); // size is from FW 3.60

typedef struct SceVfsPwriteArgs {
	SceUID uid; //!< File descriptor.
	const void *data;
	SceSize size;
	int padding; //!< Unused padding.
	SceOff offset;
} SceVfsPwriteArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceVfsPwriteArgs); // size is from FW 3.60

typedef struct SceVfsReadArgs {
	SceUID fd;
	void *data;
	SceSize size;
} SceVfsReadArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVfsReadArgs); // size is from FW 3.60

typedef struct SceVfsWriteArgs {
	SceUID fd;
	const void *data;
	SceSize size;
} SceVfsWriteArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceVfsWriteArgs); // size is from FW 3.60

typedef struct sceIoCreateErrorEventForDriverOpt {
	uint32_t vshMountId; //!< Mount ID written when the event is signaled.
	uint32_t errorCode; //!< Error code written when the event is signaled.
	uint32_t reserved1[2]; //!< Must be zero when creating the event.
	uint32_t errorDetail; //!< Additional error value written when the event is signaled.
	uint32_t reserved2[2]; //!< Must be zero when creating the event.
} sceIoCreateErrorEventForDriverOpt;
VITASDK_BUILD_ASSERT_EQ(0x1C, sceIoCreateErrorEventForDriverOpt); // size is from FW 3.60

int ksceIoChstatForVshbridge(const char *name, const SceIoStat *buf, unsigned int cbit);
int ksceIoClearErrorEvent(SceUID uid);
SceUID ksceIoCreateErrorEvent(int vshMountId, int eventBits, sceIoCreateErrorEventForDriverOpt *opt);
int ksceIoCreateMountEvent(int vshMountId, int eventBits);
int ksceIoDeleteErrorEvent(SceUID uid);
int ksceIoDeleteMountEvent(SceUID uid);
int ksceIoDreadForVshbridge(SceUID fd, SceIoDirent *dir);

/**
 * Gets the media type for a path.
 *
 * If a path-mapping callback is registered, the path is remapped for the
 * specified process before its media type is queried. A media-type query
 * failure is converted to success after writing the fallback media type 8.
 *
 * @param[in]  pid        - Process whose path mapping is used.
 * @param[in]  path       - Path to query.
 * @param[in]  ignored    - Unused ABI slot; ignored on FW 3.60.
 * @param[out] media_type - Receives a 32-bit media-type value.
 *
 * @return The non-negative media-type query result, or a negative error from
 * path remapping or temporary-buffer allocation.
 */
int ksceIoGetMediaType(SceUID pid, const char *path, int ignored, int *media_type);
int ksceIoGetThreadDefaultPriorityForSystem(void);
int ksceIoGetstatForVshbridge(const char *name, SceIoStat *buf);
int ksceIoIoctl(SceUID fd, int cmd, const void *argp, SceSize arglen, void *bufp, SceSize buflen);
SceUID ksceIoOpenForPid(SceUID pid, const char *filename, int flags, SceIoMode mode);
int ksceIoSetPathMappingFunction(SceIoPathMappingFunc *func);
int ksceIoSyncByFd2(SceUID fd, int flags);
SceUID vfsAllocateFileDummy(int flags, SceBool is_dir, const char *name);
int vfsChstat(SceVfsChstatArgs *argp);
int vfsChstatByFd(SceVfsChstatByFdArgs *args);
int vfsClose(SceVfsCloseArgs *argp);
int vfsGetMntInfo(void *mnt, SceIoMountInfo *pInfo);
int vfsGetMntList(SceIoMount *pMount, SceUInt32 nMount, SceUInt32 *pnMount);
int vfsIoctl(SceVfsIoctlArgs *argp);
SceUID vfsOpen(SceVfsOpenArgs *argp);
int vfsPread(SceVfsPreadArgs *argp);
int vfsPwrite(SceVfsPwriteArgs *argp);
int vfsRead(SceVfsReadArgs *argp);
int vfsWrite(SceVfsWriteArgs *argp);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_IOFILEMGR_H_ */
