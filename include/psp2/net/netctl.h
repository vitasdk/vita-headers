/**
 * \usergroup{SceNetCtl}
 * \usage{psp2/net/netctl.h,SceNetCtl_stub}
 */


#ifndef _PSP2_NET_NETCTL_H_
#define _PSP2_NET_NETCTL_H_

#include <psp2/net/net.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define SCE_NETCTL_INFO_CONFIG_NAME_LEN_MAX 64
#define SCE_NETCTL_INFO_SSID_LEN_MAX        32

typedef enum SceNetCtlInfoType {
	SCE_NETCTL_INFO_GET_CNF_NAME = 1,
	SCE_NETCTL_INFO_GET_DEVICE,
	SCE_NETCTL_INFO_GET_ETHER_ADDR,
	SCE_NETCTL_INFO_GET_MTU,
	SCE_NETCTL_INFO_GET_LINK,
	SCE_NETCTL_INFO_GET_BSSID,
	SCE_NETCTL_INFO_GET_SSID,
	SCE_NETCTL_INFO_GET_WIFI_SECURITY,
	SCE_NETCTL_INFO_GET_RSSI_DBM,
	SCE_NETCTL_INFO_GET_RSSI_PERCENTAGE,
	SCE_NETCTL_INFO_GET_CHANNEL,
	SCE_NETCTL_INFO_GET_IP_CONFIG,
	SCE_NETCTL_INFO_GET_DHCP_HOSTNAME,
	SCE_NETCTL_INFO_GET_PPPOE_AUTH_NAME,
	SCE_NETCTL_INFO_GET_IP_ADDRESS,
	SCE_NETCTL_INFO_GET_NETMASK,
	SCE_NETCTL_INFO_GET_DEFAULT_ROUTE,
	SCE_NETCTL_INFO_GET_PRIMARY_DNS,
	SCE_NETCTL_INFO_GET_SECONDARY_DNS,
	SCE_NETCTL_INFO_GET_HTTP_PROXY_CONFIG,
	SCE_NETCTL_INFO_GET_HTTP_PROXY_SERVER,
	SCE_NETCTL_INFO_GET_HTTP_PROXY_PORT,
} SceNetCtlInfoType;

typedef enum SceNetCtlState {
	SCE_NETCTL_STATE_DISCONNECTED,
	SCE_NETCTL_STATE_CONNECTING,
	SCE_NETCTL_STATE_FINALIZING,
	SCE_NETCTL_STATE_CONNECTED
} SceNetCtlState;

/* callback */

typedef void *(*SceNetCtlCallback)(
	int event_type,
	void *arg);

/* struct/union */

typedef union SceNetCtlInfo {
	char cnf_name[SCE_NETCTL_INFO_CONFIG_NAME_LEN_MAX + 1];
	unsigned int device;
	SceNetEtherAddr ether_addr;
	unsigned int mtu;
	unsigned int link;
	SceNetEtherAddr bssid;
	char ssid[SCE_NETCTL_INFO_SSID_LEN_MAX + 1];
	unsigned int wifi_security;
	unsigned int rssi_dbm;
	unsigned int rssi_percentage;
	unsigned int channel;
	unsigned int ip_config;
	char dhcp_hostname[256];
	char pppoe_auth_name[128];
	char ip_address[16];
	char netmask[16];
	char default_route[16];
	char primary_dns[16];
	char secondary_dns[16];
	unsigned int http_proxy_config;
	char http_proxy_server[256];
	unsigned int http_proxy_port;
} SceNetCtlInfo;


typedef struct SceNetCtlNatInfo {
	unsigned int size;
	int stun_status;
	int nat_type;
	SceNetInAddr mapped_addr;
} SceNetCtlNatInfo;

typedef struct SceNetCtlAdhocPeerInfo {
	struct SceNetCtlAdhocPeerInfo *next;
	SceNetInAddr inet_addr;
} SceNetCtlAdhocPeerInfo;

/* prototypes */

int sceNetCtlInit();
void sceNetCtlTerm();

int sceNetCtlCheckCallback();

int sceNetCtlInetGetResult(int eventType, int *errorCode);
int sceNetCtlAdhocGetResult(int eventType, int *errorCode);

int sceNetCtlInetGetInfo(int code, SceNetCtlInfo *info);
int sceNetCtlInetGetState(int *state);
int sceNetCtlGetNatInfo(SceNetCtlNatInfo *natinfo);

int sceNetCtlInetRegisterCallback(SceNetCtlCallback func, void *arg, int *cid);
int sceNetCtlInetUnregisterCallback(int cid);

int sceNetCtlAdhocRegisterCallback(SceNetCtlCallback func, void *arg, int *cid);
int sceNetCtlAdhocUnregisterCallback(int cid);
int sceNetCtlAdhocGetState(int *state);
int sceNetCtlAdhocDisconnect();
int sceNetCtlAdhocGetPeerList(unsigned int *buflen, void *buf);
int sceNetCtlAdhocGetInAddr(SceNetInAddr *inaddr);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NET_NETCTL_H_ */

