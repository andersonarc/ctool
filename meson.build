# ctool library build file

# project declaration
project('ctool', 'c',
    version: '1.2',
    license: 'GPL3')

# prepare build files
src = files('src/thread.c', 'src/log/_internal.c')
include = include_directories('include')

# find dependencies
threads = dependency('threads')

# compile library
libctool = library('ctool', [src],
    include_directories: include,
    dependencies: [threads],
    c_args: '-DCTOOL_THREAD_USE_POSIX')

# create dependency
libctool_dep = declare_dependency(
    include_directories: include,
    link_with: libctool)

# compile tests
thread_test = executable('test_thread', 
    files('test/thread.c'),
    dependencies: libctool_dep)
test('thread_test', thread_test)

log_test = executable('test_log', 
    files('test/log.c'),
    dependencies: libctool_dep)
test('log_test', log_test)

assert_test = executable('test_assert', 
    files('test/assert.c'),
    dependencies: libctool_dep)
test('assert_test', assert_test)
