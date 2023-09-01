/**
 * \kernelgroup{ScePerf}
 * \usage{psp2/perf.h,ScePerf_stub,SCE_PERF_ARM_PMON_MAIN_PIPE}
 */


#ifndef _PSP2_PERF_H_
#define _PSP2_PERF_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


#define SCE_PERF_ARM_PMON_THREAD_ID_SELF (SCE_KERNEL_THREAD_ID_SELF)

typedef enum _ScePerfArmPmonEventCode {
	SCE_PERF_ARM_PMON_SOFT_INCREMENT         = 0x00,
	SCE_PERF_ARM_PMON_ICACHE_MISS            = 0x01,
	SCE_PERF_ARM_PMON_ITLB_MISS              = 0x02,
	SCE_PERF_ARM_PMON_DCACHE_MISS            = 0x03,
	SCE_PERF_ARM_PMON_DCACHE_ACCESS          = 0x04,
	SCE_PERF_ARM_PMON_DTLB_MISS              = 0x05,
	SCE_PERF_ARM_PMON_DATA_READ              = 0x06,
	SCE_PERF_ARM_PMON_DATA_WRITE             = 0x07,
	SCE_PERF_ARM_PMON_EXCEPTION_TAKEN        = 0x09,
	SCE_PERF_ARM_PMON_EXCEPTION_RETURN       = 0x0A,
	SCE_PERF_ARM_PMON_WRITE_CONTEXTID        = 0x0B,
	SCE_PERF_ARM_PMON_SOFT_CHANGEPC          = 0x0C,
	SCE_PERF_ARM_PMON_IMMEDIATE_BRANCH       = 0x0D,
	SCE_PERF_ARM_PMON_UNALIGNED              = 0x0F,
	SCE_PERF_ARM_PMON_BRANCH_MISPREDICT      = 0x10,
	SCE_PERF_ARM_PMON_CYCLE_COUNT            = 0x11,
	SCE_PERF_ARM_PMON_PREDICT_BRANCH         = 0x12,
	SCE_PERF_ARM_PMON_COHERENT_LF_MISS       = 0x50,
	SCE_PERF_ARM_PMON_COHERENT_LF_HIT        = 0x51,
	SCE_PERF_ARM_PMON_ICACHE_STALL           = 0x60,
	SCE_PERF_ARM_PMON_DCACHE_STALL           = 0x61,
	SCE_PERF_ARM_PMON_MAINTLB_STALL          = 0x62,
	SCE_PERF_ARM_PMON_STREX_PASSED           = 0x63,
	SCE_PERF_ARM_PMON_STREX_FAILED           = 0x64,
	SCE_PERF_ARM_PMON_DATA_EVICTION          = 0x65,
	SCE_PERF_ARM_PMON_ISSUE_NO_DISPATCH      = 0x66,
	SCE_PERF_ARM_PMON_ISSUE_EMPTY            = 0x67,
	SCE_PERF_ARM_PMON_INST_RENAME            = 0x68,
	SCE_PERF_ARM_PMON_PREDICT_FUNC_RET       = 0x6E,
	SCE_PERF_ARM_PMON_MAIN_PIPE              = 0x70,
	SCE_PERF_ARM_PMON_SECOND_PIPE            = 0x71,
	SCE_PERF_ARM_PMON_LS_PIPE                = 0x72,
	SCE_PERF_ARM_PMON_FPU_RENAME             = 0x73,
	SCE_PERF_ARM_PMON_NEON_RENAME            = 0x74,
	SCE_PERF_ARM_PMON_PLD_STALL              = 0x80,
	SCE_PERF_ARM_PMON_WRITE_STALL            = 0x81,
	SCE_PERF_ARM_PMON_INST_MAINTLB_STALL     = 0x82,
	SCE_PERF_ARM_PMON_DATA_MAINTLB_STALL     = 0x83,
	SCE_PERF_ARM_PMON_INST_UTLB_STALL        = 0x84,
	SCE_PERF_ARM_PMON_DATA_UTLB_STALL        = 0x85,
	SCE_PERF_ARM_PMON_DMB_STALL              = 0x86,
	SCE_PERF_ARM_PMON_INTEGER_CLOCK          = 0x8A,
	SCE_PERF_ARM_PMON_DATAENGINE_CLOCK       = 0x8B,
	SCE_PERF_ARM_PMON_ISB                    = 0x90,
	SCE_PERF_ARM_PMON_DSB                    = 0x91,
	SCE_PERF_ARM_PMON_DMB                    = 0x92,
	SCE_PERF_ARM_PMON_EXT_INTERRUPT          = 0x93,
	SCE_PERF_ARM_PMON_PLE_LINE_REQ_COMPLETED = 0xA0,
	SCE_PERF_ARM_PMON_PLE_CHANNEL_SKIPPED    = 0xA1,
	SCE_PERF_ARM_PMON_PLE_FIFO_FLUSH         = 0xA2,
	SCE_PERF_ARM_PMON_PLE_REQ_COMPLETED      = 0xA3,
	SCE_PERF_ARM_PMON_PLE_FIFO_OVERFLOW      = 0xA4,
	SCE_PERF_ARM_PMON_PLE_REQ_PROGRAMMED     = 0xA5
} ScePerfArmPmonEventCode;


int scePerfArmPmonReset(SceUID thid);
int scePerfArmPmonSelectEvent(SceUID thid, SceUInt32 counter, SceUInt8 event_code);
int scePerfArmPmonStart(SceUID thid);
int scePerfArmPmonStop(SceUID thid);
int scePerfArmPmonGetCounterValue(SceUID thid, SceUInt32 counter, SceUInt32 *value);
int scePerfArmPmonSetCounterValue(SceUID thid, SceUInt32 counter, SceUInt32 value);
int scePerfArmPmonSoftwareIncrement(SceUInt32 mask);

SceUInt64 scePerfGetTimebaseValue(void);
SceUInt32 scePerfGetTimebaseFrequency(void);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PERF_H_ */
