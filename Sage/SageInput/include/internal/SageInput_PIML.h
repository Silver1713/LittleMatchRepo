#pragma once
#include "GLFW_Handler.h"

class SageInput_PIML
{
public:
	// Check if specific key is pressed once
	static bool Get_Key_Pressed(int keycode)
	{
		return GLFW_Input_Handler::Get_Key_Pressed(keycode);
	}

	// Check if specific key is held down
	static bool Get_Key(int keycode)
	{
		return GLFW_Input_Handler::Get_Key(keycode);
	}

	// Check if mouse is clicked once
	static bool Get_Mouse_Clicked(int mouse)
	{
		return GLFW_Input_Handler::Get_Key_Pressed(mouse);
	}

	// Check if mouse is held down
	static bool Get_Mouse(int mouse)
	{
		return GLFW_Input_Handler::Get_Key(mouse);
	}

	static void poll()
	{
		GLFW_Input_Handler::Poll_Events();
	}

	static void Set_Callback()
	{
		// Link Callback
		glfwSetKeyCallback(glfwGetCurrentContext(), GLFW_Input_Handler::key_cb);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), GLFW_Input_Handler::mouse_cb);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), GLFW_Input_Handler::mouse_pos_cb);

	}

	static double Get_Mouse_X()
	{
		return GLFW_Input_Handler::mouse_pos_x;
	}

	static double Get_Mouse_Y()
	{
		return GLFW_Input_Handler::mouse_pos_y;
	}




};
