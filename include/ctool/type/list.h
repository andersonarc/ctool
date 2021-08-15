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
#define list_resize(type) _ctool_generic_function(list, type, resize)

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
}                                                        \
                                                         \
/**                                                      \
 * Resizes a list to specified size                      \
 *                                                       \
 * @param[in] list The list                              \
 * @param[in] size New size of the list                  \
 */                                                      \
status_t list_resize(type)(list(type)* list, size_t size);

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
    if (size > 0) {                                                 \
        assertr_malloc(list->data, sizeof(type) * size, type*)      \
    } else {                                                        \
        list->data = NULL;                                          \
    }                                                               \
                                                                    \
    /* success */                                                   \
    return ST_OK;                                                   \
}                                                                   \
                                                                    \
/**                                                                 \
 * Resizes a list to specified size                                 \
 *                                                                  \
 * @param[in] list The list                                         \
 * @param[in] size New size of the list                             \
 */                                                                 \
status_t list_resize(type)(list(type)* list, size_t size) {         \
    /* if new size is 0, free memory */                             \
    if (size == 0 && list->data != NULL) {                          \
        free(list->data);                                           \
        list->data = NULL;                                          \
    } else {                                                        \
        /* else, reallocate memory */                               \
        type* pointer = (type*) realloc(list->data, size * sizeof(type)); \
                                                                    \
        /* null check */                                            \
        if (pointer == NULL) {                                      \
            /* log an error */                                      \
            loge("memory reallocation failed while resizing a " macro_stringify(list(type)) \
                   " with size %zu to size %zu", list->size, size); \
                                                                    \
            /* fail */                                              \
            return ST_ALLOC_FAIL;                                   \
        }                                                           \
                                                                    \
        /* assign new pointer */                                    \
        list->data = pointer;                                       \
    }                                                               \
                                                                    \
    /* assign new size */                                           \
    list->size = size;                                              \
                                                                    \
    /* success */                                                   \
    return ST_OK;                                                   \
}

#endif /* CTOOL_TYPE_LIST_H */