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
	SCE_SDIF_DEVICE_EMMC = 0x0, //!< Internal eMMC controller.
	SCE_SDIF_DEVICE_GC   = 0x1, //!< Game-card controller.
	SCE_SDIF_DEVICE_SDIO = 0x2, //!< WLAN/Bluetooth SDIO controller.
	SCE_SDIF_DEVICE_SD   = 0x3, //!< microSD controller index; unsupported by release FW 3.60 SceSdif.
} SceSdifDeviceIndex;

/** Alias using the internal uSD name for the microSD controller index. */
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
 * that prefix: 0x398 bytes for MMC, 0xC0 bytes for SD, and 0xD38 bytes for
 * SDIO. The context is owned by SceSdif and remains valid until that device is
 * reset or reinitialized; callers must not free it.
 */
typedef struct SceSdifContextPart SceSdifContextPart;

/**
 * Get an initialized MMC context.
 *
 * @param[in] dev_index - Device to validate.
 *
 * @return A direct pointer to ::SceSdifContextPart, or NULL if \a dev_index is
 *         unsupported or does not currently contain an initialized MMC
 *         device. The return type is still declared as
 *         `SceSdifDeviceContext *` for backwards compatibility.
 */
SceSdifDeviceContext* ksceSdifGetSdContextPartValidateMmc(SceSdifDeviceIndex dev_index);

/**
 * Initialize an MMC device.
 *
 * FW 3.60 supports ::SCE_SDIF_DEVICE_EMMC and ::SCE_SDIF_DEVICE_GC. The
 * context is static SceSdif storage and must not be freed.
 *
 * @param[in]  dev_index - Device to initialize.
 * @param[out] dev_ctx - Optional storage for the SceSdif-owned device context
 *                       pointer. It is set to NULL before
 *                       initialization is attempted.
 *
 * @return 0 on success, or a negative SceSdif error code.
 */
int ksceSdifInitializeMmcDevice(SceSdifDeviceIndex dev_index, SceSdifDeviceContext* dev_ctx);

/**
 * Send a game-card CMD56 request.
 *
 * FW 3.60 sends command argument 0 as a synchronous one-block write.
 *
 * @param[in] dev_ctx - Direct pointer to ::SceSdifContextPart. On FW 3.60,
 *                      pass the context pointer itself, not the address of
 *                      that pointer, despite the historical declaration.
 * @param[in] buf     - Command input buffer.
 * @param[in] size    - Input buffer size. It must equal the MMC block size in
 *                      the context; this is 0x200 for a FW 3.60 game card.
 *
 * @return 0 on success, 0x8032000E for an invalid pointer or size,
 *         0x80320011 when no command object is available, or another
 *         negative SceSdif error code.
 */
int ksceSdifWriteCmd56(SceSdifDeviceContext* dev_ctx, const void* buf, SceSize size);

/**
 * Receive a game-card CMD56 response.
 *
 * FW 3.60 sends command argument 1 as a synchronous one-block read.
 *
 * @param[in]  dev_ctx - Direct pointer to ::SceSdifContextPart. On FW 3.60,
 *                       pass the context pointer itself, not the address of
 *                       that pointer, despite the historical declaration.
 * @param[out] buf     - Command output buffer.
 * @param[in]  size    - Output buffer size. It must equal the MMC block size in
 *                       the context; this is 0x200 for a FW 3.60 game card.
 *
 * @return 0 on success, 0x8032000E for an invalid pointer or size,
 *         0x80320011 when no command object is available, or another
 *         negative SceSdif error code.
 */
int ksceSdifReadCmd56(SceSdifDeviceContext* dev_ctx, void* buf, SceSize size);

/**
 * Common 0x30-byte prefix of the FW 3.60 MMC, SD, and SDIO contexts.
 *
 * A ::SceSdifContextPart pointer may be cast to this type to inspect fields
 * shared by every device-specific context.
 */
typedef struct SceSdifContextPartBase {
	struct SceSdifContextGlobal *global_context; //!< Owning controller context.
	SceUInt32 card_flags; //!< Bit 0 indicates block addressing; otherwise sector arguments use byte addressing.
	union {
		SceUInt32 mmc_sector_size; //!< MMC block size in the low 16 bits.
		SceUInt32 sd_write_protected; //!< Nonzero when SD writes are prohibited.
		SceUInt32 sdio_function_count; //!< Number of SDIO functions.
	};
	union {
		SceUInt32 mmc_uses_special_sector_map; //!< Nonzero for the MF4GAM game-card layout.
		SceUInt32 sd_sector_size; //!< SD block size in the low 16 bits.
		SceUInt32 sdio_reserved_0C; //!< Its purpose is unknown.
	};
	SceUInt8 cid[16]; //!< Card identification register, in big-endian byte order.
	SceUInt8 csd[16]; //!< Card-specific data register, in big-endian byte order.
} SceSdifContextPartBase;
VITASDK_BUILD_ASSERT_EQ(0x30, SceSdifContextPartBase); // size is from FW 3.60

