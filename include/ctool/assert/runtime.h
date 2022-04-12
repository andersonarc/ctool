/**
 * @file runtime.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-14
 *
 *  Frontend for runtime assertions
 * 
 *  Runtime assertions are always executed. 
 *  They return specified status from caller function on failure
 *  and print an error message.
 * 
 *      Macro postfixes:
 *  assertr 'c' - with custom message
 */
    /* header guard */
#ifndef CTOOL_ASSERT_RUNTIME_H
#define CTOOL_ASSERT_RUNTIME_H

    /* includes */
#include <errno.h> /* errno */
#include <stdbool.h> /* boolean */

#include "ctool/assert/_internal.h" /* implementation */
#include "ctool/status.h" /* return status */

    /* defines */
/**
 * Asserts that A is equal to B
 * 
 * @param[in] a      The first value
 * @param[in] b      The second value
 * @param[in] status Status to return on error
 */
#define assertr_equals(a, b, status) _ctool_assert_r_impl(_ctool_assert_equals(a, b), (a) == (b), status)
#define assertrc_equals(a, b, status, message, ...) _ctool_assert_r_impl(message, (a) == (b), status, ##__VA_ARGS__)

/**
 * Asserts that errno is equal to 0
 * 
 * @param[in] status Status to return on error
 */
#define assertr_errno(status) assertr_equals(errno, 0, status)
#define assertrc_errno(status, message, ...) assertrc_equals(errno, 0, status, message, ##__VA_ARGS__)

/**
 * Asserts that an expression is equal to 0
 * 
 * @param[in] expression The expression
 * @param[in] status     Status to return on error
 */
#define assertr_zero(expression, status) assertr_equals(expression, 0, status)
#define assertrc_zero(expression, status, message, ...) assertrc_equals(expression, 0, status, message, ##__VA_ARGS__)

/**
 * Asserts that A is not equal to B
 * 
 * @param[in] a      The first value
 * @param[in] b      The second value
 * @param[in] status Status to return on error
 */
#define assertr_not_equals(a, b, status) _ctool_assert_r_impl(_ctool_assert_not_equals(a, b), (a) != (b), status)
#define assertrc_not_equals(a, b, status, message, ...) _ctool_assert_r_impl(message, (a) != (b), status, ##__VA_ARGS__)

/**
 * Asserts that an expression returns ST_OK
 * 
 * @param[in] expression The expression
 * @param[in] status     Status to return on error
 */
#define assertr_status(expression, status) assertr_equals(expression, ST_OK, status)
#define assertrc_status(expression, status, message, ...) assertrc_equals(expression, ST_OK, status, message, ##__VA_ARGS__)

//todo - make the error status default to ST_FAIL
/**
 * Asserts that an expression returns not ST_OK
 * 
 * @param[in] expression The expression
 * @param[in] status     Status to return on error
 */
#define assertr_bad_status(expression, status) assertr_not_equals(expression, ST_OK, status)
#define assertrc_bad_status(expression, status, message, ...) assertrc_not_equals(expression, ST_OK, status, message, ##__VA_ARGS__)


/**
 * Asserts that a condition is true
 * 
 * @param[in] condition The condition
 * @param[in] status    Status to return on error
 */
#define assertr_true(condition, status) _ctool_assert_r_impl(_ctool_assert_true(condition), (condition), status)
#define assertrc_true(condition, status, message, ...) _ctool_assert_r_impl(message, (condition), status, ##__VA_ARGS__)

/**
 * Asserts that a condition is false
 * 
 * @param[in] condition The condition
 * @param[in] status    Status to return on error
 */
#define assertr_false(condition, status) _ctool_assert_r_impl(_ctool_assert_false(condition), !(condition), status)
#define assertrc_false(condition, status, message, ...) _ctool_assert_r_impl(message, !(condition), status, ##__VA_ARGS__)

/**
 * Asserts that a variable is not NULL
 * 
 * @param[in] variable The variable
 * @param[in] status   Status to return on error
 */
#define assertr_not_null(variable, status) _ctool_assert_r_impl(_ctool_assert_not_null(variable), (variable) != NULL, status)
#define assertrc_not_null(variable, status, message, ...) _ctool_assert_r_impl(message, (variable) != NULL, status, ##__VA_ARGS__)

/**
 * Allocates memory of specified size
 * with malloc, asserts that it is not NULL,
 * then assigns it to a variable of specified type
 * 
 * @param[out] variable The variable
 * @param[in]  size     Size for allocation in bytes
 * @param[in]  type     Type of the variable
 * @param[in]  status   Status to return on error
 */
#define assertr_malloc(variable, size, type) _ctool_assert_r_impl(_ctool_assert_malloc(variable), _ctool_assert_malloc_cond(variable, size, type), ST_ALLOC_FAIL)
#define assertrc_malloc(variable, size, type, message, ...) _ctool_assert_r_impl(message, _ctool_assert_malloc_cond(variable, size, type), ST_ALLOC_FAIL, ##__VA_ARGS__)

/**
 * Special assertion that always fails,
 * prints the optional message and
 * returns the specified status
 * 
 * @param[in] status   Status to return on error
 */
#define assertr_fail(status) _ctool_assert_r_impl("assertion failed", false, status)
#define assertrc_fail(status, message, ...) _ctool_assert_r_impl(message, false, status, ##__VA_ARGS__)

#endif /* CTOOL_ASSERT_RUNTIME_H */