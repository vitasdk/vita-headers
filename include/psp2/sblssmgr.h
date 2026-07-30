/**
 * \usergroup{SceSblSsMgr}
 * \usage{psp2/sblssmgr.h,SceSblSsMgr_stub}
 */

#ifndef _PSP2_SBLSSMGR_H_
#define _PSP2_SBLSSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2/dmac5.h>
#include <psp2common/sblssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelGetRandomNumberParam {
	SceUInt32 dstSize; //!< In bytes. Must be <= 0x40.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceKernelGetRandomNumberParam;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelGetRandomNumberParam); // size is from FW 3.60

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

int _sceKernelGetOpenPsId(SceOpenPsId *pOpenPsId);

/**
 * @param[in] pParam - Parameter structure. The FW 3.60 provider only reads it.
 */
int _sceKernelGetRandomNumber(void *pDst, SceSize length, SceKernelGetRandomNumberParam *pParam);
int sceSblDmac5EncDecKeyGen(SceSblDmac5EncDecParam *pParam, SceUInt32 key_id, SceUInt32 command);
int sceSblDmac5HmacKeyGen(SceSblDmac5HashTransformParam *pParam, SceUInt32 key_id, SceUInt32 command, SceUInt32 flags);
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

#endif /* _PSP2_SBLSSMGR_H_ */
