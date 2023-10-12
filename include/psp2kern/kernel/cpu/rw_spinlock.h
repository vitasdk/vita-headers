/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu/rw_spinlock.h}
 */


#ifndef _PSP2KERN_KERNEL_CPU_RW_SPINLOCK_H_
#define _PSP2KERN_KERNEL_CPU_RW_SPINLOCK_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


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
 * @note       This function resumes interrupts only if they were enabled before the call to ::ksceKernelRWSpinlockLowReadLockCpuSuspendIntr/::ksceKernelRWSpinlockLowTryReadLockCpuSuspendIntr.
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
 * @note       This function resumes interrupts only if they were enabled before the call to ::ksceKernelSpinlockLowLockCpuSuspendIntr/::ksceKernelRWSpinlockLowTryWriteLockCpuSuspendIntr.
 */
void ksceKernelRWSpinlockLowWriteUnlockCpuResumeIntr(SceKernelRWSpinlock* lock, SceKernelIntrStatus intr_status);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_RW_SPINLOCK_H_ */
