/* Start Header ************************************************************************/
/*!
\file		GLFWHandler.cpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contain the definition of GLFW functions to hide it from the public.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
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

/*!*****************************************************************************
\brief
	Check if a specific key/mouse is pressed once
*******************************************************************************/
bool GLFWInputHandler::Get_Key_Pressed(int _keycode)
{
	// If is 1, set it back to 0 to reset
	if (key_map[_keycode] == std::byte{1})
	{
		key_map[_keycode] = std::byte{0};
		return true;
	}
	else
	{
		return false;
	}
}

/*!*****************************************************************************
\brief
	Check if a specific key/mouse is held down
*******************************************************************************/
bool GLFWInputHandler::Get_Key(int _keycode)
{
	// If it is pressed down once or held down, return true
	if (key_map[_keycode] == std::byte{ 1 } || key_map[_keycode] == std::byte{2})
	{
		return true;
	}
	else
	{
		
		return false;
	}
}

/*!*****************************************************************************
\brief
	A key callback function that is called whenever a key is pressed, released
	or held down. It register the key event using glfw call back mechanism.
*******************************************************************************/
void GLFWInputHandler::Key_Cb(GLFWwindow* _window, int _keycode, int _scancode, int _action, int _mods)
{
	if (_keycode == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, GLFW_TRUE);
	}

	switch (_action)
	{
	case GLFW_PRESS:
		key_map[_keycode] = std::byte{ 1 };
#if _DEBUG
		std::cout << "Key is Pressed\n";
#endif
		break;
	case GLFW_RELEASE:
		key_map[_keycode] = std::byte{ 0 };
#if _DEBUG
		std::cout << "Key is Released\n";
#endif
		break;
	case GLFW_REPEAT:
		key_map[_keycode] = std::byte{ 2 };
#if _DEBUG
		std::cout << "Key is Hold\n";
#endif
		break;
	default:
		break;
	}

}

/*!*****************************************************************************
\brief
	A mouse callback function that is called whenever a mouse is pressed, released
	or held down. It register the mouse event using glfw call back mechanism.
*******************************************************************************/
void GLFWInputHandler::Mouse_Cb(GLFWwindow* _window, int _button, int _action, int _mods)
{

	switch (_action)
	{
	case GLFW_PRESS:
		key_map[_button] = std::byte{ 1 };
#if _DEBUG
		std::cout << "Mouse is Pressed\n";
#endif
		break;
	case GLFW_RELEASE:
		key_map[_button] = std::byte{ 0 };
#if _DEBUG
		std::cout << "Mouse is Released\n";
#endif
		break;
	case GLFW_REPEAT:
		key_map[_button] = std::byte{ 2 };
#if _DEBUG
		std::cout << "Mouse is Hold\n";
#endif
		break;
	default:
		break;
	}
}

/*!*****************************************************************************
\brief
	A polling function to process and handle the input events
*******************************************************************************/
void GLFWInputHandler::Poll_Events()
{
	glfwPollEvents();
}

/*!*****************************************************************************
\brief
	To get the mouse position
*******************************************************************************/
void GLFWInputHandler::Mouse_Pos_Cb(GLFWwindow* _window, double _xpos, double _ypos)
{
	g_mouse_pos_x = _xpos;
	g_mouse_pos_y = _ypos;

	std::cout << "Mouse X: " << g_mouse_pos_x << " Mouse Y: " << g_mouse_pos_y << std::endl;
}



 



