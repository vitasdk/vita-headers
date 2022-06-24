/**
 * \usergroup{SceCLib}
 * \usage{psp2/kernel/clib.h,SceLibKernel_stub}
 */


#ifndef _PSP2_KERNEL_CLIB_H_
#define _PSP2_KERNEL_CLIB_H_

#include <psp2/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A handle for a managed memory space.
 */
typedef void* SceClibMspace;

/**
 * Structure for stats of SceClibMspace
 */
typedef struct SceClibMspaceStats {
    SceSize capacity;       //!< Capacity of the Mspace
    SceSize unk;            //!< Unknown, value is equal to capacity
    SceSize peak_in_use;    //!< Peak memory allocated
    SceSize current_in_use; //!< Current memory allocated
} SceClibMspaceStats;

/**
 * Run bkpt #0x88 and end the process in state -1
 *
 * @return none
 */
void sceClibAbort(void);

char sceClibLookCtypeTable(char ch);

int sceClibTolower(char ch);
int sceClibToupper(char ch);

int sceClibPrintf(const char *fmt, ...);
int sceClibSnprintf(char *dst, SceSize dst_max_size, const char *fmt, ...);
int sceClibVsnprintf(char *dst, SceSize dst_max_size, const char *fmt, va_list args);

char *sceClibStrncpy(char *dst, const char *src, SceSize len);
char *sceClibStrncat(char *dst, const char *src, SceSize len);

char *sceClibStrchr(const char *s, int ch);
char *sceClibStrrchr(const char *src, int ch);
char *sceClibStrstr(const char *s1, const char *s2);

int sceClibStrcmp(const char *s1, const char *s2);
int sceClibStrncmp(const char *s1, const char *s2, SceSize len);
int sceClibStrncasecmp(const char *s1, const char *s2, SceSize len);

SceSize sceClibStrnlen(const char *s1, SceSize max_len);

void *sceClibMemset(void *dst, int ch, SceSize len);
void *sceClibMemcpy(void *dst, const void *src, SceSize len);
void *sceClibMemcpy_safe(void *dst, const void *src, SceSize len);
void *sceClibMemmove(void *dst, const void *src, SceSize len);

int sceClibMemcmp(const void *s1, const void *s2, SceSize len);

void *sceClibMemchr(const void *src, int ch, SceSize len);

SceClibMspace sceClibMspaceCreate(void* memblock, SceSize size);
void sceClibMspaceDestroy(SceClibMspace mspace);

SceSize sceClibMspaceMallocUsableSize(void *ptr);
SceBool sceClibMspaceIsHeapEmpty(SceClibMspace mspace);

void sceClibMspaceMallocStats(SceClibMspace mspace, SceClibMspaceStats *stats);
void sceClibMspaceMallocStatsFast(SceClibMspace mspace, SceClibMspaceStats *stats);

void *sceClibMspaceMalloc(SceClibMspace mspace, SceSize size);
void *sceClibMspaceCalloc(SceClibMspace mspace, SceSize num, SceSize size);
void *sceClibMspaceRealloc(SceClibMspace mspace, void *ptr, SceSize size);
void *sceClibMspaceReallocalign(SceClibMspace mspace, void *ptr, SceSize size, SceSize alignment);
void *sceClibMspaceMemalign(SceClibMspace mspace, SceSize alignment, SceSize size);
void sceClibMspaceFree(SceClibMspace mspace, void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CLIB_H_ */

