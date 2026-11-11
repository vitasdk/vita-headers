/**
 * \kernelgroup{SceFios2Kernel}
 * \usage{psp2common/fios2.h}
 */

#ifndef _PSP2COMMON_FIOS2KERNEL_H_
#define _PSP2COMMON_FIOS2KERNEL_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


#define SCE_FIOS2_OVERLAY_PATH_SIZE       (292)
#define SCE_FIOS2_OVERLAY_PATH_MAX_LENGTH (SCE_FIOS2_OVERLAY_PATH_SIZE - 1)

typedef int32_t SceFiosOverlayID;
VITASDK_BUILD_ASSERT_EQ(4, SceFiosOverlayID);

typedef enum SceFiosOverlayType {
	SCE_FIOS_OVERLAY_TYPE_OPAQUE      = 0, //!< Always replace the matching destination path with the source path.
	SCE_FIOS_OVERLAY_TYPE_TRANSLUCENT = 1, //!< Use the source path when it exists, otherwise use the destination path.
	SCE_FIOS_OVERLAY_TYPE_NEWER       = 2, //!< Use the source path when it is newer or the destination is missing; otherwise use the destination path.
	SCE_FIOS_OVERLAY_TYPE_WRITABLE    = 3  //!< Reads prefer an existing source path and writes always use the source path.
} SceFiosOverlayType;

/**
 * File-system overlay configuration and returned state.
 *
 * When adding or modifying an overlay, FIOS2 copies the structure before the
 * function returns. Keep the structure valid until then; you may reuse or free
 * it afterwards. Supply type, order, dst, and src; FIOS2 normalizes the paths and
 * fills in the other fields. A per-process overlay remains installed until it
 * is removed or the process exits.
 */
typedef struct SceFiosOverlay {
	uint8_t type; //!< One of ::SceFiosOverlayType.
	uint8_t order; //!< Resolution order. Lower values are evaluated first; 0x00-0x7F are application orders and 0x80-0xFF are reserved for privileged overlays.
	uint16_t dst_len; //!< Destination-path length computed by FIOS2.
	uint16_t src_len; //!< Source-path length computed by FIOS2.
	uint16_t reserved; //!< Set to zero by FIOS2.
	SceUID pid; //!< Target process ID. Used by ::ksceFiosKernelOverlayAdd and overwritten by functions that take a process ID argument.
	SceFiosOverlayID id; //!< Overlay ID assigned by FIOS2; ignored when adding an overlay.
	char dst[SCE_FIOS2_OVERLAY_PATH_SIZE]; //!< Destination-path prefix matched during resolution.
	char src[SCE_FIOS2_OVERLAY_PATH_SIZE]; //!< Source-path prefix substituted according to ::SceFiosOverlayType.
} SceFiosOverlay;
VITASDK_BUILD_ASSERT_EQ(0x258, SceFiosOverlay);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_FIOS2KERNEL_H_ */
