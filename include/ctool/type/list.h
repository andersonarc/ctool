/**
 * @file list.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.2
 * @date 2021-06-19
 * 
 *  Generic list structure with a stored size field
 */
    /* header guard */
#ifndef CTOOL_TYPE_LIST_H
#define CTOOL_TYPE_LIST_H

    /* includes */
#include <stddef.h> /* size_t */
#include "ctool/type/_internal.h" /* internal definitions */

    /* defines */
/**
 * Generates a generic name for
 * a list of specified type
 * 
 * @param[in] type Type of the list
 */
#define list(type) _ctool_generic_type(list, type)

/**
 * Declares a list of specified type
 * 
 * @note The declaration should be placed in a header file
 * 
 * @param[in] type Type of the list
**/
#define list_declare(type)  \
typedef struct list(type) { \
    size_t size;            \
    type* data;             \
} list(type);               \

#endif /* CTOOL_TYPE_LIST_H */