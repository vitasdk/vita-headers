/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/address_space.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_ADDRESS_SPACE_H_
#define _PSP2KERN_KERNEL_SYSMEM_ADDRESS_SPACE_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2kern/kernel/sysclib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the physical address of a given virtual address
 *
 * @param[in]  va - The virtual address
 * @param[out] pa - The physical address
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelVAtoPA(const void *va, uintptr_t *pa);

/**
 * Get the physical address range of a given virtual address range
 *
 * @param[in]  va_range  - The virtual address range
 * @param[out] pa_range - The vector of physical addresses
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelVARangeToPARange(const SceKernelVARange *va_range, SceKernelPARange *pa_range);

/**
 * Get the physical address list of a given virtual address range
 *
 * @param[in]  va_range  - The virtual address range
 * @param[out] pa_vector - The vector of physical addresses
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelVARangeToPAVector(const SceKernelVARange *va_range, SceKernelPAVector *pa_vector);

typedef struct SceKernelProcessContext {
	SceUInt32 TTBR1;
	SceUInt32 DACR;
	SceUInt32 CONTEXTIDR;
} SceKernelProcessContext;
VITASDK_BUILD_ASSERT_EQ(0xC, SceKernelProcessContext);


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


#if defined(SCE_SDK_VERSION) && SCE_SDK_VERSION <= 0x1692000
int ksceKernelSwitchVmaForPid(SceUID pid);
#endif


/* For backwards compatibility */

#define ksceKernelGetPidContext ksceKernelProcessGetContext
#define ksceKernelSwitchPidContext ksceKernelProcessSwitchContext
#define ksceKernelGetPaddr(va, pa) ksceKernelVAtoPA(va, pa)
#define ksceKernelGetPaddrList(input, list) ksceKernelVARangeToPAVector((const SceKernelVARange *)input, list)

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
 * @param      context  The context, can be from ::ksceKernelCpuSaveContext
 */
static inline SceInt32 ksceKernelCpuRestoreContext(const SceKernelProcessContext *context)
{
	return ksceKernelProcessSwitchContext(context, NULL);
}


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_ADDRESS_SPACE_H_ */
