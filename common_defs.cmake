# Some Common Definitions...

add_definitions(-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1)
add_definitions(-DIMGUI_DISABLE_OBSOLETE_KEYIO=1)

# Debug C/C++ flags
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	add_compile_options(-fsanitize=address)
	add_link_options(-fsanitize=address)
	add_definitions(-D_DEBUG)
else()
	add_definitions(-D_NDEBUG)
endif()

if(CMAKE_CXX_BYTE_ORDER STREQUAL "BIG_ENDIAN")
	add_definitions(-DTARGET_IS_BIGENDIAN=1)
endif()

if(WIN32)
	add_definitions(-DTARGET_WINDOWS)
elseif(CYGWIN)
	add_definitions(-DTARGET_WINDOWS)
	add_definitions(-DTARGET_CYGWIN)
elseif(LINUX)
	add_definitions(-DTARGET_LINUX)
elseif(BSD)
	add_definitions(-DTARGET_BSD)
elseif(APPLE)
	add_definitions(-DTARGET_APPLE)
else()
	if(ALLOW_UNKNOWN_TARGET)
		add_definitions(-DTARGET_UNKNOWN)
	else()
		message(FATAL_ERROR "Unknown Target System: \"" ${CMAKE_SYSTEM} "\"!")
	endif()
endif()

