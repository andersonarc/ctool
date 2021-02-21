/**
 * @file main.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @brief csafe testing file
 * @version 0.1
 * @date 2021-02-21
 */
    /* includes */
#include "csafe/assertr.h" /* runtime assertions */
#include "csafe/assertd.h" /* debug assertions */
#include "csafe/log.h"     /* logging */
#include "csafe/logf.h"    /* formatted logging */
#include "csafe/safecall.h" /* safe calls */

#include <stdlib.h>        /* memory allocation */

    /* functions */
/**
 * @brief utility function
 */
char* utility_return(char* variable) {
    return variable;
}

/**
 * @brief test runtime assertions
 */
status_t test_assertr() {
    char* test;
    assertr_not_null_function_set("test_assertr", test, malloc(sizeof(char)), ST_ALLOC_FAIL);
    assertr_not_null("test_assertr", &test, ST_ALLOC_FAIL);
    assertr_not_null_function("test_assertr", utility_return(test), ST_ALLOC_FAIL);
    free(test);
    assertr_equals("test_assertr", 1, 1, ST_FAIL);
    assertr_equals_custom("test_assertr", 1, 1, "message", ST_FAIL);
    assertr_true("test_assertr", 1 == 1, ST_FAIL);
    assertr_true_custom("test_assertr", 1 == 1, "message", ST_FAIL);
    assertr_false("test_assertr", 1 != 1, ST_FAIL);
    assertr_false_custom("test_assertr", 1 != 1, "message", ST_FAIL);
    assertr_errno("test_assertr", ST_FAIL);

    assertr_false("test_assertr", true, ST_FAIL);

    return ST_OK;
}

/**
 * @brief test debug assertions
 */
status_t test_assertd() {
    char* test;
    assertd_not_null_function_set("test_assertd", test, malloc(sizeof(char)));
    assertd_not_null("test_assertd", &test);
    assertd_not_null_function("test_assertd", utility_return(test));
    free(test);
    assertd_equals("test_assertd", 1, 1);
    assertd_equals_custom("test_assertd", 1, 1, "message");
    assertd_true("test_assertd", 1 == 1);
    assertd_true_custom("test_assertd", 1 == 1, "message");
    assertd_false("test_assertd", 1 != 1);
    assertd_false_custom("test_assertd", 1 != 1, "message");
    assertd_errno("test_assertd");
    return ST_OK;
}

/**
 * @brief test logging 
 */
status_t test_log() {
    log_sp("test_log", "log_sp", "suffix", "prefix ");
    log_s("test_log", "log_s", "suffix");
    logd("test_log", "logd");
    logi("test_log", "logi");
    logw("test_log", "logw");
    loge("test_log", "loge");
    //logfe("test_log", "logfe");
    return ST_OK;
}

/**
 * @brief test formatted logging 
 */
status_t test_log_f() {
    log_sp_f("test_log", "log_sp_f %d", "suffix", "prefix ", 1);
    log_s_f("test_log", "log_s_f %d", "suffix", 2);
    logd_f("test_log", "logd_f %d", 3);
    logi_f("test_log", "logi_f %d", 4);
    logw_f("test_log", "logw_f %d", 5);
    loge_f("test_log", "loge_f %d", 6);
    //logfe_f("test_log", "logfe_f %d", 7);
    return ST_OK;
}

/**
 * @brief test safe calls
 */
status_t test_safecall() {
    char* test;
    scr("test_safecall", test, malloc(sizeof(char*)), ST_ALLOC_FAIL);
    scr_call("test_safecall", utility_return(test), ST_ALLOC_FAIL);
    free(test);
    scd("test_safecall", test, malloc(sizeof(char*)));
    scd_call("test_safecall", utility_return(test));
    free(test);
    return ST_OK;
}

/**
 * @brief main test function
 */
int main() {
    test_log();
    test_log_f();
    test_assertd();
    test_assertr();
    test_safecall();
}