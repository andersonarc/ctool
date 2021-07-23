/**
 * @file optional.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-05
 * 
 *  Tests for the generic optional type
 * 
 *  This is a pure compilation test.
 */
    /* includes */
#include <stdint.h> /* int types */
#include <stdlib.h> /* EXIT_SUCCESS */
#include "ctool/type/optional.h" /* generic optional type */

    /* typedefs */
typedef struct sample_struct {
    uint16_t a;
    char* b;
} sample_struct;

    /* generic declarations */
optional_declare(char);
optional_declare(uint32_t);
optional_declare(sample_struct);

    /* main function */
int main() {
    return EXIT_SUCCESS;
}