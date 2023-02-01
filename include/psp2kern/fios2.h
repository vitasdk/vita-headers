/**
 * \kernelgroup{SceFios2Kernel}
 * \usage{psp2kern/fios2.h,SceFios2KernelForDriver}
 */

#ifndef _PSP2KERN_FIOS2_H_
#define _PSP2KERN_FIOS2_H_

#include <psp2kern/types.h>
#include <psp2common/fios2.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Overlay process file system overlay
 *
 * @param[in]  overlay - Overlay config pointer
 * @param[out] outID   - outID pointer
 *
 * @return     Error code or zero on success
 */
int ksceFiosKernelOverlayAdd(SceFiosOverlay *overlay, SceFiosOverlayID *outID);

/**
 * Overlay process file system overlay
 *
 * @param[in]  pid     - Process id
 * @param[in]  overlay - Overlay config pointer
 * @param[out] outID   - outID pointer
 *
 * @return     Error code or zero on success
 */
int ksceFiosKernelOverlayAddForProcess(SceUID pid, SceFiosOverlay *overlay, SceFiosOverlayID *outID);

/**
 * Remove process file system overlay
 *
 * @param[in] pid - Process id
 * @param[in] id  - Overlay id
 *
 * @return     Error code or zero on success
 */
int ksceFiosKernelOverlayRemoveForProcess(SceUID pid, SceFiosOverlayID id);

/**
 * Resolve process file system overlay with sync
 *
 * @param[in]  pid         - Process id
 * @param[in]  resolveFlag - Some flags
 * @param[in]  inPath      - Path input
 * @param[out] outPath     - Path output
 * @param[in]  maxPath     - Path output max length
 *
 * @return     Error code or zero on success
 */
int ksceFiosKernelOverlayResolveSync(SceUID pid, int resolveFlag, const char *inPath, char *outPath, SceSize maxPath);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_FIOS2_H_ */
