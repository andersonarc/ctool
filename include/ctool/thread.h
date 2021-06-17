/**
 * @file thread.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.2
 * @date 2021-05-17
 * 
 *  An implementation of a thread pool pattern for multi-threaded task execution.
 *  
 *  If `CTOOL_THREAD_USE_POSIX` is defined, pthreads will be preferred over
 *  C11 threads for thread control. Thread safety is ensured by atomic index 
 *  and state, and verified by testing.
 * 
 *  @todo Different task execution modes (e.g. one function with multiple inputs)
 */
    /* header guard */
#ifndef CTOOL_THREAD_H
#define CTOOL_THREAD_H

    /* includes */
#include <stdatomic.h> /* atomic types */

#ifdef CTOOL_THREAD_USE_POSIX
    #include <pthread.h> /* posix threads api */
#else
    #include <threads.h> /* C11 threads api */
#endif

#include "ctool/status.h" /* return status */

    /* typedefs */
/**
 * Input value for a task function.
 */
typedef void* task_input_t;

/**
 * Output value for a task function.
 */
#ifdef CTOOL_THREAD_USE_POSIX
    typedef void* task_output_t;
#else
    typedef int task_output_t;
#endif

/**
 * Default task output.
 */
#ifdef CTOOL_THREAD_USE_POSIX 
    #define task_output_default NULL
#else
    #define task_output_default 0
#endif

/**
 * Default task input.
 */
#define task_input_default NULL

/**
 * Task function type.
 */
typedef task_output_t(*task_function_t)(task_input_t);

/**
 * Task structure.
 */
typedef struct task_t {
    task_function_t function;
    task_input_t input;
} task_t;

/**
 * Task list execution status.
 */
typedef enum task_list_status_t {
    CTOOL_TASK_LIST_WAITING, CTOOL_TASK_LIST_STOPPED, CTOOL_TASK_LIST_RUNNING
} task_list_status_t;

/**
 * Task list structure.
 */
typedef struct task_list_t {
    atomic_int status;
    atomic_size_t index;
    size_t size;
    task_t* data;
} task_list_t;

/**
 * Thread type.
 */
#ifdef CTOOL_THREAD_USE_POSIX 
    typedef pthread_t thread_t;
#else
    typedef thrd_t thread_t;
#endif


/**
 * Thread pool structure.
 */
typedef struct thread_pool_t {
    size_t size;
    thread_t* data;
} thread_pool_t;

/**
 * Task manager structure.
 */
typedef struct task_manager_t {
    thread_pool_t pool;
    task_list_t tasks;
} task_manager_t;

    /* functions */
/**
 * Creates a new task manager with specified
 * number of threads in a thread pool.
 * 
 * @param[in] manager The task manager
 * @param[in] threads The number of threads
 * 
 * @return ST_ALLOC_FAIL if an allocation fails, 
 *         ST_FAIL if thread initialization fails,
 *          otherwise ST_OK
 */
status_t task_manager_create(task_manager_t* manager, size_t threads);

/**
 * Creates a new task manager with specified
 * number of threads in a thread pool and executes
 * a list of tasks on it.
 * 
 * @param[in] manager The task manager
 * @param[in] tasks   The task list
 * @param[in] threads The number of threads
 * 
 * @return ST_ALLOC_FAIL if an allocation fails, 
 *         ST_FAIL if thread initialization fails,
 *          otherwise ST_OK
 */
status_t task_manager_create_run(task_manager_t* manager, task_list_t tasks, size_t threads);

/**
 * Deletes a task manager and frees it's task list.
 * 
 * @param[in] manager The task manager
 */
void task_manager_delete(task_manager_t* manager);

/**
 * Submits a task list to a task manager.
 * 
 * Previous task list is freed automatically.
 * 
 * @param[in] manager The task manager
 * @param[in] tasks   The task list
 * 
 * @return ST_FAIL if previous task list is still running,
 *          otherwise ST_OK
 */
status_t task_manager_submit(task_manager_t* manager, task_list_t tasks);

/**
 * Waits for a task manager to finish all tasks.
 * 
 * @param manager The task manager
 */
void task_manager_await(task_manager_t* manager);

/**
 * Initializes a task list and allocates memory for it.
 * 
 * @param tasks The task list
 * @param size  Tasks count
 * 
 * @return ST_ALLOC_FAIL if an allocation fails, otherwise ST_OK
 */
status_t task_list_init(task_list_t* tasks, size_t size);

#endif /* CTOOL_THREAD_H */