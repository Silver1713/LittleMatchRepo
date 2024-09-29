/* Start Header ************************************************************************/
/*!
\file		GLFWHandler.cpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contain the definition of GLFW functions to hide it from the public.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include <iostream>
#include "GLFWHandler.h"

#include <unordered_map>

std::unordered_map<int, std::byte> GLFWInputHandler::key_map{};
double GLFWInputHandler::g_mouse_pos_x = 0;
double GLFWInputHandler::g_mouse_pos_y = 0;
// Base Layer of glfw handler
static GLFWInputHandler* instance = nullptr;

bool GLFWInputHandler::Get_Key_Pressed(int keycode)
{
	if (key_map[keycode] == std::byte{1})
	{
		key_map[keycode] = std::byte{0};
		return true;
	}
	else
	{
		return false;
	}
}

bool GLFWInputHandler::Get_Key(int keycode)
{
	if (key_map[keycode] == std::byte{ 1 } || key_map[keycode] == std::byte{2})
	{
		return true;
	}
	else
	{
		
		return false;
	}
}

void GLFWInputHandler::Key_Cb(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	switch (action)
	{
	case GLFW_PRESS:
		key_map[keycode] = std::byte{ 1 };
#if _DEBUG
		std::cout << "Key is Pressed\n";
#endif
		break;
	case GLFW_RELEASE:
		key_map[keycode] = std::byte{ 0 };
#if _DEBUG
		std::cout << "Key is Released\n";
#endif
		break;
	case GLFW_REPEAT:
		key_map[keycode] = std::byte{ 2 };
#if _DEBUG
		std::cout << "Key is Hold\n";
#endif
		break;
	default:
		break;
	}

}

void GLFWInputHandler::Mouse_Cb(GLFWwindow* window, int button, int action, int mods)
{


	switch (action)
	{
	case GLFW_PRESS:
		key_map[button] = std::byte{ 1 };
#if _DEBUG
		std::cout << "Mouse is Pressed\n";
#endif
		break;
	case GLFW_RELEASE:
		key_map[button] = std::byte{ 0 };
#if _DEBUG
		std::cout << "Mouse is Released\n";
#endif
		break;
	case GLFW_REPEAT:
		key_map[button] = std::byte{ 2 };
#if _DEBUG
		std::cout << "Mouse is Hold\n";
#endif
		break;
	default:
		break;
	}
}

void GLFWInputHandler::Poll_Events()
{
	glfwPollEvents();
}

void GLFWInputHandler::Mouse_Pos_Cb(GLFWwindow* window, double xpos, double ypos)
{
	g_mouse_pos_x = xpos;
	g_mouse_pos_y = ypos;

	std::cout << "Mouse X: " << g_mouse_pos_x << " Mouse Y: " << g_mouse_pos_y << std::endl;
}



 



