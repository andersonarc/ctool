/**
 * @file optional.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-19
 * 
 *  Generic optional structure
 */
    /* header guard */
#ifndef CTOOL_TYPE_OPTIONAL_H
#define CTOOL_TYPE_OPTIONAL_H

    /* includes */
#include <stdbool.h> /* boolean */
#include "ctool/type/_internal.h" /* internal definitions */

    /* defines */
/**
 * Generates a generic name for
 * an optional structure of specified type
 * 
 * @param[in] type Type of the optional structure
 */
#define optional(type) _ctool_generic_type(optional, type)

/**
 * Declares an optional structure of specified type
 * 
 * @note The declaration should be placed in a header file
 * 
 * @param[in] type Type of the optional structure
**/
#define optional_declare(type)  \
typedef struct optional(type) { \
    bool has_value;             \
    type value;                 \
} optional(type);               \

#endif /* CTOOL_TYPE_OPTIONAL_H */