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
  
typedef struct ScePssHandle {
  uint32_t unk0;
  uint32_t unk1;
  uint32_t filesz;
  uint32_t unk3;
} ScePssCryptoHandle;

int pss_crypto_open_p(ScePssCryptoHandle *handle, char *path);
char *pss_crypto_read_p(ScePssCryptoHandle *handle, int unk);
void *pss_code_mem_alloc(SceSize *);
void pss_code_mem_flush_icache(const void *, SceSize);
void pss_code_mem_lock(void);
void pss_code_mem_unlock(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PSS_H_ */

