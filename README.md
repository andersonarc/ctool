# ctool

`ctool` is a small general-purpose C library designed to be simple and robust.
It is mainly used in my other projects, such as `mcsn`, but you are free to include `ctool` in yours. Hovewer, superior code quality is not guaranteed and you may encounter some nasty bugs. In this case, report the issue and I will try to fix it as soon as possible.

## Important warning

Function input is not sanitized, so passing a negative value as a size/count parameter or a `NULL` pointer will lead to unexpected behaviour (most likely a segmentation fault).

## Project features

### **Return status**

Return status codes for common situations such as memory allocation failure or file access error are defined in header file `ctool/status.h`. They are mostly useful combined with `runtime assertions`.

### **Assertions**

#### `Debug assertions`

Located in `ctool/assert/debug.h`, `assertd_*` and `assertdc_*` macro are practically the same as old-school C `assert()`, but with included implementations for common cases (`assertd_equals`, `assertd_malloc`, `assertd_true`) which are more verbose and easier to use. Just like `assert()`, they are compiled only in debug mode (with `NDEBUG` undefined) and would not affect your release builds, but on failure, the program will immediately **exit** with code 1.

#### `Runtime assertions`

For common checks you should prefer runtime assertions from `ctool/assert/runtime.h`. Their names start with `assertr_` and `assertrc_`, and they are always compiled, even in release mode. On failure, they return specified status code from the caller function and the program continues execution. *Make sure to handle returned status codes!*

### **Logging**

This library features a simple logging system with 5 different levels: debug `logd()`, info `logi()`, warning `logw()`, error `loge()` and fatal error `logfe()`. Debug and info messages are printed to `stdout`, error and warning messages \- to `stderr`. Fatal error messages lead to process exit, so be careful with them. On release builds (with `NDEBUG` defined), debug logging is disabled. Higher levels cannot be disabled, but this feature may be implemented later.

### **Thread pools**

An implementation of a thread pool pattern for multi-threaded task execution is present in `ctool`. Because C has no built-in thread support, we have to use either `pthreads` library or `C11` threads. If `CTOOL_THREAD_USE_POSIX` is defined, `pthreads` will be preferred. Thread safety is ensured by atomic index and state, and verified by testing.

Setting up a task manager requires few different steps.
1. Declare a task function which takes 1 argument of type `task_input_t` and returns `task_output_t`. In the function body, return `task_output_default` in the end.
2. Create an instance (or instances) of `task_t` and initialize it
    - Assign a function pointer to `task.function`
    - Assign an input value (casted to `task_input_t`) to `task.input`
3. Create an instance of `task_list_t` and initialize it with `task_list_init()`
4. Create an instance of `task_manager_t` and initialize it with `task_manager_create()` (optionally run your tasks immediately with `task_manager_create_run()`)
5. Run your task list with `task_manager_submit()`

Then you will have several options:
- Reuse the task manager for a new task list (old one is released automatically, just submit a new `task_list_t`)
- Free the task manager with `task_manager_delete()` (again, the task list is released automatically)

Planned features:
- Different task execution modes (e.g. one function with multiple inputs)

An example of `task_manager_t` usage could be found in test/thread.c file.

### **Stream IO**

Documented in source code, check ctool/io.

### **Data types**

Type-generic `list`, `arraylist` and `optional` types are defined in ctool/type.

### **File utilities**

Documented in source code, check ctool/file.h.

### **Iteration utilities**

Documented in source code, check ctool/iteration.h.