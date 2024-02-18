#include "Window.h"
#include <iostream>
#include <stdexcept>

namespace dark {

	Window::Window() {}

	Window::~Window()
	{
		glfwDestroyWindow(window_device);
		glfwTerminate();
	}

	/**
	* Initialize the window
	*
	*/
	int Window::InitWindow(int w, int h, std::string name)
	{

		// Initialize the library
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW\n";
			return -1;
		}

		window_device = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
		if (!window_device)
		{
			std::cerr << "Failed to create GLFW window\n";
			glfwTerminate();
			return -1;
		}

		// Open in windowed mode, resizeable
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		// The parent Window object is 'this' ptr
		glfwSetWindowUserPointer(window_device, this);

		// Whenever our window is resized
		glfwSetFramebufferSizeCallback(window_device, framebufferResizedCallback);

		glfwMakeContextCurrent(window_device);
		glfwSwapInterval(1);

		/*
			More Options
		*/
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		return 0;

	}

	bool Window::shouldClose() { return glfwWindowShouldClose(window_device); }

	void Window::framebufferResizedCallback(GLFWwindow* window, int width, int height)
	{
		auto _window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		_window->framebufferResized = true;
		_window->width = width;
		_window->height = height;
	}

}