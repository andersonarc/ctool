/**
 * @file csafe_safecall.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief safe function calls
 * @version 0.1
 * @date 2020-09-30
 */

    /* header guard */
#ifndef CSAFE_SAFECALL_H
#define CSAFE_SAFECALL_H

    /* includes */
#include "csafe_assert.h" /* assert */

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
 * @brief perform a safe call to function
 */
#define sc_call(function_call) \
    assert_not_null_function(function_call) \
    assert_errno()
    

#endif /* CSAFE_SAFECALL_H */