/**
 * Memory-mapped SD host-controller register block.
 *
 * FW 3.60 maps a 0x1000-byte register memblock for each of the three
 * controllers. The register prefix follows the SD Host Controller interface;
 * the remainder of the mapping is unused by the reviewed SceSdif code.
 */
typedef struct SceSdifHostRegisters {
	volatile SceUInt32 dma_system_address;
	volatile SceUInt16 block_size;
	volatile SceUInt16 block_count;
	volatile SceUInt32 argument;
	volatile SceUInt16 transfer_mode;
	volatile SceUInt16 command;
	volatile SceUInt32 response[4];
	volatile SceUInt32 buffer_data_port;
	volatile SceUInt32 present_state;
	volatile SceUInt8 host_control;
	volatile SceUInt8 power_control;
	volatile SceUInt8 block_gap_control;
	volatile SceUInt8 wakeup_control;
	volatile SceUInt16 clock_control;
	volatile SceUInt8 timeout_control;
	volatile SceUInt8 software_reset;
	volatile SceUInt16 normal_interrupt_status;
	volatile SceUInt16 error_interrupt_status;
	volatile SceUInt16 normal_interrupt_status_enable;
	volatile SceUInt16 error_interrupt_status_enable;
	volatile SceUInt16 normal_interrupt_signal_enable;
	volatile SceUInt16 error_interrupt_signal_enable;
	volatile SceUInt16 auto_cmd_error_status;
	volatile SceUInt16 host_control_2;
	volatile SceUInt32 capabilities[2];
	volatile SceUInt32 maximum_current_capabilities;
	SceUInt8 reserved_4C[4];
	volatile SceUInt16 force_event_auto_cmd_error_status;
	volatile SceUInt16 force_event_error_interrupt_status;
	volatile SceUInt8 adma_error_status;
	SceUInt8 reserved_55[3];
	volatile SceUInt32 adma_system_address;
	SceUInt8 reserved_5C[0xA0];
	volatile SceUInt16 slot_interrupt_status;
	volatile SceUInt16 host_controller_version;
	SceUInt8 reserved_100[0xF00];
} SceSdifHostRegisters;
VITASDK_BUILD_ASSERT_EQ(0x1000, SceSdifHostRegisters); // size is from FW 3.60

/** Internal state of a command owned by a controller context. */
typedef enum SceSdifCommandState {
	SCE_SDIF_COMMAND_STATE_FREE      = 0,
	SCE_SDIF_COMMAND_STATE_QUEUED    = 1,
	SCE_SDIF_COMMAND_STATE_ACTIVE    = 2,
	SCE_SDIF_COMMAND_STATE_COMPLETED = 3,
} SceSdifCommandState;

/**
 * SD/MMC command object.
 *
 * Each ::SceSdifContextGlobal owns 16 of these objects. SceSdif moves them
 * through the free, pending, active, and completed states; callers must not
 * allocate or free them independently.
 */
