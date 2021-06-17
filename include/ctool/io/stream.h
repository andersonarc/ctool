/**
 * @file stream.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.3
 * @date 2021-06-17
 * 
 *  Stream abstraction for sockets.
 * 
 *  Smart wrappers for POSIX read() and write() functions.
 *  Streams should be opened and closed manually.
 */
    /* header guard */
#ifndef CTOOL_IO_STREAM_H
#define CTOOL_IO_STREAM_H

    /* includes */
#include <stdlib.h> /* size_t */
#include "ctool/status.h" /* return status */

    /* typedefs */
/**
 * Stream data type
 */
typedef int stream_t;

    /* functions */
/**
 * Writes specified amount of bytes to a stream.
 * 
 * If the implementation fails to write all bytes at once,
 * it keeps trying while at least 1 byte is written to the stream.
 * 
 * @param[in]  stream The stream
 * @param[in]  src    Data source
 * @param[in]  count  Number of bytes to write
 * 
 * @return ST_NET_FAIL if the operation fails, otherwise ST_OK
 */
status_t stream_write(stream_t stream, char* src, size_t count);

/**
 * Reads specified amount of bytes from a stream
 * 
 * If the implementation fails to read all bytes at once,
 * it keeps trying while at least 1 byte is read from the stream.
 * 
 * @param[in]  stream The stream
 * @param[out] dest   Data destination
 * @param[in]  count  Number of bytes to read
 * 
 * @return ST_NET_FAIL if the operation fails, otherwise ST_OK
 */
status_t stream_read(stream_t stream, char* dest, size_t count);

#endif /* CTOOL_IO_STREAM_H */