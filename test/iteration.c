/**
 * @file iteration.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-05
 * 
 *  Tests for range iteration
 */
    /* includes */
#include "ctool/iteration.h" /* range iteration */
#include "ctool/assert/runtime.h" /* runtime assertions */

    /* functions */
/**
 * Tests if the iterate_range macro works correctly,
 * iterating the range from the start (inclusive) to
 * the end (exclusive) and, if used with non-single step,
 * does not go out of bounds
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_iterate_range() {
    /* fill a 10-element array with values [0, 1, 0, 1, ...] */
    int a[10];
    iterate_range(i, 0, 10, 1) {
        a[i] = 0;
    }
    iterate_range(i, 1, 10, 2) {
        a[i] = 1;
    }

    /* check array state */
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            assertr_equals(a[i], 0, ST_FAIL);
        } else {
            assertr_equals(a[i], 1, ST_FAIL);
        }
    }

    /* copy every 3rd element of a string starting 
        from index 4 to a char array */
    const char* b = "abcdefghijkl";
    char c[3];
    int counter = 0;
    iterate_range(i, 4, 12, 3) {
        c[counter] = b[i];
        counter++;
    }

    /* assert array state */
    assertr_equals(counter, 3, ST_FAIL);
    assertr_equals(c[0], b[4], ST_FAIL);
    assertr_equals(c[1], b[7], ST_FAIL);
    assertr_equals(c[2], b[10], ST_FAIL);

    return ST_OK;
}

/**
 * Since iterate_range_single,
 * iterate_range_from_zero,
 * iterate_range_from_zero_single are
 * just aliases for iterate_range,
 * their testing could be safely skipped.
 */

    /* main function */
int main() {
    if (test_iterate_range() != ST_OK) {
        return 1;
    }
    return 0;
}