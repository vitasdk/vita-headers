/**
 * \kernelgroup{SceExcpmgr}
 * \usage{psp2kern/kernel/excpmgr.h,SceExcpmgrForKernel_stub}
 */


#ifndef _PSP2KERN_KERNEL_EXCPMGR_H_
#define _PSP2KERN_KERNEL_EXCPMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceExcpKind {
	SCE_EXCP_RESET                = 0,
	SCE_EXCP_UNDEF_INSTRUCTION    = 1,
	SCE_EXCP_SVC                  = 2,
	SCE_EXCP_PABT                 = 3,
	SCE_EXCP_DABT                 = 4,
	SCE_EXCP_UNUSED               = 5,
	SCE_EXCP_IRQ                  = 6,
	SCE_EXCP_FIQ                  = 7
} SceExcpKind;

typedef enum SceExcpHandlingCode {
	SCE_EXCPMGR_EXCEPTION_HANDLED           = 0, //!< Resume from the supplied exception context.
	SCE_EXCPMGR_EXCEPTION_NOT_HANDLED       = 1, //!< Process an unhandled thread exception,
	                                             //!< then continue the handler chain.
	SCE_EXCPMGR_EXCEPTION_HANDLING_CODE_2   = 2, //!< Passed on unchanged; no code that produces this value
	                                             //!< was found in the available FW 3.60 modules.
	SCE_EXCPMGR_EXCEPTION_NOT_HANDLED_FATAL = 3, //!< Fatal exception; panics the kernel.
	SCE_EXCPMGR_EXCEPTION_HANDLING_CODE_4   = 4  //!< ThreadMgr queued the exception for later debug processing;
	                                             //!< the final handler follows the normal exception-return path.
} SceExcpHandlingCode;

typedef struct SceExcpmgrBreakpointState {
	SceKernelSpinlock lock;
	SceUInt32 reserved; //!< Ignored on FW 3.60 by Excpmgr and Intrmgr; zero in the known default state stored in BSS.
	SceUInt32 DBGBVR0;
	SceUInt32 DBGBCR0;
	SceUInt32 DBGBVR1;
	SceUInt32 DBGBCR1;
	SceUInt32 DBGBVR2;
	SceUInt32 DBGBCR2;
	SceUInt32 DBGBVR3;
	SceUInt32 DBGBCR3;
	SceUInt32 DBGBVR4;
	SceUInt32 DBGBCR4;
} SceExcpmgrBreakpointState;
VITASDK_BUILD_ASSERT_EQ(0x30, SceExcpmgrBreakpointState); // size is from FW 3.60

typedef struct SceExcpmgrWatchpointState {
	SceKernelSpinlock lock;
	SceUInt32 reserved; //!< Ignored on FW 3.60 by Excpmgr and Intrmgr; zero in the known default state stored in BSS.
	SceUInt32 DBGWVR0;
	SceUInt32 DBGWCR0;
	SceUInt32 DBGWVR1;
	SceUInt32 DBGWCR1;
	SceUInt32 DBGWVR2;
	SceUInt32 DBGWCR2;
	SceUInt32 DBGWVR3;
	SceUInt32 DBGWCR3;
} SceExcpmgrWatchpointState;
VITASDK_BUILD_ASSERT_EQ(0x28, SceExcpmgrWatchpointState); // size is from FW 3.60

typedef struct SceExcpmgrData {
	int nestedExceptionCount[4]; //!< Active UNDEF, PABT, or DABT exception depth on each CPU core.
	int reserved[4]; //!< Zero-initialized BSS; ignored on FW 3.60.
	void *ExcpStackTop[4]; //!< Base address of each CPU core's 0x1000-byte exception stack.
	void *ExcpStackBottom[4]; //!< Address immediately after each CPU core's exception stack, used as its initial stack pointer.
	void *kernelProcessContext; //!< A pointer to the kernel's ::SceKernelProcessContext,
	                            //!< used to install TTBR1 and CONTEXTIDR.
	SceExcpmgrBreakpointState *breakpointState; //!< Fallback breakpoint-register state used when TPIDRPRW is zero.
	SceExcpmgrWatchpointState *watchpointState; //!< Fallback watchpoint-state pointer;
	                                            //!< Excpmgr controls and locks the restore path,
	                                            //!< while Intrmgr reads its register fields.
} SceExcpmgrData;
VITASDK_BUILD_ASSERT_EQ(0x4C, SceExcpmgrData); // size is from FW 3.60

/** Values stored in bits 0-2 of ::SceArmWaypoint::event. */
typedef enum SceArmWaypointEventType {
	SCE_ARM_WAYPOINT_EVENT_DIRECT_BRANCH   = 0,
	SCE_ARM_WAYPOINT_EVENT_INDIRECT_BRANCH = 1,
	SCE_ARM_WAYPOINT_EVENT_EXCEPTION       = 2,
	SCE_ARM_WAYPOINT_EVENT_MEMORY_BARRIER  = 3,
	SCE_ARM_WAYPOINT_EVENT_DEBUG_ENTRY     = 4,
	SCE_ARM_WAYPOINT_EVENT_DEBUG_EXIT      = 5,
	SCE_ARM_WAYPOINT_EVENT_UNKNOWN_6       = 6,
	SCE_ARM_WAYPOINT_EVENT_UNKNOWN_7       = 7
} SceArmWaypointEventType;

