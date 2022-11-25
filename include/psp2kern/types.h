/**
 * \kernelgroup{SceTypes}
 * \usage{psp2kern/types.h}
 */

#ifndef _PSP2KERN_TYPES_H_
#define _PSP2KERN_TYPES_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_GUID_SYSROOT                     = 0x10001,
	SCE_GUID_GUID_ENTRY_HEAP             = 0x10003,
	SCE_GUID_KERNEL_PROCESS_ID           = 0x10005,
	SCE_GUID_KERNEL_ADDRESS_SPACE        = 0x10007,
	SCE_GUID_PART_ROOT                   = 0x10009,
	SCE_GUID_KERNEL_HEAP                 = 0x1000B,
	SCE_GUID_KERNEL_HEAP_UNCACHE         = 0x1000D,
	SCE_GUID_PHYMEM_PART_KERNEL          = 0x1000F,
	SCE_GUID_PHYMEM_PART_TOOL            = 0x10011,
	SCE_GUID_DUMMY_PROCESS_GAME          = 0x10013,
	SCE_GUID_DUMMY_PROCESS_SYSTEM        = 0x10015,
	SCE_GUID_CLEANER_THREAD              = 0x10017,
	SCE_GUID_IDLE_THREAD_0               = 0x10019,
	SCE_GUID_IDLE_THREAD_1               = 0x1001B,
	SCE_GUID_IDLE_THREAD_2               = 0x1001D,
	SCE_GUID_IDLE_THREAD_3               = 0x1001F,
	SCE_GUID_ALL_PROCESS                 = 0x10021,
	SCE_GUID_GLOBAL_WORK_QUEUE           = 0x10023,
	SCE_GUID_THREAD_ID_SYSTEM_ALL        = 0x10025,
	SCE_GUID_THREAD_ID_PROCESS_ALL       = 0x10027,
	SCE_GUID_RESERVED_29                 = 0x10029,
	SCE_GUID_KERNEL_HEAP_TOOL            = 0x1002B,
	SCE_GUID_RESERVED_2D                 = 0x1002D,
	SCE_GUID_RESERVED_2F                 = 0x1002F,
	SCE_GUID_RESERVED_31                 = 0x10031,
	SCE_GUID_KERNEL_FIXED_HEAP_16B       = 0x10033,
	SCE_GUID_KERNEL_FIXED_HEAP_32B       = 0x10035,
	SCE_GUID_KERNEL_FIXED_HEAP_48B       = 0x10037,
	SCE_GUID_KERNEL_FIXED_HEAP_64B       = 0x10039,
	SCE_GUID_KERNEL_FIXED_HEAP_128B      = 0x1003B,
	SCE_GUID_KERNEL_FIXED_HEAP_256B      = 0x1003D,
	SCE_GUID_KERNEL_FIXED_HEAP_512B      = 0x1003F,
	SCE_GUID_KERNEL_FIXED_HEAP_L2_OBJECT = 0x10041,
	SCE_GUID_PART_USER_SHARED            = 0x10043,
	SCE_GUID_PART_IO                     = 0x10045,
	SCE_GUID_PART_CDRAM                  = 0x10047,
	SCE_GUID_RESERVED_49                 = 0x10049,
	SCE_GUID_PART_TMP                    = 0x1004B,
	SCE_GUID_PART_ROOT_UNCACHE           = 0x1004D,
	SCE_GUID_PART_KMP                    = 0x1004F,
	SCE_GUID_PART_ROOT_UNCACHE_GPU_GAME  = 0x10051,
	SCE_GUID_PART_TMP_FS_GAME            = 0x10053,
	SCE_GUID_PART_ROOT_TOOL              = 0x10055,
	SCE_GUID_PART_ROOT_TOOL_UNCACHE      = 0x10057,
	SCE_GUID_PROCESS_BUDGET_KERNEL       = 0x10059,
	SCE_GUID_PROCESS_BUDGET_SHELL        = 0x1005B,
	SCE_GUID_PROCESS_BUDGET_FULL_GAME    = 0x1005D,
	SCE_GUID_RESERVED_5F                 = 0x1005F
	/* Random completely from 0x10061 */
};

