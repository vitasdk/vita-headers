/**
 * \usergroup{SceRazorCapture}
 * \usage{psp2/razor_capture.h,SceRazorCapture_stub,SCE_SYSMODULE_RAZOR_CAPTURE}
 */
 
#ifndef _PSP2_RAZOR_CAPTURE_H_
#define _PSP2_RAZOR_CAPTURE_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sets a trigger for a gpu capture in next frame from Razor debugger
 *
 * @param[in] filename - Filename of the file where to save capture results
*/
void sceRazorGpuCaptureSetTriggerNextFrame(const char *filename);

/**
 * Enables collecting of GPU captures when a gpucrash happens
 *
 * @param[in] filename - Filename of the file where to save capture results
*/
void sceRazorGpuCaptureEnableSalvage(const char *filename);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_RAZOR_CAPTURE_H_ */
