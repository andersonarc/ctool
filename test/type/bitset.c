/**
 * @file bitset.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-11-02
 * 
 *  Tests for the bitset type
 */
    /* includes */
#include "ctool/assert.h" /* assertions */
#include "ctool/type/bitset.h" /* bitset type */

    /* generic declarations */
bitset_declare(1);
bitset_declare(16);
bitset_declare(33);

    /* functions */
/**
 * Tests if a bitset is initialized
 * with zeroes correctly
 * 
 * @return ST_FAIL if an assertion fails,
 *          otherwise ST_OK
 */
status_t test_bitset_init() {
    /* initialize the bitsets */
    bitset(16) a;
    bitset(33) b;
    bitset(1) c;

    bitset_init(a);
    bitset_init(b);
    bitset_init(c);

    /* check if they are filled with zeroes */
    assertr_zero(a._data, ST_FAIL);
    assertr_zero(b._data, ST_FAIL);
    assertr_zero(c._data, ST_FAIL);

    return ST_OK;
}

/**
 * Tests if bits in a bitset are set correctly
 * 
 * @return ST_FAIL if an assertion fails,
 *          otherwise ST_OK
 */
status_t test_bitset_set() {
    /* initialize the bitsets */
    bitset(16) a;
    bitset(33) b;
    bitset(1) c;

    bitset_init(a);
    bitset_init(b);
    bitset_init(c);

    /* set random values */
    bitset_set(a, 0);
    bitset_set(b, 33);
    bitset_set(c, 1);

    /* check if the values are set */
    bitset_if_not_set(a, 0)  { assertrc_fail(ST_FAIL, "bitset_if_not_set(a, 0)"); }
    bitset_if_not_set(b, 33) { assertrc_fail(ST_FAIL, "bitset_if_not_set(b, 33)"); }
    bitset_if_not_set(c, 1)  { assertrc_fail(ST_FAIL, "bitset_if_not_set(c, 1)"); }

    return ST_OK;
}

/**
 * Tests if bits in a bitset are cleared correctly
 * 
 * @return ST_FAIL if an assertion fails,
 *          otherwise ST_OK
 */
status_t test_bitset_clear() {
    /* initialize the bitsets */
    bitset(16) a;
    bitset(33) b;
    bitset(4) c;

    bitset_init(a);
    bitset_init(b);
    bitset_init(c);

    /* set random values */
    bitset_set(b, 17);
    bitset_set(c, 1);
    bitset_set(c, 3);

    /* clear those values and an extra one */
    bitset_clear(b, 17);
    bitset_clear(c, 1);
    bitset_clear(c, 2);

    /* check an untouched value */
    bitset_if_set(a, 8)  { assertrc_fail(ST_FAIL, "bitset_if_set(a, 8)"); }

    /* check the cleared values */
    bitset_if_set(b, 17)  { assertrc_fail(ST_FAIL, "bitset_if_set(b, 17)"); }
    bitset_if_set(c, 1)   { assertrc_fail(ST_FAIL, "bitset_if_set(c, 1)"); }
    bitset_if_set(c, 2)   { assertrc_fail(ST_FAIL, "bitset_if_set(c, 2)"); }

    return ST_OK;
}

/**
 * Tests if bits in a bitset are toggled correctly
 * 
 * @return ST_FAIL if an assertion fails,
 *          otherwise ST_OK
 */
status_t test_bitset_toggle() {
    /* initialize the bitsets */
    bitset(9) a;
    bitset(5) b;
    bitset(64) c;

    bitset_init(a);
    bitset_init(b);
    bitset_init(c);

    /* set random values */
    bitset_set(a, 5);
    bitset_set(a, 8);
    bitset_set(b, 1);
    bitset_set(c, 16);
    bitset_set(c, 32);

    /* toggle some of those values and some extra values */
    bitset_toggle(a, 5);
    bitset_toggle(a, 6);
    bitset_clear(b, 1);
    bitset_toggle(b, 1);
    bitset_toggle(c, 16);
    bitset_toggle(c, 17);

    /* check the values */
    bitset_if_set(a, 5)      { assertrc_fail(ST_FAIL, "bitset_if_set(a, 5)"); }
    bitset_if_not_set(a, 6)  { assertrc_fail(ST_FAIL, "bitset_if_not_set(a, 6)"); }

    bitset_if_not_set(b, 1)  { assertrc_fail(ST_FAIL, "bitset_if_not_set(b, 1)"); }

    bitset_if_set(c, 15)       { assertrc_fail(ST_FAIL, "bitset_if_set(c, 15)"); }
    bitset_if_set(c, 16)       { assertrc_fail(ST_FAIL, "bitset_if_set(c, 16)"); }
    bitset_if_not_set(c, 17)   { assertrc_fail(ST_FAIL, "bitset_if_not_set(c, 17)"); }

    return ST_OK;
}


    /* main function */
int main() {
    if (test_bitset_init() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_bitset_set() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_bitset_clear() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_bitset_toggle() != ST_OK) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}