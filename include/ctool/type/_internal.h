/**
 * @file _internal.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-03
 * 
 *  Generic type system internal definitions
 */
    /* header guard */
#ifndef CTOOL_TYPE_INTERNAL_H
#define CTOOL_TYPE_INTERNAL_H

    /* includes */
#include "ctool/macro.h" /* macro utilities */

    /* defines */
/**
 * Merges a base name (e.g. array, list),
 * a generic type parameter (e.h. char, int)
 * and a function name
 * 
 * @param[in] base     The base type
 * @param[in] type     The generic type
 * @param[in] function The function name
 */
#define _ctool_generic_function(base, type, function) macro_concatenate(macro_concatenate(macro_concatenate(macro_concatenate(type, _), base), _), function)

/**
 * Merges a base name (e.g. array, list) and
 * a generic type parameter (e.h. char, int)
 * for a type definition
 * 
 * @param[in] base The base type
 * @param[in] type The generic type
 */
#define _ctool_generic_type(base, type) macro_concatenate(macro_concatenate(macro_concatenate(type, _), base), _t)

#endif /* CTOOL_TYPE_INTERNAL_H */