cmake_minimum_required(VERSION 3.15)

project(AllocViewer CXX)
set(CMAKE_CXX_STANDARD 17)

find_library (
		GLFLIB
		NAMES glfw3 libglfw3 glfw # what to look for
		HINTS "/usr/local/lib/cmake" # where to look
		#NO_DEFAULT_PATH # do not search system default paths
)
if (NOT GLFLIB)
	message(SEND_ERROR "Did not find lib hello")
endif()

set(OPENGL_INCLUDE_DIR /usr/local/include)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
		${GLFLIB}
		${OPENGL_LIBRARIES}
		)