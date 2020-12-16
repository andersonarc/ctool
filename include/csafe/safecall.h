/**
 * @file safecall.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief safe function calls with null/errno assertion
 * @version 0.2
 * @date 2020-09-30
 */

    /* header guard */
#ifndef CSAFE_SAFECALL_H
#define CSAFE_SAFECALL_H

    /* includes */
#include "csafe/assert.h" /* assertions */

    /* defines */
/**
 * @brief perform a safe call to function and set variable to the returned value
 * 
 * @param expression is an expression in format 'foo = bar(args)'
 */
#define sc(expression) \
    assert_not_null_function_set(expression) \
    assert_errno()

/**
 * @brief perform a safe call to a function
 * 
 * @param function_call function call expression
 */
#define sc_call(function_call) \
    assert_not_null_function(function_call) \
    assert_errno()

#endif /* CSAFE_SAFECALL_H */