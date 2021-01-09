/**
 * @file assert.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief assert function implementation
 * @version 0.1
 * @date 2021-01-08
 */
#include "csafe/assert.h" /* this */

/**
 * @brief custom assertion function implementation, for internal use only
 */
void _csafe_assert_impl(bool condition, char* message, ...) {
    if (condition) {
        va_list format;
        va_start(format, message);
        vfprintf(stderr, message, format);
        vfprintf(stdout, message, format);
        //?
        va_end(format);
        exit(EXIT_FAILURE);
    }
}