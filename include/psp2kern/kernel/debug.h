/**
 * \kernelgroup{SceKernelDebug}
 * \usage{psp2kern/kernel/debug.h,SceDebugForDriver_stub}
 */

// or SceDebugForKernel_stub

#ifndef _PSP2KERN_KERNEL_DEBUG_H_
#define _PSP2KERN_KERNEL_DEBUG_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceKernelDebugInfo {
	union {
		struct {
			SceUInt32 fileHash;
			SceUInt32 lineHash;
			SceUInt32 funcHash;
		};
		struct { /* For backwards compatibility */
			SceUInt32 hex_value0_hi;
			SceUInt32 hex_value0_lo;
			SceUInt32 hex_value1;
		};
	};
	const char *func;
	SceUInt32 line;
	const char *file;
} SceKernelDebugInfo;
VITASDK_BUILD_ASSERT_EQ(0x18, SceKernelDebugInfo);

typedef SceKernelDebugInfo SceKernelDebugMessageContext;

typedef enum SceKernelDebugInfoFlags {
	SCE_KERNEL_DEBUG_INFO_FLAG_NONE = 0,
	SCE_KERNEL_DEBUG_INFO_FLAG_CORE = 1,
	SCE_KERNEL_DEBUG_INFO_FLAG_FUNC = 2,
	SCE_KERNEL_DEBUG_INFO_FLAG_LINE = 4,
	SCE_KERNEL_DEBUG_INFO_FLAG_FILE = 8
} SceKernelDebugInfoFlags;

typedef enum SceKernelDebugLevel {
	SCE_KERNEL_DEBUG_LEVEL_ALWAYS = 0,
	SCE_KERNEL_DEBUG_LEVEL_DEBUG,
	SCE_KERNEL_DEBUG_LEVEL_TRACE
} SceKernelDebugLevel;

typedef enum SceKernelAssertLevel {
	SCE_KERNEL_ASSERT_LEVEL_0 = 0,
	SCE_KERNEL_ASSERT_LEVEL_1,
	SCE_KERNEL_ASSERT_LEVEL_2
} SceKernelAssertLevel;


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
int ksceKernelPrintf(const char *fmt, ...);

/**
 * @brief Kernel Printf
 *
 * @param[in] level - The printf level. see::SceKernelDebugLevel
 * @param[in] fmt   - The text format
 */
int ksceKernelPrintfLevel(SceUInt32 level, const char *fmt, ...);

/**
 * @brief Kernel Printf Level with Info
 *
 * @param[in] level   - The printf level. see::SceKernelDebugLevel
 * @param[in] flags   - The debug info flags
 * @param[in] dbginfo - The debug info
 * @param[in] fmt     - The text format
 */
int ksceKernelPrintfLevelWithInfo(SceUInt32 level, SceUInt32 flags, const SceKernelDebugInfo *dbginfo, const char *fmt, ...);

/**
 * @brief Kernel Printf with Info
 *
 * @param[in] flags   - ctx print flags, see:SceKernelDebugPrintFlags
 * @param[in] dbginfo - debug info
 * @param[in] fmt     - print fmt
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - main    log is pass to ksceDebugRegisterPutcharHandler's handler.
 *         dbginfo log is pass to ksceDebugSetHandlers's handler.
 */
int ksceKernelPrintfWithInfo(SceUInt32 flags, const SceKernelDebugInfo *dbginfo, const char *fmt, ...);

/**
 * @brief Kernel Vprintf
 *
 * @param[in] fmt - The text format
 * @param[in] arg - The fmt list
 */
int ksceKernelVprintf(const char *fmt, va_list arg);

/**
 * @brief Kernel Vprintf Level
 *
 * @param[in] level - The printf level. see::SceKernelDebugLevel
 * @param[in] fmt   - The text format
 * @param[in] arg   - The fmt list
 */
int ksceKernelVprintfLevel(SceUInt32 level, const char *fmt, va_list arg);

/**
 * @brief Kernel Panic
 *
 * @param[in] dbginfo - The debug info
 * @param[in] lr      - The link register
 */
__attribute__((__noreturn__)) void ksceKernelPanic(const SceKernelDebugInfo *dbginfo, const void *lr);

/**
 * @brief Kernel Printf Panic
 *
 * @param[in] dbginfo - The debug info
 * @param[in] lr      - The link register
 * @param[in] fmt     - The text format
 */
__attribute__((__noreturn__)) void ksceKernelPrintfPanic(const SceKernelDebugInfo *dbginfo, const void *lr, const char *fmt, ...);

/**
 * @brief Assertion. The condition SCE_FALSE to stopped CPU core.
 *
 * @param[in] condition - The condition
 * @param[in] dbginfo   - The debug info
 * @param[in] lr        - The link register
 *
 * @return none.
 */
void ksceKernelAssert(SceBool condition, const SceKernelDebugInfo *dbginfo, const void *lr);

