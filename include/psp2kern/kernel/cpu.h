/**
 * \kernelgroup{SceCPU}
 * \usage{psp2kern/kernel/cpu.h,SceCpuForDriver_stub}
 */


#ifndef _PSP2_KERNEL_CPU_H_
#define _PSP2_KERNEL_CPU_H_

#include <psp2kern/types.h>

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
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheWritebackRange(const void *ptr, SceSize len);


/**
 * @brief      Save process context
 *
 * @param      context  The context
 */
static inline void ksceKernelCpuSaveContext(int context[3])
{
	asm ("mrc p15, 0, %0, c2, c0, 1" : "=r" (context[0]));
	asm ("mrc p15, 0, %0, c3, c0, 0" : "=r" (context[1]));
	asm ("mrc p15, 0, %0, c13, c0, 1" : "=r" (context[2]));
}

/**
 * @brief      Restore process context
 *
 * @param      context  The context, can be from ::ksceKernelGetPidContext
 */
static inline void ksceKernelCpuRestoreContext(int context[3])
{
	int cpsr, tmp;

	asm volatile ("mrs %0, cpsr" : "=r" (cpsr));
	if (!(cpsr & 0x80))
		asm volatile ("cpsid i" ::: "memory");
	asm volatile ("mrc p15, 0, %0, c13, c0, 1" : "=r" (tmp));
	tmp = (tmp & 0xFFFFFF00) | context[2];
	asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (0));
	asm volatile ("isb" ::: "memory");
	asm volatile ("mcr p15, 0, %0, c2, c0, 1" :: "r" (context[0] | 0x4A));
	asm volatile ("isb" ::: "memory");
	asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (tmp));
	asm volatile ("mcr p15, 0, %0, c3, c0, 0" :: "r" (context[1] & 0x55555555));
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

	asm ("mrc p15, 0, %0, c3, c0, 0" : "=r" (prev_dacr));
	asm ("mcr p15, 0, %0, c3, c0, 0" :: "r" (0xFFFF0000));

	for (size_t i=0; i < len; i++) {
		((char *) dst)[i] = ((char *) src)[i];
	}
	ksceKernelCpuDcacheWritebackRange((void *)((uintptr_t)dst & ~0x1F), (len + 0x1F) & ~0x1F);

	asm ("mcr p15, 0, %0, c3, c0, 0" :: "r" (prev_dacr));
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
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheWritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate all the L1 dcache (without L2)
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheInvalidateAll(void);

/**
 * @brief      Writeback all the L1 dcache (without L2)
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheWritebackAll(void);

/**
 * @brief      Writeback and invalidate all the L1 dcache (without L2)
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheWritebackInvalidateAll(void);

/**
 * @brief      Writeback a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheAndL2WritebackRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheAndL2InvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheAndL2WritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate a range of L1 icache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuIcacheInvalidateRange(const void *ptr, SceSize len);

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
 *
 * @return     Zero on success
 */
int ksceKernelCpuIcacheAndL2WritebackInvalidateRange(const void *ptr, SceSize len);

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CPU_H_ */

