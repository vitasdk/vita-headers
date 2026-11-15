/**
 * \kernelgroup{SceDsi}
 * \usage{psp2kern/lowio/dsi.h,SceDsiForDriver_stub}
 */

#ifndef _PSP2KERN_LOWIO_DSI_H_
#define _PSP2KERN_LOWIO_DSI_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceDsiErrorCode {
	SCE_DSI_ERROR_INVALID_HEAD	= 0x803F0600,
	SCE_DSI_ERROR_INVALID_STATE	= 0x803F0601,
	SCE_DSI_ERROR_INVALID_PARAM	= 0x803F0602,
	SCE_DSI_ERROR_HEAD_NOT_ENABLED	= 0x803F0603,
} SceDsiErrorCode;

typedef enum SceDsiHead {
	SCE_DSI_HEAD_OLED_LCD	= 0,
	SCE_DSI_HEAD_HDMI	= 1,
} SceDsiHead;

int ksceDsiEnableHead(int head);
int ksceDsiDisableHead(int head);
int ksceDsiSendBlankingPacket(int head);
int ksceDsiSetLanesAndPixelSize(int head, int lanes, int pixelsize);
int ksceDsiSetVic(int head, int vic);
int ksceDsiGetVicResolution(int vic, int *width, int *height);
int ksceDsiGetPixelClock(int head);
int ksceDsiGenericShortWrite(int head, int param0, int param1, int param2);
int ksceDsiGenericReadRequest(int head, int param, void *buff, unsigned int size);
int ksceDsiDcsShortWrite(int head, unsigned short param0, int param1);
int ksceDsiDcsRead(int head, unsigned short param, void *buff, unsigned int size);

/**
 * Start scanout on a configured DSI head.
 *
 * FW 3.60 accepts start-control values 0 through 4 and writes the following
 * hardware start values:
 *
 * - 0: writes 1 for either head.
 * - 1: writes 1 for head 0 and 2 for head 1.
 * - 2: writes 2 for head 0 and 1 for head 1.
 * - 3 or 4: writes the given value.
 *
 * SceDisplay uses values 0 through 3; no loaded FW 3.60 caller uses value 4.
 *
 * @param[in] head - One of ::SceDsiHead.
 * @param[in] start_control - DSI start-control value from 0 through 4.
 *
 * @return 0 on success, ::SCE_DSI_ERROR_INVALID_HEAD for an invalid head,
 * ::SCE_DSI_ERROR_INVALID_PARAM for an invalid start control, or
 * ::SCE_DSI_ERROR_INVALID_STATE if the head has not been configured.
 */
int ksceDsiStartDisplay(SceDsiHead head, SceUInt32 start_control);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_DSI_H_ */
