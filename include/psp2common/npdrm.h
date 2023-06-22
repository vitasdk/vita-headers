/**
 * \kernelgroup{SceNpDrm}
 * \usage{psp2common/npdrm.h}
 */

#ifndef _PSP2COMMON_NPDRM_H_
#define _PSP2COMMON_NPDRM_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceNpDrmActivationData { // size is 0x1038
  SceInt16 act_type; 
  SceInt16 version_flag;
  SceInt32 version;
  SceUInt64 account_id;
  SceUInt8 primary_key_table[0x80][0x10];
  SceUInt8 unk1[0x40];
  SceUInt8 openpsid[0x10];
  SceUInt8 unk2[0x10];
  SceUInt8 unk3[0x10];
  SceUInt8 secondary_key_table[0x65][0x10];
  SceUInt8 rsa_signature[0x100];
  SceUInt8 unk_sigmature[0x40];
  SceUInt8 ecdsa_signature[0x28]; // checked by pspemu, and SceNpDrm.
} SceNpDrmActivationData;

typedef struct SceNpDrmLicense { // size is 0x200
  SceInt16 version;       // -1 VITA, 0 PSP, 1 PSP-VITA
  SceInt16 version_flags; // 0, 1
  SceInt16 license_type;  // 1
  SceInt16 license_flags; // 0x400:non-check ecdsa
  SceUInt64 account_id;
  char content_id[0x30];
  char key_table[0x10];
  char key1[0x10];
  SceInt64 start_time;
  SceInt64 expiration_time;
  char ecdsa_signature[0x28];
  SceInt64 flags;
  char key2[0x10];
  char unk_0xB0[0x10];
  char open_psid[0x10];
  char unk_0xD0[0x10];
  char cmd56_handshake_part[0x14];
  int debug_upgradable;
  int unk_0xF8;
  int sku_flag;
  char rsa_signature[0x100];
} SceNpDrmLicense;

typedef struct ScePsmDrmLicense {
  char magic[0x8];
  SceUInt32 unk1;
  SceUInt32 unk2;
  SceUInt64 account_id;
  SceUInt32 unk3;
  SceUInt32 unk4;
  SceUInt64 start_time;
  SceUInt64 expiration_time;
  SceUInt8 activation_checksum[0x20];
  char content_id[0x30];
  SceUInt8 unk5[0x80];
  SceUInt8 unk6[0x20];
  SceUInt8 key[0x10];
  SceUInt8 signature[0x1D0];
  SceUInt8 rsa_signature[0x100];
} ScePsmDrmLicense;


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_NPDRM_H_ */
