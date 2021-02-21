/**
 * @file log.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief csafe logging
 * @version 0.3
 * @date 2021-02-07
 */
    /* header guard */
#ifndef CSAFE_LOG_H
#define CSAFE_LOG_H

    /* includes */
#include <stdio.h> /* puts */

    /* defines */
/**
 * @brief print a message, for internal use only
 * 
 * @param message string
 */
#define _csafe_log_message(message) fputs(message, stdout)

/**
 * @brief message with custom suffix and prefix
 */
#define log_sp(function, message, suffix, prefix) _csafe_log_message(prefix "[" suffix "] " function ": " message "\n")
/**
 * @brief message with custom suffix
 */
#define log_s(function, message, suffix) log_sp(function, message, suffix, "")

/**
 * @brief error with custom suffix and prefix
 */
#define loge_sp(function, message, suffix, prefix) _csafe_log_error(prefix "[" suffix "] " function ": " message "\n")
/**
 * @brief error message with custom suffix
 */
#define loge_s(function, message, suffix) loge_sp(function, message, suffix, "")

/**
 * @brief debug message
 */
#ifdef NDEBUG
    #define logd(function, message)
#else
    #define logd(function, message) log_s(function, message, "DEBUG")
#endif /* NDEBUG */

/**
 * @brief info
 */
#define logi(function, message) log_s(function, message, "INFO")

/**
 * @brief warning
 */
#define logw(function, message) loge_sp(function, message, "WARN", "! ")

/**
 * @brief error
 */
#define loge(function, message) loge_sp(function, message, "ERROR", "!!! ")

/**
 * @brief fatal error
 */
#define logfe(function, message) _csafe_log_fatal("!!!!! [FATAL] " function ": " message "\n")

    /* functions */
/**
 * @brief print an error, for internal use only
 * 
 * @param message format string
 */
void _csafe_log_error(char* message);

/**
 * @brief print a message and exit, for internal use only
 * 
 * @param message format string
 */
void _csafe_log_fatal(char* message);

#endif /* CSAFE_LOG_H */