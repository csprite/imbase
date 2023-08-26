#include <cstdio>

#include "imbase/window.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

static GLFWwindow* window = nullptr;
static float window_bg[3] = { 0, 0, 0 };

int ImBase::Window_Init(int width, int height, const char* const title) {
	glfwInit();
	glfwSetErrorCallback([](int error, const char* desc) -> void {
		printf("ImBase Error: %d\n%s\n", error, desc);
	});
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window) {
		printf("ImBase Error: Failed to create GLFW window\n");
		window = nullptr;
		return 1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("ImBase Error: Failed to init GLAD\n");
		window = nullptr;
		return 1;
	}

	glfwSwapInterval(0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = NULL; // Disable Generation of .ini file

	glfwShowWindow(window);

	return 0;
}

void ImBase::Window_SetIcon(int width, int height, unsigned char* pixels) {
	GLFWimage iconImage;
	iconImage.width = width;
	iconImage.height = height;
	iconImage.pixels = pixels;
	glfwSetWindowIcon(window, 1, &iconImage);
}

void ImBase::Window_SetTitle(const char* const title) {
	glfwSetWindowTitle(window, title);
}

void ImBase::Window_SetBG(unsigned char r, unsigned char g, unsigned char b) {
	window_bg[0] = r / 255.0f;
	window_bg[1] = g / 255.0f;
	window_bg[2] = b / 255.0f;
}

bool ImBase::Window_ShouldClose() {
	return glfwWindowShouldClose(window);
}

void ImBase::NewFrame() {
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImBase::EndFrame() {
	ImGui::Render();

	glClearColor(window_bg[0], window_bg[1], window_bg[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
}

void ImBase::Window_Destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}

