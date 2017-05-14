/**
 * \kernelgroup{SceDmacMgr}
 * \usage{psp2kern/kernel/dmac.h,SceDmacmgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_DMAC_H_
#define _PSP2_KERNEL_DMAC_H_

#ifdef __cplusplus
extern "C" {
#endif

/***
 * DMA memcpy
 *
 * @param[in] dst - Destination
 * @param[in] src - Source
 * @param[in] size - Size
 *
 * @return dst.
*/
void *ksceDmacMemcpy(void *dst, const void *src, size_t size);

/***
 * DMA memset
 *
 * @param[in] dst - Destination
 * @param[in] c - Constant
 * @param[in] size - Size
 *
 * @return dst.
*/
void *ksceDmacMemset(void *dst, int c, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_DMAC_H_ */
