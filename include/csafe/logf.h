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

    /* includes */
#include <stdlib.h> /* exit */
#include <stdio.h>  /* io */

    /* defines */
/**
 * @brief formatted message with custom suffix and prefix
 */
#define log_sp_f(function, message, suffix, prefix, ...) fprintf(stdout, prefix "[" suffix "] " function ": " message "\n", __VA_ARGS__)
/**
 * @brief formatted message with custom suffix
 */
#define log_s_f(function, message, suffix, ...) log_sp_f(function, message, suffix, "", __VA_ARGS__)

/**
 * @brief formatted error with custom suffix and prefix
 */
#define loge_sp_f(function, message, suffix, prefix, ...) fprintf(stderr, prefix "[" suffix "] " function ": " message "\n", __VA_ARGS__)
/**
 * @brief formatted error message with custom suffix
 */
#define loge_s_f(function, message, suffix, ...) loge_sp_f(function, message, suffix, "", __VA_ARGS__)

/**
 * @brief formatted debug message
 */
#ifdef NDEBUG
    #define logd_f(function, message, ...)
#else
    #define logd_f(function, message, ...) log_s_f(function, message, "DEBUG", __VA_ARGS__)
#endif /* NDEBUG */

/**
 * @brief formatted info
 */
#define logi_f(function, message, ...) log_s_f(function, message, "INFO", __VA_ARGS__)

/**
 * @brief formatted warning
 */
#define logw_f(function, message, ...) loge_sp_f(function, message, "WARN", "! ", __VA_ARGS__)

/**
 * @brief formatted error
 */
#define loge_f(function, message, ...) loge_sp_f(function, message, "ERROR", "!!! ", __VA_ARGS__)

/**
 * @brief formatted fatal error
 */
#define logfe_f(function, message, ...) fprintf(stderr, "!!!!! [FATAL] " function ": " message "\n", __VA_ARGS__); exit(1)

#endif /* CSAFE_LOG_F_H */