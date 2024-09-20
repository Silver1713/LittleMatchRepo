#include <iostream>
#include "GLFW_Handler.h"

#include <unordered_map>

std::unordered_map<int, std::byte> GLFW_Input_Handler::key_map{};
double GLFW_Input_Handler::mouse_pos_x = 0;
double GLFW_Input_Handler::mouse_pos_y = 0;
// Base Layer of glfw handler
static GLFW_Input_Handler* instance = nullptr;

bool GLFW_Input_Handler::Get_Key_Pressed(int keycode)
{
	if (key_map[keycode] == std::byte{1})
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
	if (key_map[keycode] == std::byte{ 1 } || key_map[keycode] == std::byte{2})
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




void GLFW_Input_Handler::mouse_cb(GLFWwindow* window, int button, int action, int mods)
{


	switch (action)
	{
	case GLFW_PRESS:
		key_map[button] = std::byte{ 1 };
#if _DEBUG
		std::cout << "Key is Pressed\n";
#endif
		break;
	case GLFW_RELEASE:
		key_map[button] = std::byte{ 0 };
#if _DEBUG
		std::cout << "Key is Released\n";
#endif
		break;
	case GLFW_REPEAT:
		key_map[button] = std::byte{ 2 };
#if _DEBUG
		std::cout << "Key is Hold\n";
#endif
		break;
	default:
		break;
	}
}





void GLFW_Input_Handler::Poll_Events()
{
	glfwPollEvents();
}


void GLFW_Input_Handler::mouse_pos_cb(GLFWwindow* window, double xpos, double ypos)
{
	mouse_pos_x = xpos;
	mouse_pos_y = ypos;

	std::cout << "Mouse X: " << mouse_pos_x << " Mouse Y: " << mouse_pos_y << std::endl;
}



 



