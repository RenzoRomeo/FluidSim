#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
	Window(uint32_t width, uint32_t height, const char* title);
	~Window();

	bool ShouldClose();
	void Close();
	void StartFrame();
	void EndFrame();

	void SetKeyPressedCallback(GLFWkeyfun callback);
	void SetMousePosCallback(GLFWcursorposfun callback);
	void SetMouseButtonCallback(GLFWmousebuttonfun callback);

	uint32_t GetWidth() const { return m_Width; }
	uint32_t GetHeight() const { return m_Height; }

private:
	GLFWwindow* m_Window;
	uint32_t m_Width, m_Height;
};