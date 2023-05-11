/**
 * \usergroup{SceCpu}
 * \usage{psp2/kernel/cpu.h,SceSysmem_stub}
 */


#ifndef _PSP2_KERNEL_CPU_H_
#define _PSP2_KERNEL_CPU_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


#define SCE_KERNEL_CPU_MASK_USER_0  0x00010000
#define SCE_KERNEL_CPU_MASK_USER_1  0x00020000
#define SCE_KERNEL_CPU_MASK_USER_2  0x00040000
#define SCE_KERNEL_CPU_MASK_SYSTEM  0x00080000

#define SCE_KERNEL_CPU_MASK_USER_ALL    \
                        (SCE_KERNEL_CPU_MASK_USER_0 | SCE_KERNEL_CPU_MASK_USER_1 | SCE_KERNEL_CPU_MASK_USER_2)


int sceKernelGetCpuId(void);


void sceKernelAtomicSet8(SceInt8 *store, SceInt8 value);
void sceKernelAtomicSet16(SceInt16 *store, SceInt16 value);
void sceKernelAtomicSet32(SceInt32 *store, SceInt32 value);
void sceKernelAtomicSet64(SceInt64 *store, SceInt64 value);

void sceKernelAtomicCompareAndSet8(SceInt8 *store, SceInt8 value);
void sceKernelAtomicCompareAndSet16(SceInt16 *store, SceInt16 value);
void sceKernelAtomicCompareAndSet32(SceInt32 *store, SceInt32 value);
void sceKernelAtomicCompareAndSet64(SceInt64 *store, SceInt64 value);


SceInt8 sceKernelAtomicAddAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicAddAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicAddAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicAddAndGet64(SceInt64 *store, SceInt64 value);

SceBool sceKernelAtomicAddUnless8(SceInt8 *store, SceInt8 value, SceInt8 cmpv);
SceBool sceKernelAtomicAddUnless16(SceInt16 *store, SceInt16 value, SceInt16 cmpv);
SceBool sceKernelAtomicAddUnless32(SceInt32 *store, SceInt32 value, SceInt32 cmpv);
SceBool sceKernelAtomicAddUnless64(SceInt64 *store, SceInt64 value, SceInt64 cmpv);

SceInt8 sceKernelAtomicSubAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicSubAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicSubAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicSubAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicAndAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicAndAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicAndAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicAndAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicOrAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicOrAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicOrAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicOrAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicXorAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicXorAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicXorAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicXorAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicClearAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicClearAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicClearAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicClearAndGet64(SceInt64 *store, SceInt64 value);


SceInt8 sceKernelAtomicGetAndSet8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicGetAndSet16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicGetAndSet32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicGetAndSet64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicGetAndAdd8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicGetAndAdd16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicGetAndAdd32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicGetAndAdd64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicGetAndSub8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicGetAndSub16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicGetAndSub32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicGetAndSub64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicGetAndAnd8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicGetAndAnd16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicGetAndAnd32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicGetAndAnd64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicGetAndOr8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicGetAndOr16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicGetAndOr32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicGetAndOr64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicGetAndXor8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicGetAndXor16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicGetAndXor32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicGetAndXor64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicGetAndClear8(SceInt8 *store, SceInt8 value);
SceInt16 sceKernelAtomicGetAndClear16(SceInt16 *store, SceInt16 value);
SceInt32 sceKernelAtomicGetAndClear32(SceInt32 *store, SceInt32 value);
SceInt64 sceKernelAtomicGetAndClear64(SceInt64 *store, SceInt64 value);


void sceKernelAtomicClearMask8(SceInt8 *store, SceInt8 value);
void sceKernelAtomicClearMask16(SceInt16 *store, SceInt16 value);
void sceKernelAtomicClearMask32(SceInt32 *store, SceInt32 value);
void sceKernelAtomicClearMask64(SceInt64 *store, SceInt64 value);

SceInt8 sceKernelAtomicDecIfPositive8(SceInt8 *store);
SceInt16 sceKernelAtomicDecIfPositive16(SceInt16 *store);
SceInt32 sceKernelAtomicDecIfPositive32(SceInt32 *store);
SceInt64 sceKernelAtomicDecIfPositive64(SceInt64 *store);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CPU_H_ */
