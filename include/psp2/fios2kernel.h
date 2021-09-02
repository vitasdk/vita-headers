/**
 * \usergroup{SceFios2Kernel}
 * \usage{psp2/fios2kernel.h,SceFios2Kernel_stub}
 */


#ifndef _PSP2_FIOS2KERNEL_H_
#define _PSP2_FIOS2KERNEL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t SceFiosKernelOverlayDH;
typedef int32_t SceFiosKernelOverlayID;

// missing structs
typedef struct SceFiosKernelOverlay SceFiosKernelOverlay;
typedef struct SceFiosNativeStat SceFiosNativeStat;
typedef struct SceFiosNativeDirEntry SceFiosNativeDirEntry;

int _sceFiosKernelOverlayAdd(const SceFiosKernelOverlay *overlay, SceFiosKernelOverlayID *out_id);
int _sceFiosKernelOverlayAddForProcess(SceUID target_process, const SceFiosKernelOverlay *overlay, SceFiosKernelOverlayID *out_id);
int _sceFiosKernelOverlayDHChstatSync(SceFiosKernelOverlayDH dh, const SceFiosNativeStat *new_stat, unsigned int cbit);
int _sceFiosKernelOverlayDHCloseSync(SceFiosKernelOverlayDH dh);

typedef struct SceFiosDHOpenSyncSyscallArgs {
	SceUInt8 to_order;
	int padding[2];
} SceFiosDHOpenSyncSyscallArgs;

int _sceFiosKernelOverlayDHOpenSync(SceFiosKernelOverlayDH *out_dh, const char *path, SceUInt8 from_order, SceFiosDHOpenSyncSyscallArgs *args);
int _sceFiosKernelOverlayDHReadSync(SceFiosKernelOverlayDH dh, SceFiosNativeDirEntry *out_entry);
int _sceFiosKernelOverlayDHStatSync(SceFiosKernelOverlayDH dh, SceFiosNativeStat *out_stat);
int _sceFiosKernelOverlayDHSyncSync(SceFiosKernelOverlayDH dh, int flag);
int _sceFiosKernelOverlayGetInfo(SceFiosKernelOverlayID id, SceFiosKernelOverlay *out_overlay);
int _sceFiosKernelOverlayGetInfoForProcess(SceUID target_process, SceFiosKernelOverlayID id, SceFiosKernelOverlay *out_overlay);

typedef struct SceFiosGetListSyscallArgs {
	SceFiosKernelOverlayID *out_ids;
	int data_0x04;
	int data_0x08;
	SceSize data_0x0C;
	int data_0x10;
	int data_0x14;
} SceFiosGetListSyscallArgs;

int _sceFiosKernelOverlayGetList(SceUID pid, SceUInt8 min_order, SceUInt8 max_order, SceFiosGetListSyscallArgs *args);
int _sceFiosKernelOverlayGetRecommendedScheduler(int avail, const char *partially_resolved_path, SceUInt64 *a3);
int _sceFiosKernelOverlayModify(SceFiosKernelOverlayID id, const SceFiosKernelOverlay *new_value);
int _sceFiosKernelOverlayModifyForProcess(SceUID target_process, SceFiosKernelOverlayID id, const SceFiosKernelOverlay *new_value);
int _sceFiosKernelOverlayRemove(SceFiosKernelOverlayID id);
int _sceFiosKernelOverlayRemoveForProcess(SceUID target_process, SceFiosKernelOverlayID id);

typedef struct SceFiosResolveSyncSyscallArgs {
	char *out_path;
	int data_0x04;
	int data_0x08;
	int data_0x0C;
	int data_0x10;
	int data_0x14;
} SceFiosResolveSyncSyscallArgs;

int _sceFiosKernelOverlayResolveSync(SceUID pid, int resolve_flag, const char *in_path, SceFiosResolveSyncSyscallArgs *args);

typedef struct SceFiosResolveWithRangeSyncSyscallArgs {
	char *out_path;
	int data_0x04;
	SceUInt8 data_0x08;
	SceUInt8 data_0x09;
	int data_0x0C;
	int data_0x10;
	int data_0x14;
} SceFiosResolveWithRangeSyncSyscallArgs;

int _sceFiosKernelOverlayResolveWithRangeSync(SceUID pid, int resolve_flag, const char *in_path, SceFiosResolveWithRangeSyncSyscallArgs *args);
int _sceFiosKernelOverlayThreadIsDisabled(void);
int _sceFiosKernelOverlayThreadSetDisabled(SceInt32 disabled);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FIOS2KERNEL_H_ */
