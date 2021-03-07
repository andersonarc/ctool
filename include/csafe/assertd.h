/**
 * @file assertd.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief custom debug assertion macro for common conditions
 * @version 0.3
 * @date 2020-12-14
 */
    /* header guard */
#ifndef CSAFE_ASSERTD_H
#define CSAFE_ASSERTD_H

    /* includes */
#include <stdbool.h>    /* bool */
#include "csafe/log.h"  /* logging */
#include "csafe/logf.h" /* formatted logging */
#include <errno.h>      /* errno */
#include <string.h>     /* strerror */

    /* defines */
/**
 * @brief csafe debug assertion
 */
#ifdef NDEBUG
    #define _csafe_assertd(function, condition, message)
#else
    #define _csafe_assertd(function, condition, message)                         \
    if (condition) {                                                             \
        logfe_f(function, message ": errno is %d (%s)", errno, strerror(errno)); \
    }
#endif /* NDEBUG */

/**
 * @brief assert that variable is not null
 */
#define assertd_not_null(function, variable)                _csafe_assertd(function, (variable == NULL), "'" #variable "'" " is null, expected not null")

/**
 * @brief assert that function result is not null
 */
#define assertd_not_null_function(function, function_call)  _csafe_assertd(function, (function_call == NULL), "'" #function_call "' returned null, expected not null")

/**
 * @brief asserts that function result is not null and sets variable to the result
 */
#define assertd_not_null_function_set(function, variable, function_call)  _csafe_assertd(function, (variable = function_call) == NULL, "function call '" #function_call "' returned null, expected not null")

/**
 * @brief assert that a is equal to b
 */
#define assertd_equals(function, a, b)                      _csafe_assertd(function, !(a == b), "'" #a "' is not equal to '" #b "'")

/**
 * @brief assert that condition is true
 */
#define assertd_true(function, condition)                   _csafe_assertd(function, !(condition), "(" #condition ")" " is false, expected true")

/**
 * @brief assert that condition is false
 */
#define assertd_false(function, condition)                  _csafe_assertd(function, (condition), "(" #condition ")" " is true, expected false")

/**
 * @brief assert that a is equal to b with custom message
 */
#define assertd_equals_custom(function, a, b, message)      _csafe_assertd(function, !(a == b), message)

/**
 * @brief assert that condition is true with custom message
 */
#define assertd_true_custom(function, condition, message)   _csafe_assertd(function, !(condition), message)

/**
 * @brief assert that condition is false with custom message
 */
#define assertd_false_custom(function, condition, message)  _csafe_assertd(function, (condition), message)

/**
 * @brief assert that errno is equal to zero
 */
#define assertd_errno(function)                             assertd_equals(function, errno, 0)

#endif /* CSAFE_ASSERTD_H */