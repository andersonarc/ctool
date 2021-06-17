/**
 * @file assert.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-15
 * 
 *  Tests for assertion system
 */
    /* includes */
#include "ctool/assert.h" /* assertions */

    /* functions */
status_t test_assert_equals() {
    int a = 0;
    int b = 1;
    int c = 0;
    assertr_equals(a, c, ST_OK);
    assertd_equals(a, c);
    assertrc_equals(a, b, ST_FAIL, "%d: assert_equals test passed", 1);
    return ST_OK;
}

status_t test_assert_true() {
    int a = 0;
    int b = 1;
    int c = 0;
    assertr_true(a == c, ST_OK);
    assertd_true(a == c);
    assertrc_true(a == b, ST_FAIL, "%d: assert_true test passed", 2);
    return ST_OK;
}

status_t test_assert_false() {
    int a = 0;
    int b = 0;
    int c = 1;
    assertr_false(a != c, ST_FAIL);
    assertd_false(a != c);
    assertrc_false(a == b, ST_FAIL, "3: assert_false test passed");
    return ST_OK;
}

status_t test_assert_status() {
    status_t a = ST_OK;
    status_t b = ST_ALLOC_FAIL;
    assertr_status(a, ST_OK);
    assertd_status(a);
    assertrc_status(b, ST_FAIL, "4: assert_status test passed");
    return ST_OK;
}

status_t test_assert_notnull() {
    char a = 'a';
    char* b = &a;
    char* c = NULL;
    assertr_notnull(b, ST_OK);
    assertd_notnull(b);
    assertrc_notnull(c, ST_FAIL, "%s: assert_notnull test passed", "5");
    return ST_OK;
}

status_t test_assert_malloc() {
    char* a;
    assertr_malloc(a, sizeof(char), char*);
    *a = 'a';
    free(a);
    return ST_OK;
}

int main() {
    if (test_assert_equals() != ST_FAIL) {
        return 1;
    }
    if (test_assert_true() != ST_FAIL) {
        return 1;
    }
    if (test_assert_false() != ST_FAIL) {
        return 1;
    }
    if (test_assert_status() != ST_FAIL) {
        return 1;
    }
    if (test_assert_malloc() != ST_OK /* not a typo */) {
        return 1;
    }
    return 0;
}