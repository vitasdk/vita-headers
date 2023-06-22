/**
 * \usergroup{ScePspnetAdhocctl}
 * \usage{psp2/pspnet_adhocctl.h,ScePspnetAdhoc_stub}
 */


#ifndef _PSP2_PSPNET_ADHOCCTL_H_
#define _PSP2_PSPNET_ADHOCCTL_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2/net/net.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ScePspnetAdhocctlErrorCode {
	SCE_ERROR_NET_ADHOCCTL_INVALID_ARG             = 0x80410B04,
	SCE_ERROR_NET_ADHOCCTL_ALREADY_INITIALIZED     = 0x80410B07,
	SCE_ERROR_NET_ADHOCCTL_NOT_INITIALIZED         = 0x80410B08
} ScePspnetAdhocctlErrorCode;

typedef enum ScePspnetAdhocctlAdhocType {
	SCE_NET_ADHOCCTL_ADHOCTYPE_PRODUCT_ID  = 0,
	SCE_NET_ADHOCCTL_ADHOCTYPE_RESERVED    = 1,
	SCE_NET_ADHOCCTL_ADHOCTYPE_SYSTEM      = 2
} ScePspnetAdhocctlAdhocType;

#define SCE_NET_ADHOCCTL_ADHOCID_LEN 9
typedef struct SceNetAdhocctlAdhocId {
	int type;
	SceChar8 data[SCE_NET_ADHOCCTL_ADHOCID_LEN];
	SceUChar8 padding[3];
} SceNetAdhocctlAdhocId;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNetAdhocctlAdhocId);

#define SCE_NET_ADHOCCTL_GROUPNAME_LEN 8
typedef struct SceNetAdhocctlGroupName {
	SceChar8 data[SCE_NET_ADHOCCTL_GROUPNAME_LEN];
} SceNetAdhocctlGroupName;
VITASDK_BUILD_ASSERT_EQ(8, SceNetAdhocctlGroupName);

#define SCE_NET_ADHOCCTL_NICKNAME_LEN 128
typedef struct SceNetAdhocctlNickname {
	SceChar8 data[SCE_NET_ADHOCCTL_NICKNAME_LEN];
} SceNetAdhocctlNickname;
VITASDK_BUILD_ASSERT_EQ(0x80, SceNetAdhocctlNickname);

typedef struct SceNetAdhocctlPeerInfo {
	struct SceNetAdhocctlPeerInfo *next;
	struct SceNetAdhocctlNickname nickname;
	struct SceNetEtherAddr macAddr;
	SceUChar8 padding[6];
	SceUInt64 lastRecv;
} SceNetAdhocctlPeerInfo;
VITASDK_BUILD_ASSERT_EQ(0x98, SceNetAdhocctlPeerInfo);

#define SCE_NET_ADHOCCTL_BSSID_LEN  6
typedef struct SceNetAdhocctlBSSId {
	SceUChar8 data[SCE_NET_ADHOCCTL_BSSID_LEN];
	SceUChar8 padding[2];
} SceNetAdhocctlBSSId;
VITASDK_BUILD_ASSERT_EQ(8, SceNetAdhocctlBSSId);

typedef struct SceNetAdhocctlParameter {
	int channel;
	struct SceNetAdhocctlGroupName groupName;
	struct SceNetAdhocctlNickname nickname;
	struct SceNetAdhocctlBSSId bssid;
} SceNetAdhocctlParameter;
VITASDK_BUILD_ASSERT_EQ(0x94, SceNetAdhocctlParameter);

int sceNetAdhocctlInit(const struct SceNetAdhocctlAdhocId *adhocId);
int sceNetAdhocctlTerm(void);
int sceNetAdhocctlGetAdhocId(struct SceNetAdhocctlAdhocId *adhocId);
int sceNetAdhocctlGetPeerList(int *buflen, void *buf);
int sceNetAdhocctlGetPeerInfo(const struct SceNetEtherAddr *addr, int size, struct SceNetAdhocctlPeerInfo *peerInfo);
int sceNetAdhocctlGetAddrByName(const struct SceNetAdhocctlNickname *nickname, int *buflen, void *buf);
int sceNetAdhocctlGetNameByAddr(const struct SceNetEtherAddr *addr, struct SceNetAdhocctlNickname *nickname);
int sceNetAdhocctlGetParameter(struct SceNetAdhocctlParameter *parameter);
int sceNetAdhocctlGetEtherAddr(struct SceNetEtherAddr *addr);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PSPNET_ADHOCCTL_H_ */

