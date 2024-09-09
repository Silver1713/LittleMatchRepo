#include <iostream>
#include "GLFW_Handler.h"

#include <unordered_map>

std::unordered_map<int, int> GLFW_Input_Handler::key_map{};

// Base Layer of glfw handler
static GLFW_Input_Handler* instance = nullptr;

bool GLFW_Input_Handler::Get_Key_Pressed(int keycode)
{
	if (key_map[keycode] == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GLFW_Input_Handler::Get_Key(int keycode)
{
	if (key_map[keycode] == GLFW_PRESS || key_map[keycode] == GLFW_REPEAT)
	{
		return true;
	}
	else
	{
		
		return false;
	}
}

void GLFW_Input_Handler::key_cb(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	key_map[keycode] = action;
}

void GLFW_Input_Handler::mouse_cb(GLFWwindow* window, int button, int action, int mods)
{
	key_map[button] = action;
}


void GLFW_Input_Handler::Poll_Events()
{
	glfwPollEvents();
}


 



