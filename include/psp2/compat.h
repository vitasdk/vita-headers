/**
 * \usergroup{SceCompat}
 * \usage{psp2/compat.h,SceCompat_stub}
 */


#ifndef _PSP2_COMPAT_H_
#define _PSP2_COMPAT_H_

#include <psp2/io/devctl.h>
#include <psp2/rtc.h>
#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceCompatCacheMode {
	SCE_COMPAT_CACHE_NONE           = 0,
	SCE_COMPAT_CACHE_INVALIDATE     = 1,
	SCE_COMPAT_CACHE_WRITEBACK      = 2
} SceCompatCacheMode;

typedef enum SceCompatPeripheralMode {
	SCE_COMPAT_PERIPHERAL_POWER_IS_SUSPEND_REQUIRED   = 1,
	SCE_COMPAT_PERIPHERAL_POWER_GET_BATTERY_LIFETIME  = 2,
	SCE_COMPAT_PERIPHERAL_POWER_GET_BATTERY_PERCENT   = 3,
	SCE_COMPAT_PERIPHERAL_HPREMOTE_IS_HEADPHONE_EXIST = 4
} SceCompatPeripheralMode;

typedef struct SceCompatCdram {
	void *cached_cdram;
	void *uncached_cdram;
} SceCompatCdram;

typedef struct SceCtrlDataPsp {
	unsigned int TimeStamp;
	unsigned int Buttons;
	unsigned char Lx;
	unsigned char Ly;
	unsigned char Rx;
	unsigned char Ry;
	unsigned char Rsrv[4];
} SceCtrlDataPsp;

/**
 * Init compat
 *
 * @param[in] unk - Unknown, pass 0
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatInitEx(int unk);

/**
 * Uninit compat
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatUninit(void);

/**
 * Start compat
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatStart(void);

/**
 * Stop compat
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatStop(void);

/**
 * Allocate cdram with hole
 *
 * @param[out] cdram - A pointer to a ::SceCompatCdram structure.
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatAllocCdramWithHole(SceCompatCdram *cdram);

/**
 * Framebuffer init
 *
 * @param[in] framebuffer - Pointer to framebuffer
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatFrameBufferInit(void *framebuffer);

/**
 * Set suspend semaphores
 *
 * @param[in] semaid1 - Semaphore id 1
 * @param[in] semaid2 - Semaphore id 2
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatSetSuspendSema(SceUID semaid1, SceUID semaid2);

/**
 * Suspend/resume compat
 *
 * @param[in] unk - Unknown, pass 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatSuspendResume(int unk);

/**
 * Cache operation
 *
 * @param[in] mode - One of ::SceCompatCacheMode
 * @param[in] addr - Address
 * @param[in] size - Size
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatCache(int mode, void *addr, SceSize size);

/**
 * Wait for special request
 *
 * @param[in] unk - Unknown, pass 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatWaitSpecialRequest(int unk);

/**
 * Interrupt code
 *
 * @param[in] intr_code - Interrupt code
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatInterrupt(int intr_code);

/**
 * LCDC sync
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatLCDCSync(void);

/**
 * Get primary head
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatGetPrimaryHead(void);

/**
 * Get peripheral state
 *
 * @param[in] mode - One of ::SceCompatPeripheralMode
 *
 * @return state on success, < 0 on error.
*/
int sceCompatGetPeripheralState(int mode);

/**
 * Get compat status
 *
 * @return status on success, < 0 on error.
*/
int sceCompatGetStatus(void);

/**
 * Get update state
 *
 * @return state on success, < 0 on error.
*/
int sceCompatGetUpdateState(void);

/**
 * Set update state
 *
 * @param[in] state - State
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatSetUpdateState(int state);

/**
 * Set display config
 *
 * @param[in] unk0 - Unknown
 * @param[in] unk1 - Unknown
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatSetDisplayConfig(int unk0, int unk1);

/**
 * Set RIF name
 *
 * @param[in] rif - RIF name (max. 36 chars)
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatSetRif(const char *rif);

/**
 * Get PSP system software version
 *
 * @return version on success, < 0 on error.
*/
int sceCompatGetPspSystemSoftwareVersion(void);

/**
 * Get color space setting availability
 *
 * @return 1 if true, 0 if false, < 0 on error.
*/
int sceCompatAvailableColorSpaceSetting(void);

/**
 * Check if pocket station application is available
 *
 * @return 1 if true, 0 if false, < 0 on error.
*/
int sceCompatCheckPocketStation(void);

/**
 * Check if current title is a pocket station game
 *
 * @return 1 if true, 0 if false, < 0 on error.
*/
int sceCompatIsPocketStationTitle(void);

/**
 * Wait for command and get request
 *
 * @param[in] mode - Mode
 * @param[in] id - ID
 *
 * @return pointer to request in PspEmu RAM on success, < 0 on error.
*/
int sceCompatWaitAndGetRequest(int mode, int id);

/**
 * Read from shared sram
 *
 * @param[in] location - Location
 * @param[out] value - Pointer to a int buffer to hold the value
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatReadShared32(int location, int *value);

/**
 * Write to shared sram
 *
 * @param[in] location - Location
 * @param[in] value - Value
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatWriteShared32(int location, int value);

/**
 * Write shared control
 *
 * @param[in] info - A pointer to a ::SceCtrlDataPsp structure.
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatWriteSharedCtrl(SceCtrlDataPsp *pad_data);

/**
 * Get title list
 *
 * @param[out] buf - A 100 bytes buffer for the title list
 * @param[in] length - Must be 100
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatGetTitleList(void *buf, SceSize length);

/**
 * Get Memory Card device information
 *
 * @param[out] info - A pointer to a ::SceIoDevInfo structure.
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatGetDevInf(SceIoDevInfo *info);

/**
 * Get current secure tick
 *
 * @param[out] tick - A pointer to a ::SceRtcTick structure.
 *
 * @return 0 on success, < 0 on error.
*/
int sceCompatGetCurrentSecureTick(SceRtcTick *tick);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_COMPAT_H_ */

