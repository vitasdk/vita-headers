/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu.h,SceCpuForDriver_stub}
 */


#ifndef _PSP2_KERNEL_CPU_H_
#define _PSP2_KERNEL_CPU_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/sysclib.h>
#include <psp2kern/kernel/sysmem/mmu.h>

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
 * @brief      Writeback a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void ksceKernelCpuDcacheWritebackRange(const void *ptr, SceSize len);


/**
 * @brief      Save process context
 *
 * @param      context  The context
 */
static inline void ksceKernelCpuSaveContext(SceKernelProcessContext *context)
{
	asm ("mrc p15, 0, %0, c2, c0, 1" : "=r" (context->TTBR1));
	asm ("mrc p15, 0, %0, c3, c0, 0" : "=r" (context->DACR));
	asm ("mrc p15, 0, %0, c13, c0, 1" : "=r" (context->CONTEXTIDR));
}

/**
 * @brief      Restore process context
 *
 * @param      context  The context, can be from ::ksceKernelGetPidContext
 */
static inline void ksceKernelCpuRestoreContext(const SceKernelProcessContext *context)
{
	int cpsr, tmp;

	asm volatile ("mrs %0, cpsr" : "=r" (cpsr));
	if (!(cpsr & 0x80))
		asm volatile ("cpsid i" ::: "memory");
	asm volatile ("mrc p15, 0, %0, c13, c0, 1" : "=r" (tmp));
	tmp = (tmp & 0xFFFFFF00) | context->CONTEXTIDR;
	asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (0));
	asm volatile ("isb" ::: "memory");
	asm volatile ("mcr p15, 0, %0, c2, c0, 1" :: "r" (context->TTBR1 | 0x4A));
	asm volatile ("isb" ::: "memory");
	asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (tmp));
	asm volatile ("mcr p15, 0, %0, c3, c0, 0" :: "r" (context->DACR & 0x55555555));
	if (!(cpsr & 0x80))
		asm volatile ("cpsie i" ::: "memory");
}

/**
 * @brief      MMU permission bypassing memcpy
 *
 * This works by writing to the DACR before and after the memcpy.
 *
 * @param      dst   The destination
 * @param[in]  src   The source
 * @param[in]  len   The length
 *
 * @return     Zero on success.
 */
static inline int ksceKernelCpuUnrestrictedMemcpy(void *dst, const void *src, SceSize len)
{
	int prev_dacr;

	asm volatile("mrc p15, 0, %0, c3, c0, 0" : "=r" (prev_dacr));
	asm volatile("mcr p15, 0, %0, c3, c0, 0" :: "r" (0xFFFF0000));

	memcpy(dst, src, len);

	len += (SceSize)(((uintptr_t)dst) & 0x1F);

	dst = (void *)(((uintptr_t)dst) & ~0x1F);
	len = (len + 0x1F) & ~0x1F;

	ksceKernelCpuDcacheWritebackRange(dst, len);

	asm volatile("mcr p15, 0, %0, c3, c0, 0" :: "r" (prev_dacr));
	return 0;
}

/**
 * @brief      Returns the CPU ID of the calling processor
 *
 * @return     The CPU ID
 */
int ksceKernelCpuGetCpuId(void);

/**
 * @brief      Disabled interrupts
 *
 * @return     Interrupt masks before disabling
 */
int ksceKernelCpuDisableInterrupts(void);

/**
 * @brief      Enable interrupts
 *
 * @param[in]  flags  Interrupt masks
 *
 * @return     Zero on success
 */
int ksceKernelCpuEnableInterrupts(int flags);

/**
 * @brief      Invalidate a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void ksceKernelCpuDcacheInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void ksceKernelCpuDcacheWritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate all the L1 dcache (without L2)
 */
void ksceKernelCpuDcacheInvalidateAll(void);

/**
 * @brief      Writeback all the L1 dcache (without L2)
 */
void ksceKernelCpuDcacheWritebackAll(void);

/**
 * @brief      Writeback and invalidate all the L1 dcache (without L2)
 */
void ksceKernelCpuDcacheWritebackInvalidateAll(void);

/**
 * @brief      Writeback a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void ksceKernelCpuDcacheAndL2WritebackRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void ksceKernelCpuDcacheAndL2InvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
void ksceKernelCpuDcacheAndL2WritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate a range of L1 icache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void ksceKernelCpuIcacheInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate all the L1 icache (without L2)
 *
 * @return     Zero on success
 */
int ksceKernelCpuIcacheInvalidateAll(void);

/**
 * @brief      Writeback and invalidate a range of L1 icache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void ksceKernelCpuIcacheAndL2WritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Suspend all interrupts (disables IRQs)
 *
 * @param[in]  addr   Mutex associated to the suspend-resume pair
 *
 * @return     The current state of the interrupt controller, to be used with ::ksceKernelCpuResumeIntr.
 */
int ksceKernelCpuSuspendIntr(int *addr);

/**
 * @brief      Resume all interrupts (enables IRQs)
 *
 * @param[in]  addr   Mutex associated to the suspend-resume pair
 * @param[in]  prev_state   State obtained from ::ksceKernelCpuSuspendIntr.
 *
 * @return     The previous state of the interrupt controller.
 */
int ksceKernelCpuResumeIntr(int *addr, int prev_state);

/**
 * @brief      Disable interrupts (IRQs) and spin-lock
 *
 * @param[in]  addr   Mutex associated to the lock-unlock pair
 *
 * @return     The current state of the interrupt controller, to be passed to ::ksceKernelCpuSpinLockIrqRestore
 */
int ksceKernelCpuSpinLockIrqSave(int *addr);

/**
 * @brief      Spin-unlock and restore interrupt state
 *
 * @param[in]  addr   Mutex associated to the lock-unlock pair
 * @param[in]  flags   Previous interrupt state to be restored (returned by ::ksceKernelCpuSpinLockIrqSave)
 *
 * @return     Zero on success
 */
int ksceKernelCpuSpinLockIrqRestore(int *addr, int flags);

typedef enum SceCorelockCore {
	SCE_CORELOCK_CORE0 = 0,
	SCE_CORELOCK_CORE1 = 1,
	SCE_CORELOCK_CORE2 = 2,
	SCE_CORELOCK_CORE3 = 3
} SceCorelockCore;

typedef struct SceCorelockContext {
	int lock;
	int16_t core_count;
	int16_t last_wait_core;
} SceCorelockContext;

void ksceKernelCorelockContextInitialize(SceCorelockContext *ctx);

void ksceKernelCorelockLock(SceCorelockContext *ctx, int core);
void ksceKernelCorelockUnlock(SceCorelockContext *ctx);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CPU_H_ */

