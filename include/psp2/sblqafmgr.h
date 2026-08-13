/**
 * \usergroup{SceSblQafMgr}
 * \usage{psp2/sblqafmgr.h,SceSblSsMgr_stub}
 */

#ifndef _PSP2_SBLQAFMGR_H_
#define _PSP2_SBLQAFMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceQafToken {
	char magic[4];
	SceUInt32 qaf_version;
	char qaf_name[0x18];
	char console_id[0x10];
	char qa_flags[0x10];
	char reserved[0x30]; //!< Reserved token payload.
	char cmac[0x10];
} SceQafToken;
VITASDK_BUILD_ASSERT_EQ(0x80, SceQafToken); // size is from FW 3.60

typedef struct SceQafTokenEnc {
	char magic[4];
	SceUInt32 qaf_version;
	char qaf_name[0x18];
	char enc_data[0x60];
} SceQafTokenEnc;
VITASDK_BUILD_ASSERT_EQ(0x80, SceQafTokenEnc); // size is from FW 3.60

typedef struct SceQafTokenEx {
	/**
	 * Input to ::sceSblQafMgrSetQafToken2 has the layout of
	 * ::SceQafTokenEnc. ::sceSblQafMgrGetQafToken2 transforms this region,
	 * but its output layout is not established.
	 */
	char token_data[0x80];
	char sig[0x100];
} SceQafTokenEx;
VITASDK_BUILD_ASSERT_EQ(0x180, SceQafTokenEx); // size is from FW 3.60

int sceSblQafManagerDeleteQafTokenForUser(void);
int sceSblQafManagerGetQafNameForUser(char *buffer, unsigned int max_len);
int sceSblQafManagerIsAllowKernelDebugForUser(void);
int sceSblQafManagerSetQafTokenForUser(SceQafToken qaf_token);
int sceSblQafMgrDeleteQafToken2(void);
int sceSblQafMgrGetQafName(char *buffer, unsigned int max_len);
int sceSblQafMgrGetQafToken(SceQafToken *qaf_token);
int sceSblQafMgrGetQafToken2(SceQafTokenEx *qaf_token);
int sceSblQafMgrIsAllowAllDebugMenuDisplay(void);
int sceSblQafMgrIsAllowForceUpdate(void);
int sceSblQafMgrIsAllowLimitedDebugMenuDisplay(void);
int sceSblQafMgrIsAllowMinimumDebugMenuDisplay(void);
int sceSblQafMgrIsAllowNonQAPup(void);
int sceSblQafMgrIsAllowNpFullTest(void);
int sceSblQafMgrIsAllowNpTest(void);
int sceSblQafMgrIsAllowRemoteSysmoduleLoad(void);
int sceSblQafMgrIsAllowScreenShotAlways(void);
int sceSblQafMgrSetQafToken2(const SceQafTokenEx *qaf_token);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLQAFMGR_H_ */
