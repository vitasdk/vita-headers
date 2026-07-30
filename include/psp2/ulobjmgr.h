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
 * @param[in] revision - Protocol revision. FW 3.60 requires a value greater
 * than or equal to 0x01800000 with a nonzero low 16-bit component.
 *
 * @return 0 on success, or the bit pattern of a negative ::SceInt32 error
 * code.
 */
SceUInt32 _sceUlobjMgrRegisterLibultProtocolRevision(SceUInt32 revision);

/**
 * Create the calling process's shared user-level object registry.
 *
 * @param[in] object_capacity - Maximum number of registry object slots.
 * FW 3.60 rejects values greater than 0x02000000.
 * @param[in] sdk_ver - SDK version. FW 3.60 accepts values through 0x03600000.
 * @param[out] p_object_table_address - Receives the 32-bit user-space address
 * of the shared object registry.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceUlobjMgrStartSupportingUserlevelObject(SceUInt32 object_capacity, SceUInt32 sdk_ver, SceUInt32 *p_object_table_address);

/**
 * Destroy the calling process's shared user-level object registry.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceUlobjMgrStopSupportingUserlevelObject(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_ULOBJMGR_H_ */
