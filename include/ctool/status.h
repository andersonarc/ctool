/**
 * @file status.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.3
 * @date 2021-02-15
 * 
 *  Return status for functions
 * 
 *  Type definition of an enum with codes
 *  for common function exit cases, such as
 *  memory allocation failure or file access
 *  failure.
 */
    /* header guard */
#ifndef CTOOL_STATUS_H
#define CTOOL_STATUS_H

    /* typedefs */
/**
 * Return status structure
**/
typedef enum status_t {
    ST_OK,        /* Success                                                */
    ST_FAIL,      /* General failure                                        */
    ST_FILE_FAIL, /* File access failure (fopen returned NULL, etc.)        */
    ST_ALLOC_FAIL, /* Memory allocation failure (malloc returned NULL, etc.) */
    ST_NET_FAIL,  /* Network failure (cannot open a socket, etc.)           */
    ST_BAD_ARG     /* Bad argument passed to a function                      */
} status_t;

#endif /* CTOOL_STATUS_H */