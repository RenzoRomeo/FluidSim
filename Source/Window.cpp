#include "Window.h"

#include <iostream>

Window::Window(uint32_t width, uint32_t height, const char* title)
	: m_Width(width), m_Height(height)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW.\n";
		exit(1);
	}

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

void Window::StartFrame()
{
	glfwPollEvents();
}

void Window::EndFrame()
{
	glfwSwapBuffers(m_Window);
}

void Window::SetKeyPressedCallback(GLFWkeyfun callback)
{
	glfwSetKeyCallback(m_Window, callback);
}

void Window::SetMousePosCallback(GLFWcursorposfun callback)
{
	glfwSetCursorPosCallback(m_Window, callback);
}

void Window::SetMouseButtonCallback(GLFWmousebuttonfun callback)
{
	glfwSetMouseButtonCallback(m_Window, callback);
}
