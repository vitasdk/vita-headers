/**
 * \kernelgroup{SceTypes}
 * \usage{psp2kern/types.h}
 */

#ifndef _PSP2KERN_TYPES_H_
#define _PSP2KERN_TYPES_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_KERNEL_SYSROOT_ID                         = 0x10001,
	SCE_KERNEL_GUID_ENTRY_HEAP_ID                 = 0x10003,
	SCE_KERNEL_PROCESS_ID                         = 0x10005,
	SCE_KERNEL_ADDRESS_SPACE_ID                   = 0x10007,
	SCE_KERNEL_PARTITION_ROOT_ID                  = 0x10009,
	SCE_KERNEL_HEAP_ID                            = 0x1000B,
	SCE_KERNEL_HEAP_UNCACHE_ID                    = 0x1000D,
	SCE_KERNEL_PHYMEMPART_ID                      = 0x1000F,
	SCE_KERNEL_PHYMEMPART_TOOL_ID                 = 0x10011,
	SCE_KERNEL_DUMMY_PROCESS_GAME_ID              = 0x10013,
	SCE_KERNEL_DUMMY_PROCESS_SYSTEM_ID            = 0x10015,
	SCE_KERNEL_CLEANER_THREAD_ID                  = 0x10017,
	SCE_KERNEL_IDLE_THREAD_0_ID                   = 0x10019,
	SCE_KERNEL_IDLE_THREAD_1_ID                   = 0x1001B,
	SCE_KERNEL_IDLE_THREAD_2_ID                   = 0x1001D,
	SCE_KERNEL_IDLE_THREAD_3_ID                   = 0x1001F,
	SCE_KERNEL_ALL_PROCESS_ID                     = 0x10021,
	SCE_KERNEL_GLOBAL_WORK_QUEUE_ID               = 0x10023,
	SCE_KERNEL_THREAD_ID_SYSTEM_ALL_ID            = 0x10025,
	SCE_KERNEL_THREAD_ID_PROCESS_ALL_ID           = 0x10027,
	SCE_KERNEL_RESERVED_GUID_29                   = 0x10029,
	SCE_KERNEL_HEAP_TOOL_ID                       = 0x1002B,
	SCE_KERNEL_RESERVED_GUID_2D                   = 0x1002D,
	SCE_KERNEL_RESERVED_GUID_2F                   = 0x1002F,
	SCE_KERNEL_RESERVED_GUID_31                   = 0x10031,
	SCE_KERNEL_FIXED_HEAP_16B_ID                  = 0x10033,
	SCE_KERNEL_FIXED_HEAP_32B_ID                  = 0x10035,
	SCE_KERNEL_FIXED_HEAP_48B_ID                  = 0x10037,
	SCE_KERNEL_FIXED_HEAP_64B_ID                  = 0x10039,
	SCE_KERNEL_FIXED_HEAP_128B_ID                 = 0x1003B,
	SCE_KERNEL_FIXED_HEAP_256B_ID                 = 0x1003D,
	SCE_KERNEL_FIXED_HEAP_512B_ID                 = 0x1003F,
	SCE_KERNEL_FIXED_HEAP_L2_OBJECT_ID            = 0x10041,
	SCE_KERNEL_PARTITION_USER_SHARED_ID           = 0x10043,
	SCE_KERNEL_PARTITION_IO_ID                    = 0x10045,
	SCE_KERNEL_PARTITION_CDRAM_ID                 = 0x10047,
	SCE_KERNEL_RESERVED_GUID_49                   = 0x10049,
	SCE_KERNEL_PARTITION_TMP_ID                   = 0x1004B,
	SCE_KERNEL_PARTITION_ROOT_UNCACHE_ID          = 0x1004D,
	SCE_KERNEL_PARTITION_KMP_ID                   = 0x1004F,
	SCE_KERNEL_PARTITION_ROOT_UNCACHE_GPU_GAME_ID = 0x10051,
	SCE_KERNEL_PARTITION_TMP_FS_GAME_ID           = 0x10053,
	SCE_KERNEL_PARTITION_ROOT_TOOL_ID             = 0x10055,
	SCE_KERNEL_PARTITION_ROOT_TOOL_UNCACHE_ID     = 0x10057,
	SCE_KERNEL_PROCESS_BUDGET_KERNEL_ID           = 0x10059,
	SCE_KERNEL_PROCESS_BUDGET_SHELL_ID            = 0x1005B,
	SCE_KERNEL_PROCESS_BUDGET_FULL_GAME_ID        = 0x1005D,
	SCE_KERNEL_RESERVED_GUID_5F                   = 0x1005F,
	SCE_DEPRECATED_EX(SCE_GUID_SYSROOT,                     "use SCE_KERNEL_SYSROOT_ID")                         = SCE_KERNEL_SYSROOT_ID,
	SCE_DEPRECATED_EX(SCE_GUID_GUID_ENTRY_HEAP,             "use SCE_KERNEL_GUID_ENTRY_HEAP_ID")                 = SCE_KERNEL_GUID_ENTRY_HEAP_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_PROCESS_ID,           "use SCE_KERNEL_PROCESS_ID")                         = SCE_KERNEL_PROCESS_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_ADDRESS_SPACE,        "use SCE_KERNEL_ADDRESS_SPACE_ID")                   = SCE_KERNEL_ADDRESS_SPACE_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_ROOT,                   "use SCE_KERNEL_PARTITION_ROOT_ID")                  = SCE_KERNEL_PARTITION_ROOT_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_HEAP,                 "use SCE_KERNEL_HEAP_ID")                            = SCE_KERNEL_HEAP_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_HEAP_UNCACHE,         "use SCE_KERNEL_HEAP_UNCACHE_ID")                    = SCE_KERNEL_HEAP_UNCACHE_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PHYMEM_PART_KERNEL,          "use SCE_KERNEL_PHYMEMPART_ID")                      = SCE_KERNEL_PHYMEMPART_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PHYMEM_PART_TOOL,            "use SCE_KERNEL_PHYMEMPART_TOOL_ID")                 = SCE_KERNEL_PHYMEMPART_TOOL_ID,
	SCE_DEPRECATED_EX(SCE_GUID_DUMMY_PROCESS_GAME,          "use SCE_KERNEL_DUMMY_PROCESS_GAME_ID")              = SCE_KERNEL_DUMMY_PROCESS_GAME_ID,
	SCE_DEPRECATED_EX(SCE_GUID_DUMMY_PROCESS_SYSTEM,        "use SCE_KERNEL_DUMMY_PROCESS_SYSTEM_ID")            = SCE_KERNEL_DUMMY_PROCESS_SYSTEM_ID,
	SCE_DEPRECATED_EX(SCE_GUID_CLEANER_THREAD,              "use SCE_KERNEL_CLEANER_THREAD_ID")                  = SCE_KERNEL_CLEANER_THREAD_ID,
	SCE_DEPRECATED_EX(SCE_GUID_IDLE_THREAD_0,               "use SCE_KERNEL_IDLE_THREAD_0_ID")                   = SCE_KERNEL_IDLE_THREAD_0_ID,
	SCE_DEPRECATED_EX(SCE_GUID_IDLE_THREAD_1,               "use SCE_KERNEL_IDLE_THREAD_1_ID")                   = SCE_KERNEL_IDLE_THREAD_1_ID,
	SCE_DEPRECATED_EX(SCE_GUID_IDLE_THREAD_2,               "use SCE_KERNEL_IDLE_THREAD_2_ID")                   = SCE_KERNEL_IDLE_THREAD_2_ID,
	SCE_DEPRECATED_EX(SCE_GUID_IDLE_THREAD_3,               "use SCE_KERNEL_IDLE_THREAD_3_ID")                   = SCE_KERNEL_IDLE_THREAD_3_ID,
	SCE_DEPRECATED_EX(SCE_GUID_ALL_PROCESS,                 "use SCE_KERNEL_ALL_PROCESS_ID")                     = SCE_KERNEL_ALL_PROCESS_ID,
	SCE_DEPRECATED_EX(SCE_GUID_GLOBAL_WORK_QUEUE,           "use SCE_KERNEL_GLOBAL_WORK_QUEUE_ID")               = SCE_KERNEL_GLOBAL_WORK_QUEUE_ID,
	SCE_DEPRECATED_EX(SCE_GUID_THREAD_ID_SYSTEM_ALL,        "use SCE_KERNEL_THREAD_ID_SYSTEM_ALL_ID")            = SCE_KERNEL_THREAD_ID_SYSTEM_ALL_ID,
	SCE_DEPRECATED_EX(SCE_GUID_THREAD_ID_PROCESS_ALL,       "use SCE_KERNEL_THREAD_ID_PROCESS_ALL_ID")           = SCE_KERNEL_THREAD_ID_PROCESS_ALL_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_HEAP_TOOL,            "use SCE_KERNEL_HEAP_TOOL_ID")                       = SCE_KERNEL_HEAP_TOOL_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_16B,       "use SCE_KERNEL_FIXED_HEAP_16B_ID")                  = SCE_KERNEL_FIXED_HEAP_16B_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_32B,       "use SCE_KERNEL_FIXED_HEAP_32B_ID")                  = SCE_KERNEL_FIXED_HEAP_32B_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_48B,       "use SCE_KERNEL_FIXED_HEAP_48B_ID")                  = SCE_KERNEL_FIXED_HEAP_48B_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_64B,       "use SCE_KERNEL_FIXED_HEAP_64B_ID")                  = SCE_KERNEL_FIXED_HEAP_64B_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_128B,      "use SCE_KERNEL_FIXED_HEAP_128B_ID")                 = SCE_KERNEL_FIXED_HEAP_128B_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_256B,      "use SCE_KERNEL_FIXED_HEAP_256B_ID")                 = SCE_KERNEL_FIXED_HEAP_256B_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_512B,      "use SCE_KERNEL_FIXED_HEAP_512B_ID")                 = SCE_KERNEL_FIXED_HEAP_512B_ID,
	SCE_DEPRECATED_EX(SCE_GUID_KERNEL_FIXED_HEAP_L2_OBJECT, "use SCE_KERNEL_FIXED_HEAP_L2_OBJECT_ID")            = SCE_KERNEL_FIXED_HEAP_L2_OBJECT_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_USER_SHARED,            "use SCE_KERNEL_PARTITION_USER_SHARED_ID")           = SCE_KERNEL_PARTITION_USER_SHARED_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_IO,                     "use SCE_KERNEL_PARTITION_IO_ID")                    = SCE_KERNEL_PARTITION_IO_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_CDRAM,                  "use SCE_KERNEL_PARTITION_CDRAM_ID")                 = SCE_KERNEL_PARTITION_CDRAM_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_TMP,                    "use SCE_KERNEL_PARTITION_TMP_ID")                   = SCE_KERNEL_PARTITION_TMP_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_ROOT_UNCACHE,           "use SCE_KERNEL_PARTITION_ROOT_UNCACHE_ID")          = SCE_KERNEL_PARTITION_ROOT_UNCACHE_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_KMP,                    "use SCE_KERNEL_PARTITION_KMP_ID")                   = SCE_KERNEL_PARTITION_KMP_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_ROOT_UNCACHE_GPU_GAME,  "use SCE_KERNEL_PARTITION_ROOT_UNCACHE_GPU_GAME_ID") = SCE_KERNEL_PARTITION_ROOT_UNCACHE_GPU_GAME_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_TMP_FS_GAME,            "use SCE_KERNEL_PARTITION_TMP_FS_GAME_ID")           = SCE_KERNEL_PARTITION_TMP_FS_GAME_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_ROOT_TOOL,              "use SCE_KERNEL_PARTITION_ROOT_TOOL_ID")             = SCE_KERNEL_PARTITION_ROOT_TOOL_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PART_ROOT_TOOL_UNCACHE,      "use SCE_KERNEL_PARTITION_ROOT_TOOL_UNCACHE_ID")     = SCE_KERNEL_PARTITION_ROOT_TOOL_UNCACHE_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PROCESS_BUDGET_KERNEL,       "use SCE_KERNEL_PROCESS_BUDGET_KERNEL_ID")           = SCE_KERNEL_PROCESS_BUDGET_KERNEL_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PROCESS_BUDGET_SHELL,        "use SCE_KERNEL_PROCESS_BUDGET_SHELL_ID")            = SCE_KERNEL_PROCESS_BUDGET_SHELL_ID,
	SCE_DEPRECATED_EX(SCE_GUID_PROCESS_BUDGET_FULL_GAME,    "use SCE_KERNEL_PROCESS_BUDGET_FULL_GAME_ID")        = SCE_KERNEL_PROCESS_BUDGET_FULL_GAME_ID
	/* Random completely from 0x10061 */
};

