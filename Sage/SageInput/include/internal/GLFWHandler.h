/* Start Header ************************************************************************/
/*!
\file		GLFWHandler.h
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contain the declaration of GLFW functions to be defined to hide it from the public.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once

#ifndef _glfw3_h_
#include <GLFW/glfw3.h>
#endif

#include <string>
#include <unordered_map>

class GLFWInputHandler {
public:
	static double g_mouse_pos_x;
	static double g_mouse_pos_y;

	static std::unordered_map<int, std::byte> key_map;

	/*!*****************************************************************************
	\brief
		A polling function to process and handle the input events
	*******************************************************************************/
	static void Poll_Events();

	/*!*****************************************************************************
	\brief
		Check if a specific key/mouse is pressed once
	*******************************************************************************/
	static bool Get_Key_Pressed(int keycode); // Check if specific key/mouse is pressed once

	/*!*****************************************************************************
	\brief
		Check if a specific key/mouse is held down
	*******************************************************************************/
	static bool Get_Key(int keycode); // Check if specific key/mouse is held down

	/*!*****************************************************************************
	\brief
		A key callback function that is called whenever a key is pressed, released
		or held down. It register the key event using glfw call back mechanism.
	*******************************************************************************/
	static void Key_Cb(GLFWwindow* window, int keycode, int scancode, int action, int mods);

	/*!*****************************************************************************
	\brief
		A mouse callback function that is called whenever a mouse is pressed, released
		or held down. It register the mouse event using glfw call back mechanism.
	*******************************************************************************/
	static void Mouse_Cb(GLFWwindow* window, int button, int action, int mods);

	/*!*****************************************************************************
	\brief
		To get the mouse position
	*******************************************************************************/
	static void Mouse_Pos_Cb(GLFWwindow* window, double xpos, double ypos);
};
