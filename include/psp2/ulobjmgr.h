/**
 * \usergroup{SceUlobjMgr}
 * \usage{psp2/ulobjmgr.h,SceUlobjMgr_stub}
 */

#ifndef _PSP2_ULOBJMGR_H_
#define _PSP2_ULOBJMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Validate a libult protocol revision.
 *
 * FW 3.60 only validates the value; it does not keep any revision state.
 *
 * @param[in] revision Protocol revision. It must be at least 0x01800000, and
 * its low 16 bits must not all be zero.
 *
 * @return 0 on success, or ::SCE_KERNEL_ERROR_INVALID_ARGUMENT if the
 * revision is invalid.
 */
int _sceUlobjMgrRegisterLibultProtocolRevision(SceUInt32 revision);

/**
 * Create the calling process's shared user-level object registry.
 *
 * Only one registry may exist per process. FW 3.60 maps the same allocation
 * into user and kernel address spaces. The allocation contains a 16-byte
 * header followed by one 4-byte entry for each object. The allocation size is
 * rounded up to a multiple of 0x1000 bytes. SceFiber requests 0x3FFC entries,
 * producing a 0x10000-byte allocation.
 *
 * @param[in] object_capacity Maximum number of registered objects. The valid
 * range is 1 through 0x02000000. FW 3.60 does not reject zero, but its registry
 * initializer underflows and writes beyond the allocation.
 * @param[in] sdk_version SDK version associated with the registry. FW 3.60
 * accepts values through 0x03600000.
 * @param[out] registry Receives the base address of the user-space registry
 * mapping; must be non-NULL. If writing this output fails, the registry is
 * destroyed before the function returns.
 *
 * @warning FW 3.60 tracks 16 process registries and does not safely reject a
 * seventeenth simultaneous registration when every slot is occupied.
 *
 * @return 0 on success, ::SCE_KERNEL_ERROR_UNSUP if \a sdk_version is newer
 * than 0x03600000, ::SCE_KERNEL_ERROR_NO_MEMORY if \a object_capacity is
 * greater than 0x02000000 or the mappings cannot be allocated,
 * ::SCE_KERNEL_ERROR_ALREADY_REGISTERED if the process already owns a
 * registry, or another negative kernel error.
 */
int _sceUlobjMgrStartSupportingUserlevelObject(SceUInt32 object_capacity, SceUInt32 sdk_version, void **registry);

/**
 * Destroy the calling process's shared user-level object registry.
 *
 * Process exit and kill handlers also destroy the registry if the terminating
 * process still has one.
 *
 * @return 0 on success, or ::SCE_KERNEL_ERROR_INVALID_PID if the calling
 * process has no registry.
 */
int _sceUlobjMgrStopSupportingUserlevelObject(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_ULOBJMGR_H_ */
