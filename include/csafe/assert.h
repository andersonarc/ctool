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
#include <stdbool.h> /* bool */

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
#define _csafe_format(message) ("csafe: assert failed: " message "\n")

/**
 * @brief asserts that variable is not null
 */
#define assert_not_null(variable)                       csafe_assert(variable == NULL, _csafe_format("variable '" #variable "'" " is null, expected not null;"));

/**
 * @brief asserts that function result is not null
 */
#define assert_not_null_function(function_call)         csafe_assert(function_call == NULL, _csafe_format("function " #function_call " returned null, expected not null;"));

/**
 * @brief asserts that function result is not null and sets variable to the result
 */
#define assert_not_null_function_set(expression, ...)   csafe_assert((expression) == NULL, _csafe_format("expression (" #expression ") returned null, expected not null;"));

/**
 * @brief asserts that generic condition is true
 */
#define assert_true(condition)                          csafe_assert(!condition, _csafe_format("condition (" #condition ")" " is false, expected true;"));

/**
 * @brief asserts that generic condition is false
 */
#define assert_false(condition)                         csafe_assert(condition, _csafe_format("condition (" #condition ")" " is true, expected false;"));

/**
 * @brief asserts that errno is zero
 */
#define assert_errno()                                  csafe_assert(errno != 0, _csafe_format("errno is not equal to 0"));

#endif /* CSAFE_ASSERT_H */