/**
 * \kernelgroup{SceGrab}
 * \usage{psp2kern/lowio/grab.h,SceGrabForDriver_stub}
 */

#ifndef _PSP2KERN_LOWIO_GRAB_H_
#define _PSP2KERN_LOWIO_GRAB_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sets or releases a Grab client request mask.
 *
 * When acquiring the mask, FW 3.60 waits until the selected clients are idle.
 * ScePower uses mask 0xF00 around GPU clock changes.
 *
 * @param[in] client_mask - Client mask. Only bits 0 through 11 are accepted.
 * @param[in] release - Zero to set the request bits and wait for idle, or
 * nonzero to clear the request bits.
 *
 * @return 0 on success, 0x803F0B00 if \a client_mask contains an invalid bit.
 */
int ksceGrabSetClientRequestMask(SceUInt32 client_mask, int release);

/**
 * Writes a whitelisted indexed SceGrab register.
 *
 * @param[in] register_id - Register selector. Bits 0 through 7 select an index
 * from 0 to 31 and bits 8 through 15 select a group from 0 to 5.
 * @param[in] value - Value to write.
 *
 * @return 0 on success, 0x803F0B00 for an invalid selector.
 */
int ksceGrabWriteIndexedRegister(SceUInt32 register_id, SceUInt32 value);

/**
 * Programs a SceGrab memory-bank physical address.
 *
 * FW 3.60 SceCompat programs banks 0 through 3 and sets bit 0 in each address
 * value. The secure handler accepts eight banks.
 *
 * @param[in] bank - Memory-bank index from 0 to 7.
 * @param[in] paddr - Physical-address value to program.
 *
 * @return 0 on success, 0x803F0B00 for an invalid bank or address.
 */
int ksceGrabSetMemoryBankAddress(SceUInt32 bank, SceUIntPtr paddr);

/**
 * Starts the compatibility hardware path.
 *
 * On FW 3.60, \a mode selects the value written to the low 24 bits of
 * Pervasive register 0x1E0: zero selects 0xA and nonzero selects 0xF. The
 * exact hardware meaning of this selector is unknown.
 *
 * @param[in] mode - Compatibility start mode.
 *
 * @return 0 on FW 3.60.
 */
int ksceGrabCompatStartEx(int mode);

/**
 * Initializes the compatibility LCD DMA path.
 *
 * @return 0 on FW 3.60.
 */
int ksceGrabCompatLcdDmacInit(void);

/**
 * Stops the compatibility hardware path.
 *
 * FW 3.60 clears all eight memory-bank address registers while stopping it.
 *
 * @return 0 on FW 3.60.
 */
int ksceGrabCompatStop(void);

/**
 * Waits for flags in the second SceSonyRegbus register region.
 *
 * This function spins without a timeout until at least one selected flag is
 * set at offset 0x120 in the physical 0xE8001000 region.
 *
 * @param[in] flags - Flag mask. The accepted values are 1, 2, and 3.
 *
 * @return 0 when a selected flag is set, or 0x803F0B00 for invalid flags.
 */
int ksceGrabWaitForSonyRegbusFlags(SceUInt32 flags);

/**
 * Programs two fields in ScePervasiveBaseClk register 0x10.
 *
 * Grab clients 8 through 11 are idle while the register is changed. The
 * purpose of both fields is unknown.
 *
 * @param[in] high_field - Three-bit field written at bit 16.
 * @param[in] low_field - Three-bit field written at bit 0.
 *
 * @return 0 on success, 0x803F0000 if either field is greater than 7.
 */
int ksceGrabSetBaseClockFields(SceUInt32 high_field, SceUInt32 low_field);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_GRAB_H_ */
