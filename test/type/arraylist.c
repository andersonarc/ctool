/**
 * @file arraylist.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2022-04-14
 */

    /* includes */
#include <stdint.h> /* int types */
#include <string.h> /* string operations */
#include "ctool/type/arraylist.h" /* arraylist type */

#include "criterion/criterion.h" /* test framework */
#include "criterion/new/assert.h" 

    /* typedefs */
typedef struct sample_type {
    uint16_t a;
    char* b;
} sample_type;

    /* generic declarations */
arraylist_declare(char);
arraylist_declare(sample_type);
arraylist_declare(uint64_t);

    /* generic definitions */
arraylist_define(char);
arraylist_define(sample_type);
arraylist_define_custom(uint64_t, ARRAYLIST_RESIZE_EXACT);


    /* utility definitions */
#define create_arraylists()     \
    char_arraylist_t a;         \
    arraylist(sample_type) b;   \
    arraylist(uint64_t) c;

#define free_arraylists()               \
    arraylist_free(char)(&a);           \
    arraylist_free(sample_type)(&b);    \
    arraylist_free(uint64_t)(&c);

#define check_arraylist_state(name, expected_size, expected_allocated_size) \
    cr_assert(eq(sz, name.size, expected_size));                            \
    cr_assert(eq(sz, name._allocated_size, expected_allocated_size));

#define ncr_assert_status(block) cr_assert(ne(int, block, ST_FAIL));

#define ncr_assert_bad_status(block) cr_assert(ne(int, block, ST_OK));

    /* tests */
Test(arraylist, init) {
    create_arraylists();

    /* a random data filler is created to check for modifications */
    void* stub = (void*) (intptr_t) rand();

    /* test initializing an empty arraylist */
    ncr_assert_status(arraylist_init_empty(char)(&a));
    check_arraylist_state(a, 0, 0);
    cr_assert(eq(ptr, a.data, NULL));

    /* test initializing a structure arraylist */
    b.data = stub;
    ncr_assert_status(arraylist_init(sample_type)(&b, 4));
    check_arraylist_state(b, 0, 4);
    cr_assert(ne(ptr, b.data, stub));

    /* test initializing an integer arraylist */
    c.data = stub;
    ncr_assert_status(arraylist_init(uint64_t)(&c, 777));
    check_arraylist_state(c, 0, 777);
    cr_assert(ne(ptr, c.data, stub));

    free_arraylists();
}

Test(arraylist, init_default) {
    create_arraylists();

    /* a random data filler is created to check for modifications */
    void* stub = (void*) (intptr_t) rand();

    /* test initializing a character arraylist */
    a.data = stub;
    ncr_assert_status(arraylist_init_default(char)(&a));
    check_arraylist_state(a, 0, ARRAYLIST_DEFAULT_SIZE);
    cr_assert(ne(ptr, a.data, stub));

    /* test initializing a structure arraylist */
    b.data = stub;
    ncr_assert_status(arraylist_init_default(sample_type)(&b));
    check_arraylist_state(b, 0, ARRAYLIST_DEFAULT_SIZE);
    cr_assert(ne(ptr, b.data, stub));

    /* test initializing an integer arraylist */
    c.data = stub;
    ncr_assert_status(arraylist_init_default(uint64_t)(&c));
    check_arraylist_state(c, 0, ARRAYLIST_DEFAULT_SIZE);
    cr_assert(ne(ptr, c.data, stub));

    free_arraylists();
}

Test(arraylist, init_with) {
    create_arraylists();

    /* test initializing a character arraylist */
    ncr_assert_status(arraylist_init_with(char)(&a, 'X'));
    check_arraylist_state(a, 1, _ARRAYLIST_INITIAL_SIZE_double);
    cr_assert(eq(chr, a.data[0], 'X'));

    /* test initializing a structure arraylist */
    sample_type s1 = { .a = 17, .b = "stri" };
    ncr_assert_status(arraylist_init_with(sample_type)(&b, s1));
    check_arraylist_state(b, 1, _ARRAYLIST_INITIAL_SIZE_double);
    cr_assert(eq(u16, b.data[0].a, 17));
    cr_assert(eq(str, b.data[0].b, "stri"));

    /* test initializing an integer arraylist */
    ncr_assert_status(arraylist_init_with(uint64_t)(&c, 632363));
    check_arraylist_state(c, 1, _ARRAYLIST_INITIAL_SIZE_exact);
    cr_assert(eq(u64, c.data[0], 632363));

    free_arraylists();
}

