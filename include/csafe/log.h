/**
 * @file logf.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief csafe formatted logging
 * @version 0.2
 * @date 2021-02-07
 */
    /* header guard */
#ifndef CSAFE_LOG_H
#define CSAFE_LOG_H

    /* defines */
/**
 * @brief message with custom suffix and prefix
 */
#define log_sp(message, function, suffix, prefix) _csafe_log_message(prefix "[" suffix "] " function ": " message)
/**
 * @brief message with custom suffix
 */
#define log_s(message, function, suffix) log_sp(message, function, suffix, "")


/**
 * @brief error with custom suffix and prefix
 */
#define loge_sp(message, function, suffix, prefix) _csafe_log_error(prefix "[" suffix "] " function ": " message)
/**
 * @brief error message with custom suffix
 */
#define loge_s(message, function, suffix) loge_sp(message, function, suffix, "")


/**
 * @brief debug message
 */
#ifdef DEBUG
    #define logd(message, function) log_s(message, function, "D")
#else
    #define logd(message, function)
#endif /* DEBUG */


/**
 * @brief info
 */
#define logi(message, function) log_s(message, function, "I")


/**
 * @brief warning
 */
#define logw(message, function) loge_sp(message, function, "W", "!")


/**
 * @brief error
 */
#define loge(message, function) loge_sp(message, function, "E", "!!!")


/**
 * @brief fatal error
 */
#define logfe(message, function) _csafe_log_fatal("!!!!! [FATAL] " function ": " message)




    /* functions */
/**
 * @brief print a message, for internal use only
 * 
 * @param message format string
 */
void _csafe_log_message(char* message);

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