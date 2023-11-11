/**
 * \kernelgroup{SceExfatfs}
 * \usage{psp2kern/internal/exfatfs.h}
 */

#ifndef _PSP2KERN_INTERNAL_EXFATFS_H_
#define _PSP2KERN_INTERNAL_EXFATFS_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Added this header to vita-headers to facilitate updates without being spread out to other separate projects.
 */

/*
 * A mix of camelCase and snake_case is maintained to facilitate reverse engineering
 */


#define SCE_EXFATFS_MAX_FILE_SYSTEM (0xF)
#define SCE_EXFATFS_MAX_FNODE (0x1000)

#define SCE_EXFATFS_TYPE_FAT   (1)
#define SCE_EXFATFS_TYPE_EXFAT (2)


typedef struct _SceExfatfsDateTime { // size is 0xC-bytes
	SceUInt16 year;
	SceUInt16 month;
	SceUInt16 day;
	SceUInt16 hour;
	SceUInt16 minute;
	SceUInt16 second;
} SceExfatfsDateTime;
VITASDK_BUILD_ASSERT_EQ(0xC, SceExfatfsDateTime);

typedef struct SceExfatfsMbr { // size is 0x200-bytes
	char data[0x200];
} SceExfatfsMbr;
VITASDK_BUILD_ASSERT_EQ(0x200, SceExfatfsMbr);

typedef struct _SceExfatfsDrive { // size is 0x230-bytes
	SceUInt32 state;
	int unk_0x04[0x2F];
	const char *assignName;
	int unk_0xC4[0x47];

	// offset 0x1E0
	SceKernelFastMutex fastmutex;
	const struct SceVfsMount2 *VfsMount2;
	void *vp;
	void *unk_0x228;
	int unk_0x22C;
} SceExfatfsDrive;
VITASDK_BUILD_ASSERT_EQ(0x230, SceExfatfsDrive);

typedef struct _SceExfatfsFnode { // size is 0x290-bytes
	SceUInt16 FilePath[0x208 >> 1]; // in utf-16
	SceUInt16 *FileName;
	struct _SceExfatfsFileSystem *fileSystem;
	struct { // size is 0x40-bytes
		SceUInt16 st_mode;
		SceUInt16 st_type;
		SceUInt16 st_dev;
		SceUInt16 st_uid;
		SceOff Size;
		SceExfatfsDateTime ctime;
		SceExfatfsDateTime atime;
		SceExfatfsDateTime mtime;
		SceUInt32 StartCluster;
		SceUInt8 data_0x248;
		SceUInt8 data_0x249;
		SceUInt8 data_0x24A;
		SceUInt8 data_0x24B;
		int data_0x24C;
	} Stat;

	SceUInt32 DirCluster;
	int data_0x254;
	SceOff DirOffset;

	SceUInt32 DirOffClust;
	int data_0x264;
	SceSize dirSize;
	SceUInt8 dirGeneralSecondaryFlags;
	SceUInt8 data_0x26D;
	SceUInt8 data_0x26E;
	SceUInt8 data_0x26F;

	SceUInt16 refCount;
	SceUInt16 fdCount;
	int data_0x274;
	SceUInt32 cache_element_count;
	void *cluster_cache_array;

	SceUInt32 tailCluster;
	SceUInt32 tailIndex;
	SceUInt32 clusterCount;
	SceUInt32 chunkCount;
} SceExfatfsFnode;
VITASDK_BUILD_ASSERT_EQ(0x290, SceExfatfsFnode);

typedef struct _SceExfatfsFile { // size is 0x38-bytes
	SceExfatfsFnode *fnode;
	int mode;
	SceOff Position;
	void *Buf;
	void *BufTop;
	SceUInt32 Cluster;
	SceUInt32 clusterIndex;
	int unk_0x20;
	int unk_0x24;
	SceUInt64 cacheIndex;
	int unk_0x30;
	int unk_0x34;
} SceExfatfsFile;
VITASDK_BUILD_ASSERT_EQ(0x38, SceExfatfsFile);

typedef struct _SceExfatfsFileSystem { // size is 0x430-bytes
	const char *devname;
	int unk_4;
	int unk_8;
	int rsvd_sector;

	int unk_10;
	int available_clusters; // Number of clusters available
	void *PBRBuf;
	int unk_1C;

	int unk_20;
	int unk_24;
	void *unk_28; // pointer of unk_80
	int unk_2C;

	int unk_30;
	void *unk_34;
	void *unk_38;
	int unk_3C;

	int unk_40;
	int unk_44;
	int unk_48;
	int unk_4C;

	void *unk_50;
	void *unk_54;
	int unk_58;
	int unk_5C;

	int unk_60;
	int unk_64;
	int unk_68;
	int unk_6C;

	int unk_70;
	int unk_74;
	int unk_78;
	int unk_7C;

	int unk_80;
	int unk_84;
	int unk_88;
	int unk_8C;

	int unk_90;
	int unk_94;
	int unk_98;
	int unk_9C;

	int unk_A0;
	int unk_A4;
	int unk_A8;
	SceExfatfsDrive *drive;

	SceUInt32 mount_mode;
	int unk_B4; // SCE_EXFATFS_TYPE_*
	int unk_B8;
	SceSize sectorSize;

	SceUInt32 clusterSectorCount;
	SceUInt32 firstClusterOfRoot;
	SceUInt32 devSectors;
	int unk_CC;
	char data_0xD0[0x48];
	SceExfatfsFile file;
	SceExfatfsFnode fnode;
	SceKernelFastMutex *rootFastMutex;
	void *unk_0x3E4;
	SceUID unk_0x3E8;
	void *unk_0x3EC;
	SceKernelFastMutex fastmutex; // maybe not fastmutex...
} SceExfatfsFileSystem;
VITASDK_BUILD_ASSERT_EQ(0x430, SceExfatfsFileSystem);

typedef struct _SceExfatfsSharedResource { // size is 0x295D60-bytes
	SceExfatfsFileSystem fileSystem[SCE_EXFATFS_MAX_FILE_SYSTEM];
	SceExfatfsMbr mbr[SCE_EXFATFS_MAX_FILE_SYSTEM];
	void *data_0x5CD0;
	int data_0x5CD4;
	SceExfatfsFnode fnode[SCE_EXFATFS_MAX_FNODE];
	int data_0x295CD8[0x78 >> 2]; // unknown
	int data_0x295D50; // All SceExfatfsFnode elements number?
	int data_0x295D54; // Available SceExfatfs_data_0x5D50 elements number
	int data_0x295D58; // Related to ReserveUnusedFd
	int data_0x295D5C; // Related to ReserveUnusedFd
} SceExfatfsSharedResource;
VITASDK_BUILD_ASSERT_EQ(0x295D60, SceExfatfsSharedResource);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_INTERNAL_EXFATFS_H_ */
