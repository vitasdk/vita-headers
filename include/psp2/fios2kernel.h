/**
 * \usergroup{SceFios2Kernel}
 * \usage{psp2/fios2kernel.h,SceFios2Kernel_stub}
 */


#ifndef _PSP2_FIOS2KERNEL_H_
#define _PSP2_FIOS2KERNEL_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t SceFiosKernelOverlayDH;
VITASDK_BUILD_ASSERT_EQ(4, SceFiosKernelOverlayDH);
typedef int32_t SceFiosKernelOverlayID;
VITASDK_BUILD_ASSERT_EQ(4, SceFiosKernelOverlayID);

// missing structs
typedef struct SceFiosKernelOverlay SceFiosKernelOverlay;
typedef struct SceFiosNativeStat SceFiosNativeStat;
typedef struct SceFiosNativeDirEntry SceFiosNativeDirEntry;

int _sceFiosKernelOverlayAdd(const SceFiosKernelOverlay *overlay, SceFiosKernelOverlayID *out_id);
int _sceFiosKernelOverlayAddForProcess(SceUID target_process, const SceFiosKernelOverlay *overlay, SceFiosKernelOverlayID *out_id);
int _sceFiosKernelOverlayDHChstatSync(SceFiosKernelOverlayDH dh, const SceFiosNativeStat *new_stat, unsigned int cbit);
int _sceFiosKernelOverlayDHCloseSync(SceFiosKernelOverlayDH dh);

typedef struct SceFiosDHOpenSyncSyscallArgs {
	SceUInt8 to_order; //!< Maximum overlay order to include. On FW 3.60, the function returns an unsupported-operation error before using this value.
	int padding[2]; //!< Ignored on FW 3.60.
} SceFiosDHOpenSyncSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0xC, SceFiosDHOpenSyncSyscallArgs); // size is from FW 3.60

int _sceFiosKernelOverlayDHOpenSync(SceFiosKernelOverlayDH *out_dh, const char *path, SceUInt8 from_order, SceFiosDHOpenSyncSyscallArgs *args);
int _sceFiosKernelOverlayDHReadSync(SceFiosKernelOverlayDH dh, SceFiosNativeDirEntry *out_entry);
int _sceFiosKernelOverlayDHStatSync(SceFiosKernelOverlayDH dh, SceFiosNativeStat *out_stat);
int _sceFiosKernelOverlayDHSyncSync(SceFiosKernelOverlayDH dh, int flag);
int _sceFiosKernelOverlayGetInfo(SceFiosKernelOverlayID id, SceFiosKernelOverlay *out_overlay);
int _sceFiosKernelOverlayGetInfoForProcess(SceUID target_process, SceFiosKernelOverlayID id, SceFiosKernelOverlay *out_overlay);

typedef struct SceFiosGetListSyscallArgs {
	SceFiosKernelOverlayID *out_ids; //!< Output buffer for overlay IDs; may be NULL only when max_ids is zero.
	int max_ids; //!< Maximum number of overlay IDs to write. Value of type ::SceSize; must not exceed 128 on FW 3.60.
	int actual_ids; //!< Optional pointer receiving the total number of matching overlays, including those beyond max_ids. Declared as an int for backwards compatibility; points to a ::SceSize value.
	SceSize out_ids_buffer_size; //!< Number of bytes copied to out_ids; must not exceed 0x200 on FW 3.60.
	int reserved[2]; //!< Ignored on FW 3.60.
} SceFiosGetListSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceFiosGetListSyscallArgs); // size is from FW 3.60

int _sceFiosKernelOverlayGetList(SceUID pid, SceUInt8 min_order, SceUInt8 max_order, SceFiosGetListSyscallArgs *args);

typedef struct SceFiosGetRecommendedSchedulerSyscallArgs {
	SceUInt32 reserved[2]; //!< Copied from user memory but not used on FW 3.60.
} SceFiosGetRecommendedSchedulerSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceFiosGetRecommendedSchedulerSyscallArgs); // size is from FW 3.60

/**
 * Gets the recommended scheduler index for a partially resolved path.
 *
 * @param[in] scheduler_count         - Number of available schedulers.
 * @param[in] partially_resolved_path - Optional partially resolved path.
 * @param[in] args                    - Non-NULL pointer to an 8-byte block. Its
 *                                      contents are unused on FW 3.60. Still
 *                                      declared as a ::SceUInt64 pointer for
 *                                      backwards compatibility; points to a
 *                                      ::SceFiosGetRecommendedSchedulerSyscallArgs structure.
 *
 * @return 1 for a host[0-9]: path when scheduler_count is greater than 1,
 *         otherwise 0, or a negative error code when a user-memory copy fails.
 */
