/**
 * \kernelgroup{SceDmacMgr}
 * \usage{psp2kern/kernel/dmac.h,SceDmacmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_DMAC_H_
#define _PSP2KERN_KERNEL_DMAC_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Generic DMA Functions
 */
/** @{ */
/**
 * DMA memcpy
 *
 * @param[in] dst  - Destination
 * @param[in] src  - Source
 * @param[in] size - Size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceDmacMemcpy(void *dst, const void *src, SceSize size);

/**
 * DMA memset
 *
 * @param[in] dst  - Destination
 * @param[in] c    - Constant
 * @param[in] size - Size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceDmacMemset(void *dst, int c, SceSize size);
/** @} */

#define SCE_KERNEL_DMAC_CHAIN_END ((SceKernelDmaOpTag *)0xFFFFFFFF) //!< Signifies the end of the DMA tag chain

/**
 * @defgroup DmacRegisterFields DMAC Register Fields
 */
/** @{ */

/**
 * @name Command Fields
 */
/** @{ */
#define SCE_KERNEL_DMAC_CMD_OP_COPY              (0x00000000) 
#define SCE_KERNEL_DMAC_CMD_OP_SET               (0x0000000C) 
#define SCE_KERNEL_DMAC_CMD_OP_RNG               (0x00000004) 
#define SCE_KERNEL_DMAC_CMD_OP_HASH_SHA1         (0x00000003)
#define SCE_KERNEL_DMAC_CMD_OP_HASH_SHA224       (0x0000000B) 
#define SCE_KERNEL_DMAC_CMD_OP_HASH_SHA256       (0x00000013)
#define SCE_KERNEL_DMAC_CMD_OP_HMAC_SHA1         (0x00000023)
#define SCE_KERNEL_DMAC_CMD_OP_HMAC_SHA224       (0x0000002B)
#define SCE_KERNEL_DMAC_CMD_OP_HMAC_SHA256       (0x00000033)
#define SCE_KERNEL_DMAC_CMD_OP_ENCRYPT_AES_ECB   (0x00000001)
#define SCE_KERNEL_DMAC_CMD_OP_ENCRYPT_AES_CBC   (0x00000009)
#define SCE_KERNEL_DMAC_CMD_OP_ENCRYPT_AES_CTR   (0x00000011)
#define SCE_KERNEL_DMAC_CMD_OP_ENCRYPT_DES_ECB   (0x00000041)
#define SCE_KERNEL_DMAC_CMD_OP_ENCRYPT_DES_CBC   (0x00000049)
#define SCE_KERNEL_DMAC_CMD_OP_DECRYPT_AES_ECB   (0x00000002)
#define SCE_KERNEL_DMAC_CMD_OP_DECRYPT_AES_CBC   (0x0000000A)
#define SCE_KERNEL_DMAC_CMD_OP_DECRYPT_AES_CTR   (0x00000012)
#define SCE_KERNEL_DMAC_CMD_OP_DECRYPT_DES_ECB   (0x00000042)
#define SCE_KERNEL_DMAC_CMD_OP_DECRYPT_DES_CBC   (0x0000004A)

#define SCE_KERNEL_DMAC_CMD_USE_EXTERNAL_KEY     (0x00000080)

#define SCE_KERNEL_DMAC_CMD_KEYSIZE_64BIT        (0x00000000)
#define SCE_KERNEL_DMAC_CMD_KEYSIZE_128BIT       (0x00000100)
#define SCE_KERNEL_DMAC_CMD_KEYSIZE_192BIT       (0x00000200)
#define SCE_KERNEL_DMAC_CMD_KEYSIZE_256BIT       (0x00000300)

#define SCE_KERNEL_DMAC_CMD_HASH_UPDATE          (0x00000400)
#define SCE_KERNEL_DMAC_CMD_HASH_FINALIZE        (0x00000800)

#define SCE_KERNEL_DMAC_CMD_COHERENT_SRC         (0x01000000) //!< L2 Cache Coherent pTag->src accesses
#define SCE_KERNEL_DMAC_CMD_COHERENT_DST         (0x02000000) //!< L2 Cache Coherent pTag->dst accesses
#define SCE_KERNEL_DMAC_CMD_COHERENT_IV          (0x0C000000) //!< L2 Cache Coherent pTag->iv accesses
/** @} */

/**
 * @name Block size fields
 */
/** @{ */
#define SCE_KERNEL_DMAC_BLOCKSIZE_SRC_SHIFT (0)
#define SCE_KERNEL_DMAC_BLOCKSIZE_SRC_MASK  (0x0000FFFF)

#define SCE_KERNEL_DMAC_BLOCKSIZE_DST_SHIFT (16)
#define SCE_KERNEL_DMAC_BLOCKSIZE_DST_MASK  (0xFFFF0000)
/** @} */

/**
 * @name Stat fields
 */
