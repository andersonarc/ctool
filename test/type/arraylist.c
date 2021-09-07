/**
 * @file arraylist.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.2
 * @date 2021-07-04
 * 
 *  Tests for the generic resizable arraylist type
 */
    /* includes */
#include <stdint.h> /* int types */
#include <string.h> /* string operations */
#include "ctool/type/arraylist.h" /* arraylist type */

    /* typedefs */
typedef struct sample_struct {
    uint16_t a;
    char* b;
} sample_struct;

    /* generic declarations */
arraylist_declare(char);
arraylist_declare(uint32_t);
arraylist_declare(sample_struct);
arraylist_declare(int);

    /* generic definitions */
arraylist_define(char);
arraylist_define(uint32_t);
arraylist_define(sample_struct);
arraylist_define_custom(int, ARRAYLIST_RESIZE_EXACT);

    /* functions */
/**
 * Tests if the arraylist type could
 * be initialized correctly using
 * different methods
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK
 */
status_t test_arraylist_init() {
    /* create an empty char arraylist */
    char_arraylist_t a;
    assertr_status(arraylist_init(char)(&a, 0), ST_FAIL);
    assertr_equals(a.size, 0, ST_FAIL);
    assertr_equals(a._allocated_size, 0, ST_FAIL);
    
    /* create a preallocated uint32_t arraylist */
    uint32_t_arraylist_t b;
    assertr_status(arraylist_init(uint32_t)(&b, 0), ST_FAIL);
    assertr_equals(b.size, 0, ST_FAIL);
    assertr_equals(b._allocated_size, 0, ST_FAIL);

    /* create a preallocated sample_struct arraylist */
    sample_struct_arraylist_t c;
    assertr_status(sample_struct_arraylist_init(&c, 5), ST_FAIL);
    assertr_equals(c.size, 0, ST_FAIL);
    assertr_equals(c._allocated_size, 5, ST_FAIL);

    /* free the arraylists */
    char_arraylist_free(&a);
    arraylist_free(uint32_t)(&b);
    sample_struct_arraylist_free(&c);

    return ST_OK;
}

/**
 * Tests if a new element could be
 * added on top of an arraylist
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_arraylist_add() {
    /* create an empty char arraylist */
    char_arraylist_t a;
    assertr_status(arraylist_init(char)(&a, 0), ST_FAIL);

    /* add 'a' and 'b' elements */
    assertr_status(arraylist_add(char)(&a, 'a'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'b'), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a.size, 2, ST_FAIL);
    assertr_equals(a._allocated_size, 2, ST_FAIL);
    assertr_equals(a.data[0], 'a', ST_FAIL);
    assertr_equals(a.data[1], 'b', ST_FAIL);

    /* add a 'c' element */
    assertr_status(char_arraylist_add(&a, 'c'), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a.size, 3, ST_FAIL);
    assertr_equals(a._allocated_size, 4, ST_FAIL);
    assertr_equals(a.data[2], 'c', ST_FAIL);


    /* create a preallocated sample_struct arraylist */
    sample_struct_arraylist_t b;
    assertr_status(sample_struct_arraylist_init(&b, 5), ST_FAIL);
    sample_struct s1 = { 1, "string" };
    sample_struct s2 = { 0, "a" };

    /* add two new elements */
    assertr_status(arraylist_add(sample_struct)(&b, s1), ST_FAIL);
    assertr_status(sample_struct_arraylist_add(&b, s2), ST_FAIL);

    /* check arraylist state */
    assertr_equals(b.size, 2, ST_FAIL);
    assertr_equals(b._allocated_size, 5, ST_FAIL);
    assertr_equals(b.data[0].a, s1.a, ST_FAIL);
    assertr_equals(b.data[1].a, s2.a, ST_FAIL);
    assertr_zero(strcmp(b.data[0].b, s1.b), ST_FAIL);
    assertr_zero(strcmp(b.data[1].b, s2.b), ST_FAIL);

    /* free the arraylists */
    char_arraylist_free(&a);
    arraylist_free(sample_struct)(&b);

    return ST_OK;
}

