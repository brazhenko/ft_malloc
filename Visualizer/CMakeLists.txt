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


find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	#link_libraries(${GLEW_LIBRARIES})
endif()


git_clone(
		PROJECT_NAME    imgui
		GIT_URL         https://github.com/ocornut/imgui
		GIT_BRANCH      master)

include_directories(imgui)
include_directories(imgui/examples)
include_directories(imgui/examples/libs/gl3w)
include_directories(/usr/local/include)
include_directories(/opt/local/include)
add_executable(${PROJECT_NAME} src/main.cpp imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp
		imgui/examples/imgui_impl_opengl3.cpp
		imgui/examples/imgui_impl_opengl3.h
		imgui/examples/imgui_impl_glfw.cpp
		imgui/examples/imgui_impl_glfw.h
		imgui/examples/libs/gl3w/GL/gl3w.c
		)

target_link_libraries(${PROJECT_NAME}
		${GLFLIB}
		${OPENGL_LIBRARIES}
		GLEW::GLEW
		)