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
#include "csafe/status.h" /* return status */
#include "csafe/log.h" /* logging */
#include <errno.h>     /* errno */
#include <stdbool.h>   /* bool */

    /* defines */
/**
 * @brief csafe runtime assertion
 */
#define _csafe_assertr(function, condition, message, status) \
if (condition) {                                             \
    loge(function, message);                                 \
    return status;                                           \
}

/**
 * @brief asserts that variable is not null
 */
#define assertr_not_null(function, variable, status)                 _csafe_assertr(function, (variable == NULL), "variable '" #variable "'" " is null, expected not null", status)

/**
 * @brief assert that function result is not null
 */
#define assertr_not_null_function(function, function_call, status)   _csafe_assertr(function, (function_call == NULL), "function call '" #function_call "' returned null, expected not null", status)

/**
 * @brief asserts that function result is not null and sets variable to the result
 */
#define assertr_not_null_function_set(function, variable, function_call, status)  _csafe_assertr(function, (variable = function_call) == NULL, "function call '" #function_call "' returned null, expected not null", status)

/**
 * @brief asserts that a is equal to b
 */
#define assertr_equals(function, a, b, status)                       _csafe_assertr(function, !(a == b), "'" #a "' is not equal to '" #b "'", status)

/**
 * @brief asserts that generic condition is true
 */
#define assertr_true(function, condition, status)                    _csafe_assertr(function, !(condition), "condition (" #condition ")" " is false, expected true", status)

/**
 * @brief asserts that generic condition is false
 */
#define assertr_false(function, condition, status)                   _csafe_assertr(function, (condition), "condition (" #condition ")" " is true, expected false", status)

/**
 * @brief asserts that a is equal to b with custom message
 */
#define assertr_equals_custom(function, a, b, message, status)       _csafe_assertr(function, !(a == b), message, status)

/**
 * @brief assert that condition is true with custom message
 */
#define assertr_true_custom(function, condition, message, status)    _csafe_assertr(function, !(condition), message, status)

/**
 * @brief assert that condition is false with custom message
 */
#define assertr_false_custom(function, condition, message, status)    _csafe_assertr(function, (condition), message, status)

/**
 * @brief asserts that errno is zero
 */
#define assertr_errno(function, status)                               assertr_equals(function, errno, 0, status)

#endif /* CSAFE_ASSERTR_H */