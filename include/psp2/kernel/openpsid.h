/**
 * \usergroup{SceOpenPsid}
 * \usage{psp2/kernel/openpsid.h,SceLibKernel_stub}
 */


#ifndef _PSP2_KERNEL_OPENPSID_H_
#define _PSP2_KERNEL_OPENPSID_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelOpenPsId {
	char id[16];
} SceKernelOpenPsId;

int sceKernelGetOpenPsId(SceKernelOpenPsId *id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_OPENPSID_H_ */