Test(arraylist, add) {
    create_arraylists();

    /* create an address buffer to check for reallocations */
    void* tmp;

    /* test adding several elements to an empty char arraylist */
    ncr_assert_status(arraylist_init(char)(&a, 0));
        check_arraylist_state(a, 0, 0);

    ncr_assert_status(arraylist_add(char)(&a, 'x'));
        check_arraylist_state(a, 1, 2);
        cr_assert(eq(chr, a.data[0], 'x'));

    ncr_assert_status(arraylist_add(char)(&a, 'c'));
        check_arraylist_state(a, 2, 2);
        cr_assert(eq(chr, a.data[0], 'x'));
        cr_assert(eq(chr, a.data[1], 'c'));
        tmp = a.data;

    ncr_assert_status(arraylist_add(char)(&a, 'b'));
        check_arraylist_state(a, 3, 4);
        cr_assert(eq(chr, a.data[0], 'x'));
        cr_assert(eq(chr, a.data[1], 'c'));
        cr_assert(eq(chr, a.data[2], 'b'));


    /* test adding to a preallocated structure arraylist */
    ncr_assert_status(arraylist_init(sample_type)(&b, 7));
        check_arraylist_state(b, 0, 7);
        tmp = b.data;
    
    sample_type s1 = { .a = 17, .b = "stri" };
    ncr_assert_status(arraylist_add(sample_type)(&b, s1));
        cr_assert(eq(ptr, b.data, tmp));

    ncr_assert_status(arraylist_add(sample_type)(&b, s1));
        cr_assert(eq(ptr, b.data, tmp));

    ncr_assert_status(arraylist_add(sample_type)(&b, s1));
        cr_assert(eq(ptr, b.data, tmp));
        cr_assert(eq(u16, b.data[2].a, 17));
        cr_assert(eq(str, b.data[2].b, "stri"));


    /* test initializing an integer arraylist with exact resize configuration */
    ncr_assert_status(arraylist_init(uint64_t)(&c, 1));
        check_arraylist_state(c, 0, 1);
        tmp = c.data;

    ncr_assert_status(arraylist_add(uint64_t)(&c, 13637223));
        cr_assert(eq(ptr, c.data, tmp));
        check_arraylist_state(c, 1, 1);
        cr_assert(eq(u64, c.data[0], 13637223));

    ncr_assert_status(arraylist_add(uint64_t)(&c, 3473472));
        check_arraylist_state(c, 2, 2);
        cr_assert(eq(u64, c.data[0], 13637223));
        cr_assert(eq(u64, c.data[1], 3473472));

    ncr_assert_status(arraylist_add(uint64_t)(&c, 5823534));
        check_arraylist_state(c, 3, 3);
        cr_assert(eq(u64, c.data[0], 13637223));
        cr_assert(eq(u64, c.data[1], 3473472));
        cr_assert(eq(u64, c.data[2], 5823534));

    free_arraylists();
}

