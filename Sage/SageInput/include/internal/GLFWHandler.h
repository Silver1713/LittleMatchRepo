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

	  \param _keycode
		The key that is pressed

	  \return
		A boolean value
	*******************************************************************************/
	static bool Get_Key_Pressed(int _keycode); // Check if specific key/mouse is pressed once

	/*!*****************************************************************************
	  \brief
		Check if a specific key/mouse is held down

	  \param _keycode
		The key that is pressed/held down

	  \return
		A boolean value
	*******************************************************************************/
	static bool Get_Key(int _keycode); // Check if specific key/mouse is held down

	/*!*****************************************************************************
	  \brief
		A key callback function that is called whenever a key is pressed, released
		or held down. It register the key event using glfw call back mechanism.

	  \param _window
		The window application that receive the key event

	  \param _keycode
		The key that is pressed

	  \param _scancode
		The hardware specific code of key

	  \param _action
		The type of action occured with the key pressed

	  \param _mods
		Bitfield to describe any modifier keys that were held down

	  \return
		Null
	*******************************************************************************/
	static void Key_Cb(GLFWwindow* _window, int _keycode, int _scancode, int _action, int _mods);

	/*!*****************************************************************************
	  \brief
		A mouse callback function that is called whenever a mouse is pressed, released
		or held down. It register the mouse event using glfw call back mechanism.

	  \param _window
		The window application that receive the key event

	  \param _button
		The mouse button that is pressed

	  \param _action
		The type of action occured with the mouse pressed

	  \param _mods
		Bitfield to describe any modifier keys that were held down

	  \return
		Null
	*******************************************************************************/
	static void Mouse_Cb(GLFWwindow* _window, int _button, int _action, int _mods);

	/*!*****************************************************************************
	  \brief
		To get the mouse position

	  \param _window
		The window application that receive the key event

	  \param _xpos
		The x coordinate of the mouse

	  \param _ypos
		The y coordinate of the mouse

	  \return
		Null
	*******************************************************************************/
	static void Mouse_Pos_Cb(GLFWwindow* _window, double _xpos, double _ypos);

	// For scripting
	static void Set_Bindings();

	static void Get_Mouse_Pos(double& _xpos, double& _ypos);
};
