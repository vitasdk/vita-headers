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


#define sce_paf_private_bcmp(__ptr1__, __ptr2__, __num__)             sce_paf_bcmp((__ptr1__), (__ptr2__), (__num__))
#define sce_paf_private_bcopy(__dst__, __src__, __n__)                sce_paf_bcopy((__dst__), (__src__), (__n__))
#define sce_paf_private_bzero(__dst__, __n__)                         sce_paf_bzero((__dst__), (__n__))
#define sce_paf_private_memchr(__src__, __ch__, __length__)           sce_paf_memchr((__src__), (__ch__), (__length__))
#define sce_paf_private_memcmp(__s1__, __s2__, __n__)                 sce_paf_memcmp((__s1__), (__s2__), (__n__))
#define sce_paf_private_memcpy(__dst__, __src__, __len__)             sce_paf_memcpy((__dst__), (__src__), (__len__))
#define sce_paf_private_memmove(__dst__, __src__, __len__)            sce_paf_memmove((__dst__), (__src__), (__len__))
#define sce_paf_private_memset(__dst__, __ch__, __len__)              sce_paf_memset((__dst__), (__ch__), (__len__))
#define sce_paf_private_snprintf                                      sce_paf_snprintf
#define sce_paf_private_vsnprintf(__dst__, __max__, __fmt__, __arg__) sce_paf_vsnprintf((__dst__), (__max__), (__fmt__), (__arg__))
#define sce_paf_private_strchr(__s__, __ch__)                         sce_paf_strchr((__s__), (__ch__))
#define sce_paf_private_strcmp(__s1__, __s2__)                        sce_paf_strcmp((__s1__), (__s2__))
#define sce_paf_private_strlen(__s__)                                 sce_paf_strlen((__s__))
#define sce_paf_private_strcasecmp(__s1__, __s2__)                    sce_paf_strcasecmp((__s1__), (__s2__))
#define sce_paf_private_strncasecmp(__s1__, __s2__, __len__)          sce_paf_strncasecmp((__s1__), (__s2__), (__len__))
#define sce_paf_private_strncmp(__s1__, __s2__, __len__)              sce_paf_strncmp((__s1__), (__s2__), (__len__))
#define sce_paf_private_strncpy(__dst__, __src__, __len__)            sce_paf_strncpy((__dst__), (__src__), (__len__))
#define sce_paf_private_strrchr(__s__, __ch__)                        sce_paf_strrchr((__s__), (__ch__))


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PAF_STDC_H_ */
