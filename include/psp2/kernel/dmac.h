/**
 * \usergroup{SceDmacMgr}
 * \usage{psp2/kernel/dmac.h,SceKernelDmacMgr_stub}
 */


#ifndef _PSP2_KERNEL_DMAC_H_
#define _PSP2_KERNEL_DMAC_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * DMA memcpy
 *
 * @param[in] dst - Destination
 * @param[in] src - Source
 * @param[in] size - Size
 *
 * @return < 0 on error.
 */
int sceDmacMemcpy(void *dst, const void *src, SceSize size);

/**
 * DMA memset
 *
 * @param[in] dst  - Destination
 * @param[in] ch   - The character
 * @param[in] size - Size
 *
 * @return < 0 on error.
 */
int sceDmacMemset(void *dst, int ch, SceSize size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_DMAC_H_ */
