/**
 * \file
 * \brief Header file related to net control
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_NET_CTL_H_
#define _PSP2_NET_CTL_H_

#include <psp2/net/net.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define PSP2_NETCTL_INFO_CONFIG_NAME_LEN_MAX 64
#define PSP2_NETCTL_INFO_SSID_LEN_MAX        32

enum {
	PSP2_NETCTL_INFO_GET_CNF_NAME = 1,
	PSP2_NETCTL_INFO_GET_DEVICE,
	PSP2_NETCTL_INFO_GET_ETHER_ADDR,
	PSP2_NETCTL_INFO_GET_MTU,
	PSP2_NETCTL_INFO_GET_LINK,
	PSP2_NETCTL_INFO_GET_BSSID,
	PSP2_NETCTL_INFO_GET_SSID,
	PSP2_NETCTL_INFO_GET_WIFI_SECURITY,
	PSP2_NETCTL_INFO_GET_RSSI_DBM,
	PSP2_NETCTL_INFO_GET_RSSI_PERCENTAGE,
	PSP2_NETCTL_INFO_GET_CHANNEL,
	PSP2_NETCTL_INFO_GET_IP_CONFIG,
	PSP2_NETCTL_INFO_GET_DHCP_HOSTNAME,
	PSP2_NETCTL_INFO_GET_PPPOE_AUTH_NAME,
	PSP2_NETCTL_INFO_GET_IP_ADDRESS,
	PSP2_NETCTL_INFO_GET_NETMASK,
	PSP2_NETCTL_INFO_GET_DEFAULT_ROUTE,
	PSP2_NETCTL_INFO_GET_PRIMARY_DNS,
	PSP2_NETCTL_INFO_GET_SECONDARY_DNS,
	PSP2_NETCTL_INFO_GET_HTTP_PROXY_CONFIG,
	PSP2_NETCTL_INFO_GET_HTTP_PROXY_SERVER,
	PSP2_NETCTL_INFO_GET_HTTP_PROXY_PORT,
};

/* callback */

typedef void *(*SceNetCtlCallback)(
	int event_type,
	void *arg);

/* struct/union */

typedef union SceNetCtlInfo {
	char cnf_name[PSP2_NETCTL_INFO_CONFIG_NAME_LEN_MAX + 1];
	unsigned int device;
	SceNetEtherAddr ether_addr;
	unsigned int mtu;
	unsigned int link;
	SceNetEtherAddr bssid;
	char ssid[PSP2_NETCTL_INFO_SSID_LEN_MAX + 1];
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

#endif /* _PSP2_NET_CTL_H_ */
