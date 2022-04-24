/**
 * \kernelgroup{SceMsif}
 * \usage{psp2common/kernel/msif.h}
 */

#ifndef _PSP2COMMON_KERNEL_MSIF_H_
#define _PSP2COMMON_KERNEL_MSIF_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceMsInfo {
    int unk_0x00;
    int unk_0x04;
    SceUInt64 nbytes;
    SceUInt64 nbytes2;
    SceUInt32 sector_size;
    int unk_0x1C;
    SceUInt32 fs_offset;
    SceUInt32 unk_0x24;
    SceUInt32 unk_0x28;
    SceUInt32 unk_0x2C;
    SceUInt8 id[0x10];
} SceMsInfo;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_MSIF_H_ */
