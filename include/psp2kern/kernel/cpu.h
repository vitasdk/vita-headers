/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu.h,SceCpuForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_CPU_H_
#define _PSP2KERN_KERNEL_CPU_H_

#include <vitasdk/build_utils.h>
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
 * @brief Get the process context
 *
 * @param[in]  pid - The target process id
 * @param[out] ctx - The context output pointer of pointer
 */
int ksceKernelProcessGetContext(SceUID pid, SceKernelProcessContext **ctx);

/**
 * @brief Switch the process context
 *
 * @param[in]   new_context - The new context
 * @param[out] prev_context - The prev context
 */
int ksceKernelProcessSwitchContext(const SceKernelProcessContext *new_context, SceKernelProcessContext *prev_context);

// ksceKernelCpuUnrestrictedMemcpy removed from 3.63
#if PSP2_SDK_VERSION >= 0x3630000 && defined(__USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT)
#undef __USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT
#endif

/**
 * @brief      MMU permission bypassing memcpy
 *
 * This works by writing to the DACR before and after the memcpy.
 *
 * @param      dst   The destination
 * @param[in]  src   The source
 * @param[in]  len   The length
 *
 * @return     SCE_OK on success.
 */
#if defined(__USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT)
int ksceKernelCpuUnrestrictedMemcpy(void *dst, const void *src, SceSize len);
#else
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
#endif

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
 * @return     none
 */
void ksceKernelCpuEnableInterrupts(int flags);

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
 * @brief       Acquire a spinlock
 * 
 * @param[in]   lock     Spinlock to acquire
 */
void ksceKernelSpinlockLowLock(SceKernelSpinlock *lock);

/**
 * @brief      Attempt to acquire a spinlock
 * 
 * @param[in]  lock     Spinlock to acquire
 * 
 * @retval     SCE_OK if the spinlock is acquired
 * @retval     <0 if the spinlock could not be acquired
 */
int ksceKernelSpinlockLowTryLock(SceKernelSpinlock *lock);

/**
 * @brief      Release a previously acquired spinlock
 * 
 * @param[in]  lock     Spinlock to release
 */
void ksceKernelSpinlockLowUnlock(SceKernelSpinlock *lock);

/**
 * @brief      Acquire a spinlock and suspend interrupts if necessary
 *
 * @param[in]  lock     Spinlock to acquire
 *
 * @return     An opaque value to be used during the call to ::ksceKernelSpinlockLowUnlockCpuResumeIntr.
 */
SceKernelIntrStatus ksceKernelSpinlockLowLockCpuSuspendIntr(SceKernelSpinlock* lock);

/**
 * @brief       Attempt to acquire a spinlock and suspend interrupts if necessary
 * 
 * @param[in]  lock     Spinlock to acquire
 * 
 * @retval     >=0 if the spinlock is acquired - opaque value describing the interrupt state
 * @retval     <0 if the spinlock could not be acquired
 * @note       Interrupts are only suspended if the acquisition of the spinlock succeeds
 */
SceKernelIntrStatus ksceKernelSpinlockLowTryLockCpuSuspendIntr(SceKernelSpinlock *lock);

/**
 * @brief      Release a previously acquired spinlock and resume interrupts if necessary
 *
 * @param[in]  lock          Spinlock to release
 * @param[in]  intr_status   Status value obtained from ::ksceKernelSpinlockLowLockCpuSuspendIntr/::ksceKernelSpinlockLowTryLockCpuSuspendIntr.
 * 
 * @note       This function resumes interrupts only if they were enabled before the call to ::ksceKernelSpinlockLowLockCpuSuspendIntr/::ksceKernelSpinlockLowTryLockCpuSuspendIntrForDriver.
 */
void ksceKernelSpinlockLowUnlockCpuResumeIntr(SceKernelSpinlock* lock, SceKernelIntrStatus intr_status);

/**
 * @brief      Acquire a RWSpinlock for reading
 *
 * @param[in]  lock   RWSpinlock to acquire
 *
 * @note       It is forbidden to write to data protected by the spinlock after acquiring it with this function.
 */
