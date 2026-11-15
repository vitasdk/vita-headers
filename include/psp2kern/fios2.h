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
 * Resolves a path synchronously through a process's overlays.
 *
 * @p maxPath must be from 1 through 0x400, inclusive. The input's NUL terminator
 * must fall within that many bytes, and @p outPath must provide at least
 * @p maxPath bytes. When application overlays are disabled for the current
 * thread, orders below 0x80 are skipped.
 *
 * @param[in]  pid             - Process whose overlays are used.
 * @param[in]  resolveForWrite - Must be 0 for read resolution or 1 for write resolution.
 * @param[in]  inPath          - Path to resolve.
 * @param[out] outPath         - Resolved path output buffer.
 * @param[in]  maxPath         - Input and output path limit.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceFiosKernelOverlayResolveSync(SceUID pid, int resolveForWrite, const char *inPath, char *outPath, SceSize maxPath);


/**
 * Gets an overlay from the calling process's table.
 *
 * @param[in]  id         - Overlay identifier.
 * @param[out] out_overlay - Receives a copy of the complete overlay.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceFiosKernelOverlayGetInfo(SceFiosOverlayID id, SceFiosOverlay *out_overlay);

/**
 * Gets an overlay from a process's table.
 *
 * Copies the complete 0x258-byte overlay to @p out_overlay. The output buffer
 * must remain valid until this function returns; it is not used afterwards.
 * Access to another process's table requires the appropriate privileges.
 *
 * @param[in]  pid        - Process whose overlay table is queried.
 * @param[in]  id         - Overlay identifier.
 * @param[out] out_overlay - Receives the overlay information.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceFiosKernelOverlayGetInfoForProcess(SceUID pid, SceFiosOverlayID id, SceFiosOverlay *out_overlay);

/**
 * Gets the IDs of overlays whose order is from @p min_order through @p max_order,
 * inclusive.
 *
 * @param[in]  pid           - Process whose overlays are enumerated.
 * @param[in]  min_order      - Minimum value of an overlay's order field to include.
 * @param[in]  max_order      - Maximum value of an overlay's order field to include.
 * @param[out] out_ids        - Overlay ID output buffer, or NULL when @p max_ids is zero.
 * @param[in]  max_ids        - Maximum number of overlay IDs to write.
 * @param[out] actual_ids     - Optional pointer receiving the total number of matching overlays, including those beyond @p max_ids.
 *
 * @return 0 on success, or an error code.
 */
int ksceFiosKernelOverlayGetList(SceUID pid, SceUInt8 min_order, SceUInt8 max_order, SceFiosOverlayID *out_ids, SceSize max_ids, SceSize *actual_ids);

/**
 * Gets the recommended scheduler index for a partially resolved path.
 *
 * @param[in] scheduler_count        - Number of available schedulers.
 * @param[in] partially_resolved_path - Optional partially resolved path.
 *
 * @return 1 for a host[0-9]: path when scheduler_count is greater than 1,
 *         otherwise 0.
 */
int ksceFiosKernelOverlayGetRecommendedScheduler(int scheduler_count, const char *partially_resolved_path);

/**
 * Replaces an overlay in the calling process's table.
 *
 * Validates and copies @p new_value before returning. Keeps the process and
 * overlay IDs and recalculates both path lengths.
 *
 * @param[in] id       - Overlay identifier.
 * @param[in] new_value - Replacement overlay configuration.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceFiosKernelOverlayModify(SceFiosOverlayID id, const SceFiosOverlay *new_value);

/**
 * Replaces an overlay in a process's table.
 *
 * Copies @p new_value before returning. Keep it valid until this function
 * returns; it is not used afterwards. Access to another process's table
 * requires the appropriate privileges.
 *
 * @param[in] pid      - Process whose overlay is replaced.
 * @param[in] id       - Overlay identifier.
 * @param[in] new_value - Replacement overlay configuration.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceFiosKernelOverlayModifyForProcess(SceUID pid, SceFiosOverlayID id, const SceFiosOverlay *new_value);

/**
 * Removes an overlay synchronously from the calling process's table.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceFiosKernelOverlayRemove(SceFiosOverlayID id);

/**
 * Resolves a path through overlays whose order is from @p min_order through
 * @p max_order, inclusive.
 *
 * @p max_path must be from 1 through 0x400, inclusive. The input's NUL terminator
 * must fall within that many bytes, and @p out_path must provide at least
 * @p max_path bytes. If application overlays are disabled for the current
 * thread, the supplied @p min_order is replaced with 0x80.
 *
 * @param[in]  pid             - Process whose overlays are used.
 * @param[in]  resolve_for_write - Must be 0 for read resolution or 1 for write resolution.
 * @param[in]  in_path          - Path to resolve.
 * @param[out] out_path         - Resolved path output buffer.
 * @param[in]  max_path         - Output buffer size.
 * @param[in]  min_order        - Minimum value of an overlay's order field to include.
 * @param[in]  max_order        - Maximum value of an overlay's order field to include.
 *
 * @return 0 on success, or an error code.
 */
int ksceFiosKernelOverlayResolveWithRangeSync(SceUID pid, int resolve_for_write, const char *in_path, char *out_path, SceSize max_path, SceUInt8 min_order, SceUInt8 max_order);

/**
 * Returns whether application overlays are disabled for the current thread.
 *
 * A nonzero state skips orders 0x00 through 0x7F. Privileged overlays
 * with orders 0x80 through 0xFF remain active.
 *
 * @return 0 or 1.
 */
int ksceFiosKernelOverlayThreadIsDisabled(void);

/**
 * Enables or disables application overlays for the current thread.
 *
 * Any nonzero value skips orders 0x00 through 0x7F until this function is
 * called with zero or the thread exits. Privileged orders 0x80 through 0xFF
 * remain active.
 *
 * @param[in] disabled - Zero to enable application overlays, or any nonzero value to disable them.
 *
 * @return 0 on success, or -1 if the thread-local state is unavailable.
 */
int ksceFiosKernelOverlayThreadSetDisabled(int disabled);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_FIOS2_H_ */
