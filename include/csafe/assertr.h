/**
 * @file assertr.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief custom runtime assertion macro for common conditions
 * @version 0.1
 * @date 2021-02-21
 */
    /* header guard */
#ifndef CSAFE_ASSERTR_H
#define CSAFE_ASSERTR_H

    /* includes */
#include <stdbool.h>   /* bool */
#include "csafe/log.h" /* logging */
#include <errno.h>     /* errno */

    /* defines */
/**
 * @brief csafe runtime assertion
 */
#define _csafe_assertr(condition, message, status) if (condition) { loge("_csafe_assertr", message); return status; }

/**
 * @brief asserts that variable is not null
 */
#define assertr_not_null(variable, status)                 _csafe_assertr(variable == NULL, ("variable '" #variable "'" " is null, expected not null"), status)

/**
 * @brief assert that function result is not null
 */
#define assertr_not_null_function(function_call, status)   _csafe_assertr((function_call) == NULL, ("function call '" #function_call "' returned null, expected not null"), status)

/**
 * @brief asserts that function result is not null and sets variable to the result
 */
#define assertr_not_null_function_set(variable, function_call, status)  _csafe_assertr((variable = function_call) == NULL, ("function call '" #function_call "' returned null, expected not null"), status)

/**
 * @brief asserts that @param a is equal to @param b
 */
#define assertr_equals(a, b, status)                       _csafe_assertr(!(a == b), ("'" #a "' is not equal to '" #b "'"), status)

/**
 * @brief asserts that generic condition is true
 */
#define assertr_true(condition, status)                    _csafe_assertr(!condition, ("condition (" #condition ")" " is false, expected true"), status)

/**
 * @brief asserts that generic condition is false
 */
#define assertr_false(condition, status)                   _csafe_assertr(condition, ("condition (" #condition ")" " is true, expected false"), status)

/**
 * @brief asserts that @param a is equal to @param b with custom message
 */
#define assertr_equals(a, b, message, status)              _csafe_assertr(!(a == b), ("'" #a "' is not equal to '" #b "': " message), status)

/**
 * @brief assert that @param condition is true with custom message
 */
#define assertr_true_custom(condition, message, status)    _csafe_assertr(!condition, ("condition (" #condition ")" " is false, expected true: " message), status)

/**
 * @brief assert that @param condition is false with custom message
 */
#define assertr_false_custom(condition, message, status)    _csafe_assertr(condition, ("condition (" #condition ")" " is true, expected false: " message), status)

/**
 * @brief asserts that errno is zero
 */
#define assertr_errno(status)                               assertr_equals(errno, 0, status)

#endif /* CSAFE_ASSERTR_H */