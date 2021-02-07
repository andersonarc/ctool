/**
 * @file log.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief csafe logging
 * @version 0.1
 * @date 2021-02-07
 */
    /* header guard */
#ifndef CSAFE_LOG_H
#define CSAFE_LOG_H

    /* defines */
/**
 * @brief log error with custom suffix and prefix
 * 
 * @param message message format string
 * @param function caller function name
 * @param suffix letter suffix
 */
#define loge_sp(message, function, suffix, prefix, ...) _csafe_log_error(prefix "[" suffix "] " function ": " message, __VA_ARGS__)

/**
 * @brief log message with custom suffix and prefix
 * 
 * @param message message format string
 * @param function caller function name
 * @param suffix letter suffix
 */
#define log_sp(message, function, suffix, prefix, ...) _csafe_log_message(prefix "[" suffix "] " function ": " message, __VA_ARGS__)

/**
 * @brief log with custom suffix
 * 
 * @param message message format string
 * @param function caller function name
 * @param suffix letter suffix
 */
#define log_s(message, function, suffix, ...) log_sp(message, function, suffix, prefix, __VA_ARGS__)

/**
 * @brief log error with custom suffix
 * 
 * @param message message format string
 * @param function caller function name
 * @param suffix letter suffix
 */
#define loge_s(message, function, suffix, ...) loge_sp(message, function, suffix, prefix, __VA_ARGS__)

/**
 * @brief log debug
 * 
 * @param message message format string
 * @param function caller function name
 */
#define logd(message, function, ...) log_s(message, function, "D", __VA_ARGS__)

/**
 * @brief log info
 * 
 * @param message message format string
 * @param function caller function name
 */
#define logi(message, function, ...) log_s(message, function, "I", __VA_ARGS__)

/**
 * @brief log warning
 * 
 * @param message message format string
 * @param function caller function name
 */
#define logw(message, function, ...) loge_sp(message, function, "W", "!", __VA_ARGS__)

/**
 * @brief log error
 * 
 * @param message message format string
 * @param function caller function name
 */
#define loge(message, function, ...) loge_sp(message, function, "E", "!!!", __VA_ARGS__)

/**
 * @brief log fatal error
 * 
 * @param message message format string
 * @param function caller function name
 */
#define logef(message, function, ...) _csafe_exit_fatal("!!!!! [FATAL] " function ": " message, __VA_ARGS__)

    /* functions */
/**
 * @brief print a message, for internal use only
 * 
 * @param message format string
 */
void _csafe_log_message(char* message, ...);

/**
 * @brief print an error, for internal use only
 * 
 * @param message format string
 */
void _csafe_log_error(char* message, ...);

/**
 * @brief print a message and exit, for internal use only
 * 
 * @param message format string
 */
void _csafe_exit_fatal(char* message, ...);

#endif /* CSAFE_LOG_H */