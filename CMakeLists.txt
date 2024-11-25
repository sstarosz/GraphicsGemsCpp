cmake_minimum_required(VERSION 3.20)

project(GraphicsGems
	VERSION 1.0
	DESCRIPTION "Graphics Gems"
	LANGUAGES CXX
)

find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	#set(CMAKE_CXX_STANDARD 11)
	add_definitions(-Werror)
endif()
if(CMAKE_COMPILER_IS_GNUCC)
        add_definitions(-DGCC)
endif()

if(MSVC)
	#add_definitions(-D_CRT_SECURE_NO_WARNINGS=1) TODO: Fix this
endif()

if(APPLE)
    add_definitions(-DAPPLE)
endif()

#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(.)

add_library(FakeIrisGL fakeirisgl.hpp fakeirisgl.cpp)
target_link_libraries(FakeIrisGL PRIVATE glfw imgui::imgui)
set_target_properties(FakeIrisGL PROPERTIES LINKER_LANGUAGE CXX)

add_library(GraphicsGems GraphicsGems.h GraphicsGems.c)
set_target_properties(GraphicsGems PROPERTIES LINKER_LANGUAGE CXX)

add_library(GetOpt getopt.h getopt.c)
set_target_properties(GetOpt PROPERTIES LINKER_LANGUAGE CXX)

if(MSVC)
	add_library(m math.c)
	set_target_properties(m PROPERTIES LINKER_LANGUAGE CXX)
endif()

target_link_libraries(GraphicsGems m)

#add_subdirectory(gems)
#add_subdirectory(gemsii)
#add_subdirectory(gemsiii)
add_subdirectory(gemsiv)
#add_subdirectory(gemsv)

