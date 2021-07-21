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

int _sceFiosKernelOverlayAdd(const SceFiosKernelOverlay *pOverlay, SceFiosKernelOverlayID *pOutID);
int _sceFiosKernelOverlayAddForProcess(SceUID targetProcess, const SceFiosKernelOverlay *pOverlay, SceFiosKernelOverlayID *pOutID);
int _sceFiosKernelOverlayDHChstatSync(SceFiosKernelOverlayDH dh, const SceFiosNativeStat *pNewStat, unsigned int cbit);
int _sceFiosKernelOverlayDHCloseSync(SceFiosKernelOverlayDH dh);
int _sceFiosKernelOverlayDHOpenSync(SceFiosKernelOverlayDH *pOutDH, const char *pPath, SceUInt8 fromOrder, SceUInt8 toOrder);
int _sceFiosKernelOverlayDHReadSync(SceFiosKernelOverlayDH dh, SceFiosNativeDirEntry *pOutEntry);
int _sceFiosKernelOverlayDHStatSync(SceFiosKernelOverlayDH dh, SceFiosNativeStat *pOutStat);
int _sceFiosKernelOverlayDHSyncSync(SceFiosKernelOverlayDH dh, int flag);
int _sceFiosKernelOverlayGetInfo(SceFiosKernelOverlayID id, SceFiosKernelOverlay *pOutOverlay);
int _sceFiosKernelOverlayGetInfoForProcess(SceUID targetProcess, SceFiosKernelOverlayID id, SceFiosKernelOverlay *pOutOverlay);
int _sceFiosKernelOverlayGetList(SceUID pid, SceUInt8 minOrder, SceUInt8 maxOrder, SceFiosKernelOverlayID *pOutIDs);
int _sceFiosKernelOverlayGetRecommendedScheduler(int avail, const char *pPartiallyResolvedPath);
int _sceFiosKernelOverlayModify(SceFiosKernelOverlayID id, const SceFiosKernelOverlay *pNewValue);
int _sceFiosKernelOverlayModifyForProcess(SceUID targetProcess, SceFiosKernelOverlayID id, const SceFiosKernelOverlay *pNewValue);
int _sceFiosKernelOverlayRemove(SceFiosKernelOverlayID id);
int _sceFiosKernelOverlayRemoveForProcess(SceUID targetProcess, SceFiosKernelOverlayID id);
int _sceFiosKernelOverlayResolveSync(SceUID pid, int resolveFlag, const char *pInPath, char *pOutPath);
int _sceFiosKernelOverlayResolveWithRangeSync(SceUID pid, int resolveFlag, const char *pInPath, char *pOutPath);
int _sceFiosKernelOverlayThreadIsDisabled(void);
int _sceFiosKernelOverlayThreadSetDisabled(SceInt32 disabled);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FIOS2KERNEL_H_ */
