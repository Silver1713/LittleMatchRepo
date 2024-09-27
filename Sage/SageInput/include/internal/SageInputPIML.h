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
	// Check if specific key is pressed once
	static bool Get_Key_Pressed(int keycode);

	// Check if specific key is held down
	static bool Get_Key(int keycode);

	// Check if mouse is clicked once
	static bool Get_Mouse_Clicked(int mouse);

	// Check if mouse is held down
	static bool Get_Mouse(int mouse);

	// Start input polling - process inputs
	static void poll();

	// Link Callback
	static void Set_Callback();

	// Get mouse x position
	static double Get_Mouse_X();

	// Get mouse y position
	static double Get_Mouse_Y();
};
