/* Start Header ************************************************************************/
/*!
\file		SageWindowInternal.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		Contains the declaration for the private interface of the window class. This
			contain direct calls to OpenGL and GLFW.

			This window interface provide the private interface containing calls to
			OpenGL and GLFW, allowing window behaviours and attributes to be setup, configured
			and managed. THis allow the window to be manage by the internal class.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#ifndef Sage_Window_INTERNAL_HPP
#define Sage_Window_INTERNAL_HPP
#pragma once
#include <string>
#include "GLFW/glfw3.h"
/*!*****************************************************************************
	\brief
		Encapsulate the openGL window.

		This class represent the application window. It contain functions and
		algorithm used to create and modify the window.
*******************************************************************************/
class SageWindowInternal
{
	int posx, posy; //!< Window position
	int width, height;  //!< Window dimensions
	std::string title;  //!< Window title
	GLFWwindow* window; //!< OpenGL Window

	// Window properties

	bool should_close; //!< set to true when window is fullscreen
	bool is_fullscreen; //!< set to true when window is resizable
	bool is_resizable; //!< set to true when window is maximizable
	bool enable_maximize; //!< set to true when window should close


	bool is_active; //!< If window is active or not

public:

	/*!*****************************************************************************
	\brief
		Constructor for the window class.

		This constructor create the window with the given size and title.

	\param width
		The window's width.
	\param height
		The window's height.
	\param title
		The window's title.
	*******************************************************************************/
	SageWindowInternal(int width, int height, const char* title);
	/*!*****************************************************************************
	\brief
		Destructor for the window class

		This destructor ensure that memory is freed when the window class goes out
		Making calls to GL to delete the created window.
	*******************************************************************************/
	~SageWindowInternal();

	/*!*****************************************************************************
	\brief
		Copy constructor for the window class

		Copy constructor is deleted to prevent copying of the window class.
	\param other
		The input window class.
	*******************************************************************************/
	SageWindowInternal(const SageWindowInternal& other) = delete;

	/*!*****************************************************************************
	\brief
		Copy assignment operator for the window class

		Likewise, the copy assignemnt operator is deleted to prevent copying of the
		window class.
	\param other
		The input window class.
	*******************************************************************************/
	SageWindowInternal& operator=(const SageWindowInternal& other) = delete;

	/*!*****************************************************************************
	\brief
		Move assignment operator for the window class

		Likewise, the move assignemnt operator is deleted to prevent transfering of
		ownership to another window class.
	\param other
		The input window class.
	*******************************************************************************/
	SageWindowInternal&& operator=(SageWindowInternal&& other) = delete;

	/*!*****************************************************************************
	\brief
		Move constructor for the window class

		Likewise, the move constructor is deleted to prevent transfering of
		ownership to another window class.
	\param other
		The input window class.
	*******************************************************************************/
	SageWindowInternal(SageWindowInternal&& other) = delete;

	/*!*****************************************************************************
	\brief
		Make the window the current context allowing inputs detection and others
		window callback to be focused on the current window objects.
	*******************************************************************************/
	void Activate_Context();
	/*!*****************************************************************************
	\brief
		Deactivate the current context, freeing the context.
	*******************************************************************************/
	void Deactivate_Context();
	/*!*****************************************************************************
	\brief
		Set the window dimensions.
	\param width
		Window's width
	\param height
		Window's height
	*******************************************************************************/
	void Set_Dims(int width, int height);
	/*!*****************************************************************************
	\brief
		Set window title.
	\param title
		The window's title.
	*******************************************************************************/
	void set_title(const char* title);
	/*!*****************************************************************************
	\brief
		Toggle fullscreen.
		Calling this function whilst in fullscreen will toggled it to window mode.
	*******************************************************************************/
	void Toggle_Fullscreen();
	/*!*****************************************************************************
	\brief
		Set resizable, enabling or disabling resize of window.
	\param resizable
		Set it to true to enable resize else false.
	*******************************************************************************/
	void Set_Resizable(bool resizable);
	/*!*****************************************************************************
	\brief
		Set maximizable, enabling or disabling resize of window.
	\param maximize
		Set it to true to enable maximization else false.
	*******************************************************************************/
	void Set_Maximize(bool maximize);
	/*!*****************************************************************************
	\brief
		Set if the window should close.
	\param should_close
		True if window should close, else false.
	*******************************************************************************/
	void Set_Should_Close(bool should_close);

	/*!*****************************************************************************
	\brief
		Set window x position in the device screen space.
	\param _pos_x
		The X position
	*******************************************************************************/
	void Set_Pos_X(int _pos_x);
	/*!*****************************************************************************
	\brief
		Set window y position in the device screen space.
	\param _pos_y
		The Y position
	*******************************************************************************/
	void Set_Pos_Y(int _pos_y);
	/*!*****************************************************************************
	\brief
		Swap the framebuffer if double buffering is enabled.

	*******************************************************************************/
	void Swap_Buffers();

	/*!*****************************************************************************
	\brief
		Get the x position of the window
	\return
		The x position of the window.
	*******************************************************************************/
	int Get_Pos_X();
	/*!*****************************************************************************
	\brief
		Get the y position of the window
	\return
		The y position of the window.
	*******************************************************************************/
	int Get_Pos_Y();


	/*!*****************************************************************************
	\brief
		Check if window should close.

	\return
		True, if window should close else false.
	*******************************************************************************/
	bool Get_Should_Close() const;
	/*!*****************************************************************************
	\brief
		Check if the window is in fullscreen mode.
	\return
		True, if it is fullscreen else False.
	*******************************************************************************/
	bool Get_Fullscreen() const;
	/*!*****************************************************************************
	\brief
		Check if the window is resizable
	\return
		True, if it is resizable else False.
	*******************************************************************************/
	bool Get_Resizable() const;
	/*!*****************************************************************************
	\brief
		Check if the window is maximizable
	\return
		True, if it is maximizable else False.
	*******************************************************************************/
	bool Get_Maximize() const;
	/*!*****************************************************************************
	\brief
		Check if the window is active
	\return
		True, if it is active else False.
	*******************************************************************************/
	bool Check_Active() const;
	/*!*****************************************************************************
	\brief
		Get the title of the window.
	\return
		The title of the window.
	*******************************************************************************/
	std::string Get_Title() const;

	


	void Set_Fb_Callback();

	static void Frame_Buffersize_Cb(GLFWwindow* window, int width, int height);


};

#endif