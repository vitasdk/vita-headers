/**
 * \kernelgroup{SceCtrl}
 * \usage{psp2kern/ctrl.h,-lSceCtrlForDriver_stub}
 */


#ifndef _PSP2_KERNEL_CTRL_H_
#define _PSP2_KERNEL_CTRL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_CTRL_ERROR_INVALID_ARG	= 0x80340001,
	SCE_CTRL_ERROR_PRIV_REQUIRED	= 0x80340002,
	SCE_CTRL_ERROR_FATAL		= 0x803400FF
};

/** Enumeration for the digital controller buttons.
 * L1/R1/L3/R3 only can bind using ksceCtrlReadBufferPositiveExt2 */
enum SceCtrlPadButtons {
	SCE_CTRL_SELECT      = 0x000001,	//!< Select button.
	SCE_CTRL_L3          = 0x000002,	//!< L3 button.
	SCE_CTRL_R3          = 0x000004,	//!< R3 button.
	SCE_CTRL_START       = 0x000008,	//!< Start button.
	SCE_CTRL_UP          = 0x000010,	//!< Up D-Pad button.
	SCE_CTRL_RIGHT       = 0x000020,	//!< Right D-Pad button.
	SCE_CTRL_DOWN        = 0x000040,	//!< Down D-Pad button.
	SCE_CTRL_LEFT        = 0x000080,	//!< Left D-Pad button.
	SCE_CTRL_LTRIGGER    = 0x000100,	//!< Left trigger.
	SCE_CTRL_RTRIGGER    = 0x000200,	//!< Right trigger.
	SCE_CTRL_L1          = 0x000400,	//!< L1 button.
	SCE_CTRL_R1          = 0x000800,	//!< R1 button.
	SCE_CTRL_TRIANGLE    = 0x001000,	//!< Triangle button.
	SCE_CTRL_CIRCLE      = 0x002000,	//!< Circle button.
	SCE_CTRL_CROSS       = 0x004000,	//!< Cross button.
	SCE_CTRL_SQUARE      = 0x008000,	//!< Square button.
	SCE_CTRL_INTERCEPTED = 0x010000,        //!< Input not available because intercepted by another application
	SCE_CTRL_VOLUP       = 0x100000,	//!< Volume up button.
	SCE_CTRL_VOLDOWN     = 0x200000		//!< Volume down button.
};

/** Enumeration for the controller types. */
enum  SceCtrlExternalInputMode {
	SCE_CTRL_TYPE_UNPAIRED  = 0,
	SCE_CTRL_TYPE_PHY       = 1, //!< Physical controller for VITA
	SCE_CTRL_TYPE_VIRT      = 2, //!< Virtual controller for PSTV
	SCE_CTRL_TYPE_DS3       = 4, //!< DualShock 3
	SCE_CTRL_TYPE_DS4       = 8  //!< DualShock 4
};

/** Controller mode. */
enum SceCtrlPadInputMode {
	/** Digitial buttons only. */
	SCE_CTRL_MODE_DIGITAL = 0,
	/** Digital buttons + Analog support. */
	SCE_CTRL_MODE_ANALOG = 1,
	/** Same as ::SCE_CTRL_MODE_ANALOG, but with larger range for analog sticks. */
	SCE_CTRL_MODE_ANALOG_WIDE = 2
};

/** Returned controller data */
typedef struct SceCtrlData {
	/** The current read frame. */
	uint64_t	timeStamp;
	/** Bit mask containing zero or more of ::CtrlButtons. */
	unsigned int 	buttons;
	/** Left analogue stick, X axis. */
	unsigned char 	lx;
	/** Left analogue stick, Y axis. */
	unsigned char 	ly;
	/** Right analogue stick, X axis. */
	unsigned char 	rx;
	/** Right analogue stick, Y axis. */
	unsigned char 	ry;
	/** Reserved. */
	uint8_t		reserved0[4];
	/** Left trigger (L2) */
	unsigned char	lt;
	/** Right trigger (R2) */
	unsigned char	rt;
	/** Reserved. */
	uint8_t 	reserved1[10];
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
	uint8_t unk[6]; //!< Unknown
} SceCtrlActuator;

