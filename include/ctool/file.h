/**
 * @file file.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-19
 * 
 *  Helper functions for reading and
 *  interacting with files
 */
    /* header guard */
#ifndef CTOOL_FILE_H
#define CTOOL_FILE_H

    /* includes */
#include <stdio.h> /* file operations */
#include "ctool/status.h" /* return status */

    /* typedefs */
/**
 * File line information
 */
typedef struct file_line_info_t {
    size_t count;
    size_t max;
} file_line_info_t;

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
status_t file_size(FILE* file, size_t* size);

/**
 * Counts the number of lines in a file
 * and maximum length of a line (excluding '\n' and '\0',
 * so this value should be incremented by 2 for allocation)
 * 
 * @param[in]  file The file
 * @param[out] info File info structure for storing the result
 * 
 * @return ST_FILE_FAIL if a file operation failed,
 *          otherwise ST_OK
 */
status_t file_line_info(FILE* file, file_line_info_t* info);

#endif /* CTOOL_FILE_H */