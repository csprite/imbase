#include <cstdio>

#include "imbase/window.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

static GLFWwindow* window = nullptr;

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

void ImBase::Window_Destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}

