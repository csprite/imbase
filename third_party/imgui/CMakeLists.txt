file(
	GLOB IMGUI_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp
)

add_library(imgui_static STATIC ${IMGUI_SOURCES})
target_include_directories(imgui_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(imgui_static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/)
target_compile_definitions(imgui_static PUBLIC IMGUI_DISABLE_OBSOLETE_FUNCTIONS)
target_compile_definitions(imgui_static PUBLIC IMGUI_DISABLE_OBSOLETE_KEYIO)

