/**
 * \kernelgroup{SceFios2Kernel}
 * \usage{psp2kern/fios2.h,SceFios2KernelForDriver_stub}
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
 * @param[in]  pid             - Process id
 * @param[in]  resolveForWrite - 0 for read resolution, 1 for write resolution
 * @param[in]  inPath          - Path input
 * @param[out] outPath         - Path output
 * @param[in]  maxPath         - Path output max length
 *
 * @return     Error code or zero on success
 */
int ksceFiosKernelOverlayResolveSync(SceUID pid, int resolveForWrite, const char *inPath, char *outPath, SceSize maxPath);


int ksceFiosKernelOverlayGetInfo(SceFiosOverlayID id, SceFiosOverlay *outOverlay);
int ksceFiosKernelOverlayGetInfoForProcess(SceUID pid, SceFiosOverlayID id, SceFiosOverlay *overlay);

/**
 * Gets the overlay IDs in an inclusive order range.
 *
 * @param[in]  pid           - Process whose overlays are enumerated.
 * @param[in]  loOrderFilter - Minimum value of an overlay's order field to include; treated as a ::SceUInt8 value.
 * @param[in]  hiOrderFilter - Maximum value of an overlay's order field to include; treated as a ::SceUInt8 value.
 * @param[out] outIDs        - Overlay ID output buffer, or NULL when @p maxIDs is zero.
 * @param[in]  maxIDs        - Maximum number of overlay IDs to write.
 * @param[out] actualIDs     - Optional pointer receiving the total match count, including entries beyond @p maxIDs.
 *
 * @return Error code or zero on success.
 */
int ksceFiosKernelOverlayGetList(SceUID pid, char loOrderFilter, char hiOrderFilter, SceFiosOverlayID *outIDs, size_t maxIDs, size_t *actualIDs);

/**
 * Gets the recommended scheduler index for a partially resolved path.
 *
 * @param[in] schedulerCount        - Number of available schedulers.
 * @param[in] partiallyResolvedPath - Partially resolved path.
 *
 * @return 1 for a host[0-9]: path when schedulerCount is greater than 1, otherwise 0.
 */
int ksceFiosKernelOverlayGetRecommendedScheduler(int schedulerCount, char *partiallyResolvedPath);
int ksceFiosKernelOverlayModify(SceFiosOverlayID id, const SceFiosOverlay *newValue);
int ksceFiosKernelOverlayModifyForProcess(SceUID pid, SceFiosOverlayID id, const SceFiosOverlay *newValue);
int ksceFiosKernelOverlayRemove(SceFiosOverlayID id);

/**
 * Resolves a path through overlays within an inclusive order range.
 *
 * @param[in]  pid             - Process whose overlays are used.
 * @param[in]  resolveForWrite - 0 for read resolution, 1 for write resolution.
 * @param[in]  inPath          - Path to resolve.
 * @param[out] outPath         - Resolved path output buffer.
 * @param[in]  maxPath         - Output buffer size.
 * @param[in]  loOrderFilter   - Minimum value of an overlay's order field to include; treated as a ::SceUInt8 value.
 * @param[in]  hiOrderFilter   - Maximum value of an overlay's order field to include; treated as a ::SceUInt8 value.
 *
 * @return Error code or zero on success.
 */
int ksceFiosKernelOverlayResolveWithRangeSync(SceUID pid, int resolveForWrite, const char *inPath, char *outPath, size_t maxPath, char loOrderFilter, char hiOrderFilter);
int ksceFiosKernelOverlayThreadIsDisabled(void);
int ksceFiosKernelOverlayThreadSetDisabled(int value);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_FIOS2_H_ */
