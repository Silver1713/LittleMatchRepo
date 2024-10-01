/* Start Header ************************************************************************/
/*!
\file		SageInputPIML.h
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contain the declaration and definition of the pointer to implementation functions. 

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once
#include "GLFWHandler.h"

class SageInputPIML
{
public:
	/*!*****************************************************************************
	\brief
		Function to access glfw handler to check if a specific key is pressed once
	*******************************************************************************/
	static bool Get_Key_Pressed(int _keycode);

	/*!*****************************************************************************
	\brief
		Function to access glfw handler to check if a specific key is held down
	*******************************************************************************/
	static bool Get_Key(int _keycode);

	/*!*****************************************************************************
	\brief
		Function to access glfw handler to check if a mouse input is clicked once
	*******************************************************************************/
	static bool Get_Mouse_Clicked(int _mouse);

	/*!*****************************************************************************
	\brief
		Function to access glfw handler to check if a mouse input is held down
	*******************************************************************************/
	static bool Get_Mouse(int _mouse);

	/*!*****************************************************************************
	\brief
		A polling function to process and handle the input events
	*******************************************************************************/
	static void poll();

	/*!*****************************************************************************
	\brief
		A call back function to link the custom mouse, mouse position and key
		call back functions with the glfw call back functions
	*******************************************************************************/
	static void Set_Callback();

	/*!*****************************************************************************
	\brief
		Function to get the mouse x position
	*******************************************************************************/
	static double Get_Mouse_X();

	/*!*****************************************************************************
	\brief
		Function to get the mouse y position
	*******************************************************************************/
	static double Get_Mouse_Y();
};
