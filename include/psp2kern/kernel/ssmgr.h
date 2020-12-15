/**
 * \kernelgroup{SceSblSsMgr}
 * \usage{psp2kern/kernel/ssmgr.h,SceSblSsMgrForDriver_stub}
 */

#ifndef _PSP2_KERNEL_SBL_SS_MGR_H_
#define _PSP2_KERNEL_SBL_SS_MGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceConsoleId {
	uint16_t unk;
	uint16_t company_code;
	uint16_t product_code;
	uint16_t product_sub_code;
	uint8_t chassis_check; // factory_code = chassis_check >> 2;
	uint8_t unknown[7];
} SceConsoleId;

typedef struct SceOpenPsId {
	uint8_t open_psid[0x10];
} SceOpenPsId;

typedef struct ScePsCode {
	uint16_t company_code;
	uint16_t product_code;
	uint16_t product_sub_code;
	uint16_t factory_code;
} ScePsCode;

int ksceSblAimgrGetConsoleId(SceConsoleId *cid);
int ksceSblAimgrGetOpenPsId(SceOpenPsId *open_psid);
int ksceSblAimgrGetPscode(ScePsCode *pscode);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SBL_SS_MGR_H_ */
