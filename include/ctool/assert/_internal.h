/**
 * @file internal.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-14
 *
 *  Assertion system internal code.
 * 
 *  Macro that check conditions and indicate errors,
 *  and predefined error messages for them.
 */
    /* header guard */
#ifndef CTOOL_ASSERT__INTERNAL_H
#define CTOOL_ASSERT__INTERNAL_H

    /* includes */
#include <malloc.h> /* memory allocation */
#include "ctool/log.h" /* logging */

    /* defines */
/**
 * If a condition is false, prints a message and returns
 * specified status from the caller function.
 * 
 * @param message   Message to print on error
 * @param condition Condition to assert as true
 * @param status    Status to return on error
 */
#define _ctool_assert_r_impl(message, condition, status, ...) \
    if (!(condition)) {                                       \
        loge(message, ##__VA_ARGS__);                         \
        return status;                                        \
    }

/**
 * If a condition is false, prints a message and makes
 * the program exit with code 1.
 * 
 * @param message   Message to print on error
 * @param condition Condition to assert as true
 */
#define _ctool_assert_d_impl(message, condition, ...)         \
    if (!(condition)) {                                       \
        logfe(message, ##__VA_ARGS__);                        \
    }

    /* utility defines */
#define _ctool_assert_equals(a, b) #a " is not equal to " #b

#define _ctool_assert_true(condition) #condition "is false, expected to be true"

#define _ctool_assert_false(condition) #condition "is true, expected to be false"

#define _ctool_assert_notnull(variable) #variable "is null"

#define _ctool_assert_malloc_cond(variable, size, type) NULL != (variable = (type) malloc(size))
#define _ctool_assert_malloc(variable) "memory allocation for " #variable " failed"

#endif /* CTOOL_ASSERT__INTERNAL_H */