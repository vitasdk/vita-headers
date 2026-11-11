/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/uid_guid.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_UID_GUID_H_
#define _PSP2KERN_KERNEL_SYSMEM_UID_GUID_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2kern/kernel/sysmem/uid_class.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceGUIDKernelCreateOpt {
	union {
		SceUInt32 flags;
		SceUInt32 attr;
	};
	SceUInt32 field_4;
	SceUInt32 field_8;
	SceUInt32 pid;
	SceUInt32 field_10;
	SceUInt32 field_14;
	SceUInt32 field_18;
	SceUInt32 field_1C;
} SceGUIDKernelCreateOpt;
VITASDK_BUILD_ASSERT_EQ(0x20, SceGUIDKernelCreateOpt);

/**
 * Create a GUID object that belongs to the target process id
 *
 * @param[in]  sce_class - The target class.
 * @param[in]  name      - The guid name.
 * @param[in]  opt       - The guid create option.
 *                         If do not specify the pid, it should belong to the kernel.
 * @param[out] obj       - The object pointer output pointer.
 *
 * @return GUID on success, < 0 on error.
 */
SceUID ksceGUIDKernelCreateWithOpt(SceClass *sce_class, const char *name, SceGUIDKernelCreateOpt *opt, SceObjectBase **obj);

/**
 * Close GUID (Inactive GUID)
 *
 * @param[in] guid - The remove target guid.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDClose(SceUID guid);

/**
 * Gets an object from a UID.
 *
 * This increases the internal reference count.
 *
 * @param[in]  guid   - The target global uid.
 * @param[out] object - The object pointer output pointer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDReferObject(SceUID guid, SceObjectBase **object);

/**
 * Gets an object from a UID with class.
 *
 * This retains the object refer count internally! You must call `ksceKernelUidRelease`
 * after you are done using it.
 *
 * @param[in]  guid      - The target global uid.
 * @param[in]  sce_class - The guid parent class.
 * @param[out] object    - The object pointer output pointer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDReferObjectWithClass(SceUID guid, SceClass *sce_class, SceObjectBase **object);

/**
 * Gets an object from a UID with class and level.
 *
 * This retains the object refer count internally! You must call `ksceKernelUidRelease`
 * after you are done using it.
 *
 * @param[in]  guid      - The target global uid.
 * @param[in]  sce_class - The guid parent class.
 * @param[in]  level     - The openable level (count/number).
 *                         The max passable number is 7.
 *                         If the internal object retention count is (level + 1) or higher, get an error.
 * @param[out] object    - The object pointer output pointer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDReferObjectWithClassLevel(SceUID guid, SceClass *pClass, SceUInt32 level, SceObjectBase **object);

/**
 * Releases an object referenced by the UID.
 *
 * This decreases the internal reference count.
 *
 * @param[in]  guid   - The target global uid.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDReleaseObject(SceUID guid);

/**
 * Get created GUID vectors.
 *
 * @param[in]  cls       - The Class.
 * @param[in]  vis_level - The Visible level.
 * @param[out] vector    - The GUID vector output.
 * @param[in]  num       - The GUID vector max number.
 * @param[out] ret_num   - The GUID vector result number.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDGetUIDVectorByClass(SceClass *cls, int vis_level, SceUID *vector, SceSize num, SceSize *ret_num);


/**
 * Gets an object from a UID with the specified class.
 *
 * @param[in]  uid    - The target GUID.
 * @param[in]  pClass - The object class.
 * @param[out] obj    - The object pointer output pointer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDGetObjectWithClass(SceUID uid, SceClass *pClass, SceObjectBase **obj);

/**
 * Creates a GUID object with the specified attributes.
 *
 * @param[in]  pClass   - The target class.
 * @param[in]  name     - The GUID name.
 * @param[in]  attr     - The GUID attributes.
 * @param[out] ppEntry  - The object pointer output pointer.
 *
 * @return GUID on success, < 0 on error.
 */
int ksceGUIDKernelCreateWithAttr(SceClass *pClass, const char *name, SceUInt32 attr, SceObjectBase **ppEntry);

/**
 * Opens a GUID.
 *
 * @param[in] guid - The target GUID.
 *
 * @return The opened GUID on success, < 0 on error.
 */
SceUID ksceGUIDOpenByGUID(SceUID guid);

/**
 * Gets the process ID associated with a UID.
 *
 * @param[in] uid - The target GUID.
 *
 * @return The process ID, < 0 on error.
 */
ScePID ksceGUIDGetPID(SceUID uid);

/**
 * Sets a GUID's class, name, and object.
 *
 * @param[in] uid    - The target GUID.
 * @param[in] pClass - The object class.
 * @param[in] name   - The GUID name.
 * @param[in] obj    - The object to associate with the GUID.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDSet(SceUID uid, SceClass* pClass, const char* name, SceObjectBase* obj);

/**
 * Sets a GUID's name.
 *
 * @param[in] uid  - The target GUID.
 * @param[in] name - The new GUID name.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDSetName(SceUID uid, const char* name);

/**
 * Sets the process ID associated with a GUID.
 *
 * @param[in] uid - The target GUID.
 * @param[in] pid - The process ID to associate with the GUID.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDSetPID(SceUID uid, ScePID pid);

/**
 * Sets a GUID's visibility level.
 *
 * @param[in] uid   - The target GUID.
 * @param[in] level - The visibility level.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDSetVisibilityLevel(SceUID uid, int level);

/**
 * Gets a GUID entry.
 *
 * @param[in]  uid    - The target GUID.
 * @param[out] pEntry - The sceUIDEntry.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGUIDGetEntry(SceUID uid, void** pEntry);

/**
 * Finds a GUID by name across all classes.
 *
 * @param[in] name - The object name to search for.
 *
 * @return The matching GUID, or < 0 on error.
 */
SceUID ksceGUIDFindByNameAll(const char *name);


/* For backwards compatibility */

typedef SceGUIDKernelCreateOpt SceCreateUidObjOpt;

#define ksceKernelCreateUidObj(sce_class, name, opt, obj) ksceGUIDKernelCreateWithOpt(sce_class, name, opt, obj)
#define ksceKernelDeleteUid(guid) ksceGUIDClose(guid)
#define ksceKernelGetObjForUid(guid, sce_class, object) ksceGUIDReferObjectWithClass(guid, sce_class, object)
#define ksceKernelUidRelease(guid) ksceGUIDReleaseObject(guid)


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_UID_GUID_H_ */
