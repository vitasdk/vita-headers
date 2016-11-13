/**
 * \addtogroup ScePower Power Library
 * Battery status, CPU speed...
 */

/**
 * \defgroup ScePowerUser User
 *  \ingroup ScePower
 * Exports for User
 * \code
 * #include <psp2/power.h>
 * \endcode
 * \{
 */

/**
 * \file
 * \brief Header file which defines power variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_POWER_H_
#define _PSP2_POWER_H_

#include <psp2/types.h>


#ifdef __cplusplus
extern "C" {
#endif

/* Callbacks */

/** Callback function prototype */
typedef void (*ScePowerCallback)(int unknown, int powerInfo);

/**
 * Registers a ScePower Callback
 *
 * @param cbid - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int scePowerRegisterCallback(SceUID cbid);

/**
 * Unregister a callback
 *
 * @param cbid - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int scePowerUnregisterCallback(SceUID cbid);

/* Prototypes */

/**
 * Returns battery charging status
 *
 * @return SCE_TRUE if under charge, SCE_FALSE otherwise
 */
SceBool scePowerIsBatteryCharging(void);

/**
 * Returns battery life percentage
 *
 * @return Battery life percentage
 */
int scePowerGetBatteryLifePercent(void);

/**
 * Set configuration mode ?
 *
 * @param mode - The mode to set
 *
 * @return ?
 */
int scePowerSetConfigurationMode(int mode);

/**
 * Check if a suspend is required
 *
 * @return SCE_TRUE if suspend is required, SCE_FALSE otherwise
 */
SceBool scePowerIsSuspendRequired(void);

/**
 * Check if AC is plugged in
 *
 * @return SCE_TRUE if plugged in, SCE_FALSE otherwise
 */
SceBool scePowerIsPowerOnline(void);

/**
 * Returns battery life time
 *
 * @return Battery life time in seconds
 */
int scePowerGetBatteryLifeTime(void);

/**
 * Returns battery remaining capacity ?
 *
 * @return ?
 */
int scePowerGetBatteryRemainCapacity(void);

/**
 * Returns battery state
 *
 * @return SCE_TRUE if battery is low, SCE_FALSE otherwise
 */
SceBool scePowerIsLowBattery(void);

/**
 * Returns battery full capacity ?
 *
 * @return ?
 */
int scePowerGetBatteryFullCapacity(void);

/**
 * Returns CPU clock frequency
 *
 * @return CPU clock frequency in Mhz
 */
int scePowerGetArmClockFrequency(void); 

/**
 * Returns BUS clock frequency
 *
 * @return BUS clock frequency in Mhz
 */
int scePowerGetBusClockFrequency(void);

/**
 * Returns GPU clock frequency
 *
 * @return GPU clock frequency in Mhz
 */
int scePowerGetGpuClockFrequency(void);

/**
 * Returns GPU crossbar clock frequency
 *
 * @return GPU crossbar clock frequency in Mhz
 */
int scePowerGetGpuXbarClockFrequency(void);

/**
 * Sets CPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetArmClockFrequency(int freq);

/**
 * Sets BUS clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetBusClockFrequency(int freq);

/**
 * Sets GPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetGpuClockFrequency(int freq);

/**
 * Sets GPU crossbar clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetGpuXbarClockFrequency(int freq);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_POWER_H_ */

/**
 * \}
 */
