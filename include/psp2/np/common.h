/**
 * \usergroup{SceNp}
 * \usage{psp2/np/common.h}
 */


#ifndef _PSP2_NP_COMMON_H_
#define _PSP2_NP_COMMON_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceNpCommunicationId {
	char data[9];
	char term;
	SceUChar8 num;
	char dummy;
} SceNpCommunicationId;
VITASDK_BUILD_ASSERT_EQ(0xC, SceNpCommunicationId);

typedef struct SceNpCommunicationPassphrase {
	SceUInt8 data[0x80];
} SceNpCommunicationPassphrase;
VITASDK_BUILD_ASSERT_EQ(0x80, SceNpCommunicationPassphrase);

typedef struct SceNpCommunicationSignature {
	SceUInt8 data[0xA0];
} SceNpCommunicationSignature;
VITASDK_BUILD_ASSERT_EQ(0xA0, SceNpCommunicationSignature);

typedef struct SceNpCommunicationConfig{
	const SceNpCommunicationId *npCommId;
	const SceNpCommunicationPassphrase *npCommPass;
	const SceNpCommunicationSignature *npCommSign;
} SceNpCommunicationConfig;
VITASDK_BUILD_ASSERT_EQ(0xC, SceNpCommunicationConfig);

typedef struct SceNpOptParam {
	SceSize optSize;
} SceNpOptParam;
VITASDK_BUILD_ASSERT_EQ(0x4, SceNpOptParam);

typedef struct SceNpOnlineId {
	SceUChar8 data[16];
	SceUInt8 unk[4];
} SceNpOnlineId;
VITASDK_BUILD_ASSERT_EQ(0x14, SceNpOnlineId);

typedef struct SceNpId {
	SceNpOnlineId onlineId;
	SceUChar8 npId[8];
	SceUInt8 unk[8];
} SceNpId;
VITASDK_BUILD_ASSERT_EQ(0x24, SceNpId);

typedef struct SceNpCountryCode {
	SceUChar8 data[4]; //!< 'us', 'eu', 'jp', etc
} SceNpCountryCode;
VITASDK_BUILD_ASSERT_EQ(0x04, SceNpCountryCode);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NP_COMMON_H_ */
