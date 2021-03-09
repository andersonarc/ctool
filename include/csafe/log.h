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
#include <stdlib.h> /* exit */
#include <stdio.h>  /* io */

    /* defines */
/**
 * @brief message with custom suffix and prefix
 */
#define log_sp(function, message, suffix, prefix) puts(prefix "[" suffix "] " function ": " message)
/**
 * @brief message with custom suffix
 */
#define log_s(function, message, suffix) log_sp(function, message, suffix, "")

/**
 * @brief error with custom suffix and prefix
 */
#define loge_sp(function, message, suffix, prefix) fputs(prefix "[" suffix "] " function ": " message "\n", stderr)
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
#define logfe(function, message) fputs("!!!!! [FATAL] " function ": " message "\n", stderr); exit(1)

#endif /* CSAFE_LOG_H */