status_t test_arraylist_remove() {
    /* create an empty char arraylist */
    char_arraylist_t a;
    assertr_status(arraylist_init(char)(&a, 0), ST_FAIL);

    /* add 6 new elements */
    assertr_status(arraylist_add(char)(&a, 'a'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'b'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'c'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'd'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'e'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'f'), ST_FAIL);

    /* remove the first element */
    assertr_status(arraylist_remove(char)(&a, 0), ST_FAIL);
    
    /* check arraylist state */
    assertr_equals(a._allocated_size, 8, ST_FAIL);
    assertr_equals(a.size, 5, ST_FAIL);
    assertr_equals(a.data[0], 'b', ST_FAIL);
    assertr_equals(a.data[1], 'c', ST_FAIL);
    assertr_equals(a.data[2], 'd', ST_FAIL);
    assertr_equals(a.data[3], 'e', ST_FAIL);
    assertr_equals(a.data[4], 'f', ST_FAIL);

    /* remove the last element */
    assertr_status(arraylist_remove(char)(&a, 4), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a._allocated_size, 4, ST_FAIL);
    assertr_equals(a.size, 4, ST_FAIL);
    assertr_equals(a.data[0], 'b', ST_FAIL);
    assertr_equals(a.data[1], 'c', ST_FAIL);
    assertr_equals(a.data[2], 'd', ST_FAIL);
    assertr_equals(a.data[3], 'e', ST_FAIL);

    /* remove the second element */
    assertr_status(char_arraylist_remove(&a, 1), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a._allocated_size, 4, ST_FAIL);
    assertr_equals(a.size, 3, ST_FAIL);
    assertr_equals(a.data[0], 'b', ST_FAIL);
    assertr_equals(a.data[1], 'd', ST_FAIL);
    assertr_equals(a.data[2], 'e', ST_FAIL);


    /* create a preallocated sample_struct arraylist */
    sample_struct_arraylist_t b;
    assertr_status(sample_struct_arraylist_init(&b, 5), ST_FAIL);

    /* add 2 new elements */
    sample_struct s1 = { 1, "string" };
    sample_struct s2 = { 0, "a" };
    assertr_status(arraylist_add(sample_struct)(&b, s1), ST_FAIL);
    assertr_status(sample_struct_arraylist_add(&b, s2), ST_FAIL);

    /* remove the last element */
    assertr_status(arraylist_remove(sample_struct)(&b, 1), ST_FAIL);

    /* check arraylist state */
    assertr_equals(b._allocated_size, 1, ST_FAIL);
    assertr_equals(b.size, 1, ST_FAIL);
    assertr_equals(b.data[0].a, s1.a, ST_FAIL);
    assertr_zero(strcmp(b.data[0].b, s1.b), ST_FAIL);

    /* free the arraylists */
    arraylist_free(char)(&a);
    sample_struct_arraylist_free(&b);

    return ST_OK;
}

