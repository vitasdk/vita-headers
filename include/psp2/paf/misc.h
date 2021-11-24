/**
 * \usergroup{ScePaf}
 * \usage{psp2/paf/misc.h,ScePaf_stub}
 */


#ifndef _PSP2_PAF_MISC_H_
#define _PSP2_PAF_MISC_H_

#include <psp2/types.h>
#include <psp2/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScePafDateTime {
  SceDateTime data;
  int data_0x10;
  int data_0x14;
} ScePafDateTime;

int scePafGetCurrentClockLocalTime(ScePafDateTime *data);

typedef struct ScePafSha1Context { // size is 0x68
	uint32_t h[5];
	char unk[0x54];
} ScePafSha1Context;

int scePafSha1Init(ScePafSha1Context *context);
int scePafSha1Update(ScePafSha1Context *context, const void *data, SceSize length);
int scePafSha1Result(ScePafSha1Context *context, void *dst);

typedef struct ScePafHeapContext { // size is 0x60-bytes
	void *vtable;
	void *heap;
	void *membase;
	SceSize size;
	char name[0x20];
	SceChar8 is_import_membase;
	SceChar8 is_skip_debug_msg;
	char data_0x32;
	char data_0x33; // maybe unused. just for align.
	int data_0x34;  // maybe unused. just for align.
	SceKernelLwMutexWork lw_mtx;
	SceUID memblk_id;

	/*
	 * !1 : Game
	 *  1 : CDialog
	 */
	SceInt32 mode;
} ScePafHeapContext;

typedef struct ScePafHeapOpt { // size is 0x14-bytes
	int a1;
	int a2;
	SceChar8 is_skip_debug_msg;
	char a3[3];
	SceInt32 mode;
	int a5;
} ScePafHeapOpt;

void scePafCreateHeap(ScePafHeapContext *context, void *membase, SceSize size, const char *name, ScePafHeapOpt *opt);
void scePafDeleteHeap(ScePafHeapContext *context);

void *scePafMallocWithContext(ScePafHeapContext *context, SceSize len);
void scePafFreeWithContext(ScePafHeapContext *context, void *ptr);

void *scePafMallocAlignWithContext(ScePafHeapContext *context, SceUInt32 align, SceSize len);
void *scePafReallocWithContext(ScePafHeapContext *context, void *ptr, SceSize len);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PAF_MISC_H_ */
