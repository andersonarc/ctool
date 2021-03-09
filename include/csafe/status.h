/**
 * @file status.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief return status for functions
 * @version 0.1
 * @date 2021-02-15
 */
    /* header guard */
#ifndef CSAFE_STATUS_H
#define CSAFE_STATUS_H

    /* typedefs */
/**
 * @brief status structure
**/
typedef enum status_t {
    ST_OK, ST_FAIL, ST_FILE_FAIL, ST_ALLOC_FAIL, ST_NET_FAIL, ST_BAD_ARG
} status_t;

#endif /* CSAFE_STATUS_H */