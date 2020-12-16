/**
 * @file assert.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief custom assetion macro for common conditions
 * @version 0.3
 * @date 2020-12-14
 */

    /* header guard */
#ifndef CSAFE_ASSERT_H
#define CSAFE_ASSERT_H

    /* includes */
#include <stdlib.h> /* exit() */
#include <stdio.h>  /* print, stdout, stderr */
#include <errno.h>  /* errno */
#include <string.h> /* strerror() */

    /* defines */
/**
 * @brief generic assertion macro
 */
#define _generic_assert(condition, message, ...) \
    if (condition) {                             \
        fprintf(stderr, "csafe: assert failed: " message "\n", __VA_ARGS__); \
        fprintf(stdout, "csafe: assert failed: " message "\n", __VA_ARGS__); \
        exit(EXIT_FAILURE);                                             \
    }

/**
 * @brief errno format string
 */
#define _ERRNO_POSTFIX "errno is %d (%s)", errno, strerror(errno)
        
/**
 * @brief asserts that variable is not null
 */
#define assert_not_null(variable) _generic_assert(variable == NULL, "variable '" #variable "'" " is null, expected not null; " _ERRNO_POSTFIX);

/**
 * @brief asserts that function result is not null
 */
#define assert_not_null_function(function_call) _generic_assert(function_call == NULL, "function " #function_call " returned null, expected not null; " _ERRNO_POSTFIX);

/**
 * @brief asserts that function result is not null and sets variable to the result
 */
#define assert_not_null_function_set(expression, ...) _generic_assert((expression) == NULL, "expression (" #expression ") returned null, expected not null; " _ERRNO_POSTFIX);

/**
 * @brief asserts that generic condition is true
 */
#define assert_true(condition) _generic_assert(!condition, "condition (" #condition ")" " is false, expected true; " _ERRNO_POSTFIX);

/**
 * @brief asserts that generic condition is false
 */
#define assert_false(condition) _generic_assert(condition, "condition (" #condition ")" " is true, expected false; " _ERRNO_POSTFIX);

/**
 * @brief asserts that errno is zero
 */
#define assert_errno() _generic_assert_format(errno != 0, "errno is %d (%s), expected 0", errno, strerror(errno));

#endif /* CSAFE_ASSERT_H */