Test(arraylist, remove) {
    create_arraylists();

    /* test removing several elements from different points in a char arraylist */
    ncr_assert_status(arraylist_init(char)(&a, 9));
    ncr_assert_status(arraylist_add(char)(&a, 'a'));
    ncr_assert_status(arraylist_add(char)(&a, 'b'));
    ncr_assert_status(arraylist_add(char)(&a, 'c'));
    ncr_assert_status(arraylist_add(char)(&a, 'd'));
    ncr_assert_status(arraylist_add(char)(&a, 'e'));
    ncr_assert_status(arraylist_add(char)(&a, 'f'));
        check_arraylist_state(a, 6, 9);

    ncr_assert_status(arraylist_remove(char)(&a, 3));
        check_arraylist_state(a, 5, 9);
        cr_assert(eq(chr, a.data[0], 'a'));
        cr_assert(eq(chr, a.data[1], 'b'));
        cr_assert(eq(chr, a.data[2], 'c'));
        cr_assert(eq(chr, a.data[3], 'e'));
        cr_assert(eq(chr, a.data[4], 'f'));
    
    ncr_assert_status(arraylist_remove(char)(&a, 4));
        check_arraylist_state(a, 4, 4);
        cr_assert(eq(chr, a.data[0], 'a'));
        cr_assert(eq(chr, a.data[1], 'b'));
        cr_assert(eq(chr, a.data[2], 'c'));
        cr_assert(eq(chr, a.data[3], 'e'));
    
    ncr_assert_status(arraylist_remove(char)(&a, 0));
        check_arraylist_state(a, 3, 4);
        cr_assert(eq(chr, a.data[0], 'b'));
        cr_assert(eq(chr, a.data[1], 'c'));
        cr_assert(eq(chr, a.data[2], 'e'));

    ncr_assert_bad_status(arraylist_remove(char)(&a, 12412));
    
    /* test removing a structure from an arraylist */
    sample_type s1 = { .a = 77, .b = "aseasd" };
    sample_type s2 = { .a = 12, .b = "afe" };
    sample_type s3 = { .a = 32, .b = "hrs" };
    ncr_assert_status(arraylist_init(sample_type)(&b, 0));
    ncr_assert_status(arraylist_add(sample_type)(&b, s1));
    ncr_assert_status(arraylist_add(sample_type)(&b, s2));
    ncr_assert_status(arraylist_add(sample_type)(&b, s3));
        check_arraylist_state(b, 3, 4);

    ncr_assert_status(arraylist_remove(sample_type)(&b, 1));
        check_arraylist_state(b, 2, 2);
        cr_assert(eq(u16, b.data[0].a, 77));
        cr_assert(eq(str, b.data[0].b, "aseasd"));
        cr_assert(eq(u16, b.data[1].a, 32));
        cr_assert(eq(str, b.data[1].b, "hrs"));
    
    ncr_assert_status(arraylist_remove(sample_type)(&b, 0));
        check_arraylist_state(b, 1, 1);
        cr_assert(eq(u16, b.data[0].a, 32));
        cr_assert(eq(str, b.data[0].b, "hrs"));

    ncr_assert_status(arraylist_remove(sample_type)(&b, 0));
        check_arraylist_state(b, 0, 0);

    ncr_assert_bad_status(arraylist_remove(sample_type)(&b, 0));

    /* test removing from an exact resizing integer arraylist */
    ncr_assert_status(arraylist_init(uint64_t)(&c, 0));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 646351));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 74745));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 1244));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 45745));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 16863));
        check_arraylist_state(c, 5, 5);

    ncr_assert_status(arraylist_remove(uint64_t)(&c, 1));
        check_arraylist_state(c, 4, 5);
        cr_assert(eq(u64, c.data[0], 646351));
        cr_assert(eq(u64, c.data[1], 1244));
        cr_assert(eq(u64, c.data[2], 45745));
        cr_assert(eq(u64, c.data[3], 16863));

    ncr_assert_status(arraylist_remove(uint64_t)(&c, 0));
        check_arraylist_state(c, 3, 5);
        cr_assert(eq(u64, c.data[0], 1244));
        cr_assert(eq(u64, c.data[1], 45745));
        cr_assert(eq(u64, c.data[2], 16863));
    
    ncr_assert_status(arraylist_remove(uint64_t)(&c, 2));
        check_arraylist_state(c, 2, 2);
        cr_assert(eq(u64, c.data[0], 1244));
        cr_assert(eq(u64, c.data[1], 45745));

    ncr_assert_bad_status(arraylist_remove(uint64_t)(&c, -1));
    ncr_assert_bad_status(arraylist_remove(uint64_t)(&c, 2));

    free_arraylists();
}

