/**
 * \usergroup{SceFios2Kernel02}
 * \usage{psp2/fios2kernel02.h,SceFios2Kernel_stub}
 */

#ifndef _PSP2_FIOS2KERNEL02_H_
#define _PSP2_FIOS2KERNEL02_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/fios2.h>

#ifdef __cplusplus
extern "C" {
#endif


int sceFiosKernelOverlayAddForProcess02(SceUID pid, SceFiosOverlay *overlay, SceFiosOverlayID *outID);


typedef struct sceFiosKernelOverlayGetList02_opt {
	SceFiosOverlayID *out_ids; //!< Output buffer for overlay IDs; may be NULL only when max_ids is zero.
	SceSize max_ids; //!< Maximum number of overlay IDs to write; must not exceed 128 on FW 3.60.
	SceSize *actual_ids; //!< Optional pointer receiving the total number of matching overlays, including those beyond max_ids.
	SceSize out_ids_buffer_size; //!< Number of bytes copied to out_ids; must not exceed 0x200 on FW 3.60.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} sceFiosKernelOverlayGetList02_opt;
VITASDK_BUILD_ASSERT_EQ(0x18, sceFiosKernelOverlayGetList02_opt); // size is from FW 3.60

typedef struct sceFiosKernelOverlayGetRecommendedScheduler02_opt {
	SceUInt32 reserved[2]; //!< Copied from user memory but not used on FW 3.60.
} sceFiosKernelOverlayGetRecommendedScheduler02_opt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceFiosKernelOverlayGetRecommendedScheduler02_opt); // size is from FW 3.60

typedef struct sceFiosKernelOverlayResolveSync02_opt {
	char *out_path; //!< Resolved path output buffer.
	SceSize max_path; //!< Maximum path length used by the resolver; must be from 1 through 0x400, inclusive.
	SceUInt32 reserved0; //!< Ignored on FW 3.60.
	SceSize out_path_buffer_size; //!< Number of bytes copied to out_path; must not exceed 0x400 on FW 3.60.
	SceUInt32 reserved1[2]; //!< Ignored on FW 3.60.
} sceFiosKernelOverlayResolveSync02_opt;
VITASDK_BUILD_ASSERT_EQ(0x18, sceFiosKernelOverlayResolveSync02_opt); // size is from FW 3.60

typedef struct sceFiosKernelOverlayResolveWithRangeSync02_opt {
	char *out_path; //!< Resolved path output buffer.
	SceSize max_path; //!< Maximum path length used by the resolver; must be from 1 through 0x400, inclusive.
	SceUInt8 min_order; //!< Minimum overlay order to include.
	SceUInt8 max_order; //!< Maximum overlay order to include.
	SceUInt8 reserved0[2]; //!< Ignored on FW 3.60.
	SceUInt32 reserved1; //!< Ignored on FW 3.60.
	SceSize out_path_buffer_size; //!< Number of bytes copied to out_path; must not exceed 0x400 on FW 3.60.
	SceUInt32 reserved2[2]; //!< Ignored on FW 3.60.
} sceFiosKernelOverlayResolveWithRangeSync02_opt;
VITASDK_BUILD_ASSERT_EQ(0x1C, sceFiosKernelOverlayResolveWithRangeSync02_opt); // size is from FW 3.60

/**
 * Gets information about an overlay in a process's table.
 *
 * Copies the complete ::SceFiosOverlay to @p out_overlay. The output buffer must
 * remain valid until this function returns; it is not used afterwards.
 *
 * @param[in]  pid        - Process whose overlay table is queried.
 * @param[in]  id         - Overlay identifier.
 * @param[out] out_overlay - Receives the overlay information.
 *
 * @return 0 on success, or a negative error code.
 */
int sceFiosKernelOverlayGetInfoForProcess02(SceUID pid, SceFiosOverlayID id, SceFiosOverlay *out_overlay);

/**
 * Gets the IDs of overlays whose order is from @p min_order through @p max_order,
 * inclusive.
 *
 * @p opt must be non-NULL. When \c opt->out_ids is non-NULL, \c opt->max_ids must not
 * exceed 128 on FW 3.60. \c opt->actual_ids may be NULL; when supplied it
 * receives the total number of matching overlays, including those beyond
 * \c opt->max_ids.
 * The reserved fields are ignored on FW 3.60.
 *
 * @param[in] pid      - Process whose overlays are enumerated.
 * @param[in] min_order - Minimum overlay order to include.
 * @param[in] max_order - Maximum overlay order to include.
 * @param[in] opt      - Enumeration options and output pointers.
 *
 * @return 0 on success, or an error code.
 */
int sceFiosKernelOverlayGetList02(SceUID pid, SceUInt8 min_order, SceUInt8 max_order, const sceFiosKernelOverlayGetList02_opt *opt);

/**
 * Gets the recommended scheduler index for a partially resolved path.
 *
 * @p opt must be non-NULL. FW 3.60 copies all eight bytes from user memory but
 * does not use their contents. @p partially_resolved_path may be NULL; a
 * non-NULL path must terminate within 0x400 bytes.
 *
 * @param[in] scheduler_count        - Number of available schedulers.
 * @param[in] partially_resolved_path - Optional partially resolved path.
 * @param[in] opt                   - Non-NULL pointer to an 8-byte option block.
 *
 * @return 1 for a host[0-9]: path when scheduler_count is greater than 1,
 *         otherwise 0, or a negative error code when a user-memory copy fails.
 */
int sceFiosKernelOverlayGetRecommendedScheduler02(int scheduler_count, const char *partially_resolved_path, const sceFiosKernelOverlayGetRecommendedScheduler02_opt *opt);

/**
 * Replaces an overlay in a process's table.
 *
 * Validates and copies @p new_value before returning. Keeps the process and
 * overlay IDs, recalculates both path lengths, and moves the entry to its new
 * position in the table if its order changes. @p new_value must remain valid
 * until this function returns; it is not used afterwards.
 *
 * @param[in] pid      - Process whose overlay is replaced.
 * @param[in] id       - Overlay identifier.
 * @param[in] new_value - Replacement overlay configuration.
 *
 * @return 0 on success, or a negative error code.
 */
int sceFiosKernelOverlayModifyForProcess02(SceUID pid, SceFiosOverlayID id, const SceFiosOverlay *new_value);

/**
 * Removes an overlay synchronously from a process's table.
 *
 * @return 0 on success, or a negative error code.
 */
int sceFiosKernelOverlayRemoveForProcess02(SceUID pid, SceFiosOverlayID id);

/**
 * Resolves a path synchronously through a process's overlays.
 *
 * @p resolve_for_write must be 0 for a read or 1 for a write. @p opt must be non-NULL.
 * Its max_path field controls path validation and resolution, while
 * out_path_buffer_size independently controls the final copy to user memory.
 * The reserved fields are ignored on FW 3.60.
 *
 * @param[in] pid             - Process whose overlays are used.
 * @param[in] resolve_for_write - Must be 0 for read resolution or 1 for write resolution.
 * @param[in] in_path          - Path to resolve.
 * @param[in] opt             - Resolution options and output buffer.
 *
 * @return 0 on success, or a negative error code.
 */
int sceFiosKernelOverlayResolveSync02(SceUID pid, int resolve_for_write, const char *in_path, const sceFiosKernelOverlayResolveSync02_opt *opt);

/**
 * Resolves a path through overlays whose order is between \c min_order and
 * \c max_order, inclusive.
 *
 * @p opt must be non-NULL. min_order and max_order are unsigned, and min_order must
 * not exceed max_order. max_path controls path validation and resolution;
 * out_path_buffer_size independently controls the final copy to user memory.
 * The reserved fields are ignored on FW 3.60. If application overlays are
 * disabled for the current thread, the supplied min_order is replaced with 0x80.
 *
 * @param[in]  pid             - Process whose overlays are used.
 * @param[in]  resolve_for_write - Must be 0 for read resolution or 1 for write resolution.
 * @param[in]  in_path          - Path to resolve.
 * @param[in]  opt             - Resolution options and output buffer.
 *
 * @return 0 on success, or an error code.
 */
int sceFiosKernelOverlayResolveWithRangeSync02(SceUID pid, int resolve_for_write, const char *in_path, const sceFiosKernelOverlayResolveWithRangeSync02_opt *opt);

/**
 * Returns whether application overlays are disabled for the current thread.
 *
 * A nonzero state skips orders 0x00 through 0x7F. Privileged overlays
 * with orders 0x80 through 0xFF remain active.
 *
 * @return 0 or 1.
 */
int sceFiosKernelOverlayThreadIsDisabled02(void);

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
int sceFiosKernelOverlayThreadSetDisabled02(int disabled);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FIOS2KERNEL02_H_ */