typedef struct SceKernelAddrPair { // do not use
	uint32_t addr;             //!< Address
	uint32_t length;           //!< Length
} SceKernelAddrPair;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelAddrPair);

typedef struct SceKernelVARange { // size is 0x8
	uint32_t addr;
	SceSize size;
} SceKernelVARange;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelVARange);

typedef struct SceKernelPARange { // size is 0x8
	uint32_t addr;
	SceSize size;
} SceKernelPARange;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelPARange);

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
VITASDK_BUILD_ASSERT_EQ(0x14, SceKernelPAVector);

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
VITASDK_BUILD_ASSERT_EQ(0x40, SceSharedSecret);

typedef struct SceSelfAuthInfo { // size is 0x90-bytes
	SceUInt64 program_authority_id;
	uint8_t padding[8];
	uint8_t capability[0x20];
	uint8_t attribute[0x20];
	SceSharedSecret secret;
} SceSelfAuthInfo;
VITASDK_BUILD_ASSERT_EQ(0x90, SceSelfAuthInfo);

typedef struct SceAuthInfo { // size is 0x130-bytes
	SceUInt32 unk_0x00;
	SceUInt32 self_type;      // kernel = 0, user = 1, sm = 2
	SceSelfAuthInfo request;
	SceSelfAuthInfo response;
	SceUInt32 media_type;
	SceUInt32 unk_0x12C;
} SceAuthInfo;
VITASDK_BUILD_ASSERT_EQ(0x130, SceAuthInfo);

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
VITASDK_BUILD_ASSERT_EQ(4, SceKernelSpinlock);

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
VITASDK_BUILD_ASSERT_EQ(4, SceKernelRWSpinlock);

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
VITASDK_BUILD_ASSERT_EQ(4, SceKernelIntrStatus);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_TYPES_H_ */
