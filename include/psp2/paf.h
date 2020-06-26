/**
 * \usergroup{ScePaf}
 * \usage{psp2/paf.h,ScePaf_stub}
 */


#ifndef _PSP2_PAF_H_
#define _PSP2_PAF_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void sce_paf_private_free(void *ptr);
void *sce_paf_private_malloc(SceSize size);
void *sce_paf_private_bzero(void *ptr, SceSize num);
void *sce_paf_private_memchr(const void *ptr, int value, SceSize num);
int sce_paf_private_memcmp(const void *ptr1, const void *ptr2, SceSize num);
int sce_paf_private_bcmp(const void *ptr1, const void *ptr2, SceSize num);
void *sce_paf_private_memcpy(void *destination, const void *source, SceSize num);
void *sce_paf_private_memcpy2(void *destination, const void *source, SceSize num);
void *sce_paf_private_memmove(void *destination, const void *source, SceSize num);
void *sce_paf_private_bcopy(void *destination, const void *source, SceSize num);
void *sce_paf_private_memset(void *ptr, int value, SceSize num);
int sce_paf_private_snprintf(char *s, SceSize n, const char *format, ...);
int sce_paf_private_strcasecmp(const char *str1, const char *str2);
char *sce_paf_private_strchr(const char *str, int character);
int sce_paf_private_strcmp(const char *str1, const char *str2);
size_t sce_paf_private_strlen(const char *str);
int sce_paf_private_strncasecmp(const char *str1, const char *str2, SceSize num);
int sce_paf_private_strncmp(const char *str1, const char *str2, SceSize num);
char *sce_paf_private_strncpy(char *destination, const char *source, SceSize num);
char *sce_paf_private_strrchr(const char *str, int character);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PAF_H_ */

