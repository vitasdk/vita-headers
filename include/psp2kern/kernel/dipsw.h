/**
 * \kernelgroup{SceDipsw}
 * \usage{psp2kern/kernel/dipsw.h,SceDipswForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_DIPSW_H_
#define _PSP2KERN_KERNEL_DIPSW_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceDipsw {
	uint32_t cp_timestamp_1;
	uint16_t cp_version;
	uint16_t cp_build_id;
	uint32_t cp_timestamp_2;
	uint32_t aslr_seed;
	uint32_t sce_sdk_flags;
	uint32_t shell_flags;
	uint32_t debug_control_flags;
	uint32_t system_control_flags;
} SceDipsw;

/**
 * Get dipsw info.
 *
 * @param[in] idx - The info index
 *                - 0:CP Time
 *                - 1:bid & version
 *                - 2:CP Time
 *                - 3:ASLR
 *                - 4:SDK(SCE)
 *                - 5:SHELL
 *                - 6:debug control
 *                - 7:system control
 *
 * @return dipsw info.
 */
SceUInt32 ksceKernelGetDipswInfo(unsigned int idx);

/**
 * Check dipsw bit.
 *
 * @param[in] bit - The dipsw bit index
 *
 * @return zero or one.
 */
int ksceKernelCheckDipsw(unsigned int bit);

/**
 * Set dipsw bit.
 *
 * @param[in] bit - The dipsw bit index
 *
 * @return none.
 */
void ksceKernelSetDipsw(unsigned int bit);

/**
 * Clear dipsw bit.
 *
 * @param[in] bit - The dipsw bit index
 *
 * @return none.
 */
void ksceKernelClearDipsw(unsigned int bit);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_DIPSW_H_ */