/**
 * @brief Printf Assertion Level. The condition SCE_FALSE to stopped CPU core.
 *
 * @param[in] level     - The print level. see:SceKernelAssertLevel
 * @param[in] condition - The condition
 * @param[in] dbginfo   - The debug info
 * @param[in] lr        - The link register
 *
 * @return none.
 */
void ksceKernelAssertLevel(SceUInt32 level, SceBool condition, const SceKernelDebugInfo *dbginfo, const void *lr);

/**
 * @brief Printf Assertion Level. The condition SCE_FALSE to stopped CPU core.
 *
 * @param[in] level     - The print level. see:SceKernelAssertLevel
 * @param[in] condition - The condition
 * @param[in] dbginfo   - The debug info
 * @param[in] lr        - The link register
 * @param[in] fmt       - The text fmt
 *
 * @return none.
 */
void ksceKernelPrintfAssertLevel(SceUInt32 level, SceBool condition, const SceKernelDebugInfo *dbginfo, const void *lr, const char *fmt, ...);


#ifndef __PSP2FILEHASH__
#define __PSP2FILEHASH__ (0)
#endif

#ifndef __PSP2FILE__
#define __PSP2FILE__ __FILE__
#endif


#define SCE_KERNEL_PANIC() do { \
	static const SceKernelDebugInfo __dbginfo = {.fileHash = __PSP2FILEHASH__, .lineHash = 0, .funcHash = 0, .func = __FUNCTION__, .line = __LINE__, .file = __PSP2FILE__}; \
	ksceKernelPanic(&__dbginfo, __builtin_return_address(0)); \
	} while(0)

#define SCE_KERNEL_PRINTF_PANIC(__fmt__, ...) do { \
	static const SceKernelDebugInfo __dbginfo = {.fileHash = __PSP2FILEHASH__, .lineHash = 0, .funcHash = 0, .func = __FUNCTION__, .line = __LINE__, .file = __PSP2FILE__}; \
	ksceKernelPrintfPanic(&__dbginfo, __builtin_return_address(0), __fmt__, ##__VA_ARGS__); \
	} while(0)

#define SCE_KERNEL_ASSERT(__cond__) do { \
	static const SceKernelDebugInfo __dbginfo = {.fileHash = __PSP2FILEHASH__, .lineHash = 0, .funcHash = 0, .func = __FUNCTION__, .line = __LINE__, .file = __PSP2FILE__}; \
	ksceKernelAssert(__cond__, &__dbginfo, __builtin_return_address(0)); \
	} while(0)

#define SCE_KERNEL_ASSERT_LEVEL(__level__, __cond__) do { \
	static const SceKernelDebugInfo __dbginfo = {.fileHash = __PSP2FILEHASH__, .lineHash = 0, .funcHash = 0, .func = __FUNCTION__, .line = __LINE__, .file = __PSP2FILE__}; \
	ksceKernelAssertLevel(__level__, __cond__, &__dbginfo, __builtin_return_address(0)); \
	} while(0)

#define SCE_KERNEL_PRINTF_LEVEL(__level__, __fmt__, ...) do { \
	static const SceKernelDebugInfo __dbginfo = {.fileHash = __PSP2FILEHASH__, .lineHash = 0, .funcHash = 0, .func = __FUNCTION__, .line = __LINE__, .file = __PSP2FILE__}; \
	ksceKernelPrintfLevelWithInfo(__level__, 0xF, &__dbginfo, __fmt__, ##__VA_ARGS__); \
	} while(0)


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
int ksceKernelGetAssertLevel(void);

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
VITASDK_BUILD_ASSERT_EQ(0x1C, SceKernelDebugEventLog1);

// Related to network
typedef struct SceKernelDebugEventLog2 { // size is 0x4
	int data_0x40;    //!< 0 or 0x80412118?
} __attribute__((packed)) SceKernelDebugEventLog2;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelDebugEventLog2);

// Related to network
typedef struct SceKernelDebugEventLog3 { // size is 0x54
	int data_0x40;    //!< 0?
	char ip1[0x10];
	char ip2[0x10];
	char ip3[0x10];
	char ip4[0x10];
	char ip5[0x10];
} __attribute__((packed)) SceKernelDebugEventLog3;
VITASDK_BUILD_ASSERT_EQ(0x54, SceKernelDebugEventLog3);

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
VITASDK_BUILD_ASSERT_EQ(0x54 + 0x40, SceKernelDebugEventLog);

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


/* For backwards compatibility */

#define ksceDebugPrintf ksceKernelPrintf
#define ksceDebugPrintf2 ksceKernelPrintfWithInfo
#define ksceDebugPrintKernelPanic ksceKernelPanic
#define ksceDebugPrintfKernelPanic ksceKernelVprintfPanic
#define ksceDebugPrintKernelAssertion ksceKernelAssert
#define ksceDebugPrintfKernelAssertion ksceKernelPrintfAssertLevel
#define ksceKernelGetMinimumAssertionLevel ksceKernelGetAssertLevel


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_DEBUG_H_ */
