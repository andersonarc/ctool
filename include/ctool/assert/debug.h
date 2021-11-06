/**
 * @file debug.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-14
 *
 *  Frontend for debug assertions
 * 
 *  Debug assertions are only executed when application
 *  is compiled in debug mode (with NDEBUG left undefined).
 *  Program exits with error code 1 on debug assertion failure.
 *
 *      Macro postfixes:
 *  assertd 'c' - with custom message
 */
    /* header guard */
#ifndef CTOOL_ASSERT_DEBUG_H
#define CTOOL_ASSERT_DEBUG_H

    /* includes */
#include <errno.h> /* errno */
#include <stdbool.h> /* boolean */

#include "ctool/assert/_internal.h" /* implementation */
#include "ctool/status.h" /* return status */

    /* defines */
/**
 * Asserts that A is equal to B
 * 
 * @param[in] a The first value
 * @param[in] b The second value
 */
#define assertd_equals(a, b) _ctool_assert_d_impl(_ctool_assert_equals(a, b), (a) == (b))
#define assertdc_equals(a, b, message, ...) _ctool_assert_d_impl(message, (a) == (b), ##__VA_ARGS__)

/**
 * Asserts that errno is equal to 0
 */
#define assertd_errno() assertd_equals(errno, 0)
#define assertdc_errno(message, ...) assertdc_equals(errno, 0, message, ##__VA_ARGS__)

/**
 * Asserts that an expression is equal to 0
 * 
 * @param[in] expression The expression
 */
#define assertd_zero(expression) assertd_equals(expression, 0)
#define assertdc_zero(expression, message, ...) assertdc_equals(expression, 0, message, ##__VA_ARGS__)

/**
 * Asserts that A is not equal to B
 * 
 * @param[in] a The first value
 * @param[in] b The second value
 */
#define assertd_not_equals(a, b) _ctool_assert_d_impl(_ctool_assert_not_equals(a, b), (a) != (b))
#define assertdc_not_equals(a, b, message, ...) _ctool_assert_d_impl(message, (a) != (b), ##__VA_ARGS__)

/**
 * Asserts that an expression returns ST_OK
 * 
 * @param[in] expression The expression
 */
#define assertd_status(expression) assertd_equals(expression, ST_OK)
#define assertdc_status(expression, message, ...) assertdc_equals(expression, ST_OK, message, ##__VA_ARGS__)

/**
 * Asserts that a condition is true
 * 
 * @param[in] condition The condition
 */
#define assertd_true(condition) _ctool_assert_d_impl(_ctool_assert_true(condition), (condition))
#define assertdc_true(condition, message, ...) _ctool_assert_d_impl(message, (condition), ##__VA_ARGS__)

/**
 * Asserts that a condition is false
 * 
 * @param[in] condition The condition
 */
#define assertd_false(condition) _ctool_assert_d_impl(_ctool_assert_false(condition), !(condition))
#define assertdc_false(condition, message, ...) _ctool_assert_d_impl(message, !(condition), ##__VA_ARGS__)

/**
 * Asserts that a variable is not NULL
 * 
 * @param[in] variable The variable
 */
#define assertd_not_null(variable) _ctool_assert_d_impl(_ctool_assert_not_null(variable), (variable) != NULL)
#define assertdc_not_null(variable, message, ...) _ctool_assert_d_impl(message, (variable) != NULL, ##__VA_ARGS__)

/**
 * Allocates memory of specified size
 * with malloc, asserts that it is not NULL,
 * then assigns it to a variable of specified type
 * 
 * @param[out] variable The variable
 * @param[in]  size     Size for allocation in bytes
 * @param[in]  type     Type of the variable
 */
#define assertd_malloc(variable, size, type) _ctool_assert_d_impl(_ctool_assert_malloc(variable), _ctool_assert_malloc_cond(variable, size, type))
#define assertdc_malloc(variable, size, type, message, ...) _ctool_assert_d_impl(message, _ctool_assert_malloc_cond(variable, size, type), ##__VA_ARGS__)

/**
 * Special assertion that always fails and
 * prints the optional message
 */
#define assertd_fail() _ctool_assert_d_impl("assertion failed", false)
#define assertrd_fail(message, ...) _ctool_assert_d_impl(message, false, ##__VA_ARGS__)

#endif /* CTOOL_ASSERT_DEBUG_H */