/**
 * \usergroup{SceSblLicMgr}
 * \usage{psp2/sbllicmgr.h,SceSblLicMgr_stub}
 */

#ifndef _PSP2_SBLLICMGR_H_
#define _PSP2_SBLLICMGR_H_

#include <psp2/types.h>
#include <psp2common/sblpostssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblLicMgrActivateDevkit(char *afv_path);
int sceSblLicMgrActivateFromFs(void);
int sceSblLicMgrClearActivationData(void);
int sceSblLicMgrGetActivationKey(SceSblActivationKey *key);
int sceSblLicMgrGetExpireDate(int *expire_date, int request_data_flag);
int sceSblLicMgrGetIssueNo(int *issue_number, int request_data_flag);
int sceSblLicMgrGetLicenseStatus(void);
int sceSblLicMgrGetUsageTimeLimit(SceUInt32 *time_limit);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLLICMGR_H_ */