typedef struct SceSdifCmdInput {
	SceSize size; //!< Must be 0x240.
	/**
	 * Host-command, response, transfer, DMA, and completion flags. Observed bits
	 * include read (0x100), write (0x200), DMA (0x400), multi-block (0x800),
	 * per-command DMA-table allocation (0x100000), and forced completion
	 * (0x40000000).
	 */
	SceUInt32 state_flags;
	SceUInt32 command; //!< SD/MMC command index.
	SceUInt32 argument; //!< SD/MMC command argument.

	/// Stores a normal response without the command index and CRC-7.
	/// This can also store CID or CSD; CRC-7 is cleared.
	/// The storage order is reversed.
	union {
		SceUInt8 bytes[0x10];
		struct {
			SceUInt32 dw0;
			SceUInt32 dw1;
			SceUInt32 dw2;
			SceUInt32 dw3;
		} words;
	} response;

	void *buffer; //!< Command data buffer, split into leading, direct-DMA, and trailing regions as needed.
	SceUInt16 block_size; //!< Data block size; normally 0x200 for sector transfers.
	SceUInt16 block_count; //!< Number of data blocks.
	SceInt32 error_code; //!< Completion error written by the interrupt and timeout paths.
	SceUInt32 unknown_2C; //!< Its purpose is unknown.

	/** Command-specific storage; asynchronous SDIO transfers use its final 0x20 bytes. */
	SceUInt8 command_specific_data[0x30];

	struct SceSdifCmdInput *next_cmd;
	SceSdifCommandState state;
	SceUInt32 command_index; //!< Index from 0 through 15 in the owning controller's command array.
	/** Called after completion; its return value is passed on internally. */
	int (*completion_callback)(struct SceSdifCmdInput *cmd);

	SceUID event_flag_id; //!< Event flag used by synchronous commands.
	struct SceSdifCmdInput *secondary_cmd; //!< Dependent command started after this command succeeds.
	struct SceSdifContextGlobal *global_context;
	SceUIntPtr active_dma_descriptors_paddr; //!< Physical address of the active DMA descriptor table.

	SceUInt8 internal_dma_descriptors[0x80]; //!< Embedded table of up to 16 eight-byte DMA descriptors.

	void *active_dma_descriptors; //!< Active DMA descriptor table.
	SceKernelPARange physical_ranges[16]; //!< Storage within this command object, passed to ::ksceKernelVARangeToPAVector.

	SceUIntPtr internal_dma_descriptors_paddr; //!< Physical address of \a internal_dma_descriptors.
	SceUID dma_descriptor_memblock_uid; //!< UID of the dynamically allocated DMA descriptor memblock, if any.
	SceUInt32 unknown_18C; //!< Its purpose is unknown.

	SceUInt32 unknown_190; //!< Its purpose is unknown.
	SceUInt32 unknown_194; //!< Its purpose is unknown.
	void *aligned_buffer; //!< Direct-DMA portion of the command data buffer.
	SceSize aligned_buffer_size; //!< Size of the direct-DMA portion.

	SceSize leading_fragment_size; //!< Size of the leading unaligned fragment.
	SceSize trailing_fragment_size; //!< Size of the trailing unaligned fragment.
	SceUIntPtr leading_fragment_paddr; //!< Physical address of \a leading_fragment.
	SceUIntPtr trailing_fragment_paddr; //!< Physical address of \a trailing_fragment.

	SceInt64 start_time; //!< System time when the command starts.
	SceInt64 end_time; //!< System time when the command completes.

	SceUInt8 leading_fragment[0x40]; //!< Bounce buffer for the leading unaligned fragment.
	SceUInt8 trailing_fragment[0x40]; //!< Bounce buffer for the trailing unaligned fragment.
} SceSdifCmdInput;
VITASDK_BUILD_ASSERT_EQ(0x240, SceSdifCmdInput); // size is from FW 3.60

/** Mutable state for one FW 3.60 SDIF controller. */
typedef struct SceSdifContextData {
	SceSdifCmdInput *free_cmd_head;
	SceSdifCmdInput *free_cmd_tail;
	SceSdifCmdInput *pending_cmd_head;
	SceSdifCmdInput *pending_cmd_tail;

	SceSdifDeviceType device_type;
	SceSdifContextPartBase *device_context; //!< Device-specific context owned by SceSdif; callers must not free it.
	/** OCR voltage mask: 0x80 for controllers 0 and 2, and 0x300000 for controller 1. */
	SceUInt32 supported_voltages;
	SceUInt32 relative_card_address; //!< Relative card address in the low 16 bits.

	SceUInt32 controller_index; //!< Controller index from 0 through 2.
	SceUInt8 command_complete; //!< Set when the active host command completes.
	SceUInt8 suspended; //!< Nonzero while normal command submission is suspended.
	SceUInt8 unknown_26; //!< Its purpose is unknown.
	SceUInt8 unknown_27; //!< Its purpose is unknown.
	SceSdifCmdInput *active_cmd;
	SceSdifCmdInput *active_data_cmd;

	SceSdifHostRegisters *host_registers; //!< Base of the controller's 0x1000-byte register memblock.
	SceUInt32 enabled_subintr_mask;
	SceUInt8 timeout_control; //!< Host timeout-control value; initialized to 14 on FW 3.60.
	SceUInt8 slow_mode; //!< Enables minimum transfer delays for controller 1 MMC reads and writes.
	SceUInt8 slow_read_count; //!< Initialized from system time and incremented for each slow-mode read chunk.
	SceUInt8 slow_write_count; //!< Initialized from system time and incremented for each slow-mode write.

	SceUID host_registers_uid; //!< UID of the controller's 0x1000-byte register memblock.

	SceUID event_flag_id; //!< Controller event flag.
	SceKernelFastMutex sdif_fast_mutex; //!< Controller fast mutex.

	// It looks like this chunk is a separate structure since offset 0x2480 is used too often.

	SceUID dma_descriptor_pool_uid; //!< Offset 0x2484; UID of the 0x10000-byte DMA descriptor pool memblock.
	void *dma_descriptor_pool; //!< DMA descriptor pool used when the embedded table is too small.
	SceUInt32 ocr; //!< Last operation-conditions register value.

	SceUInt32 unknown_90; //!< Its purpose is unknown.
	SceKernelSpinlock spinlock;
	SceUInt64 last_transfer_duration; //!< Duration of the last sector transfer in microseconds.

	SceUInt8 sdio_interrupt_status;
	SceUInt8 sdio_enabled_function_mask;
	SceUInt8 sdio_pending_function_mask;
	SceUInt8 unknown_A3; //!< Its purpose is unknown.
	SceUInt32 sdio_subintr2_intr_code; //!< Interrupt code used with subinterrupt 2.
	SceUInt32 sdio_subintr3_8_intr_code; //!< Interrupt code used with subinterrupts 3 through 8.
	SceUInt32 sdio_dispatch_pending;

	SceUInt32 unknown_B0; //!< Cleared when the controller is reset; its purpose is unknown.
	SceUInt32 unknown_B4; //!< Cleared when the controller is reset; its purpose is unknown.
	SceUInt32 unknown_B8; //!< Its purpose is unknown.
	SceUInt32 unknown_BC; //!< Its purpose is unknown.
} SceSdifContextData;
VITASDK_BUILD_ASSERT_EQ(0xC0, SceSdifContextData); // size is from FW 3.60

