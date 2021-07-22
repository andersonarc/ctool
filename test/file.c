/**
 * @file file.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-05
 * 
 *  Tests for file parsing utilities
 */
    /* includes */
#include <string.h> /* string functions */
#include <unistd.h> /* ssize_t */
#include "ctool/file.h" /* file utilities */
#include "ctool/assert/runtime.h" /* runtime assertions */

    /* assistant functions */
/**
 * Creates a temporary file and fills it with text
 * 
 * @param[in]  text   The text
 * @param[out] result Pointer to the file variable
 * 
 * @return ST_FILE_FAIL if a file operation fails,
 *          otherwise ST_OK 
 */
status_t create_file(const char* text, FILE** result) {
    assertr_not_null((*result = tmpfile()), ST_FILE_FAIL);
    size_t length = strlen(text);
    assertr_equals(fwrite(text, 1, length, *result), length, ST_FILE_FAIL);
    rewind(*result);
    assertr_errno(ST_FILE_FAIL);
    return ST_OK;
}

/**
 * Tests line information for generic
 * parameters
 * 
 * @param[in] text  Array of lines
 * @param[in] lines The number of lines
 * @param[in] max   Max length of a line
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */ 
status_t test_file_line_info(char** text, size_t lines, size_t max) {
    /* create a file and fill it with text */
    FILE* file;
    char* data;
    assertr_malloc(data, (max * lines) + 1, char*);
    size_t character = 0;
    for (int i = 0; i < lines; i++) {
        size_t length = strlen(text[i]);
        for (int j = 0; j < length; j++) {
            /* move the character into data */
            data[character] = text[i][j];
            character++;
        }
    }
    data[character] = 0;
    assertr_status(create_file(data, &file), ST_FAIL);

    /* get file line info */
    file_line_info_t info;
    assertr_status(file_line_info(file, &info), ST_FAIL);

    /* check file line info */
    assertr_equals(info.count, lines, ST_FAIL);
    assertr_equals(info.max, max, ST_FAIL);

    /* reconstruct and validate text based on line info */
    char* buffer;
    assertr_malloc(buffer, info.max + 1 /* '\0' */, char*);
    for (int i = 0; i < info.count; i++) {
        assertr_not_null(fgets(buffer, info.max + 1 /* '\0' */, file), ST_FAIL);
        assertr_zero(strcmp(text[i], buffer), ST_FAIL);
    }

    /* free resources */
    fclose(file);
    free(buffer);
    free(data);

    return ST_OK;
}

    /* functions */
/**
 * Tests if file size information
 * is computed correctly
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_file_size() {
    /* create a file and fill it with 100 'a' letters */
    FILE* a;
    char string[101];
    for (int i = 0; i < 100; i++) {
        string[i] = 'a';
    }
    string[100] = 0;
    assertr_status(create_file(string, &a), ST_FAIL);

    /* check size */
    ssize_t size = -1;
    assertr_status(file_size(a, (size_t*) &size), ST_FAIL);
    assertr_equals(size, 100, ST_FAIL);

    /* create a new empty file */
    FILE* b;
    assertr_status(create_file("", &b), ST_FAIL);
    
    /* check size */
    size = -1;
    assertr_status(file_size(b, (size_t*) &size), ST_FAIL);
    assertr_equals(size, 0, ST_FAIL);

    /* free resources */
    fclose(a);
    fclose(b);

    return ST_OK;
}

/**
 * Tests if file line information 
 * is computed correctly if each
 * line of the file ends with a '\n'
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_file_line_info_1() {
    char* text[] = { "Lorem\n", "ipsum\n", "dolor\n", "sit\n", "amet\n", "consectetur\n", 
                        "adipiscing\n", "elit\n", "sed\n", "do\n", "eiusmod\n", "tempor\n", 
                        "incididunt\n", "ut\n", "labore\n", "et\n", "dolore\n", "magna\n", "aliqua\n" };
    return test_file_line_info(text, 19, 12);
}

/**
 * Tests if file line information 
 * is computed correctly if each
 * line of the file ends with a '\n',
 * except for the last
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_file_line_info_2() {
    char* text[] = { "Lorem\n", "ipsum\n", "dolor\n", "sit\n", "amet\n", "consectetur\n", 
                        "adipiscing\n", "elit\n", "sed\n", "do\n", "eiusmod\n", "tempor\n", 
                        "incididunt\n", "ut\n", "labore\n", "et\n", "dolore\n", "magna\n", "aliqua" };
    return test_file_line_info(text, 19, 12);
}


/**
 * Tests if file line information 
 * is computed correctly if each
 * line of the file ends with a '\n',
 * except for the last, which ends
 * with '\n\n'
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_file_line_info_3() {
    char* text[] = { "Lorem\n", "ipsum\n", "dolor\n", "sit\n", "amet\n", "consectetur\n", 
                        "adipiscing\n", "elit\n", "sed\n", "do\n", "eiusmod\n", "tempor\n", 
                        "incididunt\n", "ut\n", "labore\n", "et\n", "dolore\n", "magna\n", "aliqua\n", "\n" };
    return test_file_line_info(text, 20, 12);
}

/**
 * Tests if file line information 
 * is computed correctly if each
 * line of the file ends with a '\n',
 * except for one, which ends
 * with '\n\n'
 * 
 * @return ST_FAIL if an assertion failed,
 *          otherwise ST_OK 
 */
status_t test_file_line_info_4() {
    char* text[] = { "Lorem\n", "ipsum\n", "dolor\n", "sit\n", "amet\n", "consectetur\n", 
                        "adipiscing\n", "elit\n", "sed\n", "\n", "do\n", "eiusmod\n", "tempor\n", 
                        "incididunt\n", "ut\n", "labore\n", "et\n", "dolore\n", "magna\n", "aliqua\n" };
    return test_file_line_info(text, 20, 12);
}

    /* main function */
int main() {
    if (test_file_size() != ST_OK) {
        return 1;
    }
    if (test_file_line_info_1() != ST_OK) {
        return 1;
    }
    if (test_file_line_info_2() != ST_OK) {
        return 1;
    }
    if (test_file_line_info_3() != ST_OK) {
        return 1;
    }
    if (test_file_line_info_4() != ST_OK) {
        return 1;
    }
    return 0;
}