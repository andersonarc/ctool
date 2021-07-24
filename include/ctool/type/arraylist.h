/**
 * @file arraylist.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.2
 * @date 2021-05-17
 * 
 *  Dynamically resizable generic list structure
 * 
 *  A simple arraylist implementation for C language.
 *  Each reallocation doubles the allocated memory size.
 */
    /* header guard */
#ifndef CTOOL_TYPE_ARRAYLIST_H
#define CTOOL_TYPE_ARRAYLIST_H

    /* includes */
#include <stdlib.h> /* memory allocation */
#include "ctool/assert/runtime.h" /* runtime assertions */
#include "ctool/type/_internal.h" /* internal definitions */
#include "ctool/iteration.h" /* index_t */
#include "ctool/macro.h" /* macro utils */

    /* defines */
/**
 * Generates a generic name for
 * an arraylist of specified type
 * 
 * @param[in] type Type of the arraylist
 */
#define arraylist(type) _ctool_generic_type(arraylist, type)
#define arraylist_add(type) _ctool_generic_function(arraylist, type, add)
#define arraylist_remove(type) _ctool_generic_function(arraylist, type, remove)
#define arraylist_trim(type) _ctool_generic_function(arraylist, type, trim)
#define arraylist_init(type) _ctool_generic_function(arraylist, type, init)
#define arraylist_free(type) _ctool_generic_function(arraylist, type, free)

/**
 * Returns the last element of an arraylist
 * 
 * @param[in] list The arraylist
 */
#define arraylist_last(list) list.data[list.size - 1]

/**
 * Checks if the arraylist is empty
 * 
 * @param[in] list The arraylist
 */
#define arraylist_is_empty(list) (list.size == 0)

//todo check for existing arraylist

/**
 * Declares an arraylist of specified type
 * 
 * @note The declaration should be placed in a header file
 * 
 * @param[in] type Type of the arraylist
**/
#define arraylist_declare(type)                   \
typedef struct arraylist(type) {                  \
    size_t _allocated_size;                       \
    size_t size;                                  \
    type* data;                                   \
} arraylist(type);                                \
                                                  \
/**                                               \
 * Appends a new element into an arraylist        \
 *                                                \
 * @param[in] list    The arraylist               \
 * @param[in] element The element                 \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraylist_add(type)(arraylist(type)* list, type element);     \
                                                  \
/**                                               \
 * Removes an element at a specified index        \
 * from an arraylist, shrinking it                \
 * if new size is less or equal to                \
 * half of the allocated size                     \
 *                                                \
 * @param[in] list  The arraylist                 \
 * @param[in] index The index                     \
 *                                                \
 * @return ST_BAD_ARG if index is out of bounds,  \
 *         ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraylist_remove(type)(arraylist(type)* list, index_t index); \
                                                  \
/**                                               \
 * Reallocates the internal array of an arraylist \
 * to be the same size as the number of elements  \
 *                                                \
 * @param[in] list The arraylist                  \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraylist_trim(type)(arraylist(type)* list); \
                                                  \
/**                                               \
 * Initializes an arraylist with preallocated     \
 * memory for a specified number of elements,     \
 * which can be changed later via                 \
 * add or remove methods                          \
 *                                                \
 * @param[in] list The arraylist                  \
 * @param[in] size The number of elements         \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraylist_init(type)(arraylist(type)* list, size_t size);  \
                                                                    \
/**                                                                 \
 * Frees the memory allocated for                                   \
 * an arraylist                                                     \
 *                                                                  \
 * @param[in] list The arraylist                                    \                                       \
 */                                                                 \
static inline void arraylist_free(type)(arraylist(type)* list) {    \
    free(list->data);                                               \
    list->data = NULL;                                              \
    list->_allocated_size = 0;                                      \
    list->size = 0;                                                 \
}                                                                   







/**
 * Defines an arraylist implementation of specified type
 * 
 * @note The definition should be placed in a source file
 * 
 * @param[in] type Type of the arraylist
**/
#define arraylist_define(type)                    \
                                                  \
