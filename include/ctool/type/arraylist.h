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
#include "ctool/assert/runtime.h" /* assertions */
#include "ctool/type/_internal.h" /* internal definitions */
#include "ctool/type/list.h" /* lists */
#include "ctool/iteration.h" /* index_t */
#include "ctool/macro.h" /* macro utils */

    /* defines */
/**
 * Default size for preallocated arraylists
 */
#define ARRAYLIST_DEFAULT_SIZE 2

/**
 * Generates a generic name for
 * an arraylist of specified type
 * 
 * @param[in] type Type of the arraylist
 */
#define arraylist(type)              _ctool_generic_type(arraylist, type)
#define arraylist_add(type)          _ctool_generic_function(arraylist, type, add)
#define arraylist_push               arraylist_add
#define arraylist_remove(type)       _ctool_generic_function(arraylist, type, remove)
#define arraylist_trim(type)         _ctool_generic_function(arraylist, type, trim)
#define arraylist_init(type)         _ctool_generic_function(arraylist, type, init)
#define arraylist_free(type)         _ctool_generic_function(arraylist, type, free)
#define arraylist_pop(type)          _ctool_generic_function(arraylist, type, pop)
#define arraylist_revert(type)       _ctool_generic_function(arraylist, type, revert)
#define arraylist_to_list(type)      _ctool_generic_function(arraylist, type, to_list)
#define arraylist_init_with(type)    _ctool_generic_function(arraylist, type, init_with)
#define arraylist_init_empty(type)   _ctool_generic_function(arraylist, type, init_empty)
#define arraylist_init_default(type) _ctool_generic_function(arraylist, type, init_default)
#define arraylist_move_append(type)  _ctool_generic_function(arraylist, type, move_append)

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

/**
 * Returns the string representation of an arraylist
 * without its contents
 * 
 * @note use with arraylist_to_string_format
 * 
 * @param[in] type Type of the arraylist
 * @param[in] list The arraylist
 */
#define arraylist_to_string(type, list) "arraylist<" macro_stringify(arraylist(type)) "> " #list " [%zu bytes used out of %zu]"
#define arraylist_to_string_format(list) list.size, list._allocated_size

/**
 * Declares an arraylist of specified type
 * 
 * @note The declaration should be placed in a header file
 * 
 * @param[in] type Type of the arraylist
**/
#define arraylist_declare(type)                   \
                                                  \
list_declare(type);                               \
                                                  \
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
 * @param[in] list The arraylist                                    \
 */                                                                 \
static inline void arraylist_free(type)(arraylist(type)* list) {    \
    free(list->data);                                               \
    list->data = NULL;                                              \
    list->_allocated_size = 0;                                      \
    list->size = 0;                                                 \
}                                                                   \
                                                                    \
/**                                                                 \
 * Removes the last element of an arraylist                         \
 *                                                                  \
 * @param[in] list The arraylist                                    \
 */                                                                 \
static inline status_t arraylist_pop(type)(arraylist(type)* list) { \
    return arraylist_remove(type)(list, list->size - 1);            \
}                                                                   \
                                                                    \
/**                                                                 \
 * Reverts the arraylist elements                                   \
 *                                                                  \
 * @param[in] list The arraylist                                    \
 */                                                                 \
void arraylist_revert(type)(arraylist(type)* list);                 \
                                                                    \
/**                                                                 \
 * Transform the arraylist to a list,                               \
 * trimming it if required                                          \
 *                                                                  \
 * After transformation, using the source arraylist                 \
 * is undefined behaviour, because list is assigned                 \
 * with the same data pointer                                       \
 *                                                                  \
 * @param[in] src  The arraylist                                    \
 * @param[in] dest The list to write into                           \
 *                                                                  \
 * @return ST_FAIL if the arraylist can't be trimmed,               \
 *          otherwise ST_OK                                         \
 */                                                                 \
status_t arraylist_to_list(type)(arraylist(type)* src, list(type)* dest); \
                                                                    \
/**                                                                 \
 * Initializes an arraylist with one element                        \
 *                                                                  \
 * @param[in] list The arraylist                                    \
 * @param[in] element The element                                   \
 *                                                                  \
 * @return ST_FAIL if the arraylist can't be initialized,           \
 *          otherwise ST_OK                                         \
 */                                                                 \
static inline status_t arraylist_init_with(type)(arraylist(type)* list, type element) { \
    assertr_status(arraylist_init(type)(list, 0), ST_FAIL);                             \
    assertr_status(arraylist_add(type)(list, element), ST_FAIL);                        \
    return ST_OK;                                                                       \
}                                                                                       \
                                                                                        \
/**                                                                                     \
 * Initializes an empty arraylist                                                       \
 *                                                                                      \
 * Used for initializing arraylists that are likely to remain empty                     \
 * in order to conserve allocated memory                                                \
 *                                                                                      \
 * @param[in] list The arraylist                                                        \
 *                                                                                      \
 * @return ST_FAIL if the arraylist cannot be initialized,                              \
 *          otherwise ST_OK                                                             \
 */                                                                                     \
static inline status_t arraylist_init_empty(type)(arraylist(type)* list) {              \
    assertr_status(arraylist_init(type)(list, 0), ST_FAIL);                             \
    return ST_OK;                                                                       \
}                                                                                       \
                                                                                        \
/**                                                                                     \
 * Initializes an arraylist with the default non-zero size                              \
 *                                                                                      \
 * Commonly used to pre-allocate arraylists that                                        \
 * will certainly be filled afterwards but with                                         \
 * an indefenite number of elements                                                     \
 *                                                                                      \
 * @param[in] list The arraylist                                                        \
 *                                                                                      \
 * @return ST_FAIL if the arraylist cannot be initialized,                              \
 *          otherwise ST_OK                                                             \
 */                                                                                     \
