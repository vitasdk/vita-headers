/**
 * \usergroup{SceCtrl}
 * \usage{psp2/ctrl.h,SceCtrl_stub}
 */


#ifndef _PSP2_CTRL_H_
#define _PSP2_CTRL_H_

#include <stdint.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceCtrlErrorCode {
	SCE_CTRL_ERROR_INVALID_ARG   = 0x80340001,
	SCE_CTRL_ERROR_PRIV_REQUIRED = 0x80340002,
	SCE_CTRL_ERROR_NO_DEVICE     = 0x80340020,
	SCE_CTRL_ERROR_NOT_SUPPORTED = 0x80340021,
	SCE_CTRL_ERROR_INVALID_MODE  = 0x80340022,
	SCE_CTRL_ERROR_FATAL         = 0x803400FF
} SceCtrlErrorCode;

/** Enumeration for the digital controller buttons.
 * @note - L1/R1/L3/R3 only can bind using ::sceCtrlPeekBufferPositiveExt2 and ::sceCtrlReadBufferPositiveExt2
 * @note - Values bigger than 0x00010000 can be intercepted only with shell privileges
 * @note - Vita's L Trigger and R Trigger are mapped to L1 and R1 when using ::sceCtrlPeekBufferPositiveExt2 and ::sceCtrlReadBufferPositiveExt2
 */
typedef enum SceCtrlButtons {
	SCE_CTRL_SELECT      = 0x00000001,            //!< Select button.
	SCE_CTRL_L3          = 0x00000002,            //!< L3 button.
	SCE_CTRL_R3          = 0x00000004,            //!< R3 button.
	SCE_CTRL_START       = 0x00000008,            //!< Start button.
	SCE_CTRL_UP          = 0x00000010,            //!< Up D-Pad button.
	SCE_CTRL_RIGHT       = 0x00000020,            //!< Right D-Pad button.
	SCE_CTRL_DOWN        = 0x00000040,            //!< Down D-Pad button.
	SCE_CTRL_LEFT        = 0x00000080,            //!< Left D-Pad button.
	SCE_CTRL_LTRIGGER    = 0x00000100,            //!< Left trigger.
	SCE_CTRL_L2          = SCE_CTRL_LTRIGGER,     //!< L2 button.
	SCE_CTRL_RTRIGGER    = 0x00000200,            //!< Right trigger.
	SCE_CTRL_R2          = SCE_CTRL_RTRIGGER,     //!< R2 button.
	SCE_CTRL_L1          = 0x00000400,            //!< L1 button.
	SCE_CTRL_R1          = 0x00000800,            //!< R1 button.
	SCE_CTRL_TRIANGLE    = 0x00001000,            //!< Triangle button.
	SCE_CTRL_CIRCLE      = 0x00002000,            //!< Circle button.
	SCE_CTRL_CROSS       = 0x00004000,            //!< Cross button.
	SCE_CTRL_SQUARE      = 0x00008000,            //!< Square button.
	SCE_CTRL_INTERCEPTED = 0x00010000,            //!< Input not available because intercepted by another application
	SCE_CTRL_PSBUTTON    = SCE_CTRL_INTERCEPTED,  //!< Playstation (Home) button.
	SCE_CTRL_HEADPHONE   = 0x00080000,            //!< Headphone plugged in.
	SCE_CTRL_VOLUP       = 0x00100000,            //!< Volume up button.
	SCE_CTRL_VOLDOWN     = 0x00200000,            //!< Volume down button.
	SCE_CTRL_POWER       = 0x40000000             //!< Power button.
} SceCtrlButtons;

/** Enumeration for the controller types. */
typedef enum SceCtrlExternalInputMode {
	SCE_CTRL_TYPE_UNPAIRED  = 0, //!< Unpaired controller
	SCE_CTRL_TYPE_PHY       = 1, //!< Physical controller for VITA
	SCE_CTRL_TYPE_VIRT      = 2, //!< Virtual controller for PSTV
	SCE_CTRL_TYPE_DS3       = 4, //!< DualShock 3
	SCE_CTRL_TYPE_DS4       = 8  //!< DualShock 4
} SceCtrlExternalInputMode;

/** Controller mode. */
typedef enum SceCtrlPadInputMode {
	/** Digital buttons only. */
	SCE_CTRL_MODE_DIGITAL     = 0,
	/** Digital buttons + Analog support. */
	SCE_CTRL_MODE_ANALOG      = 1,
	/** Same as ::SCE_CTRL_MODE_ANALOG, but with larger range for analog sticks. */
	SCE_CTRL_MODE_ANALOG_WIDE = 2
} SceCtrlPadInputMode;

