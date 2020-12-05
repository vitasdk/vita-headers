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

typedef struct ScePssCryptoHandle {
  SceUID fd;
  uint32_t unk1;
  SceSize size;
  uint32_t unk3;
} ScePssCryptoHandle;

int pss_crypto_open(ScePssCryptoHandle *handle, char *path);
char *pss_crypto_read(ScePssCryptoHandle *handle, int *mode);
int pss_crypto_close(ScePssCryptoHandle *handle);
void *pss_code_mem_alloc(SceSize *);
void pss_code_mem_flush_icache(const void *, SceSize);
void pss_code_mem_lock(void);
void pss_code_mem_unlock(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PSS_H_ */

