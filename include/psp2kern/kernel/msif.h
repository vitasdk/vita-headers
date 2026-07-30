/**
 * \kernelgroup{SceMsif}
 * \usage{psp2kern/kernel/msif.h,SceMsifForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_MSIF_H_
#define _PSP2KERN_KERNEL_MSIF_H_

#include <psp2common/kernel/msif.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceMsifGetMsInfo(SceMsInfo *info);

int ksceMsifDisableSlowMode(void);
int ksceMsifEnableSlowMode(void);
int ksceMsifGetSlowModeState(void);
int ksceMsifReadSector(int sector, char *buffer, int nSectors);
int ksceMsifWriteSector(int sector, char *buffer, int nSectors);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_MSIF_H_ */

