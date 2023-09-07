cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(imbase C CXX)

file(GLOB SRC_FILES src/window.cpp src/texture.cpp src/launcher.cpp)
add_library(imbase STATIC ${SRC_FILES})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	if(NOT WIN32)
		target_compile_options(imbase PUBLIC -fsanitize=address)
		target_link_options(imbase PUBLIC -fsanitize=address)
	endif()
	target_compile_definitions(imbase PRIVATE _DEBUG)
else()
	target_compile_definitions(imbase PRIVATE _NDEBUG)
endif()

if(WIN32)
	target_compile_definitions(imbase PRIVATE TARGET_WINDOWS)
elseif(CYGWIN)
	target_compile_definitions(imbase PRIVATE TARGET_WINDOWS)
	target_compile_definitions(imbase PRIVATE TARGET_CYGWIN)
elseif(LINUX)
	target_compile_definitions(imbase PRIVATE TARGET_LINUX)
elseif(BSD)
	target_compile_definitions(imbase PRIVATE TARGET_BSD)
elseif(APPLE)
	target_compile_definitions(imbase PRIVATE TARGET_APPLE)
else()
	if(ALLOW_UNKNOWN_TARGET)
		target_compile_definitions(imbase PRIVATE TARGET_UNKNOWN)
	else()
		message(FATAL_ERROR "Unknown Target System: \"" ${CMAKE_SYSTEM} "\"!")
	endif()
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

