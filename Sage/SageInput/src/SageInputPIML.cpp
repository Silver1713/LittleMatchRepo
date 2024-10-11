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

  \param _keycode
	The key that is pressed

  \return
	A boolean value
*******************************************************************************/
bool SageInputPIML::Get_Key_Pressed(int _keycode) {
	return GLFWInputHandler::Get_Key_Pressed(_keycode);
}

/*!*****************************************************************************
  \brief
	Function to access glfw handler to check if a specific key is held down

  \param _keycode
	The key that is pressed/held down

  \return
	A boolean value
*******************************************************************************/
bool SageInputPIML::Get_Key(int _keycode) {
	return GLFWInputHandler::Get_Key(_keycode);
}

/*!*****************************************************************************
  \brief
	Function to access glfw handler to check if a mouse input is clicked once

  \param _mouse
	The mouse that is pressed

  \return
	A boolean value
*******************************************************************************/
bool SageInputPIML::Get_Mouse_Clicked(int _mouse) {
	return GLFWInputHandler::Get_Key_Pressed(_mouse);
}

/*!*****************************************************************************
  \brief
	Function to access glfw handler to check if a mouse input is held down

  \param _mouse
	The key that is pressed/held down

  \return
	A boolean value
*******************************************************************************/
bool SageInputPIML::Get_Mouse(int _mouse) {
	return GLFWInputHandler::Get_Key(_mouse);
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

\return
	Return a double
*******************************************************************************/
double SageInputPIML::Get_Mouse_X()
{
	return GLFWInputHandler::g_mouse_pos_x;
}

/*!*****************************************************************************
\brief
	Function to get the mouse y position

\return
	Return a double
*******************************************************************************/
double SageInputPIML::Get_Mouse_Y()
{
	return GLFWInputHandler::g_mouse_pos_y;
}