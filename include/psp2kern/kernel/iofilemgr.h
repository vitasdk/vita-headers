/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr.h,SceIofilemgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_IOFILEMGR_H_
#define _PSP2KERN_KERNEL_IOFILEMGR_H_

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_IOFILEMGR_H_ */
