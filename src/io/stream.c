/**
 * @file stream.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.4
 * @date 2021-06-17
 * 
 *  Stream abstraction for sockets.
 * 
 *  Smart wrappers for POSIX read() and write() functions.
 *  Streams should be opened and closed manually.
 */
    /* includes */
#include "ctool/io/stream.h" /* this */
#include <unistd.h> /* socket io */
#include "ctool/assert/runtime.h" /* runtime assertions */

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
status_t stream_write(stream_t stream, char* src, size_t count) {
    ssize_t written = write(stream, src, count);
    assertr_false(written < 0, ST_NET_FAIL);
    if (written == count) {
        return ST_OK;
    } else {
        /* write remaining bytes */
        while (written < count) {
            ssize_t written_now = write(stream, &src[written], count - written);
            /* at least 1 byte should be written */
            assertr_false(written_now <= 0, ST_NET_FAIL);
            written += written_now;
        }
    }
}

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
status_t stream_read(stream_t stream, char* dest, size_t count) {
    ssize_t received = read(stream, dest, count);
    assertr_false(received < 0, ST_NET_FAIL);
    if (received == count) {
        return ST_OK;
    } else {
        /* read remaining bytes */
        while (received < count) {
            ssize_t received_now = read(stream, &dest[received], count - received);
            /* at least 1 byte should be read */
            assertr_false(received_now <= 0, ST_NET_FAIL);
            received += received_now;
        }
    }
}