/** @{ */
#define SCE_KERNEL_DMAC_STAT_BUSY                  (0x00000001)
#define SCE_KERNEL_DMAC_STAT_ABORTED               (0x00000002)
#define SCE_KERNEL_DMAC_STAT_ERROR_READ            (0x00010000)
#define SCE_KERNEL_DMAC_STAT_ERROR_WRITE           (0x00020000)
#define SCE_KERNEL_DMAC_STAT_ERROR_ILLEGAL_CONFIG  (0x00040000)
#define SCE_KERNEL_DMAC_STAT_ERROR_TAG             (0x00080000)
#define SCE_KERNEL_DMAC_STAT_ERROR_ZERO_BYTE       (0x00100000)
/** @} */

/**
 * @name Coherency mask fields
 * 
 * This field, along with the SCE_KERNEL_DMAC_CMD_COHERENT_* command flags, control cache coherency behavior. \n
 * The actual encoding of the subfields is still unknown. \n
 * Observed values: \n
 * DmacMemcpy - 0x3E7F3 (src: 0x1F3 dst: 0x1F3) \n
 * DmacMemset - 0x3E600 (src: 0x000 dst: 0x1F3) \n
 * SblDmac5   - 0x3FFFF (src: 0x1FF dst: 0x1FF) \n
 */
/** @{ */
#define SCE_KERNEL_DMAC_COHERENCY_MSK_SRC_SHIFT    (0)
#define SCE_KERNEL_DMAC_COHERENCY_MSK_SRC_MASK     (0x000001FF)

#define SCE_KERNEL_DMAC_COHERENCY_MSK_DST_SHIFT    (9)
#define SCE_KERNEL_DMAC_COHERENCY_MSK_DST_MASK     (0x0003FC00)

#define SCE_KERNEL_DMAC_COHERENCY_MSK_SRC_DST_MASK (0x0003FFFF)

#define SCE_KERNEL_DMAC_COHERENCY_MSK_UNK_SHIFT    (18)
#define SCE_KERNEL_DMAC_COHERENCY_MSK_UNK_MASK     (0x07FC0000) //!< This mask is set internally by DmacMgr. It affects either DMA tag or IV coherency
/** @} */

/** @} */

typedef SceInt32 SceKernelDmaOpId;

typedef enum SceKernelDmacId {
    SCE_KERNEL_DMAC_ID_DMAC01  = 0x10, //!< DMAC0/1
    SCE_KERNEL_DMAC_ID_DMAC23  = 0x11, //!< DMAC2/3
    SCE_KERNEL_DMAC_ID_DMAC4   = 0x12, //!< DMAC4
    SCE_KERNEL_DMAC_ID_DMAC5   = 0x13, //!< DMAC5
    SCE_KERNEL_DMAC_ID_DMAC6   = 0x14  //!< DMAC6 (Devkit only)
} SceKernelDmacId;

typedef enum SceKernelDmaOpFlag {
    SCE_KERNEL_DMA_OP_PHYSICAL_ADDR    = 0x000, //!< src and dst addresses are physical addresses
    SCE_KERNEL_DMA_OP_VIRTUAL_SRC_ADDR = 0x001, //!< src addresses are virtual addresses
    SCE_KERNEL_DMA_OP_VIRTUAL_DST_ADDR = 0x010, //!< dst addresses is virtual addresses
    SCE_KERNEL_DMA_OP_VIRTUAL_ADDR     = 0x011, //!< Both src and dst addresses are virtual addresses
    SCE_KERNEL_DMA_OP_COMPLETE_CHAIN   = 0x100, //!< Full DMA chain is provided, starting from pTag and ending with pTag + 1 
} SceKernelDmaOpFlag;

typedef enum SceKernelDmaOpSyncMode {
    SCE_KERNEL_DMA_OP_SYNC_POLL       = 0x1, //!< Poll for completion without waiting
    SCE_KERNEL_DMA_OP_SYNC_WAIT       = 0x2, //!< Wait for completion
    SCE_KERNEL_DMA_OP_SYNC_TIMED_WAIT = 0x3, //!< Wait for completion with timeout
} SceKernelDmaOpSyncMode;

typedef struct SceKernelDmaOpTag {
    const void *src;
    void *dst;
    SceUInt32 len;
    SceUInt32 cmd; //!< Bitwise combination of SCE_KERNEL_DMAC_CMD_* fields
    SceUInt32 keyring;
    void *iv;
    SceUInt32 blockSize;
    struct SceKernelDmaOpTag *pNext; //!< Set to SCE_KERNEL_DMAC_CHAIN_END to signify the last tag
} SceKernelDmaOpTag;

typedef struct SceKernelDmaOpEncDec {
    SceUInt32 keyring;
    void *iv;
    SceUInt32 unk_0x8;
    SceUInt32 reserved;
    SceUInt8 key[0x40];
} SceKernelDmaOpEncDec;

