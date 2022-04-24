/**
 * \kernelgroup{SceKernelDebug}
 * \usage{psp2kern/kernel/debug.h,SceDebugForDriver_stub}
 */

// or SceDebugForKernel_stub

#ifndef _PSP2KERN_KERNEL_DEBUG_H_
#define _PSP2KERN_KERNEL_DEBUG_H_

#include <psp2kern/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelDebugMessageContext {
  SceUInt32 hex_value0_hi;
  SceUInt32 hex_value0_lo;
  SceUInt32 hex_value1;
  const char *func;
  SceSize line;
  const char *file;
} SceKernelDebugMessageContext;

typedef enum SceKernelDebugPrintFlags {
  SCE_DBG_PRINT_FLAG_NONE = 0,
  SCE_DBG_PRINT_FLAG_CORE = 1,
  SCE_DBG_PRINT_FLAG_FUNC = 2,
  SCE_DBG_PRINT_FLAG_LINE = 4,
  SCE_DBG_PRINT_FLAG_FILE = 8
} SceKernelDebugPrintFlags;

typedef enum SceDbgLogLevel {
  SCE_DBG_LOG_LEVEL_TRACE = 0, /* An extremely verbose logging level, mostly useful for internal developers. */
  SCE_DBG_LOG_LEVEL_DEBUG,     /* A diagnostic logging level. */
  SCE_DBG_LOG_LEVEL_INFO,      /* An informational logging level. */
  SCE_DBG_LOG_LEVEL_WARNING,   /* A logging level that gives warnings of situations detrimental to proper execution. */
  SCE_DBG_LOG_LEVEL_ERROR,     /* A logging level that will report erroneous conditions in execution. */
  SCE_DBG_NUM_LOG_LEVELS       /* The number of logging levels available. */
} SceDbgLogLevel;

int ksceDebugPutchar(int character);

/**
 * @brief Print log
 *
 * @param[in] fmt - print fmt
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - log is pass to ksceDebugRegisterPutcharHandler's handler.
 */
int ksceDebugPrintf(const char *fmt, ...);

/**
 * @brief Print log with ctx
 *
 * @param[in] flags - ctx print flags, see:SceKernelDebugPrintFlags
 * @param[in] ctx   - debug msg ctx
 * @param[in] fmt   - print fmt
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - main log is pass to ksceDebugRegisterPutcharHandler's handler.
 *         ctx  log is pass to ksceDebugSetHandlers's handler.
 */
int ksceDebugPrintf2(int flags, const SceKernelDebugMessageContext *ctx, const char *fmt, ...);

__attribute__((__noreturn__))
void ksceDebugPrintKernelPanic(const SceKernelDebugMessageContext *ctx, const void *lr);

__attribute__((__noreturn__))
void ksceDebugPrintfKernelPanic(const SceKernelDebugMessageContext *ctx, const void *lr, const char *fmt, ...);

/**
 * @brief Assertion with ctx
 *
 * @param[in] condition - condition
 * @param[in] ctx       - debug msg ctx
 * @param[in] lr        - The link register
 *
 * @return 0 on success, < 0 on error.
 */
int ksceDebugPrintKernelAssertion(int condition, const SceKernelDebugMessageContext *ctx, const void *lr);

/**
 * @brief Assertion with ctx and Print
 *
 * @param[in] level     - print level, see:SceDbgLogLevel
 * @param[in] condition - condition
 * @param[in] ctx       - debug msg ctx
 * @param[in] lr        - The link register
 * @param[in] fmt       - print fmt
 *
 * @return 0 on success, < 0 on error.
 */
int ksceDebugPrintfKernelAssertion(int level, int condition, const SceKernelDebugMessageContext *ctx, const void *lr, const char *fmt, ...);

int ksceDebugSetHandlers(int (* func)(int unk, const char *format, const va_list args), void *args);

int ksceDebugRegisterPutcharHandler(int (* func)(void *args, char c), void *args);

void *ksceDebugGetPutcharHandler(void);

/**
 * @brief Set kpanic flag
 *
 * @param[in] flag - If pass not zero to flag, kpanic is not stopped and do smc 0x122.
 *
 * @return previous flag.
 */
int ksceDebugDisableInfoDump(int flag);

/**
 * @brief Get current minimum assertion level
 *
 * @return current minimum assertion level.
 */
int ksceKernelGetMinimumAssertionLevel(void);

/**
 * @brief Get current minimum assertion level
 *
 * @param[in] level - new minimum assertion level
 *
 * @return previous minimum assertion level.
 */
int ksceKernelSetMinimumAssertionLevel(int level);

// process
typedef struct SceKernelDebugEventLog1 { // size is 0x1C
	int data_0x40;
	SceUID pid;
	int budget_type;
	int data_0x4C;    //!< 0xA
	char titleid[0xC];
} __attribute__((packed)) SceKernelDebugEventLog1;

// Related to network
typedef struct SceKernelDebugEventLog2 { // size is 0x4
	int data_0x40;    //!< 0 or 0x80412118?
} __attribute__((packed)) SceKernelDebugEventLog2;

// Related to network
typedef struct SceKernelDebugEventLog3 { // size is 0x54
	int data_0x40;    //!< 0?
	char ip1[0x10];
	char ip2[0x10];
	char ip3[0x10];
	char ip4[0x10];
	char ip5[0x10];
} __attribute__((packed)) SceKernelDebugEventLog3;

typedef struct SceKernelDebugEventLog {
	SceSize size;      //!< struct size(variable size)
	int data_0x04;     //!< 0xA, maybe titleid size
	char titleid[0xC]; //!< Title id of the process where the event occurred
	int flags;         //!< Event flags
	SceUID ppid;       //!< Parent process id
	SceUID data_0x1C;  //!< Thread id?
	int rsvd[4];
	SceUInt64 time;    //!< Time of the event occurred
	int data_0x38;
	SceSize item_size; //!< Event data size
	union {
		SceKernelDebugEventLog1 type1;
		SceKernelDebugEventLog2 type2;
		SceKernelDebugEventLog3 type3;
	};
} __attribute__((packed)) SceKernelDebugEventLog;

/**
 * @brief Get event log info
 *
 * @param[out] buf         - The SceKernelDebugEventLog buffer list
 * @param[in]  buf_size    - The buf size
 * @param[out] read_blocks - The read event log number
 *
 * @return < 0 on error.
 */
int ksceEventLogGetInfo(void *buf, SceSize buf_size, SceSize *read_blocks);

/**
 * @brief Get tty log info
 *
 * @param[out] buf         - The tty log buffer
 * @param[in]  buf_size    - The buf size
 *
 * @return log length on success, < 0 on error.
 */
int ksceKernelGetTtyInfo(char *buf, SceSize buf_size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_DEBUG_H_ */