/** Returned controller data */
typedef struct SceCtrlData {
	/** The current read frame. */
	uint64_t	timeStamp;
	/** Bit mask containing zero or more of ::SceCtrlButtons. */
	unsigned int 	buttons;
	/** Left analogue stick, X axis. */
	unsigned char 	lx;
	/** Left analogue stick, Y axis. */
	unsigned char 	ly;
	/** Right analogue stick, X axis. */
	unsigned char 	rx;
	/** Right analogue stick, Y axis. */
	unsigned char 	ry;
	/** Up button */
	uint8_t		up;
	/** Right button */
	uint8_t		right;
	/** Down button */
	uint8_t		down;
	/** Left button */
	uint8_t		left;
	/** Left trigger (L2) */
	uint8_t		lt;
	/** Right trigger (R2) */
	uint8_t		rt;
	/** Left button (L1) */
	uint8_t		l1;
	/** Right button (R1) */
	uint8_t		r1;
	/** Triangle button */
	uint8_t		triangle;
	/** Circle button */
	uint8_t		circle;
	/** Cross button */
	uint8_t		cross;
	/** Square button */
	uint8_t		square;
	/** Reserved. */
	uint8_t 	reserved[4];
} SceCtrlData;

/** Structure to pass as argument to ::sceCtrlSetRapidFire */
typedef struct SceCtrlRapidFireRule {
	unsigned int Mask;
	unsigned int Trigger;
	unsigned int Target;
	unsigned int Delay;
	unsigned int Make;
	unsigned int Break;
} SceCtrlRapidFireRule;

/** Structure to pass as argument to ::sceCtrlSetActuator */
typedef struct SceCtrlActuator {
	unsigned char small; //!< Vibration strength of the small motor
	unsigned char large; //!< Vibration strength of the large motor
	uint8_t unk[6];      //!< Unknown
} SceCtrlActuator;

/** Structure to pass as argument to ::sceCtrlGetControllerPortInfo */
typedef struct SceCtrlPortInfo {
	uint8_t port[5];  //!< Controller type of each port (See ::SceCtrlExternalInputMode)
	uint8_t unk[11];  //!< Unknown
} SceCtrlPortInfo;

/**
 * Set the controller mode.
 *
 * @param[in] mode - One of ::SceCtrlPadInputMode.
 *
 * @return The previous mode, <0 on error.
 */
int sceCtrlSetSamplingMode(SceCtrlPadInputMode mode);

/**
 * Set the controller extend mode.
 *
 * @param[in] mode - One of ::SceCtrlPadInputMode.
 *
 * @return The previous mode, <0 on error.
 */
int sceCtrlSetSamplingModeExt(SceCtrlPadInputMode mode);

/**
 * Get the current controller mode.
 *
 * @param[out] pMode - Return value, see ::SceCtrlPadInputMode.
 *
 * @return The current mode, <0 on error.
 */
int sceCtrlGetSamplingMode(SceCtrlPadInputMode *pMode);

/**
 * Get the controller state information (polling, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (polling, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0 - 5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositive2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (polling, positive logic).
 *
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositiveExt(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (polling, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0 - 5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositiveExt2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (polling, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (polling, negative logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferNegative2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (blocking, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositive2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller extended state information (blocking, positive logic).
 *
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositiveExt(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller extended state information (blocking, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositiveExt2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (blocking, negative logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferNegative2(int port, SceCtrlData *pad_data, int count);

/**
 * Set rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 * @param[in] pRule - structure ::SceCtrlRapidFireRule.
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetRapidFire(int port, int idx, const SceCtrlRapidFireRule* pRule);

/**
 * Clear rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 *
 * @return 0, <0 on error.
 */
int sceCtrlClearRapidFire(int port, int idx);

/**
 * Control the actuator (vibrate) on paired controllers.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[in] state - see ::SceCtrlActuator
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetActuator(int port, const SceCtrlActuator* pState);

/**
 * Control the light bar on paired controllers.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[in] r - red intensity
 * @param[in] g - green intensity
 * @param[in] b - blue intensity
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetLightBar(int port, SceUInt8 r, SceUInt8 g, SceUInt8 b);

/**
 * Get controller port information.
 *
 * @param[out] info - see ::SceCtrlPortInfo
 * @return 0, <0 on error
 */
int sceCtrlGetControllerPortInfo(SceCtrlPortInfo *info);

/**
 * Get controller battery information.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[out] batt - battery level, between 0-5, 0xEE charging, 0xEF charged
 *
 * @return 0, <0 on error.
 */
int sceCtrlGetBatteryInfo(int port, SceUInt8 *batt);

/**
 * Sets intercept
 *
 * If true, allows the current thread to intercept controls. The use case
 * might be, for example, a game plugin that wishes to capture input without
 * having the input sent to the game thread.
 * @param[in]  intercept  Boolean value
 *
 * @return 0, < 0 on error
 */
int sceCtrlSetButtonIntercept(int intercept);

/**
 * Gets intercept
 *
 * @param[out]  intercept  Boolean value
 *
 * @return 0, < 0 on error
 */
int sceCtrlGetButtonIntercept(int *intercept);

/**
 * Check if multi controller is supported
 *
 * @return 1 if yes, 0 if no
 */
int sceCtrlIsMultiControllerSupported(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_CTRL_H_ */
