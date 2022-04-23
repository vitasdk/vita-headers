/**
 * \usergroup{SceTouch}
 * \usage{psp2/touch.h,SceTouch_stub}
 */


#ifndef _PSP2_TOUCH_H_
#define _PSP2_TOUCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <psp2/types.h>

/** Touch error codes */
typedef enum SceTouchErrorCode {
	SCE_TOUCH_ERROR_INVALID_ARG   = 0x80350001,
	SCE_TOUCH_ERROR_PRIV_REQUIRED = 0x80350002,
	SCE_TOUCH_ERROR_FATAL         = 0x803500FF
} SceTouchErrorCode;

#define SCE_TOUCH_MAX_REPORT 8	//!< FIXME 6 on front | 4 on back

/**
 * Port numbers of touch panels
 *
 * @see ::sceTouchRead
 * @see ::sceTouchPeek
 */
typedef enum SceTouchPortType {
	SCE_TOUCH_PORT_FRONT   = 0, //!< Front touch panel id
	SCE_TOUCH_PORT_BACK    = 1, //!< Back touch panel id
	SCE_TOUCH_PORT_MAX_NUM = 2  //!< Number of touch panels
} SceTouchPortType;

/**
 * Sampling port setting of the touch panel
 *
 * @see ::sceTouchSetSamplingState
 */
typedef enum SceTouchSamplingState {
	SCE_TOUCH_SAMPLING_STATE_STOP   = 0,
	SCE_TOUCH_SAMPLING_STATE_START  = 1
} SceTouchSamplingState;

/**
 * Info field of ::SceTouchReport structure
 *
 * @see ::SceTouchReport
 */
typedef enum SceTouchReportInfo {
	SCE_TOUCH_REPORT_INFO_HIDE_UPPER_LAYER = 0x0001
} SceTouchReportInfo;

typedef struct SceTouchPanelInfo {
	SceInt16 minAaX;        //!< Min active area X position
	SceInt16 minAaY;        //!< Min active area Y position
	SceInt16 maxAaX;        //!< Max active area X position
	SceInt16 maxAaY;        //!< Max active area Y position
	SceInt16 minDispX;      //!< Min display X origin (top left)
	SceInt16 minDispY;      //!< Min display Y origin (top left)
	SceInt16 maxDispX;      //!< Max display X origin (bottom right)
	SceInt16 maxDispY;      //!< Max display Y origin (bottom right)
	SceUInt8 minForce;      //!< Min touch force value
	SceUInt8 maxForce;      //!< Max touch force value
	SceUInt8 reserved[30];  //!< Reserved
} SceTouchPanelInfo;

typedef struct SceTouchReport {
	SceUInt8	id;          //!< Touch ID
	SceUInt8 	force;       //!< Touch force
	SceInt16 	x;           //!< X position
	SceInt16 	y;           //!< Y position
	SceUInt8 	reserved[8]; //!< Reserved
	SceUInt16 	info;        //!< Information of this touch
} SceTouchReport;

typedef struct SceTouchData {
	SceUInt64       timeStamp;                    //!< Data timestamp
	SceUInt32       status;                       //!< Unused
	SceUInt32       reportNum;                    //!< Number of touch reports
	SceTouchReport	report[SCE_TOUCH_MAX_REPORT]; //!< Touch reports
} SceTouchData;

/**
 * Get Touch Panel information
 *
 * @param[in]	port		Port number.
 * @param[out]	pPanelInfo	The buffer to get the Touch Panel information.
 */
int sceTouchGetPanelInfo(SceUInt32 port, SceTouchPanelInfo *pPanelInfo);

/**
 * Get touch data (Blocking)
 *
 * @param[in]	port	Port Number.
 * @param[out]	pData	Buffer to receive touch data.
 * @param[in]	nBufs	Number of buffers to receive touch data.
 *
 * @return Buffers count, between 1 and 'nBufs'. <0 on error.
 */
int sceTouchRead(SceUInt32 port, SceTouchData *pData, SceUInt32 nBufs);

/**
 * Get touch data (Polling)
 *
 * @param[in]	port	port number.
 * @param[out]	pData	Buffer to receive touch data.
 * @param[in]	nBufs	Number of buffers to receive touch data.
 *
 * @return Buffers count, between 1 and 'nBufs'. <0 on error.
 */
int sceTouchPeek(SceUInt32 port, SceTouchData *pData, SceUInt32 nBufs);

/**
 * Set sampling state of touch panel.
 *
 * @param[in]	port	Port number.
 * @param[in]	state	Sampling state.
 */
int sceTouchSetSamplingState(SceUInt32 port, SceTouchSamplingState state);

/**
 * Get sampling state of touch panel.
 *
 * @param[in]	port	Port number.
 * @param[out]	pState	The buffer to receive sampling state.
 */
int sceTouchGetSamplingState(SceUInt32 port, SceTouchSamplingState *pState);

/**
 * Enable touch force output.
 *
 * @param[in]	port	Port number.
 */
int sceTouchEnableTouchForce(SceUInt32 port);

/**
 * Disable touch force output.
 *
 * @param[in]	port	Port number.
 */
int sceTouchDisableTouchForce(SceUInt32 port);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_TOUCH_H_ */

