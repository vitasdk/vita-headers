/**
 * \usergroup{ScePss}
 * \usage{psp2/pss.h,SceLibMonoBridge_stub}
 */


#ifndef _PSP2_PSS_H_
#define _PSP2_PSS_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void *pss_code_mem_alloc(SceSize *);
void pss_code_mem_flush_icache(const void *, SceSize);
void pss_code_mem_lock(void);
void pss_code_mem_unlock(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PSS_H_ */

