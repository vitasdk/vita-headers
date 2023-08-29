/**
 * \kernelgroup{SceSblSsComm}
 * \usage{psp2kern/kernel/sm_comm.h,SceSblSmCommForKernel_stub}
 */

#ifndef _PSP2KERN_KERNEL_SM_COMM_H_
#define _PSP2KERN_KERNEL_SM_COMM_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceSblSmCommPair {
	int data_00;
	int data_04;
} SceSblSmCommPair;
VITASDK_BUILD_ASSERT_EQ(8, SceSblSmCommPair);

typedef int SceSblSmCommId;

int ksceSblSmCommStartSmFromFile(SceUInt32 priority, const char *sm_path, SceUInt32 cmd_id, SceAuthInfo *auth_info, SceSblSmCommId *id);

int ksceSblSmCommCallFunc(SceSblSmCommId id, SceUInt32 service_id, SceUInt32 *service_result, void *data, SceSize size);
int ksceSblSmCommStopSm(SceSblSmCommId id, SceSblSmCommPair *result);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SM_COMM_H_ */
