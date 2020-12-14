/**
 * @file nosigsegv_errno.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief checks errno for errors
 * @version 0.1
 * @date 2020-09-30
 */

    /* includes */
#include <errno.h>  /* errno    */
#include <assert.h> /* assert() */

    /* defines */
/**
 * @brief asserts that errno == 0
 */
#define chkerrno assert(!errno)