/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu.h}
 */


#ifndef _PSP2KERN_KERNEL_CPU_H_
#define _PSP2KERN_KERNEL_CPU_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/cpu/atomic.h>
#include <psp2kern/kernel/cpu/cache.h>
#include <psp2kern/kernel/cpu/corelock.h>
#include <psp2kern/kernel/cpu/mmu.h>
#include <psp2kern/kernel/cpu/ple.h>
#include <psp2kern/kernel/cpu/rw_spinlock.h>
#include <psp2kern/kernel/cpu/spinlock.h>
#include <psp2kern/kernel/sysclib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      Call this when entering a syscall
 *
 * @param      state  The state
 */
#define ENTER_SYSCALL(state) \
	do { \
		asm volatile ("mrc p15, 0, %0, c13, c0, 3" : "=r" (state)); \
		asm volatile ("mcr p15, 0, %0, c13, c0, 3" :: "r" (state << 16) : "memory"); \
	} while(0)

/**
 * @brief      Call this when exiting a syscall
 *
 * @param      state  The state
 */
#define EXIT_SYSCALL(state) \
	do { \
		asm volatile ("mcr p15, 0, %0, c13, c0, 3" :: "r" (state) : "memory"); \
	} while (0)


/**
 * @brief Returns the CPU ID of the calling processor
 *
 * @return The CPU ID
 */
int ksceKernelCpuId(void);

/**
 * @brief Suspend intr of calling processor
 *
 * @return The prev intr status
 */
SceKernelIntrStatus ksceKernelCpuSuspendIntr(void);

/**
 * @brief Suspend intr of calling processor
 *
 * @param[in] prev_state The prev status
 *
 * @return The prev intr status
 */
SceKernelIntrStatus ksceKernelCpuResumeIntr(SceKernelIntrStatus prev_state);


// sceKernelDomainTextMemcpy removed from 3.63
#if PSP2_SDK_VERSION >= 0x3630000 && defined(__USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT)
#undef __USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT
#endif

/**
 * @brief         The domain text memcpy
 *
 * @param[in] dst The destination
 * @param[in] src The source
 * @param[in] len The length
 *
 * @return        always SCE_OK.
 */
#if defined(__USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT)
int ksceKernelDomainTextMemcpy(void *dst, const void *src, SceSize len);
#else
static inline int ksceKernelDomainTextMemcpy(void *dst, const void *src, SceSize len)
{
	SceUInt32 prev_dacr;

	asm volatile("mrc p15, 0, %0, c3, c0, 0" : "=r" (prev_dacr));
	asm volatile("mcr p15, 0, %0, c3, c0, 0" :: "r" (0xFFFF0000));

	memcpy(dst, src, len);

	ksceKernelDcacheCleanRangeForL1WBWA((void *)(((uintptr_t)dst) & ~0x1F), ((((uintptr_t)dst) + len + 0x1F) & ~0x1F) - (((uintptr_t)dst) & ~0x1F));

	asm volatile("mcr p15, 0, %0, c3, c0, 0" :: "r" (prev_dacr));

	return SCE_OK;
}
#endif


// ksceKernelGetVmaccessRange

void ksceKernelCpuBranchPredictorInvalidateAll(void);
void ksceKernelCpuBranchPredictorInvalidateAllIS(void);

SceUInt8 ksceKernelCpuGetCONTEXTIDR(void);
// ksceKernelCpuUpdateSCTLR

SceBool ksceKernelIsUncacheAddressInTmpFsGame(void *address);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_H_ */
