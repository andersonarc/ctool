/**
 * @file arraystack.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-05-17
 * 
 *  Dynamically resizable generic stack structure
 * 
 *  Actually, an arraystack with renamed functions.
 */
    /* header guard */
#ifndef CTOOL_TYPE_ARRAYSTACK_H
#define CTOOL_TYPE_ARRAYSTACK_H

    /* includes */
#include <stdlib.h> /* memory allocation */
#include "ctool/assert/runtime.h" /* runtime assertions */
#include "ctool/type/_internal.h" /* internal definitions */
#include "ctool/iteration.h" /* index_t */
#include "ctool/macro.h" /* macro utils */

    /* defines */
/**
 * Generates a generic name for
 * an arraystack of specified type
 * 
 * @param[in] type Type of the arraystack
 */
#define arraystack(type) _ctool_generic_type(arraystack, type)
#define arraystack_push(type) _ctool_generic_function(arraystack, type, push)
#define arraystack_pop(type) _ctool_generic_function(arraystack, type, pop)
#define arraystack_trim(type) _ctool_generic_function(arraystack, type, trim)
#define arraystack_init(type) _ctool_generic_function(arraystack, type, init)
#define arraystack_free(type) _ctool_generic_function(arraystack, type, free)

/**
 * Returns the top element of an arraystack
 * 
 * @param[in] stack The arraystack
 */
#define arraystack_top(stack) stack.data[stack.size - 1]

/**
 * Checks if the arraystack is empty
 * 
 * @param[in] stack The arraystack
 */
#define arraystack_is_empty(stack) (stack.size == 0)

//todo check for existing arraystack

/**
 * Declares an arraystack of specified type
 * 
 * @note The declaration should be placed in a header file
 * 
 * @param[in] type Type of the arraystack
**/
#define arraystack_declare(type)                  \
typedef struct arraystack(type) {                 \
    size_t _allocated_size;                       \
    size_t size;                                  \
    type* data;                                   \
} arraystack(type);                               \
                                                  \
/**                                               \
 * Pushes a new element into an arraystack        \
 *                                                \
 * @param[in] stack   The arraystack              \
 * @param[in] element The element                 \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraystack_push(type)(arraystack(type)* stack, type element); \
                                                  \
/**                                               \
 * Removes an element from top of                 \
 * the arraystack, shrinking it                   \
 * if new size is less or equal to                \
 * half of the allocated size                     \
 *                                                \
 * @param[in] stack  The arraystack               \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraystack_pop(type)(arraystack(type)* stack); \
                                                   \
/**                                                \
 * Reallocates the internal array of an arraystack \
 * to be the same size as the number of elements   \
 *                                                 \
 * @param[in] stack The arraystack                 \
 *                                                 \
 * @return ST_ALLOC_FAIL if an allocation fails,   \
 *          otherwise ST_OK                        \
 */                                                \
status_t arraystack_trim(type)(arraystack(type)* stack); \
                                                  \
/**                                               \
 * Initializes an arraystack with preallocated    \
 * memory for a specified number of elements,     \
 * which can be changed later via                 \
 * add or remove methods                          \
 *                                                \
 * @param[in] stack The arraystack                \
 * @param[in] size The number of elements         \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraystack_init(type)(arraystack(type)* stack, size_t size);  \
                                                                       \
/**                                                                    \
 * Frees the memory allocated for                                      \
 * an arraystack                                                       \
 *                                                                     \
 * @param[in] stack The arraystack                                     \                                       \
 */                                                                    \
static inline void arraystack_free(type)(arraystack(type)* stack) {    \
    free(stack->data);                                                 \
    stack->data = NULL;                                                \
    stack->_allocated_size = 0;                                        \
    stack->size = 0;                                                   \
}                                                                   







/**
 * Defines an arraystack implementation of specified type
 * 
 * @note The definition should be placed in a source file
 * 
 * @param[in] type Type of the arraystack
**/
#define arraystack_define(type)                   \
                                                  \
