/**
 * \kernelgroup{SceSdif}
 * \usage{psp2kern/kernel/sdif.h,SceSdifForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SDIF_H_
#define _PSP2KERN_KERNEL_SDIF_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2kern/kernel/threadmgr/fast_mutex.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceSdifDeviceIndex {
	SCE_SDIF_DEVICE_EMMC = 0x0,
	SCE_SDIF_DEVICE_GC   = 0x1,
	SCE_SDIF_DEVICE_SDIO = 0x2,
	SCE_SDIF_DEVICE_SD   = 0x3,
} SceSdifDeviceIndex;

typedef SceSdifDeviceIndex SceSdifDevice;

#define SCE_SDIF_DEVICE_USD SCE_SDIF_DEVICE_SD

typedef enum SceSdifDeviceType {
	SCE_SDIF_DEVICE_TYPE_INVALID = 0x0,
	SCE_SDIF_DEVICE_TYPE_MMC     = 0x1,
	SCE_SDIF_DEVICE_TYPE_SD      = 0x2,
	SCE_SDIF_DEVICE_TYPE_SDIO    = 0x3,
} SceSdifDeviceType;

typedef void* SceSdifDeviceContext;

/**
 * Opaque device-specific context.
 *
 * FW 3.60 MMC, SD, and SDIO contexts all begin with a
 * ::SceSdifContextPartBase, but use different layouts and storage sizes beyond
 * that prefix: 0x3A0 bytes for MMC, 0xC0 bytes for SD, and 0xD38 bytes for
 * SDIO.
 */
typedef struct SceSdifContextPart SceSdifContextPart;

/**
 * @param[in] dev_index - Device to validate.
 *
 * @return A pointer to ::SceSdifContextPart, or NULL if the device is not an initialized MMC device.
 */
SceSdifDeviceContext* ksceSdifGetSdContextPartValidateMmc(SceSdifDeviceIndex dev_index);