typedef struct SceKernelDmaOpChainParam {
    SceSize size;
    SceUInt32 coherencyMask;
    SceUInt32 setValue; //!< 8-bit value duplicated into 32 bits
} SceKernelDmaOpChainParam;

typedef struct SceKernelDmaOpEncDecChainParam {
    SceKernelDmaOpChainParam header; //!< header.size = sizeof(SceKernelDmaOpEncDecChainParam)
    SceKernelDmaOpEncDec encDec;
} SceKernelDmaOpEncDecChainParam;

typedef struct SceKernelDmaOpDirectParam {
    const void *src;
    void *dst;
    SceUInt32 len;
    SceUInt32 cmd; //!< Bitwise combination of SCE_KERNEL_DMAC_CMD_* fields
    SceUInt32 blockSize;
    SceUInt32 coherencyMask;
    SceUInt32 setValue; //!< 8-bit value duplicated into 32 bits
    SceKernelDmaOpEncDec encDec;
} SceKernelDmaOpDirectParam;

typedef void (*SceKernelDmaOpCallback)(SceKernelDmaOpId opid, SceUInt32 stat, void *pUserData, SceKernelDmaOpTag *pTag);

/**
 * @brief Allocate a DMA Op handle.
 * 
 * @param name - Name of the DMA Op.
 * 
 * @return the ID of the DMA Op on success, < 0 on error.
 */
SceKernelDmaOpId ksceKernelDmaOpAlloc(const char *name);
/**
 * @brief Free a DMA Op handle.
 * 
 * @param opid - The DMA Op to free.
 * 
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpFree(SceKernelDmaOpId opid);

/**
 * @brief Enqueue a DMA Op.
 *
 * @param opid - The target DMA Op.
 * 
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpEnQueue(SceKernelDmaOpId opid);
/**
 * @brief Dequeue a DMA Op.
 *
 * @param opid - The target DMA Op.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpDeQueue(SceKernelDmaOpId opid);
/**
 * @brief Cancel a DMA Op.
 *
 * @param opid - The target DMA Op.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpQuit(SceKernelDmaOpId opid);
/**
 * @brief Synchronize with the completion of a DMA Op
 *
 * @param opid - The target DMA Op.
 * @param syncMode - One of ::SceKernelDmaOpSyncMode
 * @param pTimeout - Time limit for ::SCE_KERNEL_DMA_OP_SYNC_TIMED_WAIT
 * @param ppErrorTag - The ::SceKernelDmaOpTag which was running when the DMA Op failed.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpSync(SceKernelDmaOpId opid, SceKernelDmaOpSyncMode syncMode, SceUInt32 *pTimeout, SceKernelDmaOpTag **ppErrorTag);

/**
 * @brief Assign a DMA Op to one of the DMA controllers.
 *
 * @param opid - The target DMA Op.
 * @param dmac - The DMA controller to assign it to.
 * @param channel  - The channel of the controller (0 - 15 for DMAC4, 0 otherwise).
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpAssign(SceKernelDmaOpId opid, SceKernelDmacId dmac, SceUInt32 channel);
/**
 * @brief Setup a DMA Op with a direct set of parameters.
 *
 * @param opid - The target DMA Op.
 * @param pParam - The parameters for the DMA Op.
 * @param flag - One of ::SceKernelDmaOpFlag, excluding ::SCE_KERNEL_DMA_OP_COMPLETE_CHAIN.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpSetupDirect(SceKernelDmaOpId opid, SceKernelDmaOpDirectParam *pParam, SceKernelDmaOpFlag flag);
/**
 * @brief Setup a DMA Op with a chain of tags
 *
 * @param opid - The target DMA Op.
 * @param pTag - The list of DMA tags for the op.
 * @param pParam - The parameters for the DMA Op.
 * @param flag - One of ::SceKernelDmaOpFlag.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpSetupChain(SceKernelDmaOpId opid, SceKernelDmaOpTag *pTag, SceKernelDmaOpChainParam *pParam, SceKernelDmaOpFlag flag);
/**
 * @brief Append a new list of tags to the DMA Op.
 *
 * @param opid - The target DMA Op.
 * @param pTag - The list of DMA tags to append.
 * @param flag - One of ::SceKernelDmaOpFlag.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpConcatenate(SceKernelDmaOpId opid, SceKernelDmaOpTag *pTag, SceKernelDmaOpFlag flag);
/**
 * @brief Set the callback for the completion of the DMA Op.
 *
 * @param opid - The target DMA Op.
 * @param callback  - The callback.
 * @param pUserData - The callback parameter.
 * 
 * @return 0 on success, < 0 on error.
 */
int ksceKernelDmaOpSetCallback(SceKernelDmaOpId opid, SceKernelDmaOpCallback callback, void *pUserData);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_DMAC_H_ */