/** Structure to pass as argument to ::sceCtrlGetControllerPortInfo */
typedef struct SceCtrlPortInfo {
	uint8_t port[5];  //!< Controller type of each ports
	uint8_t unk[11];  //!< Unknown
} SceCtrlPortInfo;

/**
 * Set the controller mode.
 *
 * @param[in] mode - One of ::CtrlMode.
 *
 * @return The previous mode, <0 on error.
 */
int ksceCtrlSetSamplingMode(int mode);

/**
 * Get the current controller mode.
 *
 * @param[out] pMode - Return value, see ::CtrlMode.
 *
 * @return The current mode, <0 on error.
 */
int ksceCtrlGetSamplingMode(int *pMode);

/**
 * Get the controller state information (polling, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlPeekBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (polling, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlPeekBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlReadBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlReadBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Set rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 * @param[in] pRule - structure ::SceCtrlRapidFireRule.
 *
 * @return 0, <0 on error.
 */
int ksceCtrlSetRapidFire(int port, int idx, const SceCtrlRapidFireRule* pRule);

/**
 * Clear rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 *
 * @return 0, <0 on error.
 */
int ksceCtrlClearRapidFire(int port, int idx);

/**
 * Get controller port information.
 *
 * @param[out] info - see ::SceCtrlPortInfo
 * @return 0, <0 on error
 */
int ksceCtrlGetControllerPortInfo(SceCtrlPortInfo *info);

/**
 * Sets intercept
 *
 * If true, allows the current thread to intercept controls. The use case
 * might be, for example, a game plugin that wishes to capture input without
 * having the input sent to the game thread.
 * @param[in]  intercept  Boolean value
 *
 * @return     0, < 0 on error
 */
int ksceCtrlSetButtonIntercept(int intercept);

/**
 * Gets intercept
 *
 * @param[out]  intercept  Boolean value
 *
 * @return     0, < 0 on error
 */
int ksceCtrlGetButtonIntercept(int *intercept);

/**
 * Emulate buttons for the digital pad.
 * @param port Use 0
 * @param slot The slot used to set the custom values. Between 0 - 3. If multiple slots are used,
 *             their settings are combined.
 * @param userButtons Emulated user buttons of ::SceCtrlPadButtons. You cannot emulate kernel
 *                    buttons and the emulated buttons will only be applied for applications
 *                    running in user mode.
 * @param kernelButtons Emulated buttons of ::SceCtrlPadButtons (you can emulate both user and
 *                      kernel buttons). The emulated buttons will only be applied for applications
 *                      running in kernel mode.
 * @param uiMake Specifies the duration of the emulation. Meassured in sampling counts.
 *
 * @return 0 on success.
 */
int ksceCtrlSetButtonEmulation(unsigned int port, unsigned char slot,
			       unsigned int userButtons, unsigned int kernelButtons,
			       unsigned int uiMake);

/**
 * Emulate values for the analog pad's X- and Y-axis.
 *
 * @param port Use 0
 * @param slot The slot used to set the custom values. Between 0 - 3. If multiple slots are used,
 *             their settings are combined.
 * @param user_lX New emulated value for the left joystick's X-axis (userspace). Between 0 - 0xFF.
 * @param user_lY New emulate value for the left joystick's Y-axis (userspace). Between 0 - 0xFF.
 * @param user_rX New emulated value for the right joystick's X-axis (userspace). Between 0 - 0xFF.
 * @param user_rY New emulate value for the right joystick's Y-axis (userspace). Between 0 - 0xFF.
 * @param kernel_lX New emulated value for the left joystick's X-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_lY New emulate value for the left joystick's Y-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_rX New emulated value for the right joystick's X-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_rY New emulate value for the right joystick's Y-axis (kernelspace). Between 0 - 0xFF.
 * @param uiMake Specifies the duration of the emulation. Meassured in sampling counts.
 *
 * @return 0 on success.
 */
int ksceCtrlSetAnalogEmulation(unsigned int port, unsigned char slot,
			      unsigned char user_lX, unsigned char user_lY,
			      unsigned char user_rX, unsigned char user_rY,
			      unsigned char kernel_lX, unsigned char kernel_lY,
			      unsigned char kernel_rX, unsigned char kernel_rY,
			      unsigned int uiMake);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2CTRL_H_ */
