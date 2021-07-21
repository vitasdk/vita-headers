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

typedef int SceRegMgrSystemParam;

// missing struct
typedef struct SceRegMgrValue SceRegMgrValue;

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param key      - Name of the key
 * @param binVal   - Pointer to a buffer to hold the value
 * @param binLen   - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrGetKeyBin(const SceChar8 *category, const SceChar8 *key, void *binVal, SceSize binLen);

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param key      - Name of the key
 * @param intVal   - Pointer to a int buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrGetKeyInt(const SceChar8 *category, const SceChar8 *key, SceInt32 *intVal);

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param key      - Name of the key
 * @param strVal   - Pointer to a char buffer to hold the value
 * @param strLen   - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrGetKeyStr(const SceChar8 *category, const SceChar8 *key, SceChar8 *strVal, SceSize strLen);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param key      - Name of the key
 * @param binVal   - Pointer to a buffer to hold the value
 * @param binLen   - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrSetKeyBin(const SceChar8 *category, const SceChar8 *key, const void *binVal, SceSize binLen);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param key      - Name of the key
 * @param intVal   - Pointer to an int buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrSetKeyInt(const SceChar8 *category, const SceChar8 *key, SceInt32 intVal);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param key      - Name of the key
 * @param strVal   - Pointer to a char buffer to hold the value
 * @param strLen   - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrSetKeyStr(const SceChar8 *category, const SceChar8 *key, const SceChar8 *strVal, SceSize strLen);

/**
 * Get all keys' initial information by category (from os0:kd/registry.db0)
 *
 * @param category  - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param keys[out] - Pointer to a char buffer to hold the values
 * @param keycnt    - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrGetInitVals(const SceChar8 *category, SceRegMgrValue *keys, SceInt32 keycnt);

/**
 * Get all keys' information by category
 *
 * @param category  - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param keys[out] - Pointer to a char buffer to hold the values
 * @param keycnt    - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrGetKeys(const SceChar8 *category, SceRegMgrValue *keys, SceInt32 keycnt);

/**
 * Set all keys' information by category
 *
 * @param categor y - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param keys[out] - Pointer to a char buffer that holds the values
 * @param keycnt    - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrSetKeys(const SceChar8 *category, const SceRegMgrValue *keys, SceInt32 keycnt);

/**
 * Get a system param key's information by id
 *
 * @param param       - The id of the key
 * @param intVal[out] - Pointer to an int to hold the value
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrSystemParamGetInt(SceRegMgrSystemParam param, SceInt32 *intVal);

/**
 * Get a system param key's information by id
 *
 * @param param       - The id of the key
 * @param strVal[out] - Pointer to a char buffer to hold the value
 * @param strLen      - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceRegMgrSystemParamGetStr(SceRegMgrSystemParam param, SceChar8 *strVal, SceSize strLen);

/**
 * Get the registry version
 *
 * @return < 0 on error
 */
SceInt32 sceRegMgrGetRegVersion(void);

SceInt32 sceRegMgrAddRegistryCallback(SceUID cbid, const SceChar8 *path);
SceInt32 sceRegMgrDbBackup(const SceChar8 *path, SceInt32 level);
SceInt32 sceRegMgrDbRestore(const SceChar8 *path);
SceInt32 sceRegMgrGetKeysInfo(const SceChar8 *category, SceRegMgrValue *keys, SceInt32 keycnt);
SceInt32 sceRegMgrInitRegistry(SceInt32 level);
SceInt32 sceRegMgrInitRegistryRegion(SceInt32 region, SceInt32 machine, SceInt32 qaflag);
SceInt32 sceRegMgrIsBlueScreen(SceInt32 regmgrError);
SceInt32 sceRegMgrRegisterCallback(SceUID cbid);
SceInt32 sceRegMgrRegisterDrvErrCallback(SceUID cbid);
SceInt32 sceRegMgrResetRegistryLv(const SceChar8 *resetPath, SceInt32 level);
SceInt32 sceRegMgrSrvCnvRegionInt(const SceChar8 *regstr);
SceInt32 sceRegMgrSrvCnvRegionPsCode(SceInt32 rgmgReg);
SceInt32 sceRegMgrSrvCnvRegionStr(SceInt32 regnum, SceChar8 *regstr, SceSize regstrsz);
SceInt32 sceRegMgrSrvGetRegion(void);
SceInt32 sceRegMgrSrvGetRegionStr(SceChar8 *regstr, SceSize regstrsz);
SceInt32 sceRegMgrStartCallback(SceUID cbid);
SceInt32 sceRegMgrStopCallback(SceUID cbid);
SceInt32 sceRegMgrSystemIsBlueScreen(SceInt32 regmgrError);
SceInt32 sceRegMgrSystemParamGetBin(SceRegMgrSystemParam param, SceChar8 *binVal, SceSize binSize);
SceInt32 sceRegMgrSystemParamSetBin(SceRegMgrSystemParam param, const SceChar8 *binVal, SceSize binSize);
SceInt32 sceRegMgrSystemParamSetInt(SceRegMgrSystemParam param, SceInt32 intVal);
SceInt32 sceRegMgrSystemParamSetStr(SceRegMgrSystemParam param, const SceChar8 *strVal, SceSize strLen);
SceInt32 sceRegMgrUnregisterCallback(SceUID cbid);
SceInt32 sceRegMgrUnregisterDrvErrCallback(SceUID cbid);
SceInt32 sceRegMgrUtilityGetBin(SceInt32 param, SceChar8 *binVal, SceSize binSize);
SceInt32 sceRegMgrUtilityGetInt(SceInt32 param, SceInt32 *intVal);
SceInt32 sceRegMgrUtilityGetStr(SceInt32 param, SceChar8 *strVal, SceSize strLen);
SceInt32 sceRegMgrUtilitySetBin(SceInt32 param, const SceChar8 *binVal, SceSize binSize);
SceInt32 sceRegMgrUtilitySetInt(SceInt32 param, SceInt32 intVal);
SceInt32 sceRegMgrUtilitySetStr(SceInt32 param, const SceChar8 *strVal, SceSize strLen);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_REGISTRYMGR_H_ */
