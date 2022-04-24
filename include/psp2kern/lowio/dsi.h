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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_DSI_H_ */

