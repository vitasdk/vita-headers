/**
 * \kernelgroup{SceSblSsMgr}
 * \usage{psp2common/sblssmgr.h}
 */

#ifndef _PSP2COMMON_SBLSSMGR_H_
#define _PSP2COMMON_SBLSSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Opaque 32-byte visible identifier returned by aimgr_sm command 8. */
typedef struct SceVisibleId {
	SceUInt8 visible_id[0x20];
} SceVisibleId;
VITASDK_BUILD_ASSERT_EQ(0x20, SceVisibleId); // size is from FW 3.60

/** Console-specific 16-byte OpenPSID. */
typedef struct SceOpenPsId {
	SceUInt8 open_psid[0x10];
} SceOpenPsId;
VITASDK_BUILD_ASSERT_EQ(0x10, SceOpenPsId); // size is from FW 3.60

/** Sixteen-byte console identifier returned by aimgr_sm command 1. */
typedef struct SceConsoleId {
	SceUInt16 unk; //!< Its purpose is unknown; the complete 16-byte identifier is cryptographically significant.
	SceUInt16 company_code;
	SceUInt16 product_code;
	SceUInt16 product_sub_code;
	union {
		struct {
			SceUInt8 unk2: 2; //!< Not interpreted by the FW 3.60 callers examined.
			SceUInt8 factory_code: 6;
		};
		SceUInt8 chassis_check;
	};
	SceUInt8 unk3[7]; //!< Its purpose is unknown; these bytes are used as part of the complete identifier.
} SceConsoleId;
VITASDK_BUILD_ASSERT_EQ(0x10, SceConsoleId); // size is from FW 3.60

/** Eight-byte platform security code returned in host byte order. */
typedef struct ScePsCode {
	SceUInt16 company_code;
	SceUInt16 product_code;
	SceUInt16 product_sub_code;
	SceUInt16 factory_code;
} ScePsCode;
VITASDK_BUILD_ASSERT_EQ(8, ScePsCode); // size is from FW 3.60

/** Fixed-capacity message used by the portability encryption services. */
typedef struct ScePortabilityData {
	SceSize msg_size; //!< Message size; must be 0, 0x10, or 0x20 on FW 3.60.
	SceUInt8 msg[0x20];
} ScePortabilityData;
VITASDK_BUILD_ASSERT_EQ(0x24, ScePortabilityData); // size is from FW 3.60

/** Parameters used to create the 0x200-byte CMA account pass phrase. */
typedef struct SceSblSsCreatePassPhraseParam {
	SceUInt32 secure_module_arg; //!< Set to 0 by the observed FW 3.60 caller; forwarded to aimgr_sm command 5. Its purpose is unknown.
	SceSize size;              //!< Ignored on FW 3.60.
	char account_id_text[0x10];  //!< Sixteen lowercase ASCII hexadecimal account-ID characters; not NUL-terminated.
} SceSblSsCreatePassPhraseParam;
VITASDK_BUILD_ASSERT_EQ(0x18, SceSblSsCreatePassPhraseParam); // size is from FW 3.60

/** NVS values supported by ::ksceSblSsGetNvsData and ::ksceSblSsSetNvsData. */
typedef enum SceSblSsNvsDataType {
	SCE_SBL_SS_NVS_DATA_SYSTEM_LANGUAGE      = 0, //!< Four-byte system-language value at NVS offset 0x4A4.
	SCE_SBL_SS_NVS_DATA_WLAN_BT_AVAILABILITY = 1, //!< One-byte WLAN/Bluetooth availability value at NVS offset 0x500.
	SCE_SBL_SS_NVS_DATA_UNK_482              = 2, //!< One-byte value at NVS offset 0x482; its purpose is unknown.
	SCE_SBL_SS_NVS_DATA_UNK_4E0              = 3, //!< 0x20-byte per-device value at NVS offset 0x4E0; its purpose is unknown.
	SCE_SBL_SS_NVS_DATA_UNK_483              = 4, //!< One-byte value at NVS offset 0x483; its purpose is unknown.
	SCE_SBL_SS_NVS_DATA_UNK_486              = 5  //!< One-byte value at NVS offset 0x486; AppMgr uses bit 0 to select a cloud-data storage location.
} SceSblSsNvsDataType;

/** Flags for supplying or returning a context in DMAC5 hash operations. */
typedef enum SceSblDmac5HashFlag {
	SCE_SBL_DMAC5_HASH_FLAG_OUTPUT_CONTEXT = 0x00000400, //!< Return an updated context instead of a digest.
	SCE_SBL_DMAC5_HASH_FLAG_INPUT_CONTEXT  = 0x00000800  //!< Continue from the supplied context.
} SceSblDmac5HashFlag;

/** DMAC5 key slots accepted by the operations whose names end in `WithKeyslot`. */
typedef enum SceSblDmac5Keyslot {
	SCE_SBL_DMAC5_KEYSLOT_1C = 0x1C,
	SCE_SBL_DMAC5_KEYSLOT_1D = 0x1D,
	SCE_SBL_DMAC5_KEYSLOT_1E = 0x1E,
	SCE_SBL_DMAC5_KEYSLOT_1F = 0x1F
} SceSblDmac5Keyslot;

/** 16-byte chaining value used by the AES-CMAC DMAC5 commands. */
typedef struct SceSblDmac5AesCmacContext {
	SceUInt8 state[0x10];
} SceSblDmac5AesCmacContext;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSblDmac5AesCmacContext); // size is from FW 3.60

/**
 * Chaining context used by SHA-1, SHA-224, and SHA-256 DMAC5 commands.
 */
typedef struct SceSblDmac5HashTransformContext {
	SceUInt32 state[8]; //!< Intermediate hash state.
	SceUInt64 length;   //!< Length of input processed so far, maintained by DMAC5.
} SceSblDmac5HashTransformContext;
VITASDK_BUILD_ASSERT_EQ(0x28, SceSblDmac5HashTransformContext); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_SBLSSMGR_H_ */
