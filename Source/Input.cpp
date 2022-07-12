#include "Input.h"

#include <iostream>

bool Input::key_pressed_data[GLFW_KEY_LAST] = {};
bool Input::mouse_button_pressed_data[GLFW_MOUSE_BUTTON_LAST] = {};
float Input::mouse_x = 0.0f;
float Input::mouse_y = 0.0f;
float Input::mouse_scroll_x = 0.0f;
float Input::mouse_scroll_y = 0.0f;
float Input::x_offset = 0.0f;
float Input::y_offset = 0.0f;

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < GLFW_KEY_LAST)
		key_pressed_data[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	x_offset = xpos - mouse_x;
	y_offset = mouse_y - ypos;

	mouse_x = (float)xpos;
	mouse_y = (float)ypos;
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
		mouse_button_pressed_data[button] = action == GLFW_PRESS;
}

void Input::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouse_scroll_x = (float)xoffset;
	mouse_scroll_y = (float)yoffset;
}

bool Input::IsKeyDown(int key)
{
	if (key >= 0 && key < GLFW_KEY_LAST)
		return key_pressed_data[key];

	return false;
}

bool Input::IsMouseButtonDown(int mouseButton)
{
	if (mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST)
		return mouse_button_pressed_data[mouseButton];

	return false;
}

void Input::ResetMouseOffsets()
{
	x_offset = 0.0f;
	y_offset = 0.0f;
}
