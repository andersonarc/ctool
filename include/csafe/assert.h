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
#include <stdlib.h>  /* exit() */
#include <stdio.h>   /* print, stdout, stderr */
#include <errno.h>   /* errno */
#include <string.h>  /* strerror() */
#include <stdbool.h> /* bool */
#include <stdarg.h>  /* vararg */

    /* functions */
/**
 * @brief custom assertion function, for internal use only
 */
void _csafe_assert_impl(bool condition, char* message, ...);

    /* defines */
/**
 * @brief csafe assertion
 */
#ifdef DEBUG
    #define csafe_assert(condition, message, ...) _csafe_assert_impl(condition, message, __VA_ARGS__)
#else
    #define csafe_assert(condition, message, ...)
#endif /* DEBUG */

/**
 * @brief header-local message formatter
 */
#define __fmt(message) ("csafe: assert failed: " message "\n")

/**
 * @brief asserts that variable is not null
 */
#define assert_not_null(variable)                       csafe_assert(variable == NULL, __fmt("variable '" #variable "'" " is null, expected not null;"));

/**
 * @brief asserts that function result is not null
 */
#define assert_not_null_function(function_call)         csafe_assert(function_call == NULL, __fmt("function " #function_call " returned null, expected not null;"));

/**
 * @brief asserts that function result is not null and sets variable to the result
 */
#define assert_not_null_function_set(expression, ...)   csafe_assert((expression) == NULL, __fmt("expression (" #expression ") returned null, expected not null;"));

/**
 * @brief asserts that generic condition is true
 */
#define assert_true(condition)                          csafe_assert(!condition, __fmt("condition (" #condition ")" " is false, expected true;"));

/**
 * @brief asserts that generic condition is false
 */
#define assert_false(condition)                         csafe_assert(condition, __fmt("condition (" #condition ")" " is true, expected false;"));

/**
 * @brief asserts that errno is zero
 */
#define assert_errno()                                  csafe_assert(errno != 0, __fmt("errno is not equal to 0"));

#undef _csfm /* undefine header-local macro */

#endif /* CSAFE_ASSERT_H */