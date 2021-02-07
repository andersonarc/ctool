/**
 * @file log.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief csafe logging implementation
 * @version 0.2
 * @date 2021-02-06
 */
    /* includes */
#include "csafe/log.h" /* this */
#include <stdlib.h>    /* exit() */
#include <stdio.h>     /* print, stdout, stderr */
#include <stdarg.h>    /* vararg */

    /* defines */
/**
 * @brief print a message, for internal use only
 * 
 * @param message string
 */
#define _csafe_log_message(message) puts(message)

    /* functions */
/**
 * @brief print a formatted message, for internal use only
 * 
 * @param message format string
 */
void _csafe_logf_message(char* message, ...) {
    va_list format;
    va_start(format, message);
    vfprintf(stderr, message, format);
    va_end(format);
}

/**
 * @brief print a formatted error, for internal use only
 * 
 * @param message format string
 */
void _csafe_logf_error(char* message, ...) {
    va_list format;
    va_start(format, message);
    vfprintf(stderr, message, format);
    vfprintf(stdout, message, format);
    va_end(format);
}

/**
 * @brief print a formatted error and exit, for internal use only
 * 
 * @param message format string
 */
void _csafe_logf_fatal(char* message, ...) {
    va_list format;
    va_start(format, message);
    vfprintf(stderr, message, format);
    vfprintf(stdout, message, format);
    va_end(format);
    exit(1);
}

/**
 * @brief print an error, for internal use only
 * 
 * @param message string
 */
void _csafe_log_error(char* message) {
    fputs(message, stderr);
    fputs(message, stdout);
}

/**
 * @brief print a message and exit, for internal use only
 * 
 * @param message string
 */
void _csafe_log_fatal(char* message) {
    fputs(message, stderr);
    fputs(message, stdout);
    exit(1);
}