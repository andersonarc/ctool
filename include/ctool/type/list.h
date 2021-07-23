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
#include "ctool/status.h" /* status_t */
#include "ctool/assert/runtime.h" /* runtime assertions */
#include "ctool/type/_internal.h" /* internal definitions */

    /* defines */
/**
 * Generates a generic name for
 * a list of specified type
 * 
 * @param[in] type Type of the list
 */
#define list(type) _ctool_generic_type(list, type)
#define list_init(type) _ctool_generic_function(list, type, init)
#define list_free(type) _ctool_generic_function(list, type, free)

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
                            \
/**                                               \
 * Initializes a list with allocated memory       \
 * for a specified number of elements             \
 *                                                \
 * @param[in] list The list                       \
 * @param[in] size The number of elements         \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t list_init(type)(list(type)* list, size_t size); \
                                                         \
/**                                                      \
 * Frees the memory allocated for a list                 \
 *                                                       \
 * @param[in] list The list                              \                                       \
 */                                                      \
static inline void list_free(type)(list(type)* list) {   \
    free(list->data);                                    \
}  

/**
 * Defines a list implementation of specified type
 * 
 * @note The definition should be placed in a source file
 * 
 * @param[in] type Type of the list
**/
#define list_define(type)                         \
                                                  \
/**                                               \
 * Initializes a list with allocated memory       \
 * for a specified number of elements             \
 *                                                \
 * @param[in] list The list                       \
 * @param[in] size The number of elements         \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t list_init(type)(list(type)* list, size_t size) {           \
    list->size = size;                                              \
    assertr_malloc(list->data, sizeof(type) * size, type*)          \
                                                                    \
    /* success */                                                   \
    return ST_OK;                                                   \
}

#endif /* CTOOL_TYPE_LIST_H */