void ksceKernelRWSpinlockLowReadLock(SceKernelRWSpinlock* lock);

/**
 * @brief       Attempt to acquire a RWSpinlock for reading
 * 
 * @param[in]  lock     Spinlock to acquire
 * 
 * @retval     SCE_OK if the spinlock is acquired
 * @retval     <0 if the spinlock could not be acquired
 * @note       It is forbidden to write to data protected by the spinlock after acquiring it with this function.
 */
int ksceKernelRWSpinlockLowTryReadLock(SceKernelRWSpinlock* lock);

/**
 * @brief      Unlock a RWSpinlock previously acquired for reading
 * 
 * @param[in]  lock    RWSpinlock to release
 */
void ksceKernelRWSpinlockLowReadUnlock(SceKernelRWSpinlock* lock);

/**
 * @brief      Acquire a RWSpinlock for reading and suspend interrupts if necessary.
 *
 * @param[in]  lock   RWSpinlock to acquire
 *
 * @return     An opaque value to be used during the call to ::ksceKernelRWSpinlockLowReadUnlockCpuResumeIntr.
 * @note       It is forbidden to write to data protected by the spinlock after acquiring it with this function.
 */
SceKernelIntrStatus ksceKernelRWSpinlockLowReadLockCpuSuspendIntr(SceKernelRWSpinlock* lock);

/**
 * @brief       Attempt to acquire a RWSpinlock for reading and suspend interrupts if necessary
 * 
 * @param[in]  lock     Spinlock to acquire
 * 
 * @retval     >=0 if the spinlock is acquired - opaque value describing the interrupt state
 * @retval     <0 if the spinlock could not be acquired
 * @note       Interrupts are only suspended if the acquisition of the spinlock succeeds
 * @note       It is forbidden to write to data protected by the spinlock after acquiring it with this function.
 */
SceKernelIntrStatus ksceKernelRWSpinlockLowTryReadLockCpuSuspendIntr(SceKernelRWSpinlock* lock);

/**
 * @brief      Release a RWSpinlock previously acquired for reading and resume interrupts if necessary.
 *
 * @param[in]  lock          RWSpinlock to release
 * @param[in]  intr_status   Status value obtained from ::ksceKernelRWSpinlockLowReadLockCpuSuspendIntr/::ksceKernelRWSpinlockLowTryReadLockCpuSuspendIntr.
 *
 * @note This function resumes interrupts only if they were enabled before the call to ::ksceKernelRWSpinlockLowReadLockCpuSuspendIntr/::ksceKernelRWSpinlockLowTryReadLockCpuSuspendIntr.
 */
void ksceKernelRWSpinlockLowReadUnlockCpuResumeIntr(SceKernelRWSpinlock* lock, SceKernelIntrStatus intr_status);

/**
 * @brief      Acquire a RWSpinlock for writing
 *
 * @param[in]  lock   RWSpinlock to acquire
 */
void ksceKernelRWSpinlockLowWriteLock(SceKernelRWSpinlock* lock);

/**
 * @brief       Attempt to acquire a RWSpinlock for writing
 * 
 * @param[in]  lock     Spinlock to acquire
 * 
 * @retval     SCE_OK if the spinlock is acquired
 * @retval     <0 if the spinlock could not be acquired
 */
int ksceKernelRWSpinlockLowTryWriteLock(SceKernelRWSpinlock* lock);

/**
 * @brief      Unlock a RWSpinlock previously acquired for writing
 * 
 * @param[in]  lock    RWSpinlock to release
 */
void ksceKernelRWSpinlockLowWriteUnlock(SceKernelRWSpinlock* lock);

/**
 * @brief      Acquire a RWSpinlock for writing and suspend interrupts if necessary.
 *
 * @param[in]  lock   RWSpinlock to acquire
 *
 * @return     An opaque value to be used during the call to ::ksceKernelRWSpinlockLowWriteUnlockCpuResumeIntr.
 */
SceKernelIntrStatus ksceKernelRWSpinlockLowWriteLockCpuSuspendIntr(SceKernelRWSpinlock* lock);

