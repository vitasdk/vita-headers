/**
 * \kernelgroup{SceExcpmgr}
 * \usage{psp2kern/kernel/excpmgr.h,SceExcpmgrForKernel_stub}
 */


#ifndef _PSP2KERN_KERNEL_EXCPMGR_H_
#define _PSP2KERN_KERNEL_EXCPMGR_H_

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
    SCE_EXCPMGR_EXCEPTION_HANDLED = 0,		//!< Exception handled
    SCE_EXCPMGR_EXCEPTION_NOT_HANDLED = 1,	//!< Exception not handled - kills app with C2-12828-1
    SCE_EXCPMGR_EXCEPTION_HANDLING_CODE_2 = 2,  
    SCE_EXCPMGR_EXCEPTION_NOT_HANDLED_FATAL = 3,//!< Fatal exception - panics the kernel
    SCE_EXCPMGR_EXCEPTION_HANDLING_CODE_4 = 4	
} SceExcpHandlingCode;
	
typedef struct SceExcpmgrData { //Data in each array is per-CPU core
    int nestedExceptionCount[4]; 	//!< Number of times an exception handler has been entered on core - panic if > 1 on exception return
    int unused[4]; 			//!< Seemingly unused
    void *ExcpStackTop[4]; 		//!< Top of the exception stack (size is 0x1000)
    void *ExcpStackBottom[4]; 		//!< Bottom of the exception stack
} SceExcpmgrData;

typedef struct SceExcpmgrExceptionContext { //!< Size is 0x400 on FW 3.60
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
    uint32_t address_of_faulting_instruction;	//<! Address where the faulty instruction is located
    SceExcpKind ExceptionKind; 			//<! The kind of exception the CPU encountered
    uint32_t SPSR;
    uint32_t CPACR;
    uint32_t FPSCR;
    uint32_t FPEXC;
    uint32_t CONTEXTIDR;
    uint32_t TPIDRURW;
    uint32_t TPIDRURO;
    uint32_t TPIDRPRW;
    uint32_t TTBR1;
    uint32_t unused68;
    uint32_t DACR;
    uint32_t DFSR;
    uint32_t IFSR;
    uint32_t DFAR;
    uint32_t IFAR;
    uint32_t PAR;
    uint32_t TEEHBR;
    uint32_t PMCR;
    uint32_t PMCNTENSET;
    uint32_t PMCNTENSET_2; //<! Second copy of PMCNTENSET
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
    uint32_t unusedD0;
    uint32_t unkD4; 		//<! Comes from SceVfpIntRegs memblock
    uint32_t DBGSCRext;
    uint32_t unusedDC[9];  
    uint64_t VFP_registers[32]; //<! Content of floating-point registers d0-d31
    uint32_t unk200[128];       //<! Comes from SceVfpIntRegs memblock
} SceExcpmgrExceptionContext;	

typedef void(SceExcpmgrExceptionHandler)(SceExcpmgrExceptionContext* context, SceExcpHandlingCode code); //<! Exception handler function

/**
 * Get a pointer to SceExcpmgr's internal data
 *
 * This is only used by exception handlers.
 *
 * @return pointer to SceExcpmgrData structure
*/
SceExcpmgrData *ksceExcpmgrGetData(void);

/**
 * Register an exception handler
 *
 * `handler` must point to eight bytes of space followed by the handler code.
 * The space will be used in the internal linked list structure.
 *
 * @param[in]  kind      The kind of exception
 * @param[in]  priority  The priority (must be 0 <= priority < 8), 0 highest
 * @param      handler   The handler
 *
 * @return     Error code or zero on success
 */
int ksceExcpmgrRegisterHandler(SceExcpKind kind, int priority, void *handler);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_EXCPMGR_H_ */
