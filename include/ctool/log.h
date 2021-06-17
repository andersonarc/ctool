/**
 * @file log.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-14
 * 
 *  Simple message logging system.
 * 
 *  There are 5 logging levels: debug, info, warning, error 
 *  and fatal error. Debug and info messages are printed to stdout, 
 *  error and warning messages - to stderr. Fatal error messages lead to 
 *  process exit, so be careful with them. On release builds 
 *  (with NDEBUG defined), debug logging is disabled. Higher levels 
 *  cannot be disabled, but this feature may be implemented later.
 */
    /* header guard */
#ifndef CTOOL_LOG_H
#define CTOOL_LOG_H

    /* includes */
#include "ctool/log/_internal.h" /* implementation */

    /* defines */
/**
 * Prints a debug message to stdout,
 * only when NDEBUG is undefined.
 * 
 * @param[in] message The message
 */
#ifndef NDEBUG
    #define logd(message, ...) _ctool_log_print_info("", "DEBUG", message, ##__VA_ARGS__)
#else 
    #define logd(message, ...)
#endif

/**
 * Prints an info message to stdout.
 * 
 * @param[in] message The message
 */
#define logi(message, ...) _ctool_log_print_info("", "INFO", message, ##__VA_ARGS__)

/**
 * Prints a warning message to stderr.
 * 
 * @param[in] message The message
 */
#define logw(message, ...) _ctool_log_print_error("!", "WARN", message, ##__VA_ARGS__)

/**
 * Prints an error message to stderr.
 * 
 * @param[in] message The message
 */
#define loge(message, ...) _ctool_log_print_error("!!!", "ERROR", message, ##__VA_ARGS__)

/**
 * Prints a fatal error message to stderr
 * and makes the program exit with error code 1.
 * 
 * @param[in] message The message
 */
#define logfe(message, ...) _ctool_log_print_fatal("!!!!!", "FATAL", message, ##__VA_ARGS__)

#endif /* CTOOL_LOG_H */