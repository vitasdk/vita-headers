/**
 * \kernelgroup{SceSdif}
 * \usage{psp2kern/lowio/sdif.h,SceSdifForDriver}
 */

#ifndef _PSP2KERN_LOWIO_SDIF_H_
#define _PSP2KERN_LOWIO_SDIF_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceSdifDeviceIndex {
	SCE_SDIF_DEVICE_EMMC = 0x0,
	SCE_SDIF_DEVICE_GC   = 0x1,
	SCE_SDIF_DEVICE_SDIO = 0x2,
	SCE_SDIF_DEVICE_SD   = 0x3,
} SceSdifDeviceIndex;

typedef enum SceSdifDeviceType {
	SCE_SDIF_DEVICE_TYPE_INVALID = 0x0,
	SCE_SDIF_DEVICE_TYPE_MMC     = 0x1,
	SCE_SDIF_DEVICE_TYPE_SD      = 0x2,
	SCE_SDIF_DEVICE_TYPE_SDIO    = 0x3,
} SceSdifDeviceType;

typedef void* SceSdifDeviceContext;

SceSdifDeviceContext* ksceSdifGetSdContextPartValidateMmc(SceSdifDeviceIndex dev_index);
int ksceSdifInitializeMmcDevice(SceSdifDeviceIndex dev_index, SceSdifDeviceContext* dev_ctx);
int ksceSdifWriteCmd56(SceSdifDeviceContext* dev_ctx, const void* buf, SceSize size);
int ksceSdifReadCmd56(SceSdifDeviceContext* dev_ctx, void* buf, SceSize size); 

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_SDIF_H_ */
