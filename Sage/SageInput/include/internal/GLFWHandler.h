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



	static void Poll_Events(); // Function to poll events

	static bool Get_Key_Pressed(int keycode); // Check if specific key/mouse is pressed once
	static bool Get_Key(int keycode); // Check if specific key/mouse is held down

	// Key Callback function
	static void Key_Cb(GLFWwindow* window, int keycode, int scancode, int action, int mods);

	static void Mouse_Cb(GLFWwindow* window, int button, int action, int mods);

	static void Mouse_Pos_Cb(GLFWwindow* window, double xpos, double ypos);
};
