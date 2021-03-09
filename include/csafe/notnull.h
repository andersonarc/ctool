/**
 * @file notnull.h
 * @author andersonarc@github
 * @brief not null variables and assertions
 * @version 0.2
 * @date 2020-09-30
 */
    /* header guard */
#ifndef CSAFE_NOTNULL_H
#define CSAFE_NOTNULL_H

    /* includes */
#include "csafe/assertd.h" /* assertions */

    /* defines */
/**
 * @brief assert that X arguments are not null
 */
#define _not_null_1(argument)         assertd_not_null(argument)
#define _not_null_2(a, b)             _not_null_1(a); _not_null_1(b)
#define _not_null_3(a, b, c)          _not_null_1(a); _not_null_2(b, c)
#define _not_null_4(a, b, c, d)       _not_null_1(a); _not_null_3(b, c, d)
#define _not_null_5(a, b, c, d, e)    _not_null_1(a); _not_null_4(b, c, d, e)
#define _not_null_6(a, b, c, d, e, f) _not_null_1(a); _not_null_5(b, c, d, e, f)

/**
 * @brief notnull macro vararg trick
 */
#define _not_null_get_macro(_, __, ___, ____, _____, _______, macro, ...) macro 

/**
 * @brief assert that variable arguments are not null
 * 
 * @param function caller function name
 */
#define not_null(function, ...) _not_null_get_macro(__VA_ARGS__, _not_null_6, _not_null_5, _not_null_4, _not_null_3, _not_null_2, _not_null_1)(function, __VA_ARGS__)

/**
 * @brief indicates that argument is not null
 */
#define notnull

/**
 * @brief indicates that argument can be null
 */
#define nullable

#endif /* CSAFE_NOTNULL_H */