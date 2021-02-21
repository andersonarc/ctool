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

    /* defines */
/**
 * @brief print a message, for internal use only
 * 
 * @param message string
 */
#define _csafe_log_message(message) puts(message)

/**
 * @brief message with custom suffix and prefix
 */
#define log_sp(function, message, suffix, prefix) _csafe_log_message(prefix "[" suffix "] " function ": " message)
/**
 * @brief message with custom suffix
 */
#define log_s(function, message, suffix) log_sp(function, message, suffix, "")

/**
 * @brief error with custom suffix and prefix
 */
#define loge_sp(function, message, suffix, prefix) _csafe_log_error(prefix "[" suffix "] " function ": " message)
/**
 * @brief error message with custom suffix
 */
#define loge_s(function, message, suffix) loge_sp(function, message, suffix, "")

/**
 * @brief debug message
 */
#ifdef DEBUG
    #define logd(function, message) log_s(function, message, "D")
#else
    #define logd(function, message)
#endif /* DEBUG */

/**
 * @brief info
 */
#define logi(function, message) log_s(function, message, "I")

/**
 * @brief warning
 */
#define logw(function, message) loge_sp(function, message, "W", "!")

/**
 * @brief error
 */
#define loge(function, message) loge_sp(function, message, "E", "!!!")

/**
 * @brief fatal error
 */
#define logfe(function, message) _csafe_log_fatal("!!!!! [FATAL] " function ": " message)

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