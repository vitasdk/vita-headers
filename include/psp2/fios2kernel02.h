/**
 * \usergroup{SceFios2Kernel}
 * \usage{psp2/fios2kernel02.h,SceFios2Kernel_stub}
 */

#ifndef _PSP2_FIOS2KERNEL02_H_
#define _PSP2_FIOS2KERNEL02_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/fios2.h>

#ifdef __cplusplus
extern "C" {
#endif


int sceFiosKernelOverlayAddForProcess02(SceUID pid, SceFiosOverlay *overlay, SceFiosOverlayID *outID);


typedef struct sceFiosKernelOverlayGetList02_opt {
	SceFiosOverlayID *outIDs; //!< Output buffer for overlay IDs; may be NULL only when maxIDs is zero.
	size_t maxIDs; //!< Maximum number of overlay IDs to write.
	size_t *actualIDs; //!< Optional pointer receiving the total match count, including entries beyond maxIDs.
	int buffer_size; //!< Size of the output buffer in bytes; a ::SceSize value.
	int reserved1; //!< Ignored on FW 3.60.
	int reserved2; //!< Ignored on FW 3.60.
} sceFiosKernelOverlayGetList02_opt;
VITASDK_BUILD_ASSERT_EQ(0x18, sceFiosKernelOverlayGetList02_opt); // size is from FW 3.60

typedef struct sceFiosKernelOverlayGetRecommendedScheduler02_opt {
	int reserved1; //!< Ignored on FW 3.60.
	int reserved2; //!< Ignored on FW 3.60.
} sceFiosKernelOverlayGetRecommendedScheduler02_opt;
VITASDK_BUILD_ASSERT_EQ(0x8, sceFiosKernelOverlayGetRecommendedScheduler02_opt); // size is from FW 3.60

typedef struct sceFiosKernelOverlayResolveSync02_opt {
	char *outPath; //!< Resolved path output buffer.
	size_t maxPath; //!< Maximum path length used by the resolver.
	int reserved1; //!< Ignored on FW 3.60.
	int outPathBufferSize; //!< Number of bytes copied to the output buffer; a ::SceSize value.
	int reserved3; //!< Ignored on FW 3.60.
	int reserved4; //!< Ignored on FW 3.60.
} sceFiosKernelOverlayResolveSync02_opt;
VITASDK_BUILD_ASSERT_EQ(0x18, sceFiosKernelOverlayResolveSync02_opt); // size is from FW 3.60

typedef struct sceFiosKernelOverlayResolveWithRangeSync02_opt {
	char *outPath; //!< Resolved path output buffer.
	size_t maxPath; //!< Maximum path length used by the resolver.
	char loOrderFilter; //!< Minimum value of an overlay's order field to include; treated as a ::SceUInt8 value.
	char hiOrderFilter; //!< Maximum value of an overlay's order field to include; treated as a ::SceUInt8 value.
	char reserved1; //!< Ignored on FW 3.60.
	char reserved2; //!< Ignored on FW 3.60.
	int reserved3; //!< Ignored on FW 3.60.
	int outPathBufferSize; //!< Number of bytes copied to the output buffer; a ::SceSize value.
	int reserved5; //!< Ignored on FW 3.60.
	int reserved6; //!< Ignored on FW 3.60.
} sceFiosKernelOverlayResolveWithRangeSync02_opt;
VITASDK_BUILD_ASSERT_EQ(0x1C, sceFiosKernelOverlayResolveWithRangeSync02_opt); // size is from FW 3.60

int sceFiosKernelOverlayGetInfoForProcess02(SceUID pid, SceFiosOverlayID id, SceFiosOverlay *overlay);

/**
 * Gets the overlay IDs in an inclusive order range.
 *
 * @param[in]  pid           - Process whose overlays are enumerated.
 * @param[in]  loOrderFilter - Minimum value of an overlay's order field to include; treated as a ::SceUInt8 value.
 * @param[in]  hiOrderFilter - Maximum value of an overlay's order field to include; treated as a ::SceUInt8 value.
 * @param[in]  opt           - Enumeration options and output pointers.
 *
 * @return Error code or zero on success.
 */
int sceFiosKernelOverlayGetList02(SceUID pid, char loOrderFilter, char hiOrderFilter, sceFiosKernelOverlayGetList02_opt *opt);

/**
 * Gets the recommended scheduler index for a partially resolved path.
 *
 * @param[in] schedulerCount        - Number of available schedulers.
 * @param[in] partiallyResolvedPath - Partially resolved path.
 * @param[in] opt                   - Reserved options copied but actually unused on FW 3.60.
 *
 * @return 1 for a host[0-9]: path when schedulerCount is greater than 1, otherwise 0.
 */
int sceFiosKernelOverlayGetRecommendedScheduler02(int schedulerCount, char *partiallyResolvedPath, sceFiosKernelOverlayGetRecommendedScheduler02_opt *opt);
int sceFiosKernelOverlayModifyForProcess02(SceUID pid, SceFiosOverlayID id, const SceFiosOverlay *newValue);
int sceFiosKernelOverlayRemoveForProcess02(SceUID pid, SceFiosOverlayID id);
int sceFiosKernelOverlayResolveSync02(SceUID pid, int resolveForWrite, const char *inPath, sceFiosKernelOverlayResolveSync02_opt *opt);

/**
 * Resolves a path through overlays within an inclusive order range.
 *
 * The order-filter fields in @p opt are treated as ::SceUInt8 values.
 *
 * @param[in]  pid             - Process whose overlays are used.
 * @param[in]  resolveForWrite - 0 for read resolution, 1 for write resolution.
 * @param[in]  inPath          - Path to resolve.
 * @param[in]  opt             - Resolution options and output buffer.
 *
 * @return Error code or zero on success.
 */
int sceFiosKernelOverlayResolveWithRangeSync02(SceUID pid, int resolveForWrite, const char *inPath, sceFiosKernelOverlayResolveWithRangeSync02_opt *opt);
int sceFiosKernelOverlayThreadIsDisabled02(void);
int sceFiosKernelOverlayThreadSetDisabled02(int value);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FIOS2KERNEL02_H_ */
