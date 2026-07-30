/**
 * \kernelgroup{SceSblPostSsMgr}
 * \usage{psp2common/sblpostssmgr.h}
 */

#ifndef _PSP2COMMON_SBLPOSTSSMGR_H_
#define _PSP2COMMON_SBLPOSTSSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceSblActivationKey {
	char open_psid[0x10]; //!< 16-byte OpenPSID.
	uint32_t vadd_hash;   //!< Vector-add hash of the OpenPSID.
} SceSblActivationKey;
VITASDK_BUILD_ASSERT_EQ(0x14, SceSblActivationKey);

typedef struct SceSblSpfsoContext {
	SceUID mem_uid;          //!< Memory block UID.
	void *mem_block_base;    //!< Mapped memory block base address.
	SceSize file_size;       //!< Exact SPSFO file size.
} SceSblSpfsoContext;
VITASDK_BUILD_ASSERT_EQ(0xC, SceSblSpfsoContext);

typedef SceSblSpfsoContext SceSblSpsfoContext;

typedef struct SceSblAppKey {
	SceSize size;       //!< Number of valid key bytes. Must be 0x10 or 0x20.
	SceUInt8 key[0x20]; //!< Key data.
} SceSblAppKey;
VITASDK_BUILD_ASSERT_EQ(0x24, SceSblAppKey); // size is from FW 3.60

typedef struct SceUtoken {
	SceUInt8 encrypted_data[0x800]; //!< Encrypted Utoken data.
} SceUtoken;
VITASDK_BUILD_ASSERT_EQ(0x800, SceUtoken); // size is from FW 3.60

typedef struct SceUtokenSelfAuthInfo {
	SceUInt64 program_authority_id; //!< Program authority ID to override.
	SceUInt8 capability[0x20];      //!< Capability bits.
	SceUInt8 attribute[0x20];       //!< Attribute bits.
	SceUInt8 shared_secret[0x10];   //!< Shared secret.
} SceUtokenSelfAuthInfo;
VITASDK_BUILD_ASSERT_EQ(0x58, SceUtokenSelfAuthInfo); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_SBLPOSTSSMGR_H_ */
