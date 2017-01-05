/**
 * \kernelgroup{SceCPU}
 * \usage{psp2kern/kernel/cpu.h,?}
 */

/**
 * \file
 * \brief Header file related to ARM CPU functions for kernel
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
#define ENTER_SYSCALL(state) do { \
  asm volatile ("mrc p15, 0, %0, c13, c0, 3" : "=r" (state)); \
  asm volatile ("mcr p15, 0, %0, c13, c0, 3" :: "r" (state << 16) : "memory"); \
} while(0)

/**
 * @brief      Call this when existing a syscall
 *
 * @param      state  The state
 */
#define EXIT_SYSCALL(state) do { \
  asm volatile ("mcr p15, 0, %0, c13, c0, 3" :: "r" (state) : "memory"); \
} while (0)

/**
 * @brief      Save process context
 *
 * @param      context  The context
 */
static inline void ksceKernelCpuSaveContext(int context[3]) {
  asm ("mrc p15, 0, %0, c2, c0, 1" : "=r" (context[0]));
  asm ("mrc p15, 0, %0, c3, c0, 0" : "=r" (context[1]));
  asm ("mrc p15, 0, %0, c13, c0, 1" : "=r" (context[2]));
}

/**
 * @brief      Restore process context
 *
 * @param      context  The context, can be from `ksceKernelGetPidContext`
 */
static inline void ksceKernelCpuRestoreContext(int context[3]) {
  int cpsr;
  int tmp;

  asm volatile ("mrs %0, cpsr" : "=r" (cpsr));
  if (!(cpsr & 0x80)) {
    asm volatile ("cpsid i" ::: "memory");
  }
  asm volatile ("mrc p15, 0, %0, c13, c0, 1" : "=r" (tmp));
  tmp = (tmp & 0xFFFFFF00) | context[2];
  asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (0));
  asm volatile ("isb" ::: "memory");
  asm volatile ("mcr p15, 0, %0, c2, c0, 1" :: "r" (context[0] | 0x4A));
  asm volatile ("isb" ::: "memory");
  asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (tmp));
  asm volatile ("mcr p15, 0, %0, c3, c0, 0" :: "r" (context[1] & 0x55555555));
  if (!(cpsr & 0x80)) {
    asm volatile ("cpsie i" ::: "memory");
  }
}

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
 * @brief      Flush L1 dcache and L2
 *
 * Note: symbols currently does not work on 3.x, need to find new ones.
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheAndL2Flush(void *ptr, size_t len);

/**
 * @brief      Flush L2 dcache without L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheFlush(void *ptr, size_t len);

/**
 * @brief      Writeback a range of L1 dcache (not sure if L2 too)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheWritebackRange(void *ptr, size_t len);

/**
 * @brief      Flush L1 icache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuIcacheAndL2Flush(void *ptr, size_t len);

/**
 * @brief      Flush L1 dcache and L2 for DMA operations
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
int ksceKernelCpuDcacheAndL2AndDMAFlush(void *ptr, size_t len);

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
int ksceKernelCpuUnrestrictedMemcpy(void *dst, const void *src, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CPU_H_ */

