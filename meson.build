# csafe library build file

# project declaration
project('csafe', 'c',
    version: '0.3',
    license: 'GPL3')

# prepare build files
src = files('src/assert.c')
include = include_directories('include')

# compile library
libcsafe = library('csafe', [src],
    include_directories: include)

# create dependency
csafe_dep = declare_dependency(
    include_directories: include,
    link_with: libcsafe)