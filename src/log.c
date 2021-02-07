/**
 * @file log.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief csafe logging implementation
 * @version 0.1
 * @date 2021-02-06
 */
    /* includes */
#include "csafe/log.h" /* this */
#include <stdlib.h>    /* exit() */
#include <stdio.h>     /* print, stdout, stderr */
#include <stdarg.h>    /* vararg */

    /* functions */
/**
 * @brief print a message, for internal use only
 * 
 * @param message format string
 */
void _csafe_log_message(char* message, ...) {
    va_list format;
    va_start(format, message);
    vfprintf(stderr, message, format);
    va_end(format);
}

/**
 * @brief print an error, for internal use only
 * 
 * @param message format string
 */
void _csafe_log_error(char* message, ...) {
    va_list format;
    va_start(format, message);
    vfprintf(stderr, message, format);
    vfprintf(stdout, message, format);
    va_end(format);
}

/**
 * @brief print a message and exit, for internal use only
 * 
 * @param message format string
 */
void _csafe_exit_fatal(char* message, ...) {
    va_list format;
    va_start(format, message);
    vfprintf(stderr, message, format);
    vfprintf(stdout, message, format);
    va_end(format);
    exit(1);
}