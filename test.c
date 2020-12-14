/**
 * @file test.c
 * @author andersonarc@github
 * @brief c library for safety and segmentation fault prevention test implementation
 * @version 0.1
 * @date 2020-09-30
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//todo errno checking
//todo safe calls with notnull assert
//todo assert return checked value
//todo assert_not_null?
#include "csafe_notnull.h"
#include "csafe_safecall.h"

long int file_size(notnull FILE* file)
{ not_null(file);
    long int old = ftell(file);
    fseek(file, 0, SEEK_END);
    long int current;
    current = ftell(file);
    fseek(file, old, SEEK_SET);
    return current;
}

notnull char* read_file(notnull FILE* file) 
{ not_null(file);
    long int size = file_size(file);
    notnull char* buffer;
    safecall_set(buffer, malloc(size + 1));
    fread(buffer, 1, size, file);
    buffer[size] = 0;
    return buffer;
}

int main(int argc, const char* argv[]) {
    printf("libnss: init\nmain: read %s\n", argc == 1 ? argv[0] : argv[1]);
    notnull char* read = read_file(fopen(argc == 1 ? argv[0] : argv[1], "r"));
    printf("main: read of size %d successful\n", strlen(read));
    return 0;
}
