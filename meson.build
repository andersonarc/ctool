# csafe library build file

# project declaration
project('csafe', 'c',
    version: '0.5',
    license: 'GPL3')

# prepare build files
src = files('src/log.c')
test = files('test/main.c')
include = include_directories('include')

# compile library
libcsafe = library('csafe', [src],
    include_directories: include)

# compile test
executable('csafe_test', [test],
    include_directories: include,
    link_with: libcsafe)

# create dependency
libcsafe_dep = declare_dependency(
    include_directories: include,
    link_with: libcsafe)