Test(arraylist, trim) {
    create_arraylists();

    /* test trimming an overallocated arraylist */
    ncr_assert_status(arraylist_init(char)(&a, 7));
        check_arraylist_state(a, 0, 7);
    ncr_assert_status(arraylist_add(char)(&a, 'a'));
    ncr_assert_status(arraylist_add(char)(&a, 'b'));
    ncr_assert_status(arraylist_add(char)(&a, 'c'));
    ncr_assert_status(arraylist_add(char)(&a, 'd'));
        check_arraylist_state(a, 4, 7);

    ncr_assert_status(arraylist_trim(char)(&a));
        check_arraylist_state(a, 4, 4);

    ncr_assert_status(arraylist_remove(char)(&a, 2));
        check_arraylist_state(a, 3, 4);
        cr_assert(eq(chr, a.data[0], 'a'));
        cr_assert(eq(chr, a.data[1], 'b'));
        cr_assert(eq(chr, a.data[2], 'd'));

    /* test trimming an initially empty structure arraylist */
    ncr_assert_status(arraylist_init(sample_type)(&b, 0));
        check_arraylist_state(b, 0, 0);
    
    ncr_assert_status(arraylist_trim(sample_type)(&b));
        check_arraylist_state(b, 0, 0);

    sample_type s1 = { .a = 77, .b = "aseasd" };
    sample_type s2 = { .a = 12, .b = "afe" };
    sample_type s3 = { .a = 32, .b = "hrs" };
    ncr_assert_status(arraylist_add(sample_type)(&b, s1));
    ncr_assert_status(arraylist_add(sample_type)(&b, s2));
    ncr_assert_status(arraylist_add(sample_type)(&b, s3));
        check_arraylist_state(b, 3, 4);

    ncr_assert_status(arraylist_trim(sample_type)(&b));
        check_arraylist_state(b, 3, 3);
        cr_assert(eq(u16, b.data[0].a, 77));
        cr_assert(eq(str, b.data[0].b, "aseasd"));
        cr_assert(eq(u16, b.data[1].a, 12));
        cr_assert(eq(str, b.data[1].b, "afe"));
        cr_assert(eq(u16, b.data[2].a, 32));
        cr_assert(eq(str, b.data[2].b, "hrs"));
    
    /* test trimming an exact resizing integer arraylist */
    ncr_assert_status(arraylist_init(uint64_t)(&c, 8));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 646351));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 74745));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 1244));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 45745));
        check_arraylist_state(c, 4, 8);

    ncr_assert_status(arraylist_trim(uint64_t)(&c));
        check_arraylist_state(c, 4, 4);
        cr_assert(eq(u64, c.data[0], 646351));
        cr_assert(eq(u64, c.data[1], 74745));
        cr_assert(eq(u64, c.data[2], 1244));
        cr_assert(eq(u64, c.data[3], 45745));

    free_arraylists();
}

Test(arraylist, revert) {
    create_arraylists();

    /* check reverting a simple char arraylist */
    ncr_assert_status(arraylist_init(char)(&a, 0));
    ncr_assert_status(arraylist_add(char)(&a, 'a'));
    ncr_assert_status(arraylist_add(char)(&a, 'b'));
    ncr_assert_status(arraylist_add(char)(&a, 'c'));
        check_arraylist_state(a, 3, 4);

    arraylist_revert(char)(&a);
        check_arraylist_state(a, 3, 4);
        cr_assert(eq(chr, a.data[0], 'c'));
        cr_assert(eq(chr, a.data[1], 'b'));
        cr_assert(eq(chr, a.data[2], 'a'));

    /* test reverting an initially empty structure arraylist */
    ncr_assert_status(arraylist_init(sample_type)(&b, 0));
        check_arraylist_state(b, 0, 0);
    
    arraylist_revert(sample_type)(&b);
        check_arraylist_state(b, 0, 0);

    sample_type s1 = { .a = 77, .b = "aseasd" };
    sample_type s2 = { .a = 12, .b = "afe" };
    sample_type s3 = { .a = 32, .b = "hrs" };
    sample_type s4 = { .a = 77, .b = "asease" };
    ncr_assert_status(arraylist_add(sample_type)(&b, s1));
    ncr_assert_status(arraylist_add(sample_type)(&b, s2));
    ncr_assert_status(arraylist_add(sample_type)(&b, s3));
    ncr_assert_status(arraylist_add(sample_type)(&b, s4));
        check_arraylist_state(b, 4, 4);

    arraylist_revert(sample_type)(&b);
        check_arraylist_state(b, 4, 4);
        cr_assert(eq(u16, b.data[0].a, 77));
        cr_assert(eq(str, b.data[0].b, "asease"));
        cr_assert(eq(u16, b.data[1].a, 32));
        cr_assert(eq(str, b.data[1].b, "hrs"));
        cr_assert(eq(u16, b.data[2].a, 12));
        cr_assert(eq(str, b.data[2].b, "afe"));
        cr_assert(eq(u16, b.data[3].a, 77));
        cr_assert(eq(str, b.data[3].b, "aseasd"));

    /* test reverting an exact resizing integer arraylist */
    ncr_assert_status(arraylist_init(uint64_t)(&c, 8));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 646351));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 74745));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 1244));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 45745));
        check_arraylist_state(c, 4, 8);

    arraylist_revert(uint64_t)(&c);
        check_arraylist_state(c, 4, 8);
        cr_assert(eq(u64, c.data[0], 45745));
        cr_assert(eq(u64, c.data[1], 1244));
        cr_assert(eq(u64, c.data[2], 74745));
        cr_assert(eq(u64, c.data[3], 646351));

    free_arraylists();
}

