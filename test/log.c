/**
 * @file log.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-15
 * 
 *  Tests for logging system
 * 
 *  These are mostly compilation tests, because
 *  we can't test for the logging output to be
 *  correct.
 */
    /* includes */
#include "ctool/log.h" /* logging */

    /* functions */
int main() {
    logi("%d: info logging test passed", 1);
    logw("2: warning logging test passed");
    loge("%s: error logging test passed", "3");
    logd("4: debug logging test passed");
    return EXIT_SUCCESS;
}