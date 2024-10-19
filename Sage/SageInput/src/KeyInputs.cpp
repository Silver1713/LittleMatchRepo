/* Start Header ************************************************************************/
/*!
\file		KeyInputs.cpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the definition of functions for the public interface for the input system.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/


#include "KeyInputs.h"

#include <iostream>

#include "GLFWHandler.h"
#include "SageInputPIML.h"

/*!*****************************************************************************
\brief
	Function to delete the pointer to implementation for sage input

\param _p
	A pointer to PIML implementation of the SageInput class
*******************************************************************************/
void SAGEInputHandler::Custom_Sage_Input_PIMPL_Delete(void*& _p)
{
	delete static_cast<SageInputPIML*>(_p);

	_p = nullptr;

}

std::unique_ptr<void, decltype(&SAGEInputHandler::Custom_Sage_Input_PIMPL_Delete)> SAGEInputHandler::impl_pointer{std::make_unique<SageInputPIML>().release()	, Custom_Sage_Input_PIMPL_Delete };

/*!*****************************************************************************
\brief
	Function to access SageInput pointer to implementation to check if a specific
	key is pressed once

\param _keycode
	The key that is pressed

\return
	Return a boolean
*******************************************************************************/
bool SAGEInputHandler::Get_Key_Pressed(int _keycode)
{
	return SageInputPIML::Get_Key_Pressed(_keycode);
}

/*!*****************************************************************************
\brief
	Function to access SageInput pointer to implementation to check if a specific
	key is held down

\param _keycode
	The key that is pressed

\return
	Return a boolean
*******************************************************************************/
bool SAGEInputHandler::Get_Key(int keycode)
{
	return SageInputPIML::Get_Key(keycode);
}

/*!*****************************************************************************
\brief
	Function to access SageInput pointer to implementation to check if the mouse
	input is clicked once

\param _mouse
	The mouse that is pressed

\return
	Return a boolean
*******************************************************************************/
bool SAGEInputHandler::Get_Mouse_Clicked(int _mouse)
{
	return SageInputPIML::Get_Mouse_Clicked(_mouse);
}

/*!*****************************************************************************
\brief
	Function to access SageInput pointer to implementation to check if the mouse
	input is held down

\param _mouse
	The mouse that is pressed

\return
	Return a boolean
*******************************************************************************/
bool SAGEInputHandler::Get_Mouse(int _mouse)
{
	return SageInputPIML::Get_Mouse(_mouse);
}

/*!*****************************************************************************
\brief
	To update the poll event function of glfw handler
*******************************************************************************/
void SAGEInputHandler::update()
{
	GLFWInputHandler::Poll_Events();
}

/*!*****************************************************************************
\brief
	To initialize the call back of SageInput pointer to implementation
*******************************************************************************/
void SAGEInputHandler::init()
{
	SageInputPIML::Set_Callback();
	GLFWInputHandler::Set_Bindings();
}

/*!*****************************************************************************
\brief
	Function to get the mouse x position using SageInput pointer to implementation

\param
	Return a double
*******************************************************************************/
double SAGEInputHandler::Get_Mouse_X()
{
	return SageInputPIML::Get_Mouse_X();
}

/*!*****************************************************************************
\brief
	Function to get the mouse y position using SageInput pointer to implementation

\param
	Return a double
*******************************************************************************/
double SAGEInputHandler::Get_Mouse_Y()
{
	return SageInputPIML::Get_Mouse_Y();
}

/*!*****************************************************************************
\brief
	Function to get the mouse coordinates using SageInput pointer to implementation

\param _x
	The x coordinate of mouse

\param _y
	The y coordinate of mouse
*******************************************************************************/
void SAGEInputHandler::Get_Mouse_Position(double& _x, double& _y)
{
	_x = SageInputPIML::Get_Mouse_X();
	_y = SageInputPIML::Get_Mouse_Y();
}
