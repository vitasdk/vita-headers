/**
 * \usergroup{SceCpu}
 * \usage{psp2/kernel/cpu.h,SceSysmem_stub}
 */


#ifndef _PSP2_KERNEL_CPU_H_
#define _PSP2_KERNEL_CPU_H_

#define SCE_KERNEL_CPU_MASK_USER_0  0x00010000
#define SCE_KERNEL_CPU_MASK_USER_1  0x00020000
#define SCE_KERNEL_CPU_MASK_USER_2  0x00040000
#define SCE_KERNEL_CPU_MASK_SYSTEM  0x00080000

#define SCE_KERNEL_CPU_MASK_USER_ALL    \
                        (SCE_KERNEL_CPU_MASK_USER_0 | SCE_KERNEL_CPU_MASK_USER_1 | SCE_KERNEL_CPU_MASK_USER_2)


#ifdef __cplusplus
extern "C" {
#endif

int sceKernelGetCpuId(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CPU_H_ */
