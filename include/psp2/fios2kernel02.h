/**
 * \kernelgroup{SceFios2Kernel}
 * \usage{psp2/fios2kernel02.h,SceFios2Kernel}
 */

#ifndef _PSP2_FIOS2KERNEL02_H_
#define _PSP2_FIOS2KERNEL02_H_

#include <psp2kern/types.h>
#include <psp2common/fios2.h>

#ifdef __cplusplus
extern "C" {
#endif


int sceFiosKernelOverlayAddForProcess02(SceUID pid, SceFiosOverlay *overlay, SceFiosOverlayID *outID);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FIOS2KERNEL02_H_ */
