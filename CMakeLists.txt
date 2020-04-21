cmake_minimum_required(VERSION 3.15)
#project("${LIBTARGETNAME}" C)
project(ft_malloc C)
set(CMAKE_C_STANDARD 99)
#set(CMAKE_SHARED_LIBRARY_SUFFIX .so)
#set(CMAKE_VERBOSE_MAKEFILE ON)

#message("$ENV{BUILD_DIR} -- ")


add_library(${PROJECT_NAME} SHARED sources/mutex_manager.c memory.h sources/malloc.c sources/utilities/utilities.h sources/realloc.c sources/free.c sources/new_cluster.c sources/get_free_block_from_cluster.c sources/service_funcs.c sources/malloc.h sources/main_wrappers.c sources/mem_dump.c sources/utilities/mem_to_hex.c sources/utilities/itoa.c sources/show_mem_hex.c sources/utilities/memcpy.c)
target_link_libraries(${PROJECT_NAME} pthread)






add_executable(test main.c)
target_link_libraries(test
		${PROJECT_NAME}
		${GLFLIB}
		${OPENGL_LIBRARIES}
		)