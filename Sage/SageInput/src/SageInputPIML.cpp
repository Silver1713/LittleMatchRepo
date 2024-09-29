/* Start Header ************************************************************************/
/*!
\file		SageInputPIML.CPP
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contain the definition of the pointer to implementation functions.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "SageInputPIML.h"

// Check if specific key is pressed once
bool SageInputPIML::Get_Key_Pressed(int keycode) {
	return GLFWInputHandler::Get_Key_Pressed(keycode);
}

// Check if specific key is held down
bool SageInputPIML::Get_Key(int keycode) {
	return GLFWInputHandler::Get_Key(keycode);
}

// Check if mouse is clicked once
bool SageInputPIML::Get_Mouse_Clicked(int mouse) {
	return GLFWInputHandler::Get_Key_Pressed(mouse);
}

// Check if mouse is held down
bool SageInputPIML::Get_Mouse(int mouse) {
	return GLFWInputHandler::Get_Key(mouse);
}

// Start input polling - process inputs
void SageInputPIML::poll() {
	GLFWInputHandler::Poll_Events();
}

// Link Callback
void SageInputPIML::Set_Callback()
{
	// Link Callback
	glfwSetKeyCallback(glfwGetCurrentContext(), GLFWInputHandler::Key_Cb);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), GLFWInputHandler::Mouse_Cb);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), GLFWInputHandler::Mouse_Pos_Cb);

}

// Get mouse x position
double SageInputPIML::Get_Mouse_X()
{
	return GLFWInputHandler::g_mouse_pos_x;
}

// Get mouse y position
double SageInputPIML::Get_Mouse_Y()
{
	return GLFWInputHandler::g_mouse_pos_y;
}