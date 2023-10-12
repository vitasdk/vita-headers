/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu/cache.h}
 */


#ifndef _PSP2KERN_KERNEL_CPU_CACHE_H_
#define _PSP2KERN_KERNEL_CPU_CACHE_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief The clean and invalidate a range the L1 dcache and L2
 *
 * @param[in] start The pointer for clean and invalidate start. value is should be aligned by 0x40.
 * @param[in] size  The clean and invalidate size. value is should be aligned by 0x40.
 */
void ksceKernelDcacheCleanInvalidateRange(void *start, unsigned int size);

/**
 * @brief The clean and invalidate a range the L1 dcache
 *
 * @param[in] start The pointer for clean and invalidate start. value is should be aligned by 0x40.
 * @param[in] size  The clean and invalidate size. value is should be aligned by 0x40.
 */
void ksceKernelDcacheCleanInvalidateRangeForL1WBWA(void *start, unsigned int size);

/**
 * @brief The clean a range the L1 dcache and L2
 *
 * @param[in] start The pointer for clean start. value is should be aligned by 0x20.
 * @param[in] size  The clean size. value is should be aligned by 0x20.
 */
void ksceKernelDcacheCleanRange(void *start, unsigned int size);

/**
 * @brief The clean a range the L1 dcache
 *
 * @param[in] start The pointer for clean start. value is should be aligned by 0x20.
 * @param[in] size  The clean size. value is should be aligned by 0x20.
 */
void ksceKernelDcacheCleanRangeForL1WBWA(void *start, unsigned int size);

/**
 * @brief The invalidate a range the L1 dcache and L2
 *
 * @param[in] start The pointer for invalidate start. value is should be aligned by 0x40.
 * @param[in] size  The invalidate size. value is should be aligned by 0x40.
 */
void ksceKernelDcacheInvalidateRange(void *start, unsigned int size);

/**
 * @brief The invalidate a range the L1 dcache
 *
 * @param[in] start The pointer for invalidate start. value is should be aligned by 0x40.
 * @param[in] size  The invalidate size. value is should be aligned by 0x40.
 */
void ksceKernelDcacheInvalidateRangeForL1WBWA(void *start, unsigned int size);

/**
 * @brief The invalidate a range the L1 icache and L2
 *
 * @param[in] start The pointer for invalidate start. value is should be aligned by 0x40.
 * @param[in] size  The invalidate size. value is should be aligned by 0x40.
 */
void ksceKernelIcacheInvalidateRange(void *start, unsigned int size);

/**
 * @brief The clean a one line the L1 icache
 *
 * @param[in] start The pointer for clean start.
 */
void ksceKernelL1DcacheClean(void *start);

/**
 * @brief The clean a range the L1 dcache
 *
 * @param[in] start The pointer for clean start.
 * @param[in] size  The clean size.
 */
void ksceKernelL1DcacheCleanRange(void *start, unsigned int size);

/**
 * @brief The clean all the L1 dcache
 */
void ksceKernelL1DcacheCleanAll(void);

/**
 * @brief The invalidate a one line the L1 icache
 *
 * @param[in] start The pointer for invalidate start.
 */
void ksceKernelL1DcacheCleanInvalidate(void *start);

/**
 * @brief The clean and invalidate a range the L1 dcache
 *
 * @param[in] start The pointer for clean and invalidate start.
 * @param[in] size  The clean and invalidate size.
 */
void ksceKernelL1DcacheCleanInvalidateRange(void *start, unsigned int size);

/**
 * @brief The clean and invalidate all the L1 dcache
 */
void ksceKernelL1DcacheCleanInvalidateAll(void);

/**
 * @brief The invalidate a one line the L1 dcache
 *
 * @param[in] start The pointer for invalidate start.
 */
void ksceKernelL1DcacheInvalidate(void *start);

/**
 * @brief The invalidate a range the L1 dcache
 *
 * @param[in] start The pointer for invalidate start.
 * @param[in] size  The invalidate size.
 */
void ksceKernelL1DcacheInvalidateRange(void *start, unsigned int size);

/**
 * @brief The invalidate all the L1 dcache
 */
void ksceKernelL1DcacheInvalidateAll(void);

/**
 * @brief The invalidate a range the L1 icache
 *
 * @param[in] start The pointer for invalidate start.
 * @param[in] size  The invalidate size.
 */
void ksceKernelL1IcacheInvalidateRange(void *start, unsigned int size);

/**
 * @brief The invalidate entire the L1 icache
 */
void ksceKernelL1IcacheInvalidateEntire(void);

/**
 * @brief The invalidate entire the L1 icache of all cores
 */
void ksceKernelL1IcacheInvalidateEntireAllCore(void);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_CACHE_H_ */
