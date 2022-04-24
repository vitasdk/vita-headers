/**
 * \kernelgroup{SceKbl}
 * \usage{psp2kern/kernel/kbl/kbl.h}
 */

#ifndef _PSP2KERN_KERNEL_KBL_KBL_H_
#define _PSP2KERN_KERNEL_KBL_KBL_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/dipsw.h>
#include <psp2kern/kernel/ssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKblParam { // size is 0x100 or 0x200. must 0x200 on 3.60.
	uint16_t version;
	uint16_t size;
	uint32_t current_fw_version;
	uint32_t factory_fw_version;
	uint32_t unk_C;
	uint32_t unk_10;
	uint8_t unk_14[0xC];
	uint8_t qa_flags[0x10];
	uint8_t boot_flags[0x10];
	SceDipsw dipsw;
	SceKernelPARange dram;
	uint32_t unk_68;
	uint32_t boot_type_indicator_1;
	SceOpenPsId openpsid;
	SceKernelPARange secure_kernel;
	SceKernelPARange context_auth_sm;
	SceKernelPARange kprx_auth_sm;
	SceKernelPARange prog_rvk;
	ScePsCode pscode;
	uint32_t __stack_chk_guard;
	uint32_t unk_AC;
	uint8_t session_id[0x10];

	/*
	 * poweroff factor
	 * 0x00000001:bsod reboot(or other serious factors)
	 * 0x00000010:bsod poweroff
	 * 0x00000400:always?
	 * 0x00020000:maybe low battery
	 */
	uint32_t unk_C0;
	uint32_t wakeup_factor;
	uint32_t unk_C8;                // usb_info
	uint32_t hold_ctrl;
	uint32_t resume_context_addr;
	uint32_t hardware_info;
	uint32_t boot_type_indicator_2; // may power_info 0x4:always? 0x8:AC connected
	uint32_t unk_DC;
	uint32_t unk_E0;                // if resume, always 0
	uint32_t unk_E4;
	uint8_t hardware_flags[0x10];
	uint32_t bootldr_revision;
	uint32_t magic;
	uint8_t coredump_session_key[0x20];
	uint8_t unused[0xE0];
} __attribute__((packed)) SceKblParam;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_KBL_KBL_H_ */
