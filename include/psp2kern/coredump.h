/**
 * \kernelgroup{SceCoredump}
 * \usage{psp2kern/coredump.h,SceCoredumpForDriver_stub}
 */


#ifndef _PSP2KERN_COREDUMP_H_
#define _PSP2KERN_COREDUMP_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceCoredumpTriggerParam {
	SceSize size;
	int data_0x04;
	int data_0x08;
	int data_0x0C;
	int data_0x10;
	SceSize titleid_len;
	const char *titleid;
	SceSize app_name_len;
	const char *app_name;
	int data_0x24; // ex: 100. maybe progress max number.
	int data_0x28;
	SceUID crash_thid;
	int data_0x30;
} SceCoredumpTriggerParam;

typedef int (* SceKernelCoredumpStateUpdateCallback)(int task_id, SceUID pid, int progress);
typedef int (* SceKernelCoredumpStateFinishCallback)(int task_id, SceUID pid, int result, const char *path, SceSize path_len, int unk);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_COREDUMP_H_ */
