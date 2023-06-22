/**
 * \usergroup{SceOpenPsid}
 * \usage{psp2/kernel/openpsid.h,SceLibKernel_stub}
 */


#ifndef _PSP2_KERNEL_OPENPSID_H_
#define _PSP2_KERNEL_OPENPSID_H_

#include <vitasdk/build_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelOpenPsId {
	char id[16];
} SceKernelOpenPsId;
VITASDK_BUILD_ASSERT_EQ(0x10, SceKernelOpenPsId);

int sceKernelGetOpenPsId(SceKernelOpenPsId *id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_OPENPSID_H_ */

