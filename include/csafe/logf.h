/**
 * @file logf.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief csafe formatted logging
 * @version 0.3
 * @date 2021-02-07
 */
    /* header guard */
#ifndef CSAFE_LOGF_H
#define CSAFE_LOGF_H

    /* defines */
/**
 * @brief formatted message with custom suffix and prefix
 */
#define log_sp_f(function, message, suffix, prefix, ...) _csafe_logf_message(prefix "[" suffix "] " function ": " message "\n", __VA_ARGS__)
/**
 * @brief formatted message with custom suffix
 */
#define log_s_f(function, message, suffix, ...) log_sp_f(function, message, suffix, "", __VA_ARGS__)


/**
 * @brief formatted error with custom suffix and prefix
 */
#define loge_sp_f(function, message, suffix, prefix, ...) _csafe_logf_error(prefix "[" suffix "] " function ": " message "\n", __VA_ARGS__)
/**
 * @brief formatted error message with custom suffix
 */
#define loge_s_f(function, message, suffix, ...) loge_sp_f(function, message, suffix, "", __VA_ARGS__)


/**
 * @brief formatted debug message
 */
#ifdef DEBUG
    #define logd_f(function, message, ...) log_s_f(function, message, "D", __VA_ARGS__)
#else
    #define logd_f(function, message, ...)
#endif /* DEBUG */


/**
 * @brief formatted info
 */
#define logi_f(function, message, ...) log_s_f(function, message, "I", __VA_ARGS__)


/**
 * @brief formatted warning
 */
#define logw_f(function, message, ...) loge_sp_f(function, message, "W", "!", __VA_ARGS__)


/**
 * @brief formatted error
 */
#define loge_f(function, message, ...) loge_sp_f(function, message, "E", "!!!", __VA_ARGS__)


/**
 * @brief formatted fatal error
 */
#define logfe_f(function, message, ...) _csafe_logf_fatal("!!!!! [FATAL] " function ": " message "\n", __VA_ARGS__)




    /* functions */
/**
 * @brief print a message, for internal use only
 * 
 * @param message format string
 */
void _csafe_logf_message(char* message, ...);

/**
 * @brief print an error, for internal use only
 * 
 * @param message format string
 */
void _csafe_logf_error(char* message, ...);

/**
 * @brief print a message and exit, for internal use only
 * 
 * @param message format string
 */
void _csafe_logf_fatal(char* message, ...);

#endif /* CSAFE_LOG_F_H */