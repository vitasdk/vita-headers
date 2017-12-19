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
 * Get all key's initial information by category (from os0:kd/registry.db0)
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf - Pointer to a char buffer to hold the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetInitVals(const char* category, char* buffer, const int elements_number);

/**
 * Get all key's information by category
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf - Pointer to a char buffer to hold the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeys(const char* category, char* buffer, const int elements_number);

/**
 * Set all key's information by category
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf - Pointer to a char buffer that holds the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeys(const char* category, char* buffer, const int elements_number);

//
/**
 * Get a system param key's information by id
 *
 * @param id - The id of the key
 * @param buf - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSystemParamGetInt(const int id, int* buf);

//SceRegMgrForGame_877ADB3F(0x008F94F9, v5 + 0xB0, 3);
/**
 * Get a system param key's information by id
 *
 * @param id - The id of the key
 * @param buf - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSystemParamGetStr(const int id, char* buf, const int size);


/**
 * Get the registry version
 *
 * @param id - The id of the key
 * @param buf - Pointer to a char buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetRegVersion(int version, char* buf);


/**
 * Registers a registry callback
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrRegisterCallback();

//v5 = "/CONFIG/DATE/date_format";
//a1 = SceRegMgr_A86F0A71(0, v5);
/**
 * Adds a registry callback
 *
 * @param unk - unknown (maybe callback_id)
 * @param key_path - The path to the key to be callbacked (e.g. "/CONFIG/DATE/date_format")
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrAddRegistryCallback(int unk, const char* key_path);

/**
 * Adds a registry callback
 *
 * @param unk - unknown (same as sceRegMgrAddRegistryCallback arg1)
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrStartCallback(int unk);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_REGISTRYMGR_H_ */