typedef struct SceArmWaypoint {
	SceUInt32 raw_data; //!< Printed and forwarded without interpretation on FW 3.60.
	SceUIntPtr pc; //!< Recorded source PC.
	SceUIntPtr target_pc; //!< Recorded target PC.
	SceUInt32 event; //!< Bit 31 marks a valid entry; bits 0-2 are one of ::SceArmWaypointEventType;
	                 //!< for exception events, bits 4-7 select the subtype; bit 8 marks a link,
	                 //!< bit 9 selects a 32-bit instruction, bit 10 marks a taken branch,
	                 //!< and bits 11-12 select the instruction-set state.
} SceArmWaypoint;
VITASDK_BUILD_ASSERT_EQ(0x10, SceArmWaypoint); // size is from FW 3.60

typedef struct SceExcpmgrExceptionContext {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r12;
	uint32_t sp;
	uint32_t lr;
	uint32_t address_of_faulting_instruction; //!< LR-8 for DABT, LR-4 for PABT or ARM UNDEF, and LR-2 for Thumb UNDEF.
	SceExcpKind ExceptionKind; //!< The kind of exception the CPU encountered.
	uint32_t SPSR;
	uint32_t CPACR;
	uint32_t FPSCR;
	uint32_t FPEXC;
	uint32_t CONTEXTIDR;
	uint32_t TPIDRURW;
	uint32_t TPIDRURO;
	uint32_t TPIDRPRW;
	uint32_t TTBR1;
	uint32_t reserved68; //!< Not written or read on FW 3.60; contains indeterminate exception-stack data.
	uint32_t DACR;
	uint32_t DFSR;
	uint32_t IFSR;
	uint32_t DFAR;
	uint32_t IFAR;
	uint32_t PAR;
	uint32_t TEEHBR;
	uint32_t PMCR;
	uint32_t PMCNTENSET;
	uint32_t PMCNTENSET_2; //!< Second copy of PMCNTENSET.
	uint32_t PMSELR;
	uint32_t PMCCNTR;
	uint32_t PMUSERENR;
	uint32_t PMXEVTYPER0;
	uint32_t PMXEVCNTR0;
	uint32_t PMXEVTYPER1;
	uint32_t PMXEVCNTR1;
	uint32_t PMXEVTYPER2;
	uint32_t PMXEVCNTR2;
	uint32_t PMXEVTYPER3;
	uint32_t PMXEVCNTR3;
	uint32_t PMXEVTYPER4;
	uint32_t PMXEVCNTR4;
	uint32_t PMXEVTYPER5;
	uint32_t PMXEVCNTR5;
	uint32_t reserved_D0; //!< Not written or read on FW 3.60; contains indeterminate exception-stack data.
	uint32_t waypoint_control; //!< Bit 0 is set during initialization and after exception processing;
	                          //!< bits 8-12 contain the current index in the waypoint ring buffer.
	uint32_t DBGSCRext;
	uint32_t reserved_DC[9]; //!< Not written or read on FW 3.60; contents are indeterminate exception-stack data.
	uint64_t VFP_registers[32]; //!< Content of floating-point registers D0-D31.
	SceArmWaypoint waypoints[32]; //!< Circular ARM waypoint trace history.
} SceExcpmgrExceptionContext;
VITASDK_BUILD_ASSERT_EQ(0x400, SceExcpmgrExceptionContext); // size is from FW 3.60

/**
 * Exception handler used at priorities 1-7.
 *
 * Handlers are entered with \p context in R0 and \p code in R1. They transfer
 * control to the next handler or the exception-return path and do not return
 * to a caller.
 */
typedef void(SceExcpmgrExceptionHandler)(SceExcpmgrExceptionContext *context, SceExcpHandlingCode code);

typedef struct SceExcpmgrExceptionHandlerContext {
	struct SceExcpmgrExceptionHandlerContext *next; //!< Pointer to the next handler record;
	                                                //!< bit 0 preserves Thumb state.
	SceUInt32 must_be_zero; //!< Must be zero when registering during cold boot; otherwise unused on FW 3.60.
} SceExcpmgrExceptionHandlerContext;
VITASDK_BUILD_ASSERT_EQ(0x8, SceExcpmgrExceptionHandlerContext); // size is from FW 3.60

/**
 * Get a pointer to SceExcpmgr's internal data.
 *
 * @return A pointer to the ::SceExcpmgrData structure.
 */
SceExcpmgrData *ksceExcpmgrGetData(void);

/**
 * Register an exception handler.
 *
 * The address obtained by clearing bits 0-1 of \p handler must point to a
 * ::SceExcpmgrExceptionHandlerContext immediately followed by the handler
 * code. In \p handler, bit 0 selects Thumb state and bit 1 must be clear.
 * Priorities 1-7 use the ::SceExcpmgrExceptionHandler prototype; priority 0 uses a raw,
 * exception-specific vector-entry ABI.
 *
 * @param[in]      kind      The kind of exception.
 * @param[in]      priority  The priority (must be 0 <= priority < 8), 0 highest.
 * @param[in,out]  handler   A pointer to a ::SceExcpmgrExceptionHandlerContext followed by the handler code.
 *
 * @return     Error code or zero on success.
 */
int ksceExcpmgrRegisterHandler(SceExcpKind kind, int priority, void *handler);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_EXCPMGR_H_ */
