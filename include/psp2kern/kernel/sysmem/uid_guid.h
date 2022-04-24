/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/uid_guid.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_UID_GUID_H_
#define _PSP2KERN_KERNEL_SYSMEM_UID_GUID_H_

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

/*
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

/*
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
int ksceGUIDReferObjectWithClassLevel(SceUID guid, SceClass *pClass, SceUInt32 level, SceObjectBase **entry);

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


typedef SceGUIDKernelCreateOpt SceCreateUidObjOpt;

#define ksceKernelCreateUidObj(sce_class, name, opt, obj) ksceGUIDKernelCreateWithOpt(sce_class, name, opt, obj)
#define ksceKernelDeleteUid(guid) ksceGUIDClose(guid)
#define ksceKernelGetObjForUid(guid, sce_class, object) ksceGUIDReferObjectWithClass(guid, sce_class, object)
#define ksceKernelUidRelease(guid) ksceGUIDReleaseObject(guid)


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_UID_GUID_H_ */
