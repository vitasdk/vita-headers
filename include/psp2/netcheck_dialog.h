/**
 * \usergroup{SceNetCheckDialog}
 * \usage{psp2/netcheck_dialog.h,SceCommonDialog_stub}
 */


#ifndef _PSP2_NETCHECK_DIALOG_H_
#define _PSP2_NETCHECK_DIALOG_H_

#include <psp2/types.h>
#include <psp2/common_dialog.h>
#include <psp2/pspnet_adhocctl.h>
#include <psp2/net/net.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceNetCheckDialoErrorCode {
	SCE_NETCHECK_DIALOG_ERROR_PARAM                       = 0x80100C01,
	SCE_NETCHECK_DIALOG_ERROR_INVALID_MODE                = 0x80100C02,
	SCE_NETCHECK_DIALOG_ERROR_LACK_OF_LIBHTTP_POOL_SIZE   = 0x80100C03,
	SCE_NETCHECK_DIALOG_ERROR_LACK_OF_LIBSSL_POOL_SIZE    = 0x80100C04,
	SCE_NETCHECK_DIALOG_ERROR_LATEST_PATCH_PKG_EXIST      = 0x80100C05,
	SCE_NETCHECK_DIALOG_ERROR_SIGN_OUT                    = 0x80100C06,
	SCE_NETCHECK_DIALOG_ERROR_INVALID_PSPADHOC_PARAM      = 0x80100C07,
	SCE_NETCHECK_DIALOG_ERROR_INVALID_TIMEOUT_PARAM       = 0x80100C08,
	SCE_NETCHECK_DIALOG_ERROR_PSN_AGE_RESTRICTION         = 0x80100C09
} SceNetCheckDialoErrorCode;

#define SCE_NETCHECK_DIALOG_LEAST_HTTP_POOL_SIZE       (36 * 1024)
#define SCE_NETCHECK_DIALOG_LEAST_SSL_POOL_SIZE        (96 * 1024)
#define SCE_NETCHECK_DIALOG_INITIAL_AGE_RESTRICTION    (-1)
#define SCE_NETCHECK_DIALOG_COUNTRY_CODE_LEN           (2)
#define SCE_NETCHECK_DIALOG_AGE_RESTRICTION_COUNT_MAX  (200)

typedef enum SceNetCheckDialogMode {
	SCE_NETCHECK_DIALOG_MODE_INVALID           = 0,
	SCE_NETCHECK_DIALOG_MODE_ADHOC_CONN        = 1,
	SCE_NETCHECK_DIALOG_MODE_PSN               = 2,
	SCE_NETCHECK_DIALOG_MODE_PSN_ONLINE        = 3,
	SCE_NETCHECK_DIALOG_MODE_PS3_CONNECT       = 4,
	SCE_NETCHECK_DIALOG_MODE_PSP_ADHOC_CONN    = 5,
	SCE_NETCHECK_DIALOG_MODE_PSP_ADHOC_CREATE  = 6,
	SCE_NETCHECK_DIALOG_MODE_PSP_ADHOC_JOIN    = 7
} SceNetCheckDialogMode;

typedef enum SceNetCheckDialogPS3ConnectAction {
	SCE_NETCHECK_DIALOG_PS3_CONNECT_ACTION_ENTER  = 0,
	SCE_NETCHECK_DIALOG_PS3_CONNECT_ACTION_LEAVE  = 1
} SceNetCheckDialogPS3ConnectAction;

typedef struct SceNpCommunicationId {
	char data[9];
	char term;
	SceUChar8 num;
	char dummy;
} SceNpCommunicationId;

typedef struct SceNetCheckDialogPS3ConnectParam {
	SceInt32 action;
	char ssid[32 + 1];
	char wpaKey[64 + 1];
	char titleId[9 + 1];
} SceNetCheckDialogPS3ConnectParam;

typedef struct SceNetCheckDialogAgeRestriction {
	char countryCode[SCE_NETCHECK_DIALOG_COUNTRY_CODE_LEN];
	SceInt8 age;
	SceInt8 padding;
} SceNetCheckDialogAgeRestriction;

typedef struct SceNetCheckDialogParam {
	SceUInt32 sdkVersion;
	SceCommonDialogParam commonParam;
	SceInt32 mode;
	SceNpCommunicationId npCommunicationId;
	SceNetCheckDialogPS3ConnectParam *ps3ConnectParam;
	SceNetAdhocctlGroupName *groupName;
	SceUInt32 timeoutUs;
	SceInt8 defaultAgeRestriction;
	SceInt8 padding[3];
	SceInt32 ageRestrictionCount;
	const SceNetCheckDialogAgeRestriction *ageRestriction;
	SceUInt8 reserved[104];
} SceNetCheckDialogParam;

typedef struct SceNetCheckDialogResult {
	SceInt32 result;
	SceBool psnModeSucceeded;
	SceUInt8 reserved[124];
} SceNetCheckDialogResult;

typedef struct SceNetCheckDialogPS3ConnectInfo {
	SceNetInAddr inaddr;
	SceUInt8 nickname[128];
	SceUInt8 macAddress[6];
	SceUInt8 reserved[6];
} SceNetCheckDialogPS3ConnectInfo;

static inline
void sceNetCheckDialogParamInit(SceNetCheckDialogParam *param)
{
	memset(param, 0x0, sizeof(SceNetCheckDialogParam));
	_sceCommonDialogSetMagicNumber(&param->commonParam);
	param->sdkVersion = PSP2_SDK_VERSION;
	param->defaultAgeRestriction = SCE_NETCHECK_DIALOG_INITIAL_AGE_RESTRICTION;
}

SceInt32 sceNetCheckDialogInit(SceNetCheckDialogParam *param);
SceCommonDialogStatus sceNetCheckDialogGetStatus(void);
SceInt32 sceNetCheckDialogAbort(void);
SceInt32 sceNetCheckDialogGetResult(SceNetCheckDialogResult *result);
SceInt32 sceNetCheckDialogGetPS3ConnectInfo(SceNetCheckDialogPS3ConnectInfo *info);
SceInt32 sceNetCheckDialogTerm(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NETCHECK_DIALOG_H_ */

