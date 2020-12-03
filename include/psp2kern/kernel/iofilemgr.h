/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr.h,SceIofilemgrForDriver_stub}
 */

#ifndef _PSP2_KERNEL_IOFILEMGR_H_
#define _PSP2_KERNEL_IOFILEMGR_H_

#include <psp2kern/types.h>
#include <psp2kern/io/devctl.h>
#include <psp2kern/io/stat.h>
#include <psp2kern/io/dirent.h>
#include <psp2kern/io/fcntl.h>

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
int sceIoGetGUIDFdListForDebugger(int vis_level, SceIoFdInfo *dst, SceSize max_size, SceSize *res_size);

#define sceIoGetGUIDFdList sceIoGetGUIDFdListForDebugger

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
int sceIoGetPUIDFdListForDebugger(int vis_level, SceIoFdInfo *dst, SceSize max_size, SceSize *res_size);

#define sceIoGetPUIDFdList sceIoGetPUIDFdListForDebugger

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_IOFILEMGR_H_ */
