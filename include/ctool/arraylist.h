/**
 * @file arraylist.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.2
 * @date 2021-05-17
 * 
 *  Dynamically resizable list structure.
 * 
 *  A simple arraylist implementation for C language.
 *  Each reallocation doubles the allocated memory size.
 *  Currently only add() function is implemented.
 * 
 *  @todo Implement a trim() function for the arraylist
 *  @todo Implement a remove() function for the arraylist
 */
    /* header guard */
#ifndef CTOOL_ARRAYLIST_H
#define CTOOL_ARRAYLIST_H

    /* includes */
#include <stdlib.h> /* memory allocation */
#include "ctool/assert/runtime.h" /* runtime assertions */

    /* defines */
/**
 * Generates a generic name for
 * arraylist of specified type.
 * 
 * @param[in] type Type of the arraylist
 */
#define arraylist(type) arraylist_##type_t
#define arraylist_add(type) arraylist_##type##_add

/**
 * Declares an arraylist of specified type.
 * 
 * @note The declaration should be placed in a header file
 * 
 * @param[in] type Type of the arraylist
**/
#define arraylist_declare(type)  \
typedef struct arraylist(type) { \
    size_t _allocated_size;      \
    size_t size;                 \
    type* data;                  \
} arraylist(type);               \
                                 \
status_t arraylist_add(type)(arraylist(type)* list, type element);

/**
 * Defines an arraylist implementation of specified type.
 * 
 * @note The definition should be placed in a source file
 * 
 * @param[in] type Type of the arraylist
**/
#define arraylist_define(type)                    \
/**                                               \
 * Appends a new element into an arraylist        \
 *                                                \
 * @param[in] list    The arraylist               \
 * @param[in] element The element                 \
 *                                                \
 * @return ST_ALLOC_FAIL if the allocation fails, \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraylist_add(type)(arraylist(type)* list, type element) { \
    /* check for free space */                       \
    if (list->size == list->_allocated_size) {       \
        /* check for empty array */                  \
        if (list->_allocated_size == 0) {            \
            /* first allocation */                   \
            list->_allocated_size = 2;               \
        } else {                                     \
            /* increase allocated length */          \
            list->_allocated_size *= 2;              \
        }                                            \
                                                     \
        /* reallocate memory */                      \
        type* pointer = (type*) realloc(list->data, list->_allocated_size * sizeof(type)); \
                                                   \
        /* null check */                           \
        if (pointer == NULL) {                     \
            /* decrease allocated length */        \
            list->_allocated_size /= 2;            \
                                                   \
            /* fail */                             \
            return ST_ALLOC_FAIL;                  \
        }                                          \
                                                   \
        /* assign new pointer */                   \
        list->data = pointer;                      \
    }                                              \
                                                   \
    /* add new element */                          \
    list->data[list->size] = element;              \
                                                   \
    /* increment length */                         \
    list->size++;                                  \
                                                   \
    /* success */                                  \
    return ST_OK;                                  \
}              

/**
 * Creates an empty instance of an arraylist.
 * 
 * @return Empty arraylist structure
 */
#define arraylist_new_empty() {0, 0, NULL}

/**
 * Creates an instance of an arraylist and
 * allocates memory for specified count of elements 
 * of specified type.
 * 
 * @param[in] list The arraylist
 * @param[in] size Initial elements count
 * @param[in] type Type of the arraylist
 */
#define arraylist_allocate(list, size, type)            \
list.size = size;                                       \
list._allocated_size = size;                            \
assertr_malloc(list.data, sizeof(type) * size, type)

#endif /* CTOOL_ARRAYLIST_H */