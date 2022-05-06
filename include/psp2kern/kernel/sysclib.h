/**
 * \kernelgroup{SceSysclib}
 * \usage{psp2kern/kernel/sysclib.h,SceSysclibForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSCLIB_H_
#define _PSP2KERN_KERNEL_SYSCLIB_H_

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef void (* SceSysclibPrntCallback)(void *argp, int ch);


/**
 * @brief Set character to memory
 *
 * @param[in] dst - The output buffer pointer
 * @param[in] ch  - The character
 * @param[in] len - The character set length
 *
 * @return dst.
 */
void *memset(void *dst, int ch, unsigned int len);

/**
 * @brief Copy memory1 to memory2
 *
 * @param[in] dst - The output buffer pointer
 * @param[in] src - The input buffer pointer
 * @param[in] len - The copy length
 *
 * @return dst.
 */
void *memcpy(void *dst, const void *src, unsigned int len);

/**
 * @brief Move memory to memory
 *
 * @param[in] dst - The buffer pointer
 * @param[in] src - The buffer pointer
 * @param[in] len - The move length
 *
 * @return dst.
 */
void *memmove(void *dst, const void *src, unsigned int len);

/**
 * @brief Memory comparison
 *
 * @param[in] s1  - The memory source1
 * @param[in] s2  - The memory source2
 * @param[in] len - The cmp length
 *
 * @return If same memory contents, zero. else not zero.
 */
int memcmp(const void *s1, const void *s2, unsigned int len);

/**
 * @brief Search character from memory
 *
 * @param[in] src - The memory source
 * @param[in] ch  - The character
 * @param[in] len - The search length
 *
 * @return If found character, return it position. else NULL.
 */
void *memchr(const void *src, int ch, unsigned int n);

/**
 * @brief Strings comparison
 *
 * @param[in] s1 - The string source1
 * @param[in] s2 - The string source2
 *
 * @return If same string contents, zero. else not zero.
 */
int strcmp(const char *s1, const char *s2);

/**
 * @brief Strings comparison with length limit
 *
 * @param[in] s1 - The string source1
 * @param[in] s2 - The string source2
 * @param[in] n  - The max length
 *
 * @return If same string contents, zero. else not zero.
 */
int strncmp(const char *s1, const char *s2, unsigned int n);

/**
 * @brief Search character from string
 *
 * @param[in] src - The string source
 * @param[in] ch  - The character
 *
 * @return If found character, return it position. else NULL.
 */
char *strchr(const char *src, int ch);

/**
 * @brief Search string from string
 *
 * @param[in] s1 - The string source1
 * @param[in] s2 - The string source2
 *
 * @return If found string, return it position. else NULL.
 */
char *strstr(const char *s1, const char *s2);

/**
 * @brief Get string length
 *
 * @param[in] s - The string pointer
 *
 * @return String length.
 */
unsigned int strlen(const char *s);

/**
 * @brief Get string length with length limit
 *
 * @param[in] s - The string pointer
 * @param[in] n - The max length
 *
 * @return String length.
 */
unsigned int strnlen(const char *s, unsigned int n);

/**
 * @brief Copy string with length limit
 *
 * @param[in] dst - The output buffer pointer
 * @param[in] src - The input buffer pointer
 * @param[in] n   - The max copy length
 *
 * @return If same string contents, zero. else not zero.
 */
char *strncpy(char *dst, const char *src, unsigned int n);

int snprintf(char *dst, unsigned int max, const char *fmt, ...);
int vsnprintf(char *dst, unsigned int max, const char *fmt, va_list arg);

void *__memcpy_chk(void *dst, const void *src, unsigned int len, unsigned int dst_len);
void *__memset_chk(void *dst, int ch, unsigned int len, unsigned int dst_len);
void *__memmove_chk(void *dst, const void *src, unsigned int len, unsigned int dst_len);
char *__strncpy_chk(char *dst, const char *src, unsigned int n, unsigned int dst_len);

/**
 * @brief Internal functions used for snprintf, vsnprintf, kscDebugPrintf
 *
 * @param[in] callback - The callback to receive ch output by this function
 * @param[in] argp     - The passed to callback
 * @param[in] fmt      - The base format. example: "%-18s"
 * @param[in] list     - The variable argument list
 *
 * @return none
 */
void __prnt(SceSysclibPrntCallback callback, void *argp, const char *fmt, va_list list);

__attribute__((__noreturn__))
void __stack_chk_fail(void);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSCLIB_H_ */
