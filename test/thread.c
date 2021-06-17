/**
 * @file thread.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-06-02
 * 
 *  Task manager testing
 */
    /* includes */
#include <time.h>          /* sleep */
#include "ctool/thread.h"  /* task manager */
#include "ctool/assert/debug.h" /* debug assertions */
#include "ctool/log.h"     /* logging */

    /* constant presets */
#define CTOOL_TASK_THREADS 10000
#define CTOOL_TASK_INSTANCES 5
#define CTOOL_EXECUTIONS_PER_TASK 100000
#define CTOOL_TASK_COUNT (CTOOL_EXECUTIONS_PER_TASK * CTOOL_TASK_INSTANCES)

    /* time presets */
struct timespec mcs1 = { 0, 1000 };
struct timespec mcs100 = { 0, 1000 * 100 };
struct timespec ms1 = { 0, 1000 * 1000 };
struct timespec ms10 = { 0, 1000 * 1000 * 10 };

    /* task execution counters */
atomic_size_t ntask0 = 0;
atomic_size_t ntask1 = 0;
atomic_size_t ntask2 = 0;
atomic_size_t ntask3 = 0;
atomic_size_t ntask4 = 0;

    /* sample tasks */
task_output_t task0(task_input_t input) {
    nanosleep(&mcs1, NULL);
    ntask0++;
    return task_output_default;
}
task_output_t task1(task_input_t input) {
    nanosleep(&mcs100, NULL);
    ntask1++;
    return task_output_default;
}
task_output_t task2(task_input_t input) {
    nanosleep(&ms1, NULL);
    ntask2++;
    return task_output_default;
}
task_output_t task3(task_input_t input) {
    nanosleep(&ms10, NULL);
    ntask3++;
    return task_output_default;
}
task_output_t task4(task_input_t input) {
    nanosleep(&ms10, NULL);
    ntask4++;
    return task_output_default;
}

    /* assistant functions */
task_function_t get_task(size_t n) {
    switch (n) {
        case 0:
            return task0;
        case 1:
            return task1;
        case 2:
            return task2;
        case 3:
            return task3;
        case 4:
            return task4;
        default:
            logfe("failed to find a task for index %zu (max %d)", n, CTOOL_TASK_INSTANCES);
    }
}

size_t get_counter(size_t n) {
    switch (n) {
        case 0:
            return ntask0;
        case 1:
            return ntask1;
        case 2:
            return ntask2;
        case 3:
            return ntask3;
        case 4:
            return ntask4;
        default:
            logfe("failed to find a counter for index %zu (max %d)", n, CTOOL_TASK_INSTANCES);
    }
}

    /* main function */
int main() {
    status_t status = ST_OK;
    task_manager_t manager;
    task_list_t tasks;

    logi("initializing task list");
    status = task_list_init(&tasks, CTOOL_TASK_COUNT);
    assertdc_status(status, "failed to create task list");
    for (size_t i = 0; i < CTOOL_TASK_COUNT; i += CTOOL_TASK_INSTANCES) {
        for (size_t j = 0; j < CTOOL_TASK_INSTANCES; j += 1) {
            task_t* task = &tasks.data[i + j];
            task->function = get_task(j);
            task->input = NULL;
        }
    }

    logi("initializing task manager");
    logi("starting %d tasks on %d threads", CTOOL_TASK_COUNT, CTOOL_TASK_THREADS);
    status = task_manager_create_run(&manager, tasks, CTOOL_TASK_THREADS);
    assertdc_status(status, "failed to initialize task manager");

    logi("waiting for all tasks to finish");
    task_manager_await(&manager);

    logi("checking task counters");
    for (size_t i = 0; i < CTOOL_TASK_INSTANCES; i++) {
        size_t counter = get_counter(i);
        logi("task %zu: [%zu | %d]", i, counter, CTOOL_EXECUTIONS_PER_TASK);
        assertd_equals(counter, CTOOL_EXECUTIONS_PER_TASK);
    }

    logi("performing cleanup");
    task_manager_delete(&manager);
    return 0;
}