/**
 * @param[in]  dev_index - Device to initialize.
 * @param[out] dev_ctx   - Receives a pointer to ::SceSdifContextPart.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifInitializeMmcDevice(SceSdifDeviceIndex dev_index, SceSdifDeviceContext* dev_ctx);

/**
 * @param[in] dev_ctx - A pointer to ::SceSdifContextPart.
 * @param[in] buf     - Command input buffer.
 * @param[in] size    - Input buffer size; the game-card caller uses 0x200 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifWriteCmd56(SceSdifDeviceContext* dev_ctx, const void* buf, SceSize size);

/**
 * @param[in]  dev_ctx - A pointer to ::SceSdifContextPart.
 * @param[out] buf     - Command output buffer.
 * @param[in]  size    - Output buffer size; the game-card caller uses 0x200 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifReadCmd56(SceSdifDeviceContext* dev_ctx, void* buf, SceSize size);

typedef struct SceSdifContextPartBase {
	struct SceSdifContextGlobal *gctx_ptr;
	uint32_t card_flags; //!< Bit 0 indicates block addressing.
	                     //!< When clear, sector arguments are converted to byte addresses.
	uint32_t def_sector_size_mmc;
	uint32_t def_sector_size_sd;
	uint8_t CID[16];
	uint8_t CSD[16];
} SceSdifContextPartBase;
VITASDK_BUILD_ASSERT_EQ(0x30, SceSdifContextPartBase); // size is from FW 3.60

typedef struct SceSdifMmcRegisters SceSdifMmcRegisters;

typedef enum SceSdifCommandState {
	SCE_SDIF_COMMAND_STATE_FREE      = 0,
	SCE_SDIF_COMMAND_STATE_QUEUED    = 1,
	SCE_SDIF_COMMAND_STATE_ACTIVE    = 2,
	SCE_SDIF_COMMAND_STATE_COMPLETED = 3,
} SceSdifCommandState;

typedef struct SceSdifCmdInput {
	uint32_t size; //!< Must be 0x240

	/// Bit 10 (shift left 0x15) is the request-invalidate flag for leading_fragment and trailing_fragment.
	/// This flag is used for CMD56 and CMD17.
	/// Bit 20 (shift left 0xB) requests that dma_descriptor_memblock_uid be freed.

	/// Bit 20 or bit 9 cancels invalidation; both must be clear.
	uint32_t state_flags; //!< Command and transfer flags used by the host-programming and completion paths.

	uint32_t command;
	uint32_t argument;

	/// Stores a normal response without the command index and CRC-7.
	/// This can also store CID or CSD; CRC-7 is cleared.
	/// The storage order is reversed.
	union {
		struct {
			char bytes[0x10];
		} db;
		struct {
			uint32_t dw0;
			uint32_t dw1;
			uint32_t dw2;
			uint32_t dw3;
		} dw;
	} response;

	void *buffer; //!< Command data buffer, split into leading, direct-DMA, and trailing regions as needed.
	uint16_t resp_block_size_24; //!< Response block size; typically the default sector size, 0x200
	uint16_t resp_n_blocks_26; //!< Number of blocks in the response; typically the number of sectors to read or write
	uint32_t error_code; //!< Error code from the interrupt handler
	uint32_t unk_2C; //!< No direct accesses were observed on FW 3.60.

	uint8_t command_specific_data[0x30]; //!< Command-specific storage; asynchronous SDIO transfers use its
	                                     //!< final 0x20 bytes.

	struct SceSdifCmdInput *next_cmd;
	uint32_t state; //!< One of ::SceSdifCommandState.
	uint32_t array_index;
	int (*set_event_flag_callback)(void *ctx);

	SceUID evid; //!< Event ID for SceSdif0, SceSdif1, SceSdif2, and possibly SceSdif3
	struct SceSdifCmdInput *secondary_cmd; //!< Used when multiple commands are sent
	struct SceSdifContextGlobal *gctx_ptr;
	uint32_t active_dma_descriptors_paddr; //!< Physical address of the active DMA descriptor table.

	char internal_dma_descriptors[0x80]; //!< Embedded table of up to 16 eight-byte DMA descriptors.

	void *active_dma_descriptors; //!< Active DMA descriptor table.
	uint8_t data_104[0x7C]; //!< No direct accesses were observed on FW 3.60.

	uint32_t unk_180; //!< No direct accesses were observed on FW 3.60.
	void *internal_dma_descriptors_paddr; //!< Physical address of internal_dma_descriptors.
	SceUID dma_descriptor_memblock_uid; //!< UID of the dynamically allocated DMA descriptor memblock, if any.
	uint32_t unk_18C; //!< No direct accesses were observed on FW 3.60.

	uint32_t unk_190; //!< No direct accesses were observed on FW 3.60.
	uint32_t unk_194; //!< No direct accesses were observed on FW 3.60.
	void *aligned_buffer; //!< Direct-DMA portion of the command data buffer.
	uint32_t aligned_buffer_size; //!< Size of the direct-DMA portion.

	uint32_t leading_fragment_size; //!< Size of the leading unaligned fragment.
	uint32_t trailing_fragment_size; //!< Size of the trailing unaligned fragment.
	void *leading_fragment_paddr; //!< Physical address of leading_fragment.
	void *trailing_fragment_paddr; //!< Physical address of trailing_fragment.

	SceInt64 start_time;
	SceInt64 end_time;

	char leading_fragment[0x40]; //!< Bounce buffer for the leading unaligned fragment.
	char trailing_fragment[0x40]; //!< Bounce buffer for the trailing unaligned fragment.
} SceSdifCmdInput;
VITASDK_BUILD_ASSERT_EQ(0x240, SceSdifCmdInput);

typedef struct SceSdifContextData {
	SceSdifCmdInput *free_cmd_head;
	SceSdifCmdInput *free_cmd_tail;
	SceSdifCmdInput *pending_cmd_head;
	SceSdifCmdInput *pending_cmd_tail;

	uint32_t dev_type_idx; //!< One of ::SceSdifDeviceType.
	SceSdifContextPartBase *ctx; //!< Pointer to a device-specific context
	uint32_t voltages; //!< MMC_VDD_165_195, MMC_VDD_32_33, etc.; observed values are 0x80 for SDIF0 and SDIF2, and 0x300000 for SDIF1 and SDIF3
	uint32_t relative_card_address;

	uint32_t array_idx; //!< One of 0, 1, or 2
	uint8_t command_complete;
	uint8_t suspended;
	uint8_t unk_26; //!< No direct accesses were observed on FW 3.60.
	uint8_t unk_27; //!< No direct accesses were observed on FW 3.60.
	SceSdifCmdInput *active_cmd;
	SceSdifCmdInput *active_data_cmd;

	SceSdifMmcRegisters *host_registers; //!< Base of the 0x1000-byte SceSdif0, SceSdif1, or SceSdif2 memblock
	uint32_t enabled_subintr_mask;
	uint8_t timeout_control;
	uint8_t slow_mode; //!< Enables minimum transfer delays for game-card reads and writes.
	uint8_t slow_read_delay_counter;
	uint8_t slow_write_delay_counter;

	SceUID host_registers_uid; //!< UID of the 0x1000-byte SceSdif0, SceSdif1, or SceSdif2 memblock

	SceUID evid; //!< Event ID for SceSdif0, SceSdif1, SceSdif2, and possibly SceSdif3
	SceKernelFastMutex sdif_fast_mutex; //!< Fast mutex for SceSdif0, SceSdif1, SceSdif2, and possibly SceSdif3

	// It looks like this chunk is a separate structure since offset 0x2480 is used too often.

	SceUID dma_descriptor_pool_uid; //!< Offset 0x2484; UID of the 0x10000-byte DMA descriptor pool memblock.
	void *dma_descriptor_pool; //!< DMA descriptor pool used when the embedded table is too small.
	uint32_t ocr;

	uint32_t unk_90; //!< No direct accesses were observed on FW 3.60.
	int spinlock; //!< Value of type ::SceKernelSpinlock.
	uint32_t last_transfer_duration_low; //!< Low word of the 64-bit last transfer duration.
	uint32_t last_transfer_duration_high; //!< High word of the 64-bit last transfer duration.

	uint8_t sdio_interrupt_status;
	uint8_t sdio_enabled_function_mask;
	uint8_t sdio_pending_function_mask;
	uint8_t unk_A3; //!< No direct accesses were observed on FW 3.60; may be padding.
	uint32_t sdio_subintr2_intr_code; //!< Interrupt code used with subinterrupt 2.
	uint32_t sdio_subintr3_8_intr_code; //!< Interrupt code used with subinterrupts 3 through 8.
	uint32_t sdio_dispatch_pending;

	uint32_t saved_device_type;
	uint32_t saved_context; //!< Pointer to the saved device-specific context, stored as a 32-bit value.
	uint32_t power_control; //!< Its low byte is copied to the host controller power-control register.
	uint32_t unk_BC; //!< No direct accesses were observed on FW 3.60.
} SceSdifContextData;
VITASDK_BUILD_ASSERT_EQ(0xC0, SceSdifContextData);

typedef struct SceSdifContextGlobal {
	SceSdifCmdInput commands[16];
	SceSdifContextData ctx_data;
} SceSdifContextGlobal;
VITASDK_BUILD_ASSERT_EQ(0x24C0, SceSdifContextGlobal);

int ksceSdifGetCardInsertState1(SceSdifDevice dev);
int ksceSdifGetCardInsertState2(int sd_ctx_index);

/**
 * @param[in]  ctx - Device context.
 * @param[out] cid - Destination for the 16-byte CID.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifGetCID(SceSdifContextPart *ctx, void *cid);
SceSdifContextGlobal *ksceSdifGetSdContextGlobal(int sd_ctx_index);
SceSdifContextPart *ksceSdifGetSdContextPartValidateSd(int sd_ctx_index);
SceSdifContextPart *ksceSdifGetSdContextPartValidateSdio(int sd_ctx_index);

/**
 * @param[in]  dev    - Device to initialize.
 * @param[out] dev_ctx - Points to storage that receives a pointer to ::SceSdifContextPart.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifInitializeSdDevice(SceSdifDevice dev, int *dev_ctx);

/**
 * @param[in]  ctx      - MMC device context.
 * @param[in]  sector   - Sector index, interpreted as a ::SceUInt32 value.
 * @param[out] buffer   - Destination buffer.
 * @param[in]  nSectors - Sector count, interpreted as a ::SceUInt32 value.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifReadSectorMmc(SceSdifContextPart *ctx, int sector, char *buffer, int nSectors);

/**
 * @param[in]  ctx      - SD device context.
 * @param[in]  sector   - Sector index, interpreted as a ::SceUInt32 value.
 * @param[out] buffer   - Destination buffer.
 * @param[in]  nSectors - Sector count, interpreted as a ::SceUInt32 value.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifReadSectorSd(SceSdifContextPart *ctx, int sector, char *buffer, int nSectors);

/**
 * @param[in] ctx      - MMC device context.
 * @param[in] sector   - Sector index, interpreted as a ::SceUInt32 value.
 * @param[in] buffer   - Read-only source buffer.
 * @param[in] nSectors - Sector count, interpreted as a ::SceUInt32 value.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifWriteSectorMmc(SceSdifContextPart *ctx, int sector, char *buffer, int nSectors);

/**
 * @param[in] ctx      - SD device context.
 * @param[in] sector   - Sector index, interpreted as a ::SceUInt32 value.
 * @param[in] buffer   - Read-only source buffer.
 * @param[in] nSectors - Sector count, interpreted as a ::SceUInt32 value.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSdifWriteSectorSd(SceSdifContextPart *ctx, int sector, char *buffer, int nSectors);

/**
 * Enables minimum transfer delays for game-card reads and writes.
 *
 * @return 0.
 */
int ksceSdifMemoryCardEnableSlowMode(void);

/**
 * Disables the extra game-card transfer delays.
 *
 * @return 0.
 */
int ksceSdifDisableSlowCardMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SDIF_H_ */