/**                                               \
 * Pushes a new element into an arraystack        \
 *                                                \
 * @param[in] stack    The arraystack             \
 * @param[in] element The element                 \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraystack_push(type)(arraystack(type)* stack, type element) { \
    /* check for free space */                    \
    if (stack->size == stack->_allocated_size) {  \
        /* new pointer */                         \
        type* pointer;                            \
                                                  \
        /* check for empty stack */               \
        if (stack->_allocated_size == 0 || stack->data == NULL) { \
            /* first allocation */                \
            stack->_allocated_size = 2;           \
                                                  \
            /* allocate memory */                 \
            pointer = (type*) malloc(2 * sizeof(type)); \
        } else {                                  \
            /* increase allocated length */       \
            stack->_allocated_size *= 2;          \
                                                  \
            /* reallocate memory */               \
            pointer = (type*) realloc(stack->data, stack->_allocated_size * sizeof(type)); \
        }                                         \
                                                  \
        /* null check */                          \
        if (pointer == NULL) {                    \
            /* revert allocated size */           \
            stack->_allocated_size /= 2;          \
                                                  \
            if (stack->_allocated_size == 1) {    \
                /* first allocation failed */     \
                stack->_allocated_size = 0;       \
            }                                     \
                                                  \
            /* log an error */                    \
            loge("memory reallocation failed while adding new element to a " macro_stringify(arraystack(type)) \
                " with size %zu and allocated size %zu", stack->size, stack->_allocated_size); \
                                                  \
            /* fail */                            \
            return ST_ALLOC_FAIL;                 \
        }                                         \
                                                  \
        /* assign new pointer */                  \
        stack->data = pointer;                    \
    }                                             \
                                                  \
    /* add new element */                         \
    stack->data[stack->size] = element;           \
                                                  \
    /* increment length */                        \
    stack->size++;                                \
                                                  \
    /* success */                                 \
    return ST_OK;                                 \
}                                                 \
                                                  \
/**                                               \
 * Removes an element from top of                 \
 * the arraystack, shrinking it                   \
 * if new size is less or equal to                \
 * half of the allocated size                     \
 *                                                \
 * @param[in] stack  The arraystack               \
 *                                                \
 * @return ST_ALLOC_FAIL if an allocation fails,  \
 *          otherwise ST_OK                       \
 */                                               \
status_t arraystack_pop(type)(arraystack(type)* stack) {     \
    /* decrement arraystack size */                    \
    stack->size--;                                     \
                                                       \
    /* do nothing with the element */                  \
                                                       \
    if (stack->size <= stack->_allocated_size / 2) {   \
        /* trim the arraystack */                      \
        assertr_status(arraystack_trim(type)(stack), ST_ALLOC_FAIL); \
    }                                                  \
                                                       \
    /* success */                                      \
    return ST_OK;                                      \
}                                                      \
                                                       \
/**                                                    \
 * Reallocates the internal array of an arraystack     \
 * to be the same size as the number of elements       \
 *                                                     \
 * @param[in] stack The arraystack                     \
 *                                                     \
 * @return ST_ALLOC_FAIL if an allocation fails,       \
 *          otherwise ST_OK                            \
 */                                                    \
status_t arraystack_trim(type)(arraystack(type)* stack) { \
    /* if the stack is unallocated, return */             \
    if (stack->_allocated_size == 0) {                    \
        logw("attempted to trim an unallocated " macro_stringify(arraystack(type)) \
                " with size %zu and allocated size %zu", stack->size, stack->_allocated_size); \
        return ST_OK;                                     \
    }                                                     \
                                                          \
    /* if the stack is empty, free memory */              \
    if (stack->size == 0) {                               \
        free(stack->data);                                \
        stack->data = NULL;                               \
    } else {                                              \
        /* else, reallocate memory */                     \
        type* pointer = (type*) realloc(stack->data, stack->size * sizeof(type)); \
                                                          \
        /* null check */                                  \
        if (pointer == NULL) {                            \
            /* log an error */                            \
            loge("memory reallocation failed while trimming a " macro_stringify(arraystack(type)) \
                    " with size %zu and allocated size %zu", stack->size, stack->_allocated_size); \
                                                          \
            /* fail */                                    \
            return ST_ALLOC_FAIL;                         \
        }                                                 \
                                                          \
        /* assign new pointer */                          \
        stack->data = pointer;                            \
    }                                                  \
                                                       \
    /* change allocated size */                        \
    stack->_allocated_size = stack->size;              \
                                                       \
    /* success */                                      \
    return ST_OK;                                      \
}                                                      \
                                                       \
/**                                                    \
 * Initializes an arraystack with preallocated         \
 * memory for a specified number of elements,          \
 * which can be changed later via                      \
 * add or remove methods                               \
 *                                                     \
 * @param[in] stack The arraystack                     \
 * @param[in] size The number of elements              \
 *                                                     \
 * @return ST_ALLOC_FAIL if an allocation fails,       \
 *          otherwise ST_OK                            \
 */                                                    \
status_t arraystack_init(type)(arraystack(type)* stack, size_t size) { \
    stack->size = 0;                                                   \
    stack->_allocated_size = size;                                     \
    assertr_malloc(stack->data, sizeof(type) * size, type*)            \
                                                                       \
    /* success */                                                      \
    return ST_OK;                                                      \
}                                                                      \



/**
 * Creates an empty instance of an arraystack
 * 
 * @return Empty arraystack structure
 */
#define arraystack_empty {0, 0, NULL}

#endif /* CTOOL_TYPE_ARRAYSTACK_H */