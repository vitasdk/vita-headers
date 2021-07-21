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

SceSize sceKernelPaGetTraceBufferSize(SceUInt32 type);

SceUInt32 sceKernelPaGetIoBaseAddress(void);
SceUInt32 sceKernelPaGetTimebaseFrequency(void);
SceUInt32 sceKernelPaGetTraceBufferStatus(void);
SceUInt32 sceKernelPaGetWritePointer(void);
SceUInt64 sceKernelPaGetTimebaseValue(void);

int _sceKernelPaAddArmTrace(const SceKernelPaArmTraceParam *param);
int _sceKernelPaAddArmTraceByKey(const int key, const SceKernelPaArmTraceParam *param);
int _sceKernelPaAddCounterTrace(const SceKernelPaCounterTraceParam *param);
int _sceKernelPaAddCounterTraceByKey(const int key, const SceKernelPaCounterTraceParam *param);
int _sceKernelPaAddGpuTrace(const SceKernelPaGpuTraceParam *param);
int _sceKernelPaAddGpuTraceByKey(const int key, const SceKernelPaGpuTraceParam *param);
int _sceKernelPaGetGpuSampledData(SceKernelPaGpuSampledData *data);
int _sceKernelPaSetupTraceBuffer(const SceKernelPaTraceBufferParam *param);
int _sceKernelPaSetupTraceBufferByKey(const int key, const SceKernelPaTraceBufferParam *param);

int sceKernelPaFlushTraceBuffer(const void *buffer, SceUInt32 type);
int sceKernelPaFlushTraceBufferByKey(const int key, const void *buffer, SceUInt32 type);
int sceKernelPaInsertBookmark(SceUInt32 fifo, SceUInt32 channel, SceUInt32 data);
int sceKernelPaRegister(void);
int sceKernelPaRemoveArmTrace(void);
int sceKernelPaRemoveArmTraceByKey(const int key);
int sceKernelPaRemoveCounterTrace(void);
int sceKernelPaRemoveCounterTraceByKey(const int key);
int sceKernelPaRemoveGpuTrace(void);
int sceKernelPaRemoveGpuTraceByKey(const int key);
int sceKernelPaSetBookmarkChannelEnable(SceUInt32 fifo, SceUInt32 mask);
int sceKernelPaSetBookmarkChannelEnableByKey(const int key, SceUInt32 fifo, SceUInt32 mask);
int sceKernelPaStart(void);
int sceKernelPaStartByKey(const int key);
int sceKernelPaStop(void);
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
