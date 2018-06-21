cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror -pedantic -g")
project(madd)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${madd_SOURCE_DIR})
add_subdirectory(src)

if("${CMAKE_SYSTEM_NAME}" STREQUAL Windows)
#	set(CMAKE_EXE_LINKER_FLAGS "-lglfw3 -lopengl32 -lglu32 -lgdi32")
#	set(LIBS "glfw3;opengl32;glu32;gdi32")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL Linux)
	set(CMAKE_STATIC_LINKER_FLAGS "-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl")
#	set(LIBS "glfw;GL;X11;pthread;Xrandr;Xi;dl")
endif()

#foreach(LIB ${LIBS})
#	string(TOUPPER ${LIB} LIB_NAME)
#	find_package("${LIB}")
#endforeach()