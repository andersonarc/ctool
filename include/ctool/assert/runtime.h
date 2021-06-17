/**
 * @file runtime.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-14
 *
 *  Frontend for runtime assertions.
 * 
 *  Runtime assertions are always executed. 
 *  They return specified status from caller function on failure
 *  and print an error message.
 * 
 *      Macro postfixes:
 *  assertr_'c' - with custom message
 */
    /* header guard */
#ifndef CTOOL_ASSERT_RUNTIME_H
#define CTOOL_ASSERT_RUNTIME_H

    /* includes */
#include "ctool/assert/_internal.h" /* implementation */
#include "ctool/status.h" /* return status */

    /* defines */
/**
 * Asserts that A is equal to B.
 * 
 * @param[in] a The first value
 * @param[in] b The second value
 */
#define assertr_equals(a, b, status) _ctool_assert_r_impl(_ctool_assert_equals(a, b), (a) == (b), status)
#define assertrc_equals(a, b, status, message, ...) _ctool_assert_r_impl(message, (a) == (b), status, ##__VA_ARGS__)

/**
 * Asserts that a status variable is equal to ST_OK.
 * 
 * @param[in] variable The status variable
 */
#define assertr_status(variable, status) assertr_equals(variable, ST_OK, status)
#define assertrc_status(variable, status, message, ...) assertrc_equals(variable, ST_OK, status, message, ##__VA_ARGS__)

/**
 * Asserts that a condition is true.
 * 
 * @param[in] condition The condition
 */
#define assertr_true(condition, status) _ctool_assert_r_impl(_ctool_assert_true(condition), (condition), status)
#define assertrc_true(condition, status, message, ...) _ctool_assert_r_impl(message, (condition), status, ##__VA_ARGS__)

/**
 * Asserts that a condition is false.
 * 
 * @param[in] condition The condition
 */
#define assertr_false(condition, status) _ctool_assert_r_impl(_ctool_assert_false(condition), !(condition), status)
#define assertrc_false(condition, status, message, ...) _ctool_assert_r_impl(message, !(condition), status, ##__VA_ARGS__)

/**
 * Asserts that a variable is not NULL.
 * 
 * @param[in] variable The variable
 */
#define assertr_notnull(variable, status) _ctool_assert_r_impl(_ctool_assert_notnull(variable), (variable) != NULL, status)
#define assertrc_notnull(variable, status, message, ...) _ctool_assert_r_impl(message, (variable) != NULL, status, ##__VA_ARGS__)

/**
 * Allocates memory of specified size
 * with malloc, asserts that it is not NULL,
 * then assigns it to a variable of specified type.
 * 
 * @param[out] variable The variable
 * @param[in] size      Size for allocation in bytes
 * @param[in] type      Type of the variable
 */
#define assertr_malloc(variable, size, type) _ctool_assert_r_impl(_ctool_assert_malloc(variable), _ctool_assert_malloc_cond(variable, size, type), ST_ALLOC_FAIL)
#define assertrc_malloc(variable, size, type, message, ...) _ctool_assert_r_impl(message, _ctool_assert_malloc_cond(variable, size, type), ST_ALLOC_FAIL, ##__VA_ARGS__)

#endif /* CTOOL_ASSERT_RUNTIME_H */