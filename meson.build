# ctool library build file

# project declaration
project('ctool', 'c',
    version: '1.3',
    license: 'GPL3')

# prepare build files
src = files('src/thread.c', 'src/log/_internal.c', 'src/file.c', 'src/io/stream.c')
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

arraylist_test = executable('test_arraylist', 
    files('test/type/arraylist.c'),
    dependencies: libctool_dep)
test('arraylist_test', arraylist_test)

list_test = executable('test_list', 
    files('test/type/list.c'),
    dependencies: libctool_dep)
test('list_test', list_test)

optional_test = executable('test_optional', 
    files('test/type/optional.c'),
    dependencies: libctool_dep)
test('optional_test', optional_test)

iteration_test = executable('test_iteration', 
    files('test/iteration.c'),
    dependencies: libctool_dep)
test('iteration_test', iteration_test)

file_test = executable('test_file',
    files('test/file.c'),
    dependencies: libctool_dep)
test('file_test', file_test)

bitset_test = executable('bitset_test',
    files('test/type/bitset.c'),
    dependencies: libctool_dep)
test('bitset_test', bitset_test)