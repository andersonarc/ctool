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
#include <stdbool.h>   /* bool */
#include "csafe/log.h" /* logging */
#include <errno.h>     /* errno */

    /* defines */
/**
 * @brief csafe debug assertion
 */
#ifdef DEBUG
    #define _csafe_assertd(condition, message) if (condition) { logfe("_csafe_assertd", message); }
#else
    #define _csafe_assertd(condition, message)
#endif /* DEBUG */

/**
 * @brief assert that variable is not null
 */
#define assertd_not_null(variable)                _csafe_assertd(variable == NULL, ("variable '" #variable "'" " is null, expected not null"))

/**
 * @brief assert that function result is not null
 */
#define assertd_not_null_function(function_call)  _csafe_assertd((function_call) == NULL, ("function call '" #function_call "' returned null, expected not null"))

/**
 * @brief assert that function result is not null and set variable to the result
 */
#define assertd_not_null_function_set(expression) _csafe_assertd((expression) == NULL, ("expression (" #expression ") returned null, expected not null"))

/**
 * @brief assert that @param a is equal to @param b
 */
#define assertd_equals(a, b)                      _csafe_assertd(!(a == b), ("'" #a "' is not equal to '" #b "'"))

/**
 * @brief assert that @param condition is true
 */
#define assertd_true(condition)                   _csafe_assertd(!condition, ("condition (" #condition ")" " is false, expected true"))

/**
 * @brief assert that @param condition is false
 */
#define assertd_false(condition)                  _csafe_assertd(condition, ("condition (" #condition ")" " is true, expected false"))

/**
 * @brief assert that @param a is equal to @param b with custom message
 */
#define assertd_equals(a, b, message)             _csafe_assertd(!(a == b), ("'" #a "' is not equal to '" #b "': " message))

/**
 * @brief assert that @param condition is true with custom message
 */
#define assertd_true_custom(condition, message)   _csafe_assertd(!condition, ("condition (" #condition ")" " is false, expected true: " message))

/**
 * @brief assert that @param condition is false with custom message
 */
#define assertd_false_custom(condition, message)  _csafe_assertd(condition, ("condition (" #condition ")" " is true, expected false: " message))

/**
 * @brief assert that errno is equal to zero
 */
#define assertd_errno()                           assertd_equals(errno, 0)

#endif /* CSAFE_ASSERTD_H */