//-- redo, (list has the same data pointer)
Test(arraylist, to_list) {
    create_arraylists();

    /* check converting a simple char arraylist */
    ncr_assert_status(arraylist_init(char)(&a, 0));
    ncr_assert_status(arraylist_add(char)(&a, 'a'));
    ncr_assert_status(arraylist_add(char)(&a, 'b'));
    ncr_assert_status(arraylist_add(char)(&a, 'c'));
        check_arraylist_state(a, 3, 4);

    list(char) la;
    ncr_assert_status(arraylist_to_list(char)(&a, &la));
        check_arraylist_state(a, 3, 3);
        cr_assert(eq(sz, la.size, 3));
        cr_assert(eq(ptr, a.data, la.data));
        cr_assert(eq(chr, a.data[0], la.data[0]));
        cr_assert(eq(chr, a.data[1], la.data[1]));
        cr_assert(eq(chr, a.data[2], la.data[2]));
        cr_assert(eq(chr, la.data[0], 'a'));
        cr_assert(eq(chr, la.data[1], 'b'));
        cr_assert(eq(chr, la.data[2], 'c'));

    /* test converting an initially empty structure arraylist */
    ncr_assert_status(arraylist_init(sample_type)(&b, 0));
        check_arraylist_state(b, 0, 0);
    
    list(sample_type) lb;
    ncr_assert_status(arraylist_to_list(sample_type)(&b, &lb));
        cr_assert(eq(sz, lb.size, 0));
        cr_assert(eq(ptr, lb.data, NULL));
        cr_assert(eq(ptr, b.data, lb.data));
        check_arraylist_state(b, 0, 0);

    sample_type s1 = { .a = 77, .b = "aseasd" };
    sample_type s2 = { .a = 12, .b = "afe" };
    sample_type s3 = { .a = 32, .b = "hrs" };
    sample_type s4 = { .a = 77, .b = "asease" };
    ncr_assert_status(arraylist_add(sample_type)(&b, s1));
    ncr_assert_status(arraylist_add(sample_type)(&b, s2));
    ncr_assert_status(arraylist_add(sample_type)(&b, s3));
    ncr_assert_status(arraylist_add(sample_type)(&b, s4));
        check_arraylist_state(b, 4, 4);

    ncr_assert_status(arraylist_to_list(sample_type)(&b, &lb));
        check_arraylist_state(b, 4, 4);
        cr_assert(eq(sz, lb.size, 4));
        cr_assert(eq(ptr, b.data, lb.data));
        cr_assert(eq(u16, lb.data[0].a, 77));
        cr_assert(eq(str, lb.data[0].b, "aseasd"));
        cr_assert(eq(u16, lb.data[1].a, 12));
        cr_assert(eq(str, lb.data[1].b, "afe"));
        cr_assert(eq(u16, lb.data[2].a, 32));
        cr_assert(eq(str, lb.data[2].b, "hrs"));
        cr_assert(eq(u16, lb.data[2].a, 32));
        cr_assert(eq(str, lb.data[2].b, "hrs"));

    /* test converting an exact resizing integer arraylist */
    ncr_assert_status(arraylist_init(uint64_t)(&c, 8));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 646351));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 74745));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 1244));
    ncr_assert_status(arraylist_add(uint64_t)(&c, 45745));
        check_arraylist_state(c, 4, 8);

    list(uint64_t) lc;
    ncr_assert_status(arraylist_to_list(uint64_t)(&c, &lc));
        cr_assert(eq(sz, lc.size, 4));
        check_arraylist_state(c, 4, 4);
        cr_assert(eq(ptr, c.data, lc.data));
        cr_assert(eq(u64, lc.data[0], c.data[0]));
        cr_assert(eq(u64, lc.data[1], c.data[1]));
        cr_assert(eq(u64, lc.data[2], c.data[2]));
        cr_assert(eq(u64, lc.data[3], c.data[3]));

    free_arraylists();
}

Test(arraylist, move_append) {

}