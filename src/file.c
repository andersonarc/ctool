/**
 * @file file.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-03
 * 
 *  Helper functions for reading and
 *  interacting with files
 */
    /* includes */
#include "ctool/file.h" /* this */
#include "ctool/assert/runtime.h" /* runtime assertions */

    /* functions */
/**
 * Calculates the size of a file
 * 
 * @param[in]  file The file
 * @param[out] size Variable for storing the result
 * 
 * @return ST_FILE_FAIL if a file operation failed,
 *          otherwise ST_OK
 */
status_t file_size(FILE* file, size_t* size) {
    long position = ftell(file);
    assertr_not_equals(position, -1L, ST_FILE_FAIL);

    assertr_zero(fseek(file, 0, SEEK_END),
        ST_FILE_FAIL);

    *size = ftell(file);
    assertr_not_equals(*size, -1L, ST_FILE_FAIL);

    assertr_zero(fseek(file, position, SEEK_SET),
        ST_FILE_FAIL);

    return ST_OK;
}

/**
 * Counts the number of lines in a file
 * and maximum length of a line (including '\n', but excluding '\0',
 * so this value should be incremented by 1 for allocation)
 * 
 * @param[in]  file The file
 * @param[out] info File info structure for storing the result
 * 
 * @return ST_FILE_FAIL if a file operation failed,
 *          otherwise ST_OK
 */
status_t file_line_info(FILE* file, file_line_info_t* info) {
    size_t char_counter = 0; 
    char previous = 0;
    char current;
           
    info->count = 0;
    info->max = 0;

    /* previous file position */
    size_t position = ftell(file);  
    assertr_not_equals(position, -1L, ST_FILE_FAIL);

    /* iterate file characters */
    while ((current = fgetc(file)) != EOF) {
        if (current == '\n') {
            /* increment line counter */
            info->count++;
            if (char_counter > info->max) {
                /* new max line size */
                info->max = char_counter;
            }
            /* reset char counter */
            char_counter = 0;
        } else {
            /* line hasn't ended yet */
            char_counter++;
        }
        previous = current;
    }
    assertr_errno(ST_FILE_FAIL);

    /* fix for files without '\n' at the end */
    if (previous != '\n') {
        info->count++;
    }

    /* fix for '\n' at the end of a line */
    info->max++;

    /* restore file position */
    assertr_zero(fseek(file, position, SEEK_SET),
        ST_FILE_FAIL);

    /* success */
    return ST_OK;
}