/**
 * Process-global state for one SDIF controller.
 *
 * FW 3.60 owns three instances, selected by controller indices 0 through 2.
 */
typedef struct SceSdifContextGlobal {
	SceSdifCmdInput commands[16]; //!< Controller-owned command pool.
	SceSdifContextData ctx_data;
} SceSdifContextGlobal;
VITASDK_BUILD_ASSERT_EQ(0x24C0, SceSdifContextGlobal); // size is from FW 3.60

/**
 * Get a controller's card-detect input.
 *
 * On FW 3.60 this function is identical to
 * ::ksceSdifGetCardInsertState2.
 *
 * @param[in] device_index - Controller index. FW 3.60 accepts indices 0
 *                           through 2.
 *
 * @return 1 when a card is detected, 0 when no card is detected, or
 *         0x80320013 when \a device_index is unsupported.
 */
int ksceSdifGetCardInsertState1(SceSdifDeviceIndex device_index);

/**
 * Get a controller's card-detect input.
 *
 * On FW 3.60 this function is identical to
 * ::ksceSdifGetCardInsertState1.
 *
 * @param[in] device_index - Controller index. FW 3.60 accepts indices 0
 *                           through 2.
 *
 * @return 1 when a card is detected, 0 when no card is detected, or
 *         0x80320013 when \a device_index is unsupported.
 */
int ksceSdifGetCardInsertState2(SceSdifDeviceIndex device_index);

/**
 * Copy a device's card identification register.
 *
 * @param[in]  ctx - Initialized MMC or SD device context.
 * @param[out] cid - Destination for the 16-byte CID.
 *
 * @return 0 on success, or 0x8032000E when either pointer is NULL.
 */
int ksceSdifGetCID(const SceSdifContextPart *ctx, void *cid);

/**
 * Get a controller's process-global context.
 *
 * @param[in] device_index - Controller index. FW 3.60 accepts indices 0
 *                           through 2.
 *
 * @return The SceSdif-owned controller context, or NULL when
 *         \a device_index is unsupported. The returned pointer must not be
 *         freed.
 */
SceSdifContextGlobal *ksceSdifGetSdContextGlobal(SceSdifDeviceIndex device_index);

/**
 * Get an initialized SD context.
 *
 * @param[in] dev_index - Controller to validate.
 *
 * @return A direct pointer to ::SceSdifContextPart when the controller's
 *         current device type is ::SCE_SDIF_DEVICE_TYPE_SD, or NULL
 *         otherwise. The return type is still declared as
 *         `SceSdifDeviceContext *` for backwards compatibility.
 */
SceSdifDeviceContext* ksceSdifGetSdContextPartValidateSd(SceSdifDeviceIndex dev_index);

/**
 * Get an initialized SDIO context.
 *
 * @param[in] device_index - Controller to validate. The FW 3.60 WLAN and
 *                           Bluetooth callers use
 *                           ::SCE_SDIF_DEVICE_SDIO.
 *
 * @return The SceSdif-owned device context when the current device type is
 *         ::SCE_SDIF_DEVICE_TYPE_SDIO, or NULL otherwise. The returned
 *         pointer must not be freed.
 */
