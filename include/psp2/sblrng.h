/**
 * \usergroup{SceSblRng}
 * \usage{psp2/sblrng.h,SceSblSsMgr_stub}
 */

#ifndef _PSP2_SBLRNG_H_
#define _PSP2_SBLRNG_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelGetRandomNumberParam {
	SceUInt32 dstSize; //!< In bytes. Must be <= 0x40.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceKernelGetRandomNumberParam;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelGetRandomNumberParam); // size is from FW 3.60

/**
 * @param[in] pParam - Parameter structure. The FW 3.60 provider only reads it.
 */
int _sceKernelGetRandomNumber(void *pDst, SceSize length, SceKernelGetRandomNumberParam *pParam);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLRNG_H_ */
