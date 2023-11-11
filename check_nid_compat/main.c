
#ifndef __USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT
#define __USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT
#endif

#include <psp2common/defs.h>
#include <psp2kern/kernel/cpu.h>
#include <psp2kern/kernel/debug.h>
#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/kernel/uart.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/excpmgr.h>
#include <psp2kern/kernel/intrmgr.h>
#include <psp2kern/kernel/processmgr.h>
#include <psp2kern/kernel/threadmgr.h>


const SceUInt32 module_sdk_version = PSP2_SDK_VERSION;

typedef struct {
	const char *function_name;
	void *function;
} function_entry;

#define _x(__name__) {.function_name = #__name__, .function = k##__name__}

const function_entry SceCpuForKernel[] = {
	_x(sceKernelAtomicAdd32AndGet64InHiLoRange),
	_x(sceKernelAtomicAdd32AndGet64InRange),
	_x(sceKernelAtomicAddAndGetPositive32InRange),
	_x(sceKernelAtomicDecIfLowPositive32),
	_x(sceKernelAtomicGet32AndSet64),
	_x(sceKernelAtomicGet32AndSet64_2),
	_x(sceKernelAtomicIncrementHighwaterCounter),
	_x(sceKernelAtomicLimit64),
	_x(sceKernelAtomicSubIfGreater64),
	_x(sceKernelCorelockInitialize),
	_x(sceKernelCorelockLock),
	_x(sceKernelCorelockUnlock),
	_x(sceKernelCpuBranchPredictorInvalidateAll),
	_x(sceKernelCpuBranchPredictorInvalidateAllIS),
	_x(sceKernelCpuGetCONTEXTIDR),
	_x(sceKernelCpuUpdateSCTLR),
	_x(sceKernelGetVmaccessRange),
	_x(sceKernelIcacheInvalidateRange),
	_x(sceKernelL1DcacheClean),
	_x(sceKernelL1DcacheCleanAll),
	_x(sceKernelL1DcacheCleanInvalidate),
	_x(sceKernelL1DcacheCleanInvalidateAll),
	_x(sceKernelL1DcacheCleanInvalidateRange),
	_x(sceKernelL1DcacheCleanRange),
	_x(sceKernelL1DcacheInvalidate),
	_x(sceKernelL1DcacheInvalidateAll),
	_x(sceKernelL1DcacheInvalidateRange),
	_x(sceKernelL1IcacheInvalidateEntire),
	_x(sceKernelL1IcacheInvalidateEntireAllCore),
	_x(sceKernelL1IcacheInvalidateRange),
	_x(sceKernelMMUGetMemoryType),
	_x(sceKernelMMUVAtoPA),
	_x(sceKernelMMUVAtoPAWithMode),
	_x(sceKernelPleFlushRequest),
#if defined(PSP2_SDK_VERSION) && PSP2_SDK_VERSION < 0x3630000
	_x(sceKernelDomainTextMemcpy),
#endif
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceDebugForKernel[] = {
	_x(sceDebugDisableInfoDump),
	_x(sceDebugGetPutcharHandler),
	_x(sceDebugPutchar),
	_x(sceDebugRegisterPutcharHandler),
	_x(sceDebugSetHandlers),
	_x(sceKernelSetMinimumAssertionLevel),
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceSysmemForKernel[] = {
	_x(sceGUIDGetObjectWithClass),
	_x(sceGUIDGetUIDVectorByClass),
	_x(sceGUIDKernelCreateWithAttr),
	_x(sceGUIDKernelCreateWithOpt),
	_x(sceGUIDOpenByGUID),
	_x(sceKernelAddressSpaceFreeAllMemBlock),
	_x(sceKernelAddressSpaceSetPhyMemPart),
	_x(sceKernelAddressSpaceUnmap),
	_x(sceKernelAddressSpaceVAtoPA),
	_x(sceKernelAlloc),
	_x(sceKernelAllocPartitionMemBlock),
	_x(sceKernelCopyToUserDomain),
	_x(sceKernelCopyToUserProcTextDomain),
	_x(sceKernelCopyToUserTextDomain),
	_x(sceKernelCreateAddressSpace),
	_x(sceKernelDeleteAddressSpace),
	_x(sceKernelFindClassByName),
	_x(sceKernelFree),
	_x(sceKernelFreeSimpleMemBlock),
	_x(sceKernelGetFixedHeapInfoByPointer),
	_x(sceKernelGetHeapInfo),
	_x(sceKernelGetHeapInfoByPtr),
	_x(sceKernelGetMemBlockType),
	_x(sceKernelGetUIDDLinkClass),
	_x(sceKernelGetUIDHeapClass),
	_x(sceKernelGetUIDMemBlockClass),
	_x(sceKernelNameHeapGetInfo),
	_x(sceKernelUIDEntryHeapGetInfo),
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceUartForKernel[] = {
	_x(sceUartInit),
	_x(sceUartRead),
	_x(sceUartReadAvailable),
	_x(sceUartWrite),
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceExcpmgrForKernel[] = {
	_x(sceExcpmgrGetData),
	_x(sceExcpmgrRegisterHandler),
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceModulemgrForKernel[] = {
	_x(sceKernelFinalizeKbl),
	_x(sceKernelGetExportedLibraryListInModule),
	_x(sceKernelGetImportedLibraryListInModule),
	_x(sceKernelGetLibEntCBListForSyslibtrace),
	_x(sceKernelGetLibraryClientList),
	_x(sceKernelGetLibraryDBFlags),
	_x(sceKernelGetLibraryExportInfoForDebugger),
	_x(sceKernelGetLibraryInfoForDebugger),
	_x(sceKernelGetLostLibraryInfo),
	_x(sceKernelGetLostLibraryList),
	_x(sceKernelGetLostLibraryListInModule),
	_x(sceKernelGetMetaDataForDebugger),
	_x(sceKernelGetModuleCB),
	_x(sceKernelGetModuleCBByAddr),
	_x(sceKernelGetModuleEntryPoint),
	_x(sceKernelGetModuleFingerprint),
	_x(sceKernelGetModuleIdByAddrForDebugger),
	_x(sceKernelGetModuleIdByPid),
	_x(sceKernelGetModuleInfo),
	_x(sceKernelGetModuleInfoForDebugger),
	_x(sceKernelGetModuleInfoMinByAddr),
	_x(sceKernelGetModuleIsSharedByAddr),
	_x(sceKernelGetModuleList),
	_x(sceKernelGetModulePath),
	_x(sceKernelGetLibraryList),
	_x(sceKernelGetProgramIdentificationInfo),
	_x(sceKernelGetStubInfoForDebugger),
	_x(sceKernelGetStubList),
	_x(sceKernelGetStubNidTableForDebugger),
	_x(sceKernelLoadModuleForPid),
	_x(sceKernelLoadPreloadingModules),
	_x(sceKernelLoadProcessImage),
	_x(sceKernelLoadPtLoadSegForFwloader),
	_x(sceKernelModuleUnloadMySelf),
	_x(sceKernelMountBootfs),
	_x(sceKernelRegisterModulesAfterBoot),
	_x(sceKernelRegisterSyscall),
	_x(sceKernelStartModuleForPid),
	_x(sceKernelStartPreloadingModules),
	_x(sceKernelStopModuleForPid),
	_x(sceKernelUmountBootfs),
	_x(sceKernelUnloadProcessModules),
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceIntrmgrForKernel[] = {
	_x(sceKernelQueryIntrHandlerInfo),
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceProcessmgrForKernel[] = {
	_x(sceKernelCreateProcess),
	_x(sceKernelExitProcess),
	_x(sceKernelGetProcessKernelBuf),
	_x(sceKernelGetProcessMainThread),
	_x(sceKernelGetProcessModuleInfo),
	_x(sceKernelGetProcessSelfAuthInfo),
	_x(sceKernelGetUIDProcessClass),
	_x(sceKernelLibcGettimeofday),
	_x(sceKernelLibcTime),
	_x(sceKernelResumeProcess),
	_x(sceKernelSuspendProcess),
	{
		.function_name = NULL,
		.function = NULL
	}
};

const function_entry SceThreadmgrForKernel[] = {
	_x(sceKernelGetThreadContextInfo),
	{
		.function_name = NULL,
		.function = NULL
	}
};

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp){

#define _print(__lib__) ksceKernelPrintf("%s %p %d\n", #__lib__, __lib__, (sizeof(__lib__) / sizeof(__lib__[0])))

	_print(SceCpuForKernel);
	_print(SceDebugForKernel);
	_print(SceIntrmgrForKernel);
	_print(SceModulemgrForKernel);
	// _print(ScePfsMgrForKernel);
	_print(SceProcessmgrForKernel);
	// _print(SceSblACMgrForKernel);
	// _print(SceSblAuthMgrForKernel);
	// _print(SceSblSmCommForKernel);
	// _print(SceSblSmSchedProxyForKernel);
	// _print(SceSblSsMgrForKernel);
	_print(SceSysmemForKernel);
	// _print(SceSysrootForKernel);
	_print(SceThreadmgrForKernel);
	_print(SceUartForKernel);

	return SCE_KERNEL_START_SUCCESS;
}