status_t test_arraylist_trim() {
    /* create an empty char arraylist */
    char_arraylist_t a;
    assertr_status(arraylist_init(char)(&a, 0), ST_FAIL);

    /* add 3 new elements */
    assertr_status(arraylist_add(char)(&a, 'a'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'b'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'c'), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a._allocated_size, 4, ST_FAIL);
    assertr_equals(a.size, 3, ST_FAIL);
    assertr_equals(a.data[0], 'a', ST_FAIL);
    assertr_equals(a.data[1], 'b', ST_FAIL);
    assertr_equals(a.data[2], 'c', ST_FAIL);

    /* trim the arraylist */
    assertr_status(char_arraylist_trim(&a), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a._allocated_size, a.size, ST_FAIL);
    assertr_equals(a._allocated_size, 3, ST_FAIL);
    assertr_equals(a.data[0], 'a', ST_FAIL);
    assertr_equals(a.data[1], 'b', ST_FAIL);
    assertr_equals(a.data[2], 'c', ST_FAIL);


    /* create a preallocated sample_struct arraylist */
    sample_struct_arraylist_t b;
    assertr_status(sample_struct_arraylist_init(&b, 5), ST_FAIL);

    /* add 2 new elements */
    sample_struct s1 = { 1, "string" };
    sample_struct s2 = { 0, "a" };
    assertr_status(arraylist_add(sample_struct)(&b, s1), ST_FAIL);
    assertr_status(sample_struct_arraylist_add(&b, s2), ST_FAIL);

    /* check arraylist state */
    assertr_equals(b._allocated_size, 5, ST_FAIL);
    assertr_equals(b.size, 2, ST_FAIL);

    /* trim the arraylist */
    assertr_status(arraylist_trim(sample_struct)(&b), ST_FAIL);

    /* check arraylist state */
    assertr_equals(b._allocated_size, b.size, ST_FAIL);
    assertr_equals(b._allocated_size, 2, ST_FAIL);

    /* free the arraylists */
    arraylist_free(char)(&a);
    arraylist_free(sample_struct)(&b);

    return ST_OK;
}

status_t test_arraylist_revert() {
    /* create an empty char arraylist */
    char_arraylist_t a;
    assertr_status(arraylist_init(char)(&a, 0), ST_FAIL);

    /* add 3 new elements */
    assertr_status(arraylist_add(char)(&a, 'a'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'b'), ST_FAIL);
    assertr_status(char_arraylist_add(&a, 'c'), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a._allocated_size, 4, ST_FAIL);
    assertr_equals(a.size, 3, ST_FAIL);
    assertr_equals(a.data[0], 'a', ST_FAIL);
    assertr_equals(a.data[1], 'b', ST_FAIL);
    assertr_equals(a.data[2], 'c', ST_FAIL);

    /* revert the arraylist */
    char_arraylist_revert(&a);

    /* check arraylist state */
    assertr_equals(a.data[0], 'c', ST_FAIL);
    assertr_equals(a.data[1], 'b', ST_FAIL);
    assertr_equals(a.data[2], 'a', ST_FAIL);


    /* create a preallocated sample_struct arraylist */
    sample_struct_arraylist_t b;
    assertr_status(sample_struct_arraylist_init(&b, 5), ST_FAIL);

    /* add 2 new elements */
    sample_struct s1 = { 1, "string" };
    sample_struct s2 = { 0, "a" };
    assertr_status(arraylist_add(sample_struct)(&b, s1), ST_FAIL);
    assertr_status(sample_struct_arraylist_add(&b, s2), ST_FAIL);

    /* check arraylist state */
    assertr_equals(b._allocated_size, 5, ST_FAIL);
    assertr_equals(b.size, 2, ST_FAIL);
    assertr_equals(b.data[0].a, 1, ST_FAIL);
    assertr_zero(strcmp(b.data[0].b, "string"), ST_FAIL);
    assertr_equals(b.data[1].a, 0, ST_FAIL);
    assertr_zero(strcmp(b.data[1].b, "a"), ST_FAIL);

    /* revert the arraylist */
    arraylist_revert(sample_struct)(&b);

     /* check arraylist state */
    assertr_equals(b._allocated_size, 5, ST_FAIL);
    assertr_equals(b.size, 2, ST_FAIL);
    assertr_equals(b.data[0].a, 0, ST_FAIL);
    assertr_zero(strcmp(b.data[0].b, "a"), ST_FAIL);
    assertr_equals(b.data[1].a, 1, ST_FAIL);
    assertr_zero(strcmp(b.data[1].b, "string"), ST_FAIL);

    /* free the arraylists */
    arraylist_free(char)(&a);
    arraylist_free(sample_struct)(&b);

    return ST_OK;
}