/**
 * @brief       Attempt to acquire a RWSpinlock for writing and suspend interrupts if necessary
 * 
 * @param[in]  lock     Spinlock to acquire
 * 
 * @retval     >=0 if the spinlock is acquired - opaque value describing the interrupt state
 * @retval     <0 if the spinlock could not be acquired
 * @note       Interrupts are only suspended if the acquisition of the spinlock succeeds
 */
SceKernelIntrStatus ksceKernelRWSpinlockLowTryWriteLockCpuSuspendIntr(SceKernelRWSpinlock* lock);

/**
 * @brief      Release a RWSpinlock acquired for writing and resume interrupts if necessary.
 *
 * @param[in]  lock          RWSpinlock to release
 * @param[in]  intr_status   Status value obtained from ::ksceKernelRWSpinlockLowWriteLockCpuSuspendIntr/::ksceKernelRWSpinlockLowTryWriteLockCpuSuspendIntr.
 *
 * @note This function resumes interrupts only if they were enabled before the call to ::ksceKernelSpinlockLowLockCpuSuspendIntr/::ksceKernelRWSpinlockLowTryWriteLockCpuSuspendIntr.
 */
void ksceKernelRWSpinlockLowWriteUnlockCpuResumeIntr(SceKernelRWSpinlock* lock, SceKernelIntrStatus intr_status);

typedef struct SceCorelockContext {
	int lock;
	int16_t core_count;
	int16_t last_wait_core;
} SceCorelockContext;
VITASDK_BUILD_ASSERT_EQ(8, SceCorelockContext);

void ksceKernelCorelockInitialize(SceCorelockContext *ctx);

void ksceKernelCorelockLock(SceCorelockContext *ctx, SceUInt32 core);
void ksceKernelCorelockUnlock(SceCorelockContext *ctx);

/* For backwards compatibility */

/**
 * @brief      Save process context
 *
 * @param      context  The context
 */
static inline SceInt32 ksceKernelCpuSaveContext(SceKernelProcessContext *context)
{
	int res;
	SceKernelProcessContext *ctx;

	res = ksceKernelProcessGetContext(SCE_KERNEL_PROCESS_ID_SELF, &ctx);
	if(res < 0){
		return res;
	}

	memcpy(context, ctx, sizeof(*context));

	return 0;
}

/**
 * @brief      Restore process context
 *
 * @param      context  The context, can be from ::ksceKernelGetPidContext
 */
static inline SceInt32 ksceKernelCpuRestoreContext(const SceKernelProcessContext *context)
{
	return ksceKernelProcessSwitchContext(context, NULL);
}

//This name conflicts with the official name for ksceKernelCpuDisableInterrupts and may become deprecated soon
static inline __attribute__((deprecated("Use ksceKernelSpinlockLowLockCpuSuspendIntr"))) int ksceKernelCpuSuspendIntr(int *addr) {
	return ksceKernelSpinlockLowLockCpuSuspendIntr((SceKernelSpinlock*)addr);
}

//This name conflicts with the official name for ksceKernelCpuEnableInterrupts and may become deprecated soon
static inline __attribute__((deprecated("Use ksceKernelSpinlockLowUnlockCpuResumeIntr"))) int ksceKernelCpuResumeIntr(int *addr, int prev_state) {
	ksceKernelSpinlockLowUnlockCpuResumeIntr((SceKernelSpinlock*)addr, (SceKernelIntrStatus)prev_state);
	return 0;
}

static inline __attribute__((deprecated("Use ksceKernelRWSpinlockLowReadLockCpuSuspendIntr"))) int ksceKernelCpuSpinLockIrqSave(int *addr) {
	return ksceKernelRWSpinlockLowReadLockCpuSuspendIntr((SceKernelRWSpinlock*)addr);
}

static inline __attribute__((deprecated("Use ksceKernelRWSpinlockLowReadUnlockCpuResumeIntr"))) int ksceKernelCpuSpinLockIrqRestore(int *addr, int flags) {
	ksceKernelRWSpinlockLowReadUnlockCpuResumeIntr((SceKernelRWSpinlock*)addr, (SceKernelIntrStatus)flags);
	return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_H_ */

