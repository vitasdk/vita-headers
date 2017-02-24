/**
 * \kernelgroup{SceSblAuthMgr}
 * \usage{psp2kern/sblauthmgr.h,-lSceSblAuthMgrForKernel_stub}
 */


#ifndef _PSP2_KERNEL_SBLAUTHMGR_H_
#define _PSP2_KERNEL_SBLAUTHMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceSblAuthMgrClearDmac5Key(int slot_id, int val);
int ksceSblAuthMgrSetDmac5Key(const void *key, size_t keylen, int slot_id, int key_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SBLAUTHMGR_H_ */

