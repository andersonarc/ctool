/**
 * @file list.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-05
 * 
 *  Tests for the generic list type
 */
    /* includes */
#include <stdint.h> /* int types */
#include "ctool/type/list.h" /* generic list type */

    /* typedefs */
typedef struct sample_struct {
    uint16_t a;
    char* b;
} sample_struct;

    /* generic declarations */
list_declare(char);
list_declare(uint32_t);
list_declare(sample_struct);

    /* generic definitions */
list_define(char);
list_define(uint32_t);
list_define(sample_struct);

    /* functions */
/**
 * Tests list initialization
 * 
 * @return ST_FAIL on error,
 *          otherwise ST_OK 
 */
status_t test_list_init() {
    char_list_t a;
    list(uint32_t) b;
    sample_struct_list_t c;

    assertr_status(list_init(char)(&a, 5), ST_FAIL);
    assertr_equals(a.size, 5, ST_FAIL);
    assertr_status(uint32_t_list_init(&b, 0), ST_FAIL);
    assertr_equals(b.size, 0, ST_FAIL);
    assertr_status(sample_struct_list_init(&c, 10), ST_FAIL);
    assertr_not_null(c.data, ST_FAIL);
    
    list_free(char)(&a);
    uint32_t_list_free(&b);
    sample_struct_list_free(&c);

    return ST_OK;
}

/**
 * Tests list resizing
 * 
 * @return ST_FAIL on error,
 *          otherwise ST_OK
 */
status_t test_list_resize() {
    char_list_t a;
    assertr_status(list_init(char)(&a, 5), ST_FAIL);
    a.data[0] = 1;
    a.data[1] = -7;
    assertr_equals(a.size, 5, ST_FAIL);
    assertr_status(list_resize(char)(&a, 2), ST_FAIL);
    assertr_equals(a.size, 2, ST_FAIL);
    assertr_equals(a.data[0], 1, ST_FAIL);
    assertr_equals(a.data[1], -7, ST_FAIL);
    assertr_status(list_resize(char)(&a, 0), ST_FAIL);
    assertr_equals(a.size, 0, ST_FAIL);
    assertr_equals(a.data, NULL, ST_FAIL);

    sample_struct_list_t b;
    assertr_status(sample_struct_list_init(&b, 0), ST_FAIL);
    assertr_equals(b.data, NULL, ST_FAIL);
    assertr_status(sample_struct_list_resize(&b, 4), ST_FAIL);
    assertr_not_null(b.data, ST_FAIL);
    assertr_equals(b.size, 4, ST_FAIL);
    
    list_free(char)(&a);
    sample_struct_list_free(&b);

    return ST_OK;
}

    /* main function */
int main() {
    if (test_list_init() != ST_OK) {
        return EXIT_FAILURE;
    }
    if (test_list_resize() != ST_OK) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}