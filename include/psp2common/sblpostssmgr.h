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

/** Product modes reported by SceSblPmMgr. */
typedef enum SceSblProductMode {
	SCE_SBL_PRODUCT_MODE_NORMAL        = 0,
	SCE_SBL_PRODUCT_MODE_MANUFACTURING = 1
} SceSblProductMode;

/** Cached development/testing-kit activation states reported by SceSblLicMgr. */
typedef enum SceSblLicenseStatus {
	SCE_SBL_LICENSE_STATUS_UNINITIALIZED          = -1,
	SCE_SBL_LICENSE_STATUS_ACTIVATED              = 0,
	SCE_SBL_LICENSE_STATUS_EXPIRED                = 1,
	SCE_SBL_LICENSE_STATUS_BACKUP_BATTERY_FAILURE = 2
} SceSblLicenseStatus;

typedef struct SceSblActivationKey {
	SceUInt8 open_psid[0x10]; //!< A ::SceOpenPsId value.
	SceUInt32 vadd_hash;      //!< Four byte-wise sums of the OpenPSID lanes.
} SceSblActivationKey;
VITASDK_BUILD_ASSERT_EQ(0x14, SceSblActivationKey); // size is from FW 3.60

/** An SPSFO file mapped by ::ksceSblSpsfoMgrOpen. */
typedef struct SceSblSpsfoContext {
	SceUID mem_uid;          //!< Memory block UID.
	void *mem_block_base;    //!< Mapped memory block base address.
	SceSize file_size;       //!< Exact SPSFO file size.
} SceSblSpsfoContext;
VITASDK_BUILD_ASSERT_EQ(0xC, SceSblSpsfoContext); // size is from FW 3.60

/** Misspelled alias retained for backwards compatibility. */
typedef SceSblSpsfoContext SceSblSpfsoContext;

typedef struct SceSblAppKey {
	SceSize size;       //!< Number of valid key bytes. Must be 0x10 or 0x20.
	SceUInt8 key[0x20]; //!< Key data.
} SceSblAppKey;
VITASDK_BUILD_ASSERT_EQ(0x24, SceSblAppKey); // size is from FW 3.60

typedef struct SceUtoken {
	SceUInt8 encrypted_data[0x800]; //!< Encrypted Utoken file contents.
} SceUtoken;
VITASDK_BUILD_ASSERT_EQ(0x800, SceUtoken); // size is from FW 3.60

/** Complete SELF authorization override stored in Utoken segment type 11. */
typedef struct SceUtokenSelfAuthInfo {
	SceUInt64 program_authority_id; //!< Replacement program authority ID.
	SceUInt8 capability[0x20];      //!< Replacement capability bits.
	SceUInt8 attribute[0x20];       //!< Replacement attribute bits.
	SceUInt8 shared_secret[0x10];   //!< Replacement shared secret.
} SceUtokenSelfAuthInfo;
VITASDK_BUILD_ASSERT_EQ(0x58, SceUtokenSelfAuthInfo); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_SBLPOSTSSMGR_H_ */