/**
 * Tests if a new element could be
 * added on top of an arraylist
 * with an "exact" resizing configurations
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_arraylist_add_exact() {
    /* create an empty int arraylist */
    int_arraylist_t a;
    assertr_status(arraylist_init(int)(&a, 0), ST_FAIL);

    /* add 2 elements */
    assertr_status(arraylist_add(int)(&a, -1), ST_FAIL);
    assertr_status(int_arraylist_add(&a, 777), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a.size, 2, ST_FAIL);
    assertr_equals(a._allocated_size, 2, ST_FAIL);
    assertr_equals(a.data[0], -1, ST_FAIL);
    assertr_equals(a.data[1], 777, ST_FAIL);

    /* add a third element */
    assertr_status(int_arraylist_add(&a, 1171), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a.size, 3, ST_FAIL);
    assertr_equals(a._allocated_size, 3, ST_FAIL);
    assertr_equals(a.data[2], 1171, ST_FAIL);

    /* free the arraylist */
    int_arraylist_free(&a);

    return ST_OK;
}

/**
 * Tests if an arraylist
 * can be transformed to a list
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_arraylist_to_list() {
    /* create an empty int arraylist */
    int_arraylist_t a;
    assertr_status(arraylist_init(int)(&a, 0), ST_FAIL);

    /* add 3 elements */
    assertr_status(arraylist_add(int)(&a, 11), ST_FAIL);
    assertr_status(int_arraylist_add(&a, 33), ST_FAIL);
    assertr_status(int_arraylist_add(&a, -710), ST_FAIL);

    /* check arraylist state */
    assertr_equals(a.size, 3, ST_FAIL);
    assertr_equals(a._allocated_size, 3, ST_FAIL);
    assertr_equals(a.data[0], 11, ST_FAIL);
    assertr_equals(a.data[1], 33, ST_FAIL);
    assertr_equals(a.data[2], -710, ST_FAIL);

    /* transform */
    int_list_t a_l;
    assertr_status(arraylist_to_list(int)(&a, &a_l), ST_FAIL);

    /* check list state */
    assertr_equals(a_l.size, 3, ST_FAIL);
    assertr_equals(a_l.data, a.data, ST_FAIL);
    assertr_equals(a_l.data[0], 11, ST_FAIL);
    assertr_equals(a_l.data[1], 33, ST_FAIL);
    assertr_equals(a_l.data[2], -710, ST_FAIL);


    /* create a preallocated sample_struct arraylist */
    sample_struct_arraylist_t b;
    assertr_status(sample_struct_arraylist_init(&b, 5), ST_FAIL);
    sample_struct s1 = { 1, "string" };
    sample_struct s2 = { 0, "a" };

    /* add 2 new elements */
    assertr_status(arraylist_add(sample_struct)(&b, s1), ST_FAIL);
    assertr_status(sample_struct_arraylist_add(&b, s2), ST_FAIL);

    /* check arraylist state */
    assertr_equals(b._allocated_size, 5, ST_FAIL);
    assertr_equals(b.size, 2, ST_FAIL);

    /* transform */
    list(sample_struct) b_l;
    assertr_status(arraylist_to_list(sample_struct)(&b, &b_l), ST_FAIL);

    /* check list state */
    assertr_equals(b_l.size, 2, ST_FAIL);
    assertr_equals(b_l.data[0].a, 1, ST_FAIL);
    assertr_zero(strcmp(b_l.data[0].b, "string"), ST_FAIL);
    assertr_equals(b_l.data[1].a, 0, ST_FAIL);
    assertr_zero(strcmp(b_l.data[1].b, "a"), ST_FAIL);

    /* free the arraylists */
    int_arraylist_free(&a);
    arraylist_free(sample_struct)(&b);

    return ST_OK;
}

    /* main function */
int main() {
    if (test_arraylist_init() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_arraylist_add() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_arraylist_remove() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_arraylist_trim() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_arraylist_revert() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_arraylist_add_exact() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_arraylist_to_list() != ST_OK) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}