cmake_minimum_required(VERSION 3.15)
#project("${LIBTARGETNAME}" C)
project(ft_malloc C)
set(CMAKE_C_STANDARD 99)
#set(CMAKE_SHARED_LIBRARY_SUFFIX .so)
#set(CMAKE_VERBOSE_MAKEFILE ON)

#message("$ENV{BUILD_DIR} -- ")

add_library(${PROJECT_NAME} SHARED memory.c memory.h malloc.c show_alloc_mem.c cluster_alloc.c)
target_link_libraries(${PROJECT_NAME} pthread)

add_executable(test main.c)
target_link_libraries(test ${PROJECT_NAME})