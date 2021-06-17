/**
 * @file _internal.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-15
 * 
 *  Logging system implementation
 */
    /* includes */
#include "ctool/log/_internal.h" /* this */
#include <errno.h> /* errno */
#include <string.h> /* strerror */

    /* functions */
/**
 * Print errno value if it indicates an error.
 */
void _ctool_log_perrno() {
    int value = errno;
    if (value != 0) {
        fprintf(stderr, "[ERRNO] %s", strerror(value));
    }
}