/**
 * @file iterator.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-03
 * 
 *  Macro for iteration over ranges and arrays,
 *  and index type definition
 */
    /* header guard */
#ifndef CTOOL_ITERATION_H
#define CTOOL_ITERATION_H

    /* includes */
#include <stdlib.h> /* size_t */

    /* typedefs */
/**
 * Index type, similar to size_t
 */
typedef size_t index_t;

    /* defines */
/**
 * Iterates a range from the start (inclusive) to
 * the end (exclusive), incrementing the counter by
 * specified offset every iteration
 * 
 * @param[in] name  The counter name
 * @param[in] start Range start, inclusive
 * @param[in] end   Range end, exclusive
 * @param[in] step  Counter step
 */
#define iterate_range(name, start, end, step) \
    for (index_t name = start; name < end; name += step)

/**
 * Iterates a range from the start (inclusive) to
 * the end (exclusive), incrementing the counter 
 * by 1 every iteration
 * 
 * @param[in] name  The counter name
 * @param[in] start Range start, inclusive
 * @param[in] end   Range end, exclusive
 */
#define iterate_range_single(name, start, end) iterate_range(name, start, end, 1)

/**
 * Iterates a range from 0 to the end (exclusive), 
 * incrementing the counter 
 * by specified offset every iteration
 * 
 * @param[in] name  The counter name
 * @param[in] end   Range end, exclusive
 * @param[in] step  Counter step
 */
#define iterate_from_zero(name, end, step) iterate_range(name, 0, end, step)

/**
 * Iterates a range from 0 to the end (exclusive), 
 * incrementing the counter by 1 every iteration
 * 
 * @param[in] name  The counter name
 * @param[in] end   Range end, exclusive
 */
#define iterate_from_zero_single(name, end) iterate_from_zero(name, end, 1)

/**
 * Alias for iterate_from_zero_single for 
 * simpler array iteration
 */
#define iterate_array iterate_from_zero_single

#endif /* CTOOL_ITERATION_H */