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
	SceUInt8 to_order; //!< Overlay-order bound; ignored on FW 3.60.
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
	int max_ids; //!< Maximum number of overlay IDs to write; a ::SceSize value.
	int actual_ids; //!< Optional user pointer receiving the total match count,
	                //!< including entries beyond max_ids; points to a ::SceSize value.
	SceSize out_ids_buffer_size; //!< Number of bytes copied to the output buffer.
	int reserved1; //!< Ignored on FW 3.60.
	int reserved2; //!< Ignored on FW 3.60.
} SceFiosGetListSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceFiosGetListSyscallArgs); // size is from FW 3.60

int _sceFiosKernelOverlayGetList(SceUID pid, SceUInt8 lo_order_filter, SceUInt8 hi_order_filter, SceFiosGetListSyscallArgs *args);

typedef struct SceFiosGetRecommendedSchedulerSyscallArgs {
	int reserved1; //!< Ignored on FW 3.60.
	int reserved2; //!< Ignored on FW 3.60.
} SceFiosGetRecommendedSchedulerSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x8, SceFiosGetRecommendedSchedulerSyscallArgs); // size is from FW 3.60

/**
 * Gets the recommended scheduler index for a partially resolved path.
 *
 * @param[in] scheduler_count         - Number of available schedulers.
 * @param[in] partially_resolved_path - Partially resolved path.
 * @param[in] args                    - Points to a ::SceFiosGetRecommendedSchedulerSyscallArgs structure.
 *
 * @return 1 for a host[0-9]: path when scheduler_count is greater than 1, otherwise 0.
 */
int _sceFiosKernelOverlayGetRecommendedScheduler(int scheduler_count, const char *partially_resolved_path, SceUInt64 *args);
int _sceFiosKernelOverlayModify(SceFiosKernelOverlayID id, const SceFiosKernelOverlay *new_value);
int _sceFiosKernelOverlayModifyForProcess(SceUID target_process, SceFiosKernelOverlayID id, const SceFiosKernelOverlay *new_value);
int _sceFiosKernelOverlayRemove(SceFiosKernelOverlayID id);
int _sceFiosKernelOverlayRemoveForProcess(SceUID target_process, SceFiosKernelOverlayID id);

typedef struct SceFiosResolveSyncSyscallArgs {
	char *out_path; //!< Resolved path output buffer.
	int max_path; //!< Maximum path length used by the resolver; a ::SceSize value.
	int reserved1; //!< Ignored on FW 3.60.
	int out_path_buffer_size; //!< Number of bytes copied to the output buffer; a ::SceSize value.
	int reserved3; //!< Ignored on FW 3.60.
	int reserved4; //!< Ignored on FW 3.60.
} SceFiosResolveSyncSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x18, SceFiosResolveSyncSyscallArgs); // size is from FW 3.60

int _sceFiosKernelOverlayResolveSync(SceUID pid, int resolve_for_write, const char *in_path, SceFiosResolveSyncSyscallArgs *args);

typedef struct SceFiosResolveWithRangeSyncSyscallArgs {
	char *out_path; //!< Resolved path output buffer.
	int max_path; //!< Maximum path length used by the resolver; a ::SceSize value.
	SceUInt8 lo_order_filter; //!< Minimum value of an overlay's order field to include.
	SceUInt8 hi_order_filter; //!< Maximum value of an overlay's order field to include.
	SceUInt8 reserved1; //!< Ignored on FW 3.60.
	SceUInt8 reserved2; //!< Ignored on FW 3.60.
	int reserved3; //!< Ignored on FW 3.60.
	int out_path_buffer_size; //!< Number of bytes copied to the output buffer; a ::SceSize value.
	int reserved5; //!< Ignored on FW 3.60.
	int reserved6; //!< Ignored on FW 3.60.
} SceFiosResolveWithRangeSyncSyscallArgs;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceFiosResolveWithRangeSyncSyscallArgs); // size is from FW 3.60

/**
 * Resolves a path through overlays within an inclusive order range.
 *
 * @param[in]  pid               - Process whose overlays are used.
 * @param[in]  resolve_for_write - 0 for read resolution, 1 for write resolution.
 * @param[in]  in_path           - Path to resolve.
 * @param[in,out] args           - Resolution options and output buffer.
 *
 * @return Error code or zero on success.
 */
int _sceFiosKernelOverlayResolveWithRangeSync(SceUID pid, int resolve_for_write, const char *in_path, SceFiosResolveWithRangeSyncSyscallArgs *args);
int _sceFiosKernelOverlayThreadIsDisabled(void);
int _sceFiosKernelOverlayThreadSetDisabled(SceInt32 disabled);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FIOS2KERNEL_H_ */