typedef struct SceKernelAddrPair { // do not use
	uint32_t addr;             //!< Address
	uint32_t length;           //!< Length
} SceKernelAddrPair;

typedef struct SceKernelVARange { // size is 0x8
	uint32_t addr;
	SceSize size;
} SceKernelVARange;

typedef struct SceKernelPARange { // size is 0x8
	uint32_t addr;
	SceSize size;
} SceKernelPARange;

typedef struct SceKernelPAVector { // size is 0x14
	SceSize size;              //!< Size of this structure
	union {
		struct {
			uint32_t ranges_size;    //!< Ex: 8
			uint32_t data_in_vector; //!< Must be <= 8
			uint32_t count;
			SceKernelPARange *ranges;
		};
		struct { // do not use.
			uint32_t list_size;             //!< Size in elements of the list array
			uint32_t ret_length;            //!< Total physical size of the memory pairs
			uint32_t ret_count;             //!< Number of elements of list filled by ksceKernelGetPaddrList
			SceKernelAddrPair *list;        //!< Array of physical addresses and their lengths pairs
		};
	};
} SceKernelPAVector;

typedef SceKernelPAVector SceKernelPaddrList; // do not use.

typedef struct SceSharedSecret { // size is 0x40-bytes
	uint8_t shared_secret_0[0x10];
	uint8_t klicensee[0x10];
	uint8_t shared_secret_2[0x10];
	uint32_t shared_secret_3_0; // ex: 0x10
	uint32_t shared_secret_3_1;
	uint32_t shared_secret_3_2;
	uint32_t shared_secret_3_3;
} SceSharedSecret;

typedef struct SceSelfAuthInfo { // size is 0x90-bytes
	SceUInt64 program_authority_id;
	uint8_t padding[8];
	uint8_t capability[0x20];
	uint8_t attribute[0x20];
	SceSharedSecret secret;
} SceSelfAuthInfo;

/**
 * @brief Regular Spinlock
 * 
 * Spinlocks are a simple mutual exclusion mechanism implemented
 * using atomic primitives (LDREX/STREX). Unlike other kernel
 * synchronisation primitives, spinlocks can be acquired under
 * any context, including an IRQ or exception handler.
 * 
 * Since threads/CPUs trying to acquire a spinlock loop until
 * the lock is free, this synchronisation primitive should only
 * be used when the data to protect may be accessed under a context
 * in which entering WAITING state is not allowed (e.g. IRQ handler).
 * 
 * Spinlocks cannot be acquired recursively. Attempting to recursively
 * acquire a regular spinlock will deadlock.
 *
 * 
 * The regular Spinlock works similarly to a mutex - only one thread
 * or CPU may own the Spinlock at a time.
 */
typedef int SceKernelSpinlock;

/**
 * @brief RW Spinlock
 * 
 * (Refer to the regular spinlock description for more details
 * about the spinlock synchronisation primitive)
 * 
 * 
 * The RWSpinlock works similarly to a RWLock - multiple threads/CPUs
 * can access the protected data at the same time as long as only reads
 * are performed. When acquired for writing, a single thread/CPU at a time
 * is allowed to own the RWSpinlock and is thus free to modify the data.
 * Modifying data protected by a RWSpinlock while holding it for reading is
 * undefined behaviour and will lead to data corruption and system instability.
 * 
 * RW Spinlocks may be acquired by up to ?128? readers at a time. It is
 * also possible to recursively acquire a RWSpinlock for reading. Recursively
 * acquiring a RWSpinlock for writing is not allowed and will deadlock.
 */
typedef int SceKernelRWSpinlock;

/**
 * @brief Interrupt status
 * 
 * This opaque value is used to hold the interruptability status
 * (whether the CPU can be interrupted) on entry to functions that
 * temporarily suspend interrupts. For readers familiar with the
 * Windows NT kernel, this is similar in spirit to the IRQL value.
 * 
 * The only usage that can be made of this value is to compare it
 * against zero to check whether a function call failed, if applicable.
 * See the description of functions using this datatype for more details.
 */
typedef int SceKernelIntrStatus;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_TYPES_H_ */
