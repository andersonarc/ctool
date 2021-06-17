/**
 * @file _internal.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-14
 * 
 *  Logging system internal code.
 * 
 *  Functions that format log messages and
 *  print them to stdout or stderr.
 */
    /* header guard */
#ifndef CTOOL_LOG__INTERNAL_H
#define CTOOL_LOG__INTERNAL_H

    /* includes */
#include <stdio.h> /* print */
#include <stdlib.h> /* exit */

    /* defines */
/**
 * Formats a message for logging with a
 * prefix and a suffix.
 * 
 * @param[in] prefix The prefix
 * @param[in] suffix The suffix
 * @param[in] message The message
 */
#define _ctool_log_message(prefix, suffix, message) prefix " [" suffix "] %s: " message

/**
 * Prints a message with formatting
 * paramters, a prefix and a suffix to stdout.
 * 
 * @param[in] prefix The prefix
 * @param[in] suffix The suffix
 * @param[in] message The message
 */
#define _ctool_log_print_info(prefix, suffix, message, ...) printf(_ctool_log_message(prefix, suffix, message) "\n", __func__, ##__VA_ARGS__)

/**
 * Prints a message with formatting
 * paramters, a prefix and a suffix to stderr.
 * 
 * @param[in] prefix The prefix
 * @param[in] suffix The suffix
 * @param[in] message The message
 */
#define _ctool_log_print_error(prefix, suffix, message, ...) fprintf(stderr, _ctool_log_message(prefix, suffix, message) "\n", __func__, ##__VA_ARGS__); _ctool_log_perrno()

/**
 * Prints a message with formatting
 * paramters, a prefix and a suffix to stderr,
 * then makes the program exit with code 1.
 * 
 * @param[in] prefix The prefix
 * @param[in] suffix The suffix
 * @param[in] message The message
 */
#define _ctool_log_print_fatal(prefix, suffix, message, ...) fprintf(stderr, _ctool_log_message(prefix, suffix, message) "\n", __func__, ##__VA_ARGS__); _ctool_log_perrno(); exit(1)

    /* functions */
/**
 * Prints errno value if it indicates an error,
 * otherwise does nothing.
 */
void _ctool_log_perrno();

#endif /* CTOOL_LOG__INTERNAL_H */