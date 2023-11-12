/**
 * \kernelgroup{SceSdstor}
 * \usage{psp2kern/internal/sdstor.h}
 */

#ifndef _PSP2KERN_INTERNAL_SDSTOR_H_
#define _PSP2KERN_INTERNAL_SDSTOR_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Added this header to vita-headers to facilitate updates without being spread out to other separate projects.
 */


typedef enum {
	SCE_SDSTOR_SDPART_PORT_EMMC     = 0x0,
	SCE_SDSTOR_SDPART_PORT_GC       = 0x1,
	SCE_SDSTOR_SDPART_PORT_RM       = 0x2,
	SCE_SDSTOR_SDPART_PORT_UMA      = 0x3,
	SCE_SDSTOR_SDPART_PORT_USD      = 0x4,
	SCE_SDSTOR_SDPART_PORT_PSUDO_MC = 0xFF
} SceSdstorSdpartPort;
VITASDK_BUILD_ASSERT_EQ(1, SceSdstorSdpartPort);

typedef enum {
	SCE_SDSTOR_SDPART_STAT_INA = 0,
	SCE_SDSTOR_SDPART_STAT_ACT = 1,
	SCE_SDSTOR_SDPART_STAT_IGN = 2
} SceSdstorSdpartStat;
VITASDK_BUILD_ASSERT_EQ(1, SceSdstorSdpartStat);

typedef enum {
	SCE_SDSTOR_SDPART_KIND_INVALID  = 0x0,
	SCE_SDSTOR_SDPART_KIND_GC       = 0x1,
	SCE_SDSTOR_SDPART_KIND_RM       = 0x2,
	SCE_SDSTOR_SDPART_KIND_USD      = 0x3
} SceSdstorSdpartKind; // maybe inaccurate
VITASDK_BUILD_ASSERT_EQ(1, SceSdstorSdpartKind);

typedef struct _SceSdstorSddev { // size is 0x54
	SceKernelFastMutex fastmutex;
	SceUInt8 kind;
	SceSdstorSdpartPort port;
	SceUInt8 stat;
	SceUInt8 prev_stat;
	SceUInt32 unk_44;
	SceUInt32 unk_48;
	SceUInt32 unk_4C;
	void *sdif_ctx;
} SceSdstorSddev;
VITASDK_BUILD_ASSERT_EQ(0x54, SceSdstorSddev);

typedef struct _SceSdstorPartitionEntry { // size is 0x1C
	SceUInt32 start_lba;
	SceUInt32 n_sectors;
	struct _SceSdstorSdpart *sdpart;
	void *partition_entry; // in mbr buffer entry
	char numeric_name[4];
	SceUInt8 type;
	SceUInt8 flag;
	SceUInt16 acl;
	SceUInt16 unused;
	SceUInt16 unk;
} SceSdstorPartitionEntry;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceSdstorPartitionEntry);

typedef struct _SceSdstorSdpart { // size is 0x238
	SceKernelFastMutex fastmutex;
	SceUInt32 unk_40; // maybe sector size ?
	SceSdstorSddev *sddev;
	SceUInt32 unk_48; // maybe sector size ?
	SceUInt32 unk_4C;
	SceUInt32 unk_50;
	void *mbr_ptr;
	SceSdstorPartitionEntry pentry[17];
	SceUInt8 stat;
	SceUInt8 prev_stat;
	SceUInt8 unk_236;
	SceUInt8 unk_237;
} SceSdstorSdpart;
VITASDK_BUILD_ASSERT_EQ(0x238, SceSdstorSdpart);

/*
 * setup on lookup
 */
typedef struct _SceSdstorOpHandle { // size is 0xC
	SceSdstorPartitionEntry *pentry;
	SceSdstorSddev *sddev;
	int unk_0x08;
} SceSdstorOpHandle;
VITASDK_BUILD_ASSERT_EQ(0xC, SceSdstorOpHandle);

/*
 * setup on open
 */
typedef struct _SceSdstorFd { // size is 0x58
	SceKernelFastMutex fastmutex;
	SceUInt32 unk_40; // maybe sector size?
	SceUInt32 start_lba;
	SceUInt32 n_sectors;
	int flags;
	SceSdstorPartitionEntry *pentry;
	SceSdstorSddev *sddev;
} SceSdstorFd;
VITASDK_BUILD_ASSERT_EQ(0x58, SceSdstorFd);

typedef struct _SceSdstorSdintr { // size is 0x28
	int unk_0x00;
	SceUID request_id;
	SceUID op_sync_id;
	int unk_0x0C;
	int unk_0x10;
	SceUInt32 mediaid[4];
	SceSdstorSdpartPort port;
	SceUInt8 stat;
	SceUInt8 unk_0x26;
	SceUInt8 unk_0x27;
} SceSdstorSdintr;
VITASDK_BUILD_ASSERT_EQ(0x28, SceSdstorSdintr);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_INTERNAL_SDSTOR_H_ */
