
#include "defs.h"
#include <vitasdkkern.h>

__attribute__ ((used)) const unsigned int version = PSP2_SDK_VERSION;

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(unsigned int args, void *argp){
	taiGetModuleInfoForKernel(0x10005, "SceSysmem", ((void *)0));
	return 0;
}