int _sceFiosKernelOverlayGetRecommendedScheduler(int scheduler_count, const char *partially_resolved_path, SceUInt64 *args);
int _sceFiosKernelOverlayModify(SceFiosKernelOverlayID id, const SceFiosKernelOverlay *new_value);
int _sceFiosKernelOverlayModifyForProcess(SceUID target_process, SceFiosKernelOverlayID id, const SceFiosKernelOverlay *new_value);
int _sceFiosKernelOverlayRemove(SceFiosKernelOverlayID id);
int _sceFiosKernelOverlayRemoveForProcess(SceUID target_process, SceFiosKernelOverlayID id);

typedef struct SceFiosResolveSyncSyscallArgs {
	char *out_path; //!< Resolved path output buffer.
	int max_path; //!< Maximum path length used by the resolver. Value of type ::SceSize; must be from 1 through 0x400, inclusive.
	int reserved0; //!< Ignored on FW 3.60.
	int out_path_buffer_size; //!< Number of bytes copied to out_path. Value of type ::SceSize; must not exceed 0x400.
	int reserved1[2]; //!< Ignored on FW 3.60.
} SceFiosResolveSyncSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceFiosResolveSyncSyscallArgs); // size is from FW 3.60

/**
 * Resolves a path synchronously through a process's overlays.
 *
 * @p args must be non-NULL. Its max_path field controls input validation and path
 * resolution, while out_path_buffer_size independently controls the final
 * copy to user memory. The reserved fields are ignored on FW 3.60.
 *
 * @param[in]     pid               - Process whose overlays are used.
 * @param[in]     resolve_for_write - Must be 0 for read resolution or 1 for write resolution.
 * @param[in]     in_path           - Path to resolve.
 * @param[in,out] args              - Resolution options and output buffer.
 *
 * @return 0 on success, or a negative error code.
 */
int _sceFiosKernelOverlayResolveSync(SceUID pid, int resolve_for_write, const char *in_path, SceFiosResolveSyncSyscallArgs *args);

typedef struct SceFiosResolveWithRangeSyncSyscallArgs {
	char *out_path; //!< Resolved path output buffer.
	int max_path; //!< Maximum path length used by the resolver. Value of type ::SceSize; must be from 1 through 0x400, inclusive.
	SceUInt8 min_order; //!< Minimum overlay order to include.
	SceUInt8 max_order; //!< Maximum overlay order to include.
	SceUInt8 reserved0[2]; //!< Ignored on FW 3.60.
	int reserved1; //!< Ignored on FW 3.60.
	int out_path_buffer_size; //!< Number of bytes copied to out_path. Value of type ::SceSize; must not exceed 0x400.
	int reserved2[2]; //!< Ignored on FW 3.60.
} SceFiosResolveWithRangeSyncSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceFiosResolveWithRangeSyncSyscallArgs); // size is from FW 3.60

/**
 * Resolves a path through overlays whose order is between \c min_order and
 * \c max_order, inclusive.
 *
 * @p args must be non-NULL. min_order and max_order are unsigned, and min_order
 * must not exceed max_order. max_path controls path validation and resolution;
 * out_path_buffer_size independently controls the final copy to user memory.
 * The reserved fields are ignored on FW 3.60. If application overlays are
 * disabled for the current thread, the supplied min_order is replaced with 0x80.
 *
 * @param[in]  pid               - Process whose overlays are used.
 * @param[in]  resolve_for_write - Must be 0 for read resolution or 1 for write resolution.
 * @param[in]  in_path           - Path to resolve.
 * @param[in,out] args           - Resolution options and output buffer.
 *
 * @return 0 on success, or an error code.
 */
int _sceFiosKernelOverlayResolveWithRangeSync(SceUID pid, int resolve_for_write, const char *in_path, SceFiosResolveWithRangeSyncSyscallArgs *args);
int _sceFiosKernelOverlayThreadIsDisabled(void);
int _sceFiosKernelOverlayThreadSetDisabled(SceInt32 disabled);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FIOS2KERNEL_H_ */
