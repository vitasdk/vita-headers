/**
 * \usergroup{SceLoadcore}
 * \usage{psp2/kernel/loadcore.h}
 */


#ifndef _PSP2_KERNEL_LOADCORE_
#define _PSP2_KERNEL_LOADCORE_

#include <stdint.h>

typedef struct {
	uint16_t size;
	uint16_t ver;
	uint16_t attr;
	uint16_t funcNum;
	uint32_t varNum;
	uint32_t unkNum;
	uint32_t nid;
	const char *name;
	const uint32_t *nids;
	const void **ents;
} SceLibraryEntryTable;

#endif

