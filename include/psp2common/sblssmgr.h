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

typedef struct SceVisibleId {
	unsigned char visible_id[0x20];
} SceVisibleId;
VITASDK_BUILD_ASSERT_EQ(0x20, SceVisibleId); // size is from FW 3.60

typedef struct SceOpenPsId {
	uint8_t open_psid[0x10];
} SceOpenPsId;
VITASDK_BUILD_ASSERT_EQ(0x10, SceOpenPsId); // size is from FW 3.60

typedef enum SceSblDmac5HashFlag {
	SCE_SBL_DMAC5_HASH_FLAG_OUTPUT_CONTEXT = 0x00000400, //!< Store the updated hash context.
	SCE_SBL_DMAC5_HASH_FLAG_INPUT_CONTEXT  = 0x00000800  //!< Load the supplied hash context.
} SceSblDmac5HashFlag;

/**
 * Chaining context used by SHA-1, SHA-224, and SHA-256 DMAC5 commands.
 */
typedef struct SceSblDmac5HashTransformContext {
	SceUInt32 state[8]; //!< Intermediate hash state.
	SceUInt64 length; //!< Processed input length.
} SceSblDmac5HashTransformContext;
VITASDK_BUILD_ASSERT_EQ(0x28, SceSblDmac5HashTransformContext); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_SBLSSMGR_H_ */
