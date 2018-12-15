/**
 * \kernelgroup{SceIdStorage}
 * \usage{psp2kern/idstorage.h,SceIdStorageForDriver_stub}
 */

#ifndef _PSP2_KERNEL_IDSTORAGE_H_
#define _PSP2_KERNEL_IDSTORAGE_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param[in] leafnum - 0x0 ~ 0x80 / leafnum > 0x80 = error
 * @param[out] buf - Leaf data
 * @param[in] buf_size - set 0x200 / buf_size != 0x200 = 0x800F090D
 *
 * @return 0 on success, < 0 on error.
 */
int ksceIdStorageReadLeaf(int leafnum, void *buf, int buf_size);
int ksceIdStorageWriteLeaf(int leafnum, const void *buf, int buf_size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_IDSTORAGE_H_ */
