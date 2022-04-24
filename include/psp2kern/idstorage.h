/**
 * \kernelgroup{SceIdStorage}
 * \usage{psp2kern/idstorage.h,SceIdStorageForDriver_stub}
 */

#ifndef _PSP2KERN_IDSTORAGE_H_
#define _PSP2KERN_IDSTORAGE_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param[in]  leafnum - The read target leaf number
 * @param[out] buf     - The leaf data buffer pointer, size is 512 byte
 *
 * @return 0 on success, < 0 on error.
 */
int ksceIdStorageReadLeaf(SceSize leafnum, void *buf);

/**
 * @param[in] leafnum - The write target leaf number
 * @param[in] buf     - The leaf data buffer pointer, size is 512 byte
 *
 * @return 0 on success, < 0 on error.
 *
 * note - Writing to leaf requires manufacturing mode.
 */
int ksceIdStorageWriteLeaf(SceSize leafnum, const void *buf);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_IDSTORAGE_H_ */
