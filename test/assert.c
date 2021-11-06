/**
 * @file assert.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-15
 * 
 *  Tests for assertion system
 * 
 *  These are mostly compilation tests, because
 *  we can't test for the logging output to be
 *  correct.
 */
    /* includes */
#include "ctool/assert.h" /* assertions */

    /* functions */
status_t test_assert_equals() {
    int a = 0;
    int b = 1;
    int c = 0;
    assertr_equals(a, c, ST_FAIL);
    assertd_equals(a, c);
    assertrc_equals(a, b, ST_OK, "%d: assert_equals test passed", 1);
    return ST_OK;
}

status_t test_assert_true() {
    int a = 0;
    int b = 1;
    int c = 0;
    assertr_true(a == c, ST_FAIL);
    assertd_true(a == c);
    assertrc_true(a == b, ST_OK, "%d: assert_true test passed", 2);
    return ST_OK;
}

status_t test_assert_false() {
    int a = 0;
    int b = 0;
    int c = 1;
    assertr_false(a == c, ST_FAIL);
    assertd_false(a == c);
    assertrc_false(a == b, ST_OK, "3: assert_false test passed");
    return ST_OK;
}

status_t test_assert_status() {
    status_t a = ST_OK;
    status_t b = ST_ALLOC_FAIL;
    assertr_status(a, ST_FAIL);
    assertd_status(a);
    assertrc_status(b, ST_OK, "4: assert_status test passed");
    return ST_OK;
}

status_t test_assert_not_null() {
    char a = 'a';
    char* b = &a;
    char* c = NULL;
    assertr_not_null(b, ST_FAIL);
    assertd_not_null(b);
    assertrc_not_null(c, ST_OK, "%s: assert_not_null test passed", "5");
    return ST_OK;
}

status_t test_assert_malloc() {
    char* a;
    assertr_malloc(a, sizeof(char), char*);
    *a = 'a';
    free(a);
    return ST_OK;
}

status_t test_assert_zero() {
    int a = 0;
    int b = 1;
    int c = 0;
    assertr_zero(a, ST_FAIL);
    assertd_zero(c);
    assertrc_zero(ST_OK, b, "%d: assert_zero test passed", 6);
    return ST_OK;
}

status_t test_assert_not_equals() {
    int a = 0;
    char b = 'b';
    int c = 0;
    assertr_not_equals(a, b, ST_FAIL);
    assertd_not_equals(b, c);
    assertrc_not_equals(a, c, ST_OK, "%d: assert_not_equals test passed", 7);
    return ST_OK;
}

status_t test_assert_fail() {
    assertrc_fail(ST_OK, "8: assert_fail test passed");
}

int main() {
    if (test_assert_equals() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_assert_true() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_assert_false() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_assert_status() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_assert_malloc() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_assert_zero() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_assert_not_equals() != ST_OK) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}