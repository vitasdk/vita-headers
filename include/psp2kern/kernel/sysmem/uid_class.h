/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/uid_class.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_UID_CLASS_H_
#define _PSP2KERN_KERNEL_SYSMEM_UID_CLASS_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (* SceClassCallback)(void *item);

typedef struct SceClass {
	struct SceClass *next;
	struct SceClass *root;
	struct SceClass *prev;
	const char *name;
	struct SceClass *uidclass;
	unsigned int attributes;
	unsigned short itemsize;
	unsigned short itemsize_aligned;
	unsigned int unk1C;
	SceClassCallback create_cb;
	SceClassCallback destroy_cb;
	unsigned int magic; /* 0xABCE9DA5 */
} SceClass; /* size = 0x2C */

typedef struct SceObjectBase { // size is 0x8-bytes
	union {
		uint32_t sce_reserved[2];
		struct { // used by internally.
			void *object; // PUID entry, kernel heap object, etc...
			SceClass *sce_class;
		};
	};
	uint32_t data[];
} SceObjectBase;

SceClass *ksceKernelGetUidClass(void);
SceClass *ksceKernelGetUidDLinkClass(void);
SceClass *ksceKernelGetUidHeapClass(void);
SceClass *ksceKernelGetUidMemBlockClass(void);

int ksceKernelCreateClass(SceClass *cls, const char *name, void *uidclass, SceSize itemsize, SceClassCallback create, SceClassCallback destroy);

int ksceKernelFindClassByName(const char *name, SceClass **cls);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_UID_CLASS_H_ */
