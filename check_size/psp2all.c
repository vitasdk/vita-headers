
#include "defs.h"
// #include <vitasdk.h>
// #include <vitasdkkern.h>

#include <psp2/ctrl.h>
#include <psp2kern/ctrl.h>

// #include <psp2/net/net.h>
// #include <psp2kern/net/net.h>

// #include <psp2/kernel/threadmgr.h>
// #include <psp2kern/kernel/threadmgr.h>

#include <psp2/kernel/modulemgr.h>
#include <psp2kern/kernel/modulemgr.h>

#include <psp2/kernel/processmgr.h>
#include <psp2kern/kernel/processmgr.h>
#include <psp2kern/kernel/suspend.h>

#include <psp2/rtc.h>
#include <psp2kern/kernel/rtc.h>

// #include <psp2/jpegenc.h>
// #include <psp2kern/avcodec/jpegenc.h>

#include <psp2/display.h>
#include <psp2kern/display.h>

// #include <psp2/power.h>
// #include <psp2kern/power.h>

// #include <psp2/udcd.h>
// #include <psp2kern/udcd.h>

// #include <psp2/usbd.h>
// #include <psp2kern/usbd.h>

__attribute__ ((used)) const unsigned int version = PSP2_SDK_VERSION;

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(unsigned int args, void *argp){
	taiGetModuleInfo("SceLibKernel", ((void *)0));
	return 0;
}
