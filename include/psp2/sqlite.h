/**
 * \usergroup{SceSqlite}
 * \usage{psp2/sqlite.h,SceSqlite_stub,SCE_SYSMODULE_SQLITE}
 */


#ifndef _PSP2_SQLITE_H_
#define _PSP2_SQLITE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	void *(*xMalloc)(int);
	void *(*xRealloc)(void*,int);
	void (*xFree)(void*);
} SceSqliteMallocMethods;

/**
 * Wrapper for sqlite3_config(SQLITE_CONFIG_MALLOC)
 *
 * @param[in] methods - A proper set of memory allocation methods
 *
 * @return 0 on success, < 0 on error.
*/
int sceSqliteConfigMallocMethods(SceSqliteMallocMethods* methods);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SQLITE_H_ */

