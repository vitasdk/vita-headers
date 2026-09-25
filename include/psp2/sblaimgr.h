/**
 * \usergroup{SceSblAimgr}
 * \usage{psp2/sblaimgr.h,SceSblSsMgr_stub}
 */

#ifndef _PSP2_SBLAIMGR_H_
#define _PSP2_SBLAIMGR_H_

#include <psp2/types.h>
#include <psp2common/sblssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Copy the console's OpenPSID to user memory.
 *
 * This is the underlying export called by ::sceKernelGetOpenPsId.
 *
 * @param[out] open_ps_id - Required output for the 16-byte OpenPSID.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceKernelGetOpenPsId(SceOpenPsId *open_ps_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLAIMGR_H_ */