SceSdifContextPart *ksceSdifGetSdContextPartValidateSdio(SceSdifDeviceIndex device_index);

/**
 * Initialize an SD device.
 *
 * @param[in] device_index - Controller to initialize. FW 3.60 accepts indices
 *                           0 through 2, but initialization succeeds only when
 *                           the detected device is an SD card.
 * @param[out] result - Optional storage for a pointer to the SceSdif-owned
 *                      0xC0-byte SD context. The pointer is set to NULL before
 *                      initialization is attempted. Callers must not free the
 *                      context.
 *
 * @return 0 on success, 0x80320013 for an unsupported controller,
 *         0x80320017 when the detected device is not an SD card, or another
 *         negative SceSdif error code.
 */
int ksceSdifInitializeSdDevice(SceSdifDeviceIndex device_index, SceSdifContextPart **result);

/**
 * Read MMC sectors.
 *
 * FW 3.60 uses CMD17 for one sector and CMD18 for multiple sectors. The
 * MF4GAM game-card layout translates logical sectors through its partition
 * map and splits large reads into chunks of at most 0x1000 sectors.
 *
 * @param[in]  ctx      - MMC device context.
 * @param[in]  sector   - First logical sector to read.
 * @param[out] buffer   - Destination buffer.
 * @param[in]  sector_count - Number of sectors to read. Must not be 0.
 *
 * @return 0 on success, 0x8032000E for an invalid pointer, zero count, or
 *         invalid partition range, 0x80320011 when no command object is
 *         available, or another negative SceSdif error code.
 */
int ksceSdifReadSectorMmc(SceSdifContextPart *ctx, SceUInt32 sector, void *buffer, SceUInt32 sector_count);

/**
 * Read SD sectors.
 *
 * FW 3.60 uses CMD17 for one sector and CMD18 for multiple sectors. A
 * block-addressed card receives \a sector directly; a byte-addressed card
 * receives `sector << 9`.
 *
 * @param[in]  ctx      - SD device context.
 * @param[in]  sector   - First logical sector to read.
 * @param[out] buffer   - Destination buffer.
 * @param[in]  sector_count - Number of sectors to read. Must not be 0.
 *
 * @return 0 on success, 0x8032000E for an invalid pointer or zero count,
 *         0x80320011 when no command object is available, or another
 *         negative SceSdif error code.
 */
int ksceSdifReadSectorSd(SceSdifContextPart *ctx, SceUInt32 sector, void *buffer, SceUInt32 sector_count);

/**
 * Write MMC sectors.
 *
 * FW 3.60 uses CMD24 for one sector and CMD25 for multiple sectors. The
 * source buffer is read but not modified.
 *
 * @param[in] ctx      - MMC device context.
 * @param[in] sector   - First logical sector to write.
 * @param[in] buffer   - Source buffer.
 * @param[in] sector_count - Number of sectors to write. Must not be 0.
 *
 * @return 0 on success, 0x8032000E for an invalid pointer, zero count, or
 *         invalid partition range, 0x80320011 when no command object is
 *         available, or another negative SceSdif error code.
 */
int ksceSdifWriteSectorMmc(SceSdifContextPart *ctx, SceUInt32 sector, const void *buffer, SceUInt32 sector_count);

/**
 * Write SD sectors.
 *
 * FW 3.60 uses CMD24 for one sector and CMD25 for multiple sectors. A
 * block-addressed card receives \a sector directly; a byte-addressed card
 * receives `sector << 9`. The source buffer is read but not modified.
 *
 * @param[in] ctx      - SD device context.
 * @param[in] sector   - First logical sector to write.
 * @param[in] buffer   - Source buffer.
 * @param[in] sector_count - Number of sectors to write. Must not be 0.
 *
 * @return 0 on success, 0x8032001C when the SD context reports write
 *         protection, or another negative error code.
 */
int ksceSdifWriteSectorSd(SceSdifContextPart *ctx, SceUInt32 sector, const void *buffer, SceUInt32 sector_count);

/**
 * Enable slow-mode delays for controller 1 MMC transfers.
 *
 * This affects SceSdif game-card MMC sector reads and writes only. It does not
 * affect SD, SDIO, or SceMsif Memory Stick transfers.
 *
 * @return 0.
 */
int ksceSdifMemoryCardEnableSlowMode(void);

/**
 * Disable slow-mode delays for controller 1 MMC transfers.
 *
 * @return 0.
 */
int ksceSdifMemoryCardDisableSlowMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SDIF_H_ */
