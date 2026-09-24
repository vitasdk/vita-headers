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
 * Set or clear Grab client request bits.
 *
 * When setting the request bits, FW 3.60 waits until the selected clients are idle.
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
 * Write one of the allowed indexed SceGrab registers.
 *
 * @param[in] register_id - Register selector. Bits 0 through 7 select an index
 * from 0 to 31 and bits 8 through 15 select a group from 0 to 5.
 * Bits 16 through 31 are ignored. On FW 3.60, group 0 accepts indices 6 and
 * 8 through 11; group 1 accepts 1 and 8 through 11. Groups 2 through 5 all
 * accept indices 0 through 5. Group 2 also accepts index 8, group 3 accepts
 * index 9, group 4 accepts index 10, and group 5 accepts index 11.
 * @param[in] value - Value to write.
 *
 * @return 0 on success, 0x803F0B00 for an invalid selector.
 */
int ksceGrabWriteIndexedRegister(SceUInt32 register_id, SceUInt32 value);

/**
 * Set a SceGrab memory-bank physical address.
 *
 * FW 3.60 SceCompat programs banks 0 through 3 and sets bit 0 in each address
 * value. The secure handler accepts eight banks.
 *
 * @param[in] bank - Memory-bank index from 0 to 7.
 * @param[in] paddr - Physical-address value to program. FW 3.60 accepts the
 * range 0x20000000 through 0x2FFFFFFF and a SoC-dependent high-memory range
 * ending at 0x7FFFFFFF. The high-memory lower bound is either 0x42200000 or
 * 0x42600000.
 *
 * @return 0 on success, 0x803F0B00 for an invalid bank or address.
 */
int ksceGrabSetMemoryBankAddress(SceUInt32 bank, SceUIntPtr paddr);

/**
 * Start the compatibility hardware path.
 *
 * On FW 3.60, \a mode selects the value written to the low 24 bits of
 * Pervasive register 0x1E0: zero selects 0xA and nonzero selects 0xF. The
 * exact hardware meaning of this selector is unknown. SceCompat passes only
 * 0 and 1 and preserves the value across suspend and resume. The secure
 * handler quiesces all 12 Grab clients while starting the hardware.
 *
 * @param[in] mode - Compatibility start mode.
 *
 * @return 0 on FW 3.60.
 */
int ksceGrabCompatStartEx(int mode);

/**
 * Initialize the compatibility LCD DMA path. The secure handler quiesces all
 * 12 Grab clients while changing its hardware state.
 *
 * @return 0 on FW 3.60.
 */
int ksceGrabCompatLcdDmacInit(void);

/**
 * Stop the compatibility hardware path.
 *
 * FW 3.60 quiesces Grab clients 6 and 7 and clears all eight memory-bank
 * address registers while stopping it.
 *
 * @return 0 on FW 3.60.
 */
int ksceGrabCompatStop(void);

/**
 * Wait for flags in the second SceSonyRegbus register region.
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
 * Set the GPU core and GPU MP clock selectors.
 *
 * Grab clients 8 through 11 are idle while ScePervasiveBaseClk register 0x10
 * is changed. This function does not control the compatibility processor
 * clock.
 *
 * @param[in] gpu_core_selector - GPU core clock selector written to bits 16
 * through 18.
 * @param[in] gpu_mp_selector - GPU MP clock selector written to bits 0
 * through 2.
 *
 * @return 0 on success, 0x803F0000 if either selector is greater than 7.
 */
int ksceGrabSetGpuClockSelectors(SceUInt32 gpu_core_selector, SceUInt32 gpu_mp_selector);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_GRAB_H_ */
