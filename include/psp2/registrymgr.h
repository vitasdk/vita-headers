/**
 * \usergroup{SceRegistryMgr}
 * \usage{psp2/registrymgr.h,SceRegistryMgr_stub}
 */

#ifndef _PSP2_REGISTRYMGR_H_
#define _PSP2_REGISTRYMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeyBin(const char *category, const char *name, void *buf, int size);

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a int buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeyInt(const char* category, const char* name, int* buf);

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeyStr(const char* category, const char* name, char* buf, const int size);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeyBin(const char *category, const char *name, void *buf, int size);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to an int buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeyInt(const char* category, const char* name, int buf);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeyStr(const char* category, const char* name, char* buf, const int size);

/**
 * Get all keys' initial information by category (from os0:kd/registry.db0)
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf[out] - Pointer to a char buffer to hold the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetInitVals(const char* category, char* buf, const int elements_number);

/**
 * Get all keys' information by category
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf[out] - Pointer to a char buffer to hold the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeys(const char* category, char* buf, const int elements_number);

/**
 * Set all keys' information by category
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf[out] - Pointer to a char buffer that holds the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeys(const char* category, char* buf, const int elements_number);

/**
 * Get a system param key's information by id
 *
 * @param id - The id of the key
 * @param buf[out] - Pointer to an int to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSystemParamGetInt(const int id, int* buf);

/**
 * Get a system param key's information by id
 *
 * @param id - The id of the key
 * @param buf[out] - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSystemParamGetStr(const int id, char* buf, const int size);


/**
 * Get the registry version
 *
 * @param id - The id of the key
 * @param buf[out] - Pointer to a char buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetRegVersion(int version, char* buf);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_REGISTRYMGR_H_ */
