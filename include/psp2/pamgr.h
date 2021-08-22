/**
 * \kernelgroup{ScePamgr}
 * \usage{psp2/pamgr.h,ScePamgr_stub}
 */


#ifndef _PSP2_PAMGR_H_
#define _PSP2_PAMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// missing structs
typedef struct SceKernelPaTraceBufferParam SceKernelPaTraceBufferParam;
typedef struct SceKernelPaGpuSampledData SceKernelPaGpuSampledData;
typedef struct SceKernelPaGpuTraceParam SceKernelPaGpuTraceParam;
typedef struct SceKernelPaCounterTraceParam SceKernelPaCounterTraceParam;
typedef struct SceKernelPaArmTraceParam SceKernelPaArmTraceParam;

SceSize sceKernelPaGetTraceBufferSize(SceUInt32 type);
SceUInt32 sceKernelPaGetIoBaseAddress(void);
SceUInt32 sceKernelPaGetTimebaseFrequency(void);
SceUInt32 sceKernelPaGetTraceBufferStatus(void);
SceUInt32 sceKernelPaGetWritePointer(void);
SceUInt64 sceKernelPaGetTimebaseValue(void);
int _sceKernelPaAddArmTraceByKey(const int key, const SceKernelPaArmTraceParam *param);
int _sceKernelPaAddCounterTraceByKey(const int key, const SceKernelPaCounterTraceParam *param);
int _sceKernelPaAddGpuTraceByKey(const int key, const SceKernelPaGpuTraceParam *param);
int _sceKernelPaGetGpuSampledData(SceKernelPaGpuSampledData *data);
int _sceKernelPaSetupTraceBufferByKey(const int key, const SceKernelPaTraceBufferParam *param);
int sceKernelPaInsertBookmark(SceUInt32 fifo, SceUInt32 channel, SceUInt32 data);
int sceKernelPaRegister(void);
int sceKernelPaRemoveArmTraceByKey(const int key);
int sceKernelPaRemoveCounterTraceByKey(const int key);
int sceKernelPaRemoveGpuTraceByKey(const int key);
int sceKernelPaSetBookmarkChannelEnableByKey(const int key, SceUInt32 fifo, SceUInt32 mask);
int sceKernelPaStartByKey(const int key);
int sceKernelPaStopByKey(const int key);
int sceKernelPaUnregister(const int key);
int sceKernelPerfArmPmonClose(void);
int sceKernelPerfArmPmonOpen(void);
int sceKernelPerfArmPmonReset(SceUID threadId);
int sceKernelPerfArmPmonSelectEvent(SceUID threadId, SceUInt32 counter, SceUInt8 eventCode);
int sceKernelPerfArmPmonSetCounterValue(SceUID threadId, SceUInt32 counter, SceUInt32 value);
int sceKernelPerfArmPmonStart(SceUID threadId);
int sceKernelPerfArmPmonStop(SceUID threadId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PAMGR_H_ */
