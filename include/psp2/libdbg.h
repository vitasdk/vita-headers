/**
 * \usergroup{SceLibDbg}
 * \usage{psp2/libdbg.h,SceLibDbg_stub, SCE_SYSMODULE_DBG}
 */

#ifndef _PSP2_LIBDBG_H_
#define _PSP2_LIBDBG_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Logging level for sceDbgLoggingHandler.
 */
typedef enum SceDbgLogLevel {
	SCE_DBG_LOG_LEVEL_TRACE = 0, /* An extremely verbose logging level, mostly useful for internal developers. */
	SCE_DBG_LOG_LEVEL_DEBUG,     /* A diagnostic logging level. */
	SCE_DBG_LOG_LEVEL_INFO,      /* An informational logging level. */
	SCE_DBG_LOG_LEVEL_WARNING,   /* A logging level that gives warnings of situations detrimental to proper execution. */
	SCE_DBG_LOG_LEVEL_ERROR,     /* A logging level that will report erroneous conditions in execution. */
	SCE_DBG_NUM_LOG_LEVELS       /* The number of logging levels available. */
} SceDbgLogLevel;

/**
 * Macro for the component SceLibDbg is being called within.
 *
 * If undefined, NULL will be passed.
 */
#ifndef SCE_DBG_COMPONENT
#define SCE_DBG_COMPONENT NULL
#endif /* SCE_DBG_COMPONENT */

/**
 * Set whether or not to break/stop when an assertion fails.
 *
 * Enabled by default.
 */
#ifndef SCE_DBG_BREAK_ON_ASSERT
#define SCE_DBG_BREAK_ON_ASSERT 1
#endif /* SCE_DBG_BREAK_ON_ASSERT */

/**
 * Set the break/stop action when an assertion fails.
 *
 * Set to a breakpoint by default. abort() is an example of
 * a suitable break action.
 */
#ifndef SCE_DBG_BREAK_ACTION
#define SCE_DBG_BREAK_ACTION asm volatile ("bkpt 0x0")
#endif /* SCE_DBG_BREAK_ACTION */

#ifndef NDEBUG
/**
 * Assertion macro.
 *
 * @param[in] expression - The expression to be tested.
 */
#define SCE_DBG_ASSERT(expression) \
do { \
	if (!(expression)) { \
		sceDbgAssertionHandler(__FILE__, __LINE__, 0, SCE_DBG_COMPONENT, "Assertion ("#expression") failed.\n"); \
		if (SCE_DBG_BREAK_ON_ASSERT) \
			SCE_DBG_BREAK_ACTION; \
	} \
} while (0)
/**
 * Assertion macro with custom msg.
 *
 * @param[in] expression - The expression to be tested.
 * @param[in] msg        - printf format string message.
 */
#define SCE_DBG_ASSERT_MSG(expression, msg, ...) \
do { \
	if (!(expression)) { \
		sceDbgAssertionHandler(__FILE__, __LINE__, 0, SCE_DBG_COMPONENT, msg, ##__VA_ARGS__); \
		if (SCE_DBG_BREAK_ON_ASSERT) \
			SCE_DBG_BREAK_ACTION; \
	} \
} while (0)
/**
 * Logging macro.
 *
 * @param[in] logLevel - One of ::SceDbgLogLevel.
 * @param[in] msg      - printf formatted message.
 */
#define SCE_DBG_LOG(logLevel, msg, ...) \
sceDbgLoggingHandler(__FILE__, __LINE__, logLevel, SCE_DBG_COMPONENT, msg, ##__VA_ARGS__)

/**
 * Logging macros for individual log levels.
 */
#define SCE_DBG_LOG_TRACE(msg, ...) SCE_DBG_LOG(SCE_DBG_LOG_LEVEL_TRACE, msg, ##__VA_ARGS__)
#define SCE_DBG_LOG_INFO(msg, ...) SCE_DBG_LOG(SCE_DBG_LOG_LEVEL_INFO, msg, ##__VA_ARGS__)
#define SCE_DBG_LOG_DEBUG(msg, ...) SCE_DBG_LOG(SCE_DBG_LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__)
#define SCE_DBG_LOG_WARNING(msg, ...) SCE_DBG_LOG(SCE_DBG_LOG_LEVEL_WARNING, msg, ##__VA_ARGS__)
#define SCE_DBG_LOG_ERROR(msg, ...) SCE_DBG_LOG(SCE_DBG_LOG_LEVEL_ERROR, msg, ##__VA_ARGS__)
#else // Disable macros if NDEBUG is defined.
#define SCE_DBG_ASSERT(expression)
#define SCE_DBG_ASSERT_MSG(expression, msg, ...)
#define SCE_DBG_LOG(msg, ...)

#define SCE_DBG_LOG_TRACE(msg, ...)
#define SCE_DBG_LOG_INFO(msg, ...)
#define SCE_DBG_LOG_DEBUG(msg, ...)
#define SCE_DBG_LOG_WARNING(msg, ...)
#define SCE_DBG_LOG_ERROR(msg, ...)
#endif /* NDEBUG */

/**
 * Handler for assertion logging in this library. The complete formatted
 * output must not exceed 511 characters, so it is advised your message
 * does not exceed ~256 characters. The output will be truncated if it
 * does exceed 511 characters.
 *
 * @param[in] file      - Name of the file where the call was made.
 * @param[in] line      - Line number where the call was made.
 * @param[in] unk       - Unknown, never used internally.
 * @param[in] component - Name of the component where the call was made. Optional field.
 * @param[in] msg       - printf formatted message.
 *
 * @return Will return the unk parameter.
 */
int sceDbgAssertionHandler(const char* file, int line, int unk, const char* component, const char* msg, ...);
/**
 * Handler for logging in this library. The complete formatted
 * output must not exceed 511 characters, so it is advised
 * that your message does not exceed ~300 characters. The output
 * will be truncated if it does exceed 511 characters. A line break
 * is automatically appended.
 *
 * @param[in] file      - Name of the file where the call was made.
 * @param[in] line      - Line number where the call was made.
 * @param[in] logLevel  - One of ::SceDbgLogLevel.
 * @param[in] component - Name of the component where the call was made. Optional field.
 * @param[in] msg       - printf formatted message.
 *
 * @return 0 on success, <0 on truncation of message.
 */
int sceDbgLoggingHandler(const char* file, int line, SceDbgLogLevel logLevel, const char* component, const char* msg, ...);

/**
 * Set whether or not to enter a breakpoint upon logging an error.
 * Disabled by default.
 *
 * @param[in] breakOnError - Enter the breakpoint?
 */
void sceDbgSetBreakOnErrorState(SceBool breakOnError);
/**
 * Set whether or not to enter a breakpoint upon logging a warning.
 * Disabled by default.
 *
 * @param[in] breakOnWarning - Enter the breakpoint?
 */
void sceDbgSetBreakOnWarningState(SceBool breakOnWarning);
/**
 * Set the minimum logging level. Any attempts to log at a level lower
 * than this will not be outputted.
 */
void sceDbgSetMinimumLogLevel(SceDbgLogLevel level);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_LIBDBG_H_ */
