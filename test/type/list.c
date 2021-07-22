/**
 * @file list.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-05
 * 
 *  Tests for the generic list type
 * 
 *  This is a pure compilation test.
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

    /* main function */
int main() {
    return 0;
}