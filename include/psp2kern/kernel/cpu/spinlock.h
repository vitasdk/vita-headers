/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu/spinlock.h}
 */


#ifndef _PSP2KERN_KERNEL_CPU_SPINLOCK_H_
#define _PSP2KERN_KERNEL_CPU_SPINLOCK_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


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
int ksceKernelSpinlockLowTrylock(SceKernelSpinlock *lock);

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
SceKernelIntrStatus ksceKernelSpinlockLowLockCpuSuspendIntr(SceKernelSpinlock *lock);

/**
 * @brief       Attempt to acquire a spinlock and suspend interrupts if necessary
 * 
 * @param[in]  lock     Spinlock to acquire
 * 
 * @retval     >=0 if the spinlock is acquired - opaque value describing the interrupt state
 * @retval     <0 if the spinlock could not be acquired
 * @note       Interrupts are only suspended if the acquisition of the spinlock succeeds
 */
SceKernelIntrStatus ksceKernelSpinlockLowTrylockCpuSuspendIntr(SceKernelSpinlock *lock);

/**
 * @brief      Release a previously acquired spinlock and resume interrupts if necessary
 *
 * @param[in]  lock          Spinlock to release
 * @param[in]  intr_status   Status value obtained from ::ksceKernelSpinlockLowLockCpuSuspendIntr/::ksceKernelSpinlockLowTryLockCpuSuspendIntr.
 * 
 * @note       This function resumes interrupts only if they were enabled before the call to ::ksceKernelSpinlockLowLockCpuSuspendIntr/::ksceKernelSpinlockLowTryLockCpuSuspendIntr.
 */
void ksceKernelSpinlockLowUnlockCpuResumeIntr(SceKernelSpinlock *lock, SceKernelIntrStatus intr_status);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_SPINLOCK_H_ */
