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

	static void setcallback()
	{
		// Link Callback
		// glfwSetKeyCallback(window, GLFW_Input_Handler::key_cb);
	}
};