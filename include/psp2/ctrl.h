/**
 * \file ctrl.h
 * \brief Header file which defines control related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_CTRL_H_
#define _PSP2_CTRL_H_

#include <stdint.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_CTRL_ERROR_INVALID_ARG	= 0x80340001,
	SCE_CTRL_ERROR_PRIV_REQUIRED	= 0x80340002,
	SCE_CTRL_ERROR_FATAL		= 0x803400FF
};

/** Enumeration for the digital controller buttons. */
enum {
	SCE_CTRL_SELECT     = 0x000001,	//!< Select button.
	SCE_CTRL_START      = 0x000008,	//!< Start button.
	SCE_CTRL_UP         = 0x000010,	//!< Up D-Pad button.
	SCE_CTRL_RIGHT      = 0x000020,	//!< Right D-Pad button.
	SCE_CTRL_DOWN       = 0x000040,	//!< Down D-Pad button.
	SCE_CTRL_LEFT       = 0x000080,	//!< Left D-Pad button.
	SCE_CTRL_LTRIGGER   = 0x000100,	//!< Left trigger.
	SCE_CTRL_RTRIGGER   = 0x000200,	//!< Right trigger.
	SCE_CTRL_TRIANGLE   = 0x001000,	//!< Triangle button.
	SCE_CTRL_CIRCLE     = 0x002000,	//!< Circle button.
	SCE_CTRL_CROSS      = 0x004000,	//!< Cross button.
	SCE_CTRL_SQUARE     = 0x008000,	//!< Square button.
	SCE_CTRL_ANY        = 0x010000	//!< Any input intercepted.
};

/** Controller mode. */
enum {
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
	uint8_t 	reserved[16];
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
	int enable;  //!< Enable the actuator vibration
	int unk;     //!< Unknown
} SceCtrlActuator;

/**
 * Set the controller mode.
 *
 * @param[in] mode - One of ::CtrlMode.
 *
 * @return The previous mode, <0 on error.
 */
int sceCtrlSetSamplingMode(int mode);

/**
 * Get the current controller mode.
 *
 * @param[out] pMode - Return value, see ::CtrlMode.
 *
 * @return The current mode, <0 on error.
 */
int sceCtrlGetSamplingMode(int *pMode);

/**
 * Get the controller state information (polling, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (polling, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferNegative(int port, SceCtrlData *pad_data, int count);

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2CTRL_H_ */
