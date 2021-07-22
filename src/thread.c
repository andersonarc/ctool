/**
 * @file thread.c
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.2
 * @date 2021-05-17
 *  
 *  An implementation of a thread pool pattern for multi-threaded task execution
 *  
 *  If `CTOOL_THREAD_USE_POSIX` is defined, pthreads will be preferred over
 *  C11 threads for thread control. Thread safety is ensured by atomic index 
 *  and state, and verified by testing.
 */
    /* includes */
#include "ctool/thread.h" /* this */
#include <time.h> /* sleep */
#include "ctool/assert/runtime.h" /* runtime assertions */
#include "ctool/iteration.h" /* range iteration */

    /* static content */
/**
 * Default time for waiting (100 milliseconds)
 */
const struct timespec idle_time = { 0, 100000000 };

    /* defines */
/**
 * Initializes a thread instance and
 * executes a task list on it
 * 
 * @param[in] thread Pointer to the thread
 * @param[in] tasks  The task list
 * 
 * @return 0 if everything is OK
 */
#ifdef CTOOL_THREAD_USE_POSIX
    #define thread_initialize(thread, tasks) pthread_create(thread, NULL, (task_function_t) &task_thread_main, tasks)
#else
    #define thread_initialize(thread, tasks) thrd_create(&manager->pool.data[i], (task_function_t) &task_thread_main, tasks)
#endif

    /* functions */
/**
 * Executes a task list concurrently with
 * other threads
 * 
 * @param[in] tasks The task list
 * 
 * @return Default task output
 */
task_output_t task_thread_main(task_list_t* tasks) {
    while (tasks->status != CTOOL_TASK_LIST_STOPPED) {
        /* wait for new tasks */
        if (tasks->status == CTOOL_TASK_LIST_WAITING) {
            nanosleep(&idle_time, NULL);
        }

        /* get a task index safely */
        size_t index = atomic_fetch_add(&tasks->index, 1);
        if (index >= tasks->size) {
            /* out of tasks, go to sleep */
            tasks->status = CTOOL_TASK_LIST_WAITING;
            continue;
        }

        /* execute a task */
        task_t current = tasks->data[index];
        current.function(current.input);
    }
    return task_output_default;
}

/**
 * Creates a new task manager with specified
 * number of threads in a thread pool
 * 
 * @param[in] manager The task manager
 * @param[in] threads The number of threads
 * 
 * @return ST_ALLOC_FAIL if an allocation fails, 
 *         ST_FAIL if thread initialization fails,
 *          otherwise ST_OK
 */
status_t task_manager_create(task_manager_t* manager, size_t threads) {
    manager->pool.size = threads;
    assertr_malloc(manager->pool.data, sizeof(thread_t) * threads, thread_t*)
    manager->tasks.status = CTOOL_TASK_LIST_WAITING;
    manager->tasks.data = NULL;
    manager->tasks.index = 0;
    manager->tasks.size = 0;
    iterate_array(i, threads) {
        assertr_zero(thread_initialize(&manager->pool.data[i], &manager->tasks), 
            ST_FAIL);
    }
    return ST_OK;
}

/**
 * Creates a new task manager with specified
 * number of threads in a thread pool and executes
 * a list of tasks on it
 * 
 * @param[in] manager The task manager
 * @param[in] tasks   The task list
 * @param[in] threads The number of threads
 * 
 * @return ST_ALLOC_FAIL if an allocation fails, 
 *         ST_FAIL if thread initialization fails,
 *          otherwise ST_OK
 */
status_t task_manager_create_run(task_manager_t* manager, task_list_t tasks, size_t threads) {
    manager->pool.size = threads;
    assertr_malloc(manager->pool.data, sizeof(thread_t) * threads, thread_t*)
    manager->tasks = tasks;
    iterate_array(i, threads) {
        assertr_zero(thread_initialize(&manager->pool.data[i], &manager->tasks), 
            ST_FAIL);
    }
    return ST_OK;
}

/**
 * Deletes a task manager
 * 
 * The task list is freed automatically.
 * 
 * @param[in] manager The task manager
 */
void task_manager_delete(task_manager_t* manager) {
    manager->tasks.status = CTOOL_TASK_LIST_STOPPED;
    free(manager->pool.data);
    task_list_free(&manager->tasks);
}

/**
 * Submits a task list to a task manager
 * 
 * Previous task list is freed automatically.
 * 
 * @param[in] manager The task manager
 * @param[in] tasks   The task list
 * 
 * @return ST_FAIL if previous task list is still running,
 *          otherwise ST_OK
 */
status_t task_manager_submit(task_manager_t* manager, task_list_t tasks) {
    assertrc_false(manager->tasks.status == CTOOL_TASK_LIST_RUNNING, ST_FAIL, 
        "previous tasks haven't completed yet, use task_manager_await() to wait for them")
    task_list_free(&manager->tasks);
    manager->tasks = tasks;
    return ST_OK;
}

/**
 * Waits for a task manager to finish all tasks
 * 
 * @param[in] manager The task manager
 */
void task_manager_await(task_manager_t* manager) {
    while (manager->tasks.status == CTOOL_TASK_LIST_RUNNING) {
        nanosleep(&idle_time, NULL);
    }
}

/**
 * Initializes a task list and allocates memory for it
 * 
 * @param[in] tasks The task list
 * @param[in] size  Tasks count
 * 
 * @return ST_ALLOC_FAIL if an allocation fails, otherwise ST_OK
 */
status_t task_list_init(task_list_t* tasks, size_t size) {
    tasks->status = CTOOL_TASK_LIST_RUNNING;
    assertr_malloc(tasks->data, sizeof(task_t) * size, task_t*);
    tasks->size = size;
    tasks->index = 0;
    return ST_OK;
}