/**
 * @file assert.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief assert function implementation
 * @version 0.2
 * @date 2021-01-08
 */
    /* includes */
#include "csafe/assert.h" /* this */
#include <stdlib.h>       /* exit() */
#include <stdio.h>        /* print, stdout, stderr */
#include <errno.h>        /* errno */
#include <string.h>       /* strerror() */
#include <stdarg.h>       /* vararg */

    /* functions */
/**
 * @brief custom assertion function implementation, for internal use only
 * 
 * @param condition if true then error
 * @param message format string
 */
void _csafe_assert_impl(bool condition, char* message, ...) {
    if (condition) {
        va_list format;
        va_start(format, message);
        vfprintf(stderr, message, format);
        vfprintf(stdout, message, format);
        va_end(format);
        exit(EXIT_FAILURE);
    }
}