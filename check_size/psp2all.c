
#include "defs.h"
// #include <vitasdk.h>
// #include <vitasdkkern.h>

#include <psp2/ctrl.h>
#include <psp2kern/ctrl.h>

__attribute__ ((used)) const unsigned int version = PSP2_SDK_VERSION;

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(unsigned int args, void *argp){
	taiGetModuleInfo("SceLibKernel", ((void *)0));
	return 0;
}
