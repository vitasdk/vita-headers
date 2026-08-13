/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu/atomic.h,SceCpuForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_CPU_ATOMIC_H_
#define _PSP2KERN_KERNEL_CPU_ATOMIC_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


SceInt32 ksceKernelAtomicAdd32AndGet64InHiLoRange(SceUInt64 *val, SceInt32 add_val, SceInt32 limit);
SceInt32 ksceKernelAtomicAdd32AndGet64InRange(SceUInt64 *val, SceInt32 add_val, SceInt32 limit);
SceInt32 ksceKernelAtomicAddAndGetPositive32InRange(SceInt32 *val, SceInt32 add_val, SceInt32 limit);
SceInt32 ksceKernelAtomicDecIfLowPositive32(SceInt32 *addr);
SceInt32 ksceKernelAtomicGet32AndSet64(SceUInt64 *result, SceInt32 src);
SceInt32 ksceKernelAtomicGet32AndSet64_2(SceUInt64 *result, SceInt32 src);
SceUInt32 ksceKernelAtomicIncrementHighwaterCounter(SceUInt32 *counter);
SceInt32 ksceKernelAtomicLimit64(SceUInt64 *result, SceInt32 limit);
SceInt32 ksceKernelAtomicSubIfGreater64(SceUInt64 *a1, SceUInt32 a2);


void ksceKernelAtomicSet8(SceInt8 *store, SceInt8 value);
void ksceKernelAtomicSet16(SceInt16 *store, SceInt16 value);
void ksceKernelAtomicSet32(SceInt32 *store, SceInt32 value);
void ksceKernelAtomicSet64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicCompareAndSet8(SceInt8 *store, SceInt8 value, SceInt8 new_value);
SceInt16 ksceKernelAtomicCompareAndSet16(SceInt16 *store, SceInt16 value, SceInt16 new_value);
SceInt32 ksceKernelAtomicCompareAndSet32(SceInt32 *store, SceInt32 value, SceInt32 new_value);
SceInt64 ksceKernelAtomicCompareAndSet64(SceInt64 *store, SceInt64 value, SceInt64 new_value);


SceInt8 ksceKernelAtomicAddAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicAddAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicAddAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicAddAndGet64(SceInt64 *store, SceInt64 value);

SceBool ksceKernelAtomicAddUnless8(SceInt8 *store, SceInt8 value, SceInt8 cmpv);
SceBool ksceKernelAtomicAddUnless16(SceInt16 *store, SceInt16 value, SceInt16 cmpv);
SceBool ksceKernelAtomicAddUnless32(SceInt32 *store, SceInt32 value, SceInt32 cmpv);
SceBool ksceKernelAtomicAddUnless64(SceInt64 *store, SceInt64 value, SceInt64 cmpv);

SceInt8 ksceKernelAtomicSubAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicSubAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicSubAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicSubAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicAndAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicAndAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicAndAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicAndAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicOrAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicOrAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicOrAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicOrAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicXorAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicXorAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicXorAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicXorAndGet64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicClearAndGet8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicClearAndGet16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicClearAndGet32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicClearAndGet64(SceInt64 *store, SceInt64 value);


SceInt8 ksceKernelAtomicGetAndSet8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicGetAndSet16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicGetAndSet32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicGetAndSet64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicGetAndAdd8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicGetAndAdd16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicGetAndAdd32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicGetAndAdd64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicGetAndSub8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicGetAndSub16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicGetAndSub32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicGetAndSub64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicGetAndAnd8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicGetAndAnd16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicGetAndAnd32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicGetAndAnd64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicGetAndOr8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicGetAndOr16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicGetAndOr32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicGetAndOr64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicGetAndXor8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicGetAndXor16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicGetAndXor32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicGetAndXor64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicGetAndClear8(SceInt8 *store, SceInt8 value);
SceInt16 ksceKernelAtomicGetAndClear16(SceInt16 *store, SceInt16 value);
SceInt32 ksceKernelAtomicGetAndClear32(SceInt32 *store, SceInt32 value);
SceInt64 ksceKernelAtomicGetAndClear64(SceInt64 *store, SceInt64 value);

void ksceKernelAtomicClearMask8(SceInt8 *store, SceInt8 value);
void ksceKernelAtomicClearMask16(SceInt16 *store, SceInt16 value);
void ksceKernelAtomicClearMask32(SceInt32 *store, SceInt32 value);
void ksceKernelAtomicClearMask64(SceInt64 *store, SceInt64 value);

SceInt8 ksceKernelAtomicDecIfPositive8(SceInt8 *store);
SceInt16 ksceKernelAtomicDecIfPositive16(SceInt16 *store);
SceInt32 ksceKernelAtomicDecIfPositive32(SceInt32 *store);
SceInt64 ksceKernelAtomicDecIfPositive64(SceInt64 *store);


/**
 * Atomically updates a 16-bit value when \p val compares greater.
 *
 * The firmware sign-extends the value loaded from \p addr before a signed
 * comparison, while using \p val as passed in the argument register. The
 * historical unsigned types are retained for backwards compatibility; a normal C
 * caller therefore passes \p val zero-extended.
 *
 * @param[in,out] addr Address updated with an exclusive 16-bit load/store.
 * @param[in] val Candidate value. Only its low 16 bits are stored.
 *
 * @return \p val if it compares greater than the sign-extended previous value;
 * otherwise the previous value, through the historical unsigned return type.
 */
unsigned short ksceKernelAtomicSetIfGreaterGet16(unsigned short *addr, unsigned short val);

/**
 * Atomically stores \p val when it is greater under a signed 32-bit comparison.
 *
 * @param[in,out] addr Address updated with an exclusive 32-bit load/store.
 * @param[in] val Candidate whose bit pattern is interpreted as signed.
 *
 * @return The signed maximum of the previous value and \p val, through the
 * historical unsigned return type.
 */
unsigned int ksceKernelAtomicSetIfGreaterGet32(unsigned int *addr, unsigned int val);

/**
 * Atomically updates an 8-bit value when \p val compares greater.
 *
 * The firmware sign-extends the value loaded from \p addr before a signed
 * comparison, while using \p val as passed in the argument register. The
 * historical unsigned types are retained for backwards compatibility; a normal C
 * caller therefore passes \p val zero-extended.
 *
 * @param[in,out] addr Address updated with an exclusive 8-bit load/store.
 * @param[in] val Candidate value. Only its low 8 bits are stored.
 *
 * @return \p val if it compares greater than the sign-extended previous value;
 * otherwise the previous value, through the historical unsigned return type.
 */
unsigned char ksceKernelAtomicSetIfGreaterGet8(unsigned char *addr, unsigned char val);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_ATOMIC_H_ */
