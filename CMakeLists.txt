cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(imbase C CXX)
add_library(imbase STATIC src/window.cpp src/texture.cpp src/launcher.cpp)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	if(NOT WIN32)
		target_compile_options(imbase PUBLIC -fsanitize=address)
		target_link_options(imbase PUBLIC -fsanitize=address)
	endif()
endif()

if(WIN32 OR CYGWIN)
	target_compile_definitions(imbase PRIVATE TARGET_WINDOWS)
elseif(APPLE)
	target_compile_definitions(imbase PRIVATE TARGET_APPLE)
elseif(LINUX) # LINUX variable is new in CMake v3.5
	target_compile_definitions(imbase PRIVATE TARGET_LINUX)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/)

target_include_directories(imbase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include/)
target_link_libraries(imbase PUBLIC glad_loader)
target_link_libraries(imbase PUBLIC glfw)
target_link_libraries(imbase PUBLIC imgui_static)
target_link_libraries(imgui_static PUBLIC glfw)

target_compile_options(imbase PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

