/**
 * \usergroup{ScePaf}
 * \usage{psp2/paf/stdc.h,ScePaf_stub}
 */


#ifndef _PSP2_PAF_STDC_H_
#define _PSP2_PAF_STDC_H_

#include <psp2/types.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void *sce_paf_malloc(SceSize size);
void sce_paf_free(void *ptr);

/**
 * @brief Alloc memory with align
 *
 * @param[in] align  The align size
 * @param[in] length The alloc length
 *
 * @return memory pointer or NULL
 */
void *sce_paf_memalign(SceSize align, SceSize length);

void *sce_paf_memchr(const void *src, int ch, SceSize length);
int sce_paf_memcmp(const void *s1, const void *s2, SceSize n);

void *sce_paf_memcpy(void *dst, const void *src, SceSize len);
void *sce_paf_memset(void *dst, int ch, SceSize len);
void *sce_paf_memmove(void *dst, const void *src, SceSize len);

int sce_paf_snprintf(char *dst, unsigned int max, const char *fmt, ...);
int sce_paf_vsnprintf(char *dst, unsigned int max, const char *fmt, va_list arg);

int sce_paf_bcmp(const void *ptr1, const void *ptr2, SceSize num);
void *sce_paf_bcopy(void *dst, const void *src, SceSize n);
void *sce_paf_bzero(void *dst, SceSize n);

char *sce_paf_strchr(const char *s, int ch);
int sce_paf_strcmp(const char *s1, const char *s2);
size_t sce_paf_strlen(const char *s);
int sce_paf_strcasecmp(const char *s1, const char *s2);
int sce_paf_strncasecmp(const char *s1, const char *s2, SceSize len);
int sce_paf_strncmp(const char *s1, const char *s2, SceSize len);
char *sce_paf_strncpy(char *dst, const char *src, SceSize len);
char *sce_paf_strrchr(const char *s, int ch);

/**
 * @brief string to double
 *
 * @param[in]  nptr   The input float string
 * @param[out] endptr The float string endpoint
 *
 * @return parsed value
 */
double sce_paf_strtod(const char *nptr, char **endptr);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PAF_STDC_H_ */
