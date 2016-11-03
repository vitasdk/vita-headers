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

/* callback */
typedef void (*ScePowerCallback)(int unknown, int powerInfo);

/* prototypes */
int scePowerRegisterCallback(int slot, SceUID cbid);
int scePowerIsBatteryCharging();
int scePowerGetBatteryLifePercent();
int scePowerSetConfigurationMode(int mode); //?
SceBool scePowerIsSuspendRequired(); //?
int scePowerIsPowerOnline();
int scePowerGetBatteryLifeTime();
int scePowerGetBatteryRemainCapacity(); //?
int scePowerIsLowBattery();
int scePowerUnregisterCallback(int slot);
int scePowerGetBatteryFullCapacity(); //?
int scePowerGetArmClockFrequency(); //Get Clock Frequency of the ARM
int scePowerGetBusClockFrequency(); //Get Clock Frequency of the BUS
int scePowerGetGpuClockFrequency(); //Get Clock Frequency of the Gpu
int scePowerGetGpuXbarClockFrequency(); //Get Clock Frequency of the Gpu Crossbar
int scePowerSetArmClockFrequency(int freq); // Set Clock Frequency of the ARM
int scePowerSetBusClockFrequency(int freq); // Set Clock Frequency of the BUS
int scePowerSetGpuClockFrequency(int freq); // Set Clock Frequency of the Gpu
int scePowerSetGpuXbarClockFrequency(int freq); // Set Clock Frequency of the Gpu Crossbar

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_POWER_H_ */
