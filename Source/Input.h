#pragma once

#include <GLFW/glfw3.h>

namespace Input
{
	extern bool key_pressed_data[GLFW_KEY_LAST];
	extern bool mouse_button_pressed_data[GLFW_MOUSE_BUTTON_LAST];
	extern float mouse_x;
	extern float mouse_y;
	extern float mouse_scroll_x;
	extern float mouse_scroll_y;
	extern float x_offset;
	extern float y_offset;

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	bool IsKeyDown(int key);
	bool IsMouseButtonDown(int mouseButton);

	void ResetMouseOffsets();
}