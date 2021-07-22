/**
 * @file buffered.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.6
 * @date 2021-02-08
 * 
 *  Buffered stream IO system
 * 
 *  An abstraction built on top of a stream wrapper, 
 *  which allows you to write and read data from a
 *  stream using an internal buffer, where you can
 *  accumulate that data with bstream_push macro.
 */
    /* header guard */
#ifndef CTOOL_IO_BUFFER_H
#define CTOOL_IO_BUFFER_H

    /* includes */
#include <stdlib.h> /* memory functions and size_t */
#include "ctool/io/stream.h" /* stream io */
#include "ctool/assert/runtime.h" /* runtime assertions */
#include "ctool/iteration.h" /* index_t */

    /* typedefs */
/**
 * Buffered stream structure
 */
typedef struct buffered_stream_t {
    size_t size;
    index_t index;
    stream_t stream;
    char* data;
} buffered_stream_t;

/**
 * Shorthand alias for the buffered stream data type
 */
typedef buffered_stream_t bstream_t;

    /* functions */
/**
 * Returns a pointer to the current position in a buffered stream
 * 
 * @warning Buffer index should be increased after modification 
 *              with bstream_increase()
 * 
 * @warning Manual usage of this function is unrecommended,
 *              prefer bstream_push macro instead
 * 
 * @param[in] bstream Pointer to the buffered stream structure
 * 
 * @return Pointer to the current position in the buffer
 */
static inline char* bstream_position(bstream_t* bstream) {
    return &bstream->data[bstream->index];
}

/**
 * Increases the index of a buffered stream
 * 
 * @warning Manual usage of this function is unrecommended,
 *              prefer bstream_push macro instead
 * 
 * @param[in] bstream Pointer to the buffered stream structure
 * @param[in] count   Number of bytes to add for index
 */
static inline void bstream_increase(bstream_t* bstream, size_t count) {
    bstream->index += count;
}

/**
 * Pushes a primitive value to the buffer of
 * a buffered stream
 * 
 * @param[in] bstream Pointer to the buffered stream structure
 * @param[in] value   Primitive value (int, char, ...) that must not be a pointer
 */
#define bstream_push_primitive(bstream, value) \
    bstream_position(bstream) = value;         \
    bstream_increase(bstream, sizeof(value));

/**
 * Pushes a single-dimensional array of primitive values
 * to the buffer of a buffered stream
 * 
 * @param[in] bstream Pointer to the buffered stream structure
 * @param[in] array   Array of primitive values (int, char, ...) which must not be pointers
 * @param[in] size    Size of the array (number of elements)
 */
#define bstream_push_array(bstream, array, size)                     \
    memcpy(bstream_position(bstream), array, size * sizeof(*array)); \
    bstream_increase(size * sizeof(*array));

/**
 * Binds a stream to a buffered stream
 * 
 * @warning Do not forget to close the stream after usage
 *
 * @param[in] bstream Pointer to the buffered stream structure
 * @param[in] stream  The stream
 */
static inline void bstream_bind(bstream_t* bstream, stream_t stream) {
    bstream->stream = stream;
}

/**
 * Allocates a buffer for a buffered stream
 * 
 * @warning Do not forget to free the buffer after usage
 *
 * @param[in] bstream Pointer to the buffered stream structure
 * @param[in] size    Buffer size
 * 
 * @return ST_ALLOC_FAIL if an allocation fails, otherwise ST_OK
 */
static inline status_t bstream_allocate(bstream_t* bstream, size_t size) {
    assertr_malloc(bstream->data, size, char*)
    bstream->size = size;
    bstream->index = 0;
}

/**
 * Assigns an already allocated buffer to a 
 * buffered stream
 *
 * @param[in] bstream Pointer to the buffered stream structure
 * @param[in] buffer  Pointer to the buffer
 * @param[in] size    Buffer size
 */
static inline void bstream_assign(bstream_t* bstream, char* buffer, size_t size) {
    bstream->data = buffer;
    bstream->size = size;
}

/**
 * Fills the buffer of a buffered stream with data 
 * from a previously bound stream
 * 
 * @param[in] bstream Pointer to the buffered stream structure
 * 
 * @return ST_NET_FAIL if the operation fails, otherwise ST_OK
 */
static inline status_t bstream_read(bstream_t* bstream) {
    return stream_read(bstream->stream, bstream->data, bstream->size);
}

/**
 * Frees allocated memory for a buffered stream
 *
 * @param[in] bstream Pointer to the buffered stream structure
 */
static inline void bstream_free(bstream_t* bstream) {
    free(bstream->data);
}

/**
 * Writes the buffer of a buffered stream
 * into a previously bound stream
 * 
 * @param[in] bstream Pointer to the buffered stream structure
 * 
 * @return ST_NET_FAIL if the operation fails, otherwise ST_OK
 */
static inline status_t bstream_write(bstream_t* buffer) {
    stream_write(buffer->stream, buffer->data, buffer->size);
}

#endif /* CTOOL_IO_BUFFER_H */