/**                                               \
 * Appends a new element into an arraylist        \
 *                                                \
 * @param[in] list    The arraylist               \
 * @param[in] element The element                 \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraylist_add(type)(arraylist(type)* list, type element) { \
    /* check for free space */                    \
    if (list->size == list->_allocated_size) {    \
        /* new pointer */                         \
        type* pointer;                            \
                                                  \
        /* check for empty list */                \
        if (list->_allocated_size == 0 || list->data == NULL) { \
            /* first allocation */                \
            list->_allocated_size = 2;            \
                                                  \
            /* allocate memory */                 \
            pointer = (type*) malloc(2 * sizeof(type)); \
        } else {                                  \
            /* increase allocated length */       \
            list->_allocated_size *= 2;           \
                                                  \
            /* reallocate memory */               \
            pointer = (type*) realloc(list->data, list->_allocated_size * sizeof(type)); \
        }                                         \
                                                  \
        /* null check */                          \
        if (pointer == NULL) {                    \
            /* revert allocated size */           \
            list->_allocated_size /= 2;           \
                                                  \
            if (list->_allocated_size == 1) {     \
                /* first allocation failed */     \
                list->_allocated_size = 0;        \
            }                                     \
                                                  \
            /* log an error */                    \
            loge("memory reallocation failed while adding new element to a " macro_stringify(arraylist(type)) \
                " with size %zu and allocated size %zu", list->size, list->_allocated_size); \
                                                  \
            /* fail */                            \
            return ST_ALLOC_FAIL;                 \
        }                                         \
                                                  \
        /* assign new pointer */                  \
        list->data = pointer;                     \
    }                                             \
                                                  \
    /* add new element */                         \
    list->data[list->size] = element;             \
                                                  \
    /* increment length */                        \
    list->size++;                                 \
                                                  \
    /* success */                                 \
    return ST_OK;                                 \
}                                                 \
                                                  \
/**                                               \
 * Removes an element at specified index          \
 * from an arraylist, shrinking it                \
 * if new size is less or equal to                \
 * half of the allocated size                     \
 *                                                \
 * @param[in] list  The arraylist                 \
 * @param[in] index The index                     \
 *                                                \
 * @return ST_BAD_ARG if index is out of bounds,  \
 *         ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraylist_remove(type)(arraylist(type)* list, index_t index) {   \
    /* check for index being out of bounds (and arraylist being empty) */ \
    assertr_false(index >= list->size, ST_BAD_ARG);    \
                                                       \
    /* decrement arraylist size */                     \
    list->size--;                                      \
                                                       \
    if (index < list->size) {                          \
        /* shift arraylist elements in place of the removed one */      \
        iterate_range_single(i, index, list->size) {   \
            list->data[i] = list->data[i + 1];         \
        }                                              \
    }                                                  \
    /* if the element is the last, do nothing */       \
                                                       \
    if (list->size <= list->_allocated_size / 2) {     \
        /* trim the arraylist */                       \
        assertr_status(arraylist_trim(type)(list), ST_ALLOC_FAIL); \
    }                                                  \
                                                       \
    /* success */                                      \
    return ST_OK;                                      \
}                                                      \
                                                       \
/**                                                    \
 * Reallocates the internal array of an arraylist     \
 * to be the same size as the number of elements       \
 *                                                     \
 * @param[in] list The arraylist                     \
 *                                                     \
 * @return ST_ALLOC_FAIL if an allocation fails,       \
 *          otherwise ST_OK                            \
 */                                                    \
status_t arraylist_trim(type)(arraylist(type)* list) { \
    /* if the list is unallocated, return */             \
    if (list->_allocated_size == 0) {                    \
        logw("attempted to trim an unallocated " macro_stringify(arraylist(type)) \
                " with size %zu and allocated size %zu", list->size, list->_allocated_size); \
        return ST_OK;                                     \
    }                                                     \
                                                          \
    /* if the list is empty, free memory */               \
    if (list->size == 0) {                                \
        free(list->data);                                 \
        list->data = NULL;                                \
    } else {                                              \
        /* else, reallocate memory */                     \
        type* pointer = (type*) realloc(list->data, list->size * sizeof(type)); \
                                                          \
        /* null check */                                  \
        if (pointer == NULL) {                            \
            /* log an error */                            \
            loge("memory reallocation failed while trimming a " macro_stringify(arraylist(type)) \
                    " with size %zu and allocated size %zu", list->size, list->_allocated_size); \
                                                          \
            /* fail */                                    \
            return ST_ALLOC_FAIL;                         \
        }                                                 \
                                                          \
        /* assign new pointer */                          \
        list->data = pointer;                             \
    }                                                     \
                                                          \
    /* change allocated size */                           \
    list->_allocated_size = list->size;                   \
                                                       \
    /* success */                                      \
    return ST_OK;                                      \
}                                                      \
                                                       \
/**                                                    \
 * Initializes an arraylist with preallocated          \
 * memory for a specified number of elements,          \
 * which can be changed later via                      \
 * add or remove methods                               \
 *                                                     \
 * @param[in] list The arraylist                       \
 * @param[in] size The number of elements              \
 *                                                     \
 * @return ST_ALLOC_FAIL if an allocation fails,       \
 *          otherwise ST_OK                            \
 */                                                    \
status_t arraylist_init(type)(arraylist(type)* list, size_t size) { \
    list->size = 0;                                                 \
    list->_allocated_size = size;                                   \
    assertr_malloc(list->data, sizeof(type) * size, type*)          \
                                                                    \
    /* success */                                                   \
    return ST_OK;                                                   \
}                                                                   \



/**
 * Creates an empty instance of an arraylist
 * 
 * @return Empty arraylist structure
 */
#define arraylist_empty {0, 0, NULL}

#endif /* CTOOL_TYPE_ARRAYLIST_H */