static inline status_t arraylist_init_default(type)(arraylist(type)* list) {            \
    assertr_status(arraylist_init(type)(list, ARRAYLIST_DEFAULT_SIZE), ST_FAIL);        \
    return ST_OK;                                                                       \
}                                                                                       \
                                                                                        \
/**                                                                                     \
 * Assigns the arraylist to a supplied variable                                         \
 * while appending a new element to it                                                  \
 *                                                                                      \
 * Might be useful in some complex algorithms,                                          \
 * but generally is unused                                                              \
 *                                                                                      \
 * @param[in] list The arraylist                                                        \
 * @param[in] element The element                                                       \
 * @param[in] variable The variable to be assigned                                      \
 *                                                                                      \
 * @return ST_FAIL if the element cannot be added,                                      \
 *          otherwise ST_OK                                                             \
 */                                                                                     \
static inline status_t arraylist_move_append(type)(arraylist(type)* list, type element, arraylist(type)* variable) { \
    *variable = *list;                                                                  \
    assertr_status(arraylist_add(type)(variable, element), ST_FAIL);                    \
    return ST_OK;                                                                       \
}







/**
 * Arraylist resizing methods definition
 * 
 * @param[in] size The size variable
 * 
 * Exact resizing increases arraylist size
 * each time an element is added, 
 * saving memory for small arraylists
 * 
 * Double resizing multiplies arraylist size
 * by two each time an element is added,
 * reducing allocation overhead for big arraylists
 */
#define ARRAYLIST_RESIZE_EXACT  exact
#define ARRAYLIST_RESIZE_DOUBLE double
#define _ARRAYLIST_INITIAL_SIZE_exact  1
#define _ARRAYLIST_INITIAL_SIZE_double 2
#define _arraylist_resize_op_exact(size)  size + 1
#define _arraylist_resize_op_double(size) size * 2

/**
 * Defines an arraylist implementation of specified type
 * 
 * @note The definition should be placed in a source file
 * 
 * @param[in] type Type of the arraylist
 * @param[in] resize_method Arraylist resizing method ("ARRAYLIST_RESIZE_EXACT" or "ARRAYLIST_RESIZE_DOUBLE")
**/
#define arraylist_define(type) arraylist_define_custom(type, ARRAYLIST_RESIZE_DOUBLE)
#define arraylist_define_custom(type, resize_method) \
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
        /* new size */                            \
        size_t old_size = list->_allocated_size;  \
                                                  \
        /* check for empty list */                \
        if (list->_allocated_size == 0 || list->data == NULL) { \
            /* first allocation */                \
            list->_allocated_size = macro_concatenate(_ARRAYLIST_INITIAL_SIZE_, resize_method); \
                                                  \
            /* allocate memory */                 \
            pointer = (type*) malloc(list->_allocated_size * sizeof(type)); \
        } else {                                  \
            /* increase allocated length */       \
            list->_allocated_size = macro_concatenate(_arraylist_resize_op_, resize_method)(list->_allocated_size); \
                                                  \
            /* reallocate memory */               \
            pointer = (type*) realloc(list->data, list->_allocated_size * sizeof(type)); \
        }                                         \
                                                  \
        /* null check */                          \
        if (pointer == NULL) {                    \
            /* log an error */                    \
            loge("memory reallocation to size %zu failed while adding new element to a " macro_stringify(arraylist(type)) \
                " with size %zu and allocated size %zu", list->_allocated_size, list->size, old_size); \
                                                  \
            /* revert allocated size */           \
            list->_allocated_size = old_size;     \
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
 * Reallocates the internal array of an arraylist      \
 * to be the same size as the number of elements       \
 *                                                     \
 * @param[in] list The arraylist                       \
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
    if (size == 0) {                                                \
        list->data = NULL;                                          \
    } else {                                                        \
        assertr_malloc(list->data, sizeof(type) * size, type*)      \
    }                                                               \
                                                                    \
    /* success */                                                   \
    return ST_OK;                                                   \
}                                                                   \
                                                                    \
/**                                                                 \
 * Reverts the arraylist elements                                   \
 *                                                                  \
 * @param[in] list The arraylist                                    \
 */                                                                 \
void arraylist_revert(type)(arraylist(type)* list) {                \
    iterate_array(i, list->size / 2) {                              \
        index_t inverted = list->size - i - 1;                      \
        type tmp = list->data[i];                                   \
        list->data[i] = list->data[inverted];                       \
        list->data[inverted] = tmp;                                 \
    }                                                               \
}                                                                   \
                                                                    \
/**                                                                 \
 * Transform the arraylist to a list,                               \
 * trimming it if required                                          \
 *                                                                  \
 * After transformation, using the source arraylist                 \
 * is undefined behaviour, because list is assigned                 \
 * with the same data pointer                                       \
 *                                                                  \
 * @param[in] src  The arraylist                                    \
 * @param[in] dest The list to write into                           \
 *                                                                  \
 * @return ST_FAIL if the arraylist can't be trimmed,               \
 *          otherwise ST_OK                                         \
 */                                                                 \
status_t arraylist_to_list(type)(arraylist(type)* src, list(type)* dest) {  \
    if (src->size != src->_allocated_size) {                                \
        assertr_status(arraylist_trim(type)(src), ST_FAIL);                 \
    }                                                                       \
                                                                            \
    dest->data = src->data;                                                 \
    dest->size = src->size;                                                 \
    return ST_OK;                                                           \
}

#endif /* CTOOL_TYPE_ARRAYLIST_H */