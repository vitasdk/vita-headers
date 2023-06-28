/**
 * \kernelgroup{SceProcessmgr}
 * \usage{psp2common/kernel/processmgr.h}
 */

#ifndef _PSP2COMMON_KERNEL_PROCESSMGR_H_
#define _PSP2COMMON_KERNEL_PROCESSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef SceUInt32 SceKernelProcessType;

typedef SceUInt64 SceKernelClock;
typedef SceUInt32 SceKernelTime; 

typedef enum SceKernelProcessPrioritySystem : SceInt32 {
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_HIGH     = 32,
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_DEFAULT  = 96,
	SCE_KERNEL_PROCESS_PRIORITY_SYSTEM_LOW      = 159
} SceKernelProcessPrioritySystem;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelProcessPrioritySystem);

typedef enum SceKernelProcessPriorityUser : SceInt32 {
	SCE_KERNEL_PROCESS_PRIORITY_USER_HIGH       = 64,
	SCE_KERNEL_PROCESS_PRIORITY_USER_DEFAULT    = 96,
	SCE_KERNEL_PROCESS_PRIORITY_USER_LOW        = 127
} SceKernelProcessPriorityUser;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelProcessPriorityUser);

typedef enum SceKernelPowerTickType : SceInt32 {
	/** Cancel all timers */
	SCE_KERNEL_POWER_TICK_DEFAULT			= 0,
	/** Cancel automatic suspension timer */
	SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND	= 1,
	/** Cancel OLED-off timer */
	SCE_KERNEL_POWER_TICK_DISABLE_OLED_OFF		= 4,
	/** Cancel OLED dimming timer */
	SCE_KERNEL_POWER_TICK_DISABLE_OLED_DIMMING	= 6
} SceKernelPowerTickType;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelPowerTickType);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_PROCESSMGR_H_ */
