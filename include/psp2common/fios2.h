/**
 * \kernelgroup{SceFios2Kernel}
 * \usage{psp2common/fios2.h}
 */

#ifndef _PSP2COMMON_FIOS2KERNEL_H_
#define _PSP2COMMON_FIOS2KERNEL_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


#define SCE_FIOS2_OVERLAY_PATH_SIZE       (292)
#define SCE_FIOS2_OVERLAY_PATH_MAX_LENGTH (SCE_FIOS2_OVERLAY_PATH_SIZE - 1)

typedef int32_t SceFiosOverlayID;

typedef enum SceFiosOverlayType {
  // src replaces dst. All accesses to dst are redirected to src.
  SCE_FIOS_OVERLAY_TYPE_OPAQUE      = 0,

  // src merges with dst. Reads check src first, then dst. Writes go to dst.
  SCE_FIOS_OVERLAY_TYPE_TRANSLUCENT = 1,

  // src merges with dst. Reads check both src and dst, and use whichever has the most recent modification time.
  // If both src and dst have the same modification time, dst is used.
  // If no file exists at src or dst, dst is used; if no file exists at dst, but a file exists at src, src is used. Writes go to dst.
  SCE_FIOS_OVERLAY_TYPE_NEWER       = 2,

  // src merges with dst. Reads check src first, then dst. Writes go to src.
  SCE_FIOS_OVERLAY_TYPE_WRITABLE    = 3
} SceFiosOverlayType;

typedef struct SceFiosOverlay {
  uint8_t type; // see SceFiosOverlayType
  uint8_t order;
  uint16_t dst_len;
  uint16_t src_len;
  uint16_t unk2;
  SceUID pid;
  SceFiosOverlayID id;
  char dst[SCE_FIOS2_OVERLAY_PATH_SIZE];
  char src[SCE_FIOS2_OVERLAY_PATH_SIZE]; // src path replaces dst path based on type policy
} SceFiosOverlay;


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_FIOS2KERNEL_H_ */
