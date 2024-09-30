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

/*!*****************************************************************************
\brief
	Function to access glfw handler to check if a specific key is pressed once
*******************************************************************************/
bool SageInputPIML::Get_Key_Pressed(int keycode) {
	return GLFWInputHandler::Get_Key_Pressed(keycode);
}

/*!*****************************************************************************
\brief
	Function to access glfw handler to check if a specific key is held down
*******************************************************************************/
bool SageInputPIML::Get_Key(int keycode) {
	return GLFWInputHandler::Get_Key(keycode);
}

/*!*****************************************************************************
\brief
	Function to access glfw handler to check if a mouse input is clicked once
*******************************************************************************/
bool SageInputPIML::Get_Mouse_Clicked(int mouse) {
	return GLFWInputHandler::Get_Key_Pressed(mouse);
}

/*!*****************************************************************************
\brief
	Function to access glfw handler to check if a mouse input is held down
*******************************************************************************/
bool SageInputPIML::Get_Mouse(int mouse) {
	return GLFWInputHandler::Get_Key(mouse);
}

/*!*****************************************************************************
\brief
	A polling function to process and handle the input events
*******************************************************************************/
void SageInputPIML::poll() {
	GLFWInputHandler::Poll_Events();
}

/*!*****************************************************************************
\brief
	A call back function to link the custom mouse, mouse position and key
	call back functions with the glfw call back functions
*******************************************************************************/
void SageInputPIML::Set_Callback()
{
	// Link Callback
	glfwSetKeyCallback(glfwGetCurrentContext(), GLFWInputHandler::Key_Cb);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), GLFWInputHandler::Mouse_Cb);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), GLFWInputHandler::Mouse_Pos_Cb);

}

/*!*****************************************************************************
\brief
	Function to get the mouse x position
*******************************************************************************/
double SageInputPIML::Get_Mouse_X()
{
	return GLFWInputHandler::g_mouse_pos_x;
}

/*!*****************************************************************************
\brief
	Function to get the mouse y position
*******************************************************************************/
double SageInputPIML::Get_Mouse_Y()
{
	return GLFWInputHandler::g_mouse_pos_y;
}