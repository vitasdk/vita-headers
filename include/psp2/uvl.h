#ifndef _PSP2_UVL_H_
#define _PSP2_UVL_H_

#ifdef __cplusplus
extern "C" {
#endif

void *uvl_alloc_code_mem(unsigned int *p_len);
void uvl_unlock_mem(void);
void uvl_lock_mem(void);
void uvl_flush_icache(void *addr, unsigned int len);
int uvl_load(const char *path);
void uvl_exit(int status);
int uvl_log_write(const void* buffer, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif
