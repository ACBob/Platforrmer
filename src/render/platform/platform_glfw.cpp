// Implements platform.h with GLFW.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/platform.h"

// TODO: LOGGING MODULE
#include <iostream>

namespace platform
{

	// initialise the platform
	void InitPlatform()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// Someone will get annoyed if we don't try supporting mac
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	}

	// Resizes the opengl viewport
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	// Creates a window with the specified width and height.
	// Title may be omitted.
	PLATFORM_WINDOW_REF CreatePlatformWindow(int width, int height, const char *title)
	{
		GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!window)
		{ // TODO: find error?
			printf("Failed to create GLFW Window\n");
			return 0;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// Load Glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialise GLAD\n");
			return 0;
		}

		return (PLATFORM_WINDOW_REF)window;
	}

	// Updates events, and returns true if the window should close
	bool PollPlatformWindow(PLATFORM_WINDOW_REF window)
	{
		glfwPollEvents();

		return glfwWindowShouldClose((GLFWwindow*)window);
	}

	// Presents the window to the forefront.
	void PresentPlatformWindow(PLATFORM_WINDOW_REF window)
	{
		glfwSwapBuffers((GLFWwindow*)window);
	}

	// Cleans up everything.
	void TerminatePlatform()
	{
		glfwTerminate();
	}
}