/* Start Header ************************************************************************/
/*!
\file		SageWindowImpl.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The PIMPL implementation of the SageWindow class  is used to facilitate calls to the
			private interface that implements the window.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SAGE_WINDOW_IMPL_HPP
#define SAGE_WINDOW_IMPL_HPP


#include "SageWindow.hpp"
#include "SageWindowInternal.hpp"



class SageWindowInternal; //!< Forward declaration to the private interface.

/*!*****************************************************************************
	\brief
		Encapsulate the PIMPL class for the window.

		This class represent the PIMPL implementation of the window. It contain
		functions and algorithm used to create and modify the window. It delegates
		calls from the public interface to the internal class, allowing interaction
		witn OpenGL without exposure.
*******************************************************************************/
class SageWindow::SageWindowImpl
{

	int posx, posy;//!< Window position
	int width{}, height{}; //!< Window dimensions

	std::string title{}; //!< Window title
	std::unique_ptr<SageWindowInternal> window; //!< A unique pointer to the private interface
	SageWindow* parent; //!< The public interface

	bool fullscreen{ false };  //!< set to true when window is fullscreen
	bool resizable{ false };  //!< set to true when window is resizable
	bool maximize{ false }; //!< set to true when window is maximizable
	bool should_close{ false };  //!< set to true when window should close
public:
	/*!*****************************************************************************
	\brief
		Construct a PIMPL class with the parent being the public interface, allowing
		for information to be retrieved from the public interface and allow the
		PIMPL data memebers to follow the public interface.
	\param prn The public interface for the PIMPL idiom.
	*******************************************************************************/
	SageWindowImpl(SageWindow* prn);
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
	\param w
		Window's width
	\param h
		Window's height
	*******************************************************************************/
	void Set_Dimensions(int w, int h);
	/*!*****************************************************************************
	\brief
		Set window title.
	\param title
		The window's title.
	*******************************************************************************/
	void Set_Title(const char* t);
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
	void Set_Resizable(bool can_resize);
	/*!*****************************************************************************
	\brief
		Set maximizable, enabling or disabling resize of window.
	\param maximize
		Set it to true to enable maximization else false.
	*******************************************************************************/
	void Set_Maximize(bool can_maximize);

	/*!*****************************************************************************
	\brief
		Set window x position in the device screen space.
	\param pos_x
		The X position
	*******************************************************************************/
	void Set_Pos_X(int pos_x);
	/*!*****************************************************************************
	\brief
		Set window y position in the device screen space.
	\param pos_y
		The Y position
	*******************************************************************************/
	void Set_Pos_Y(int pos_y);

	/*!*****************************************************************************
	\brief
		Check if window should close.

	\return
		True, if window should close else false.
	*******************************************************************************/
	bool Get_Should_Close() const;

	/*!*****************************************************************************
	\brief
		Check if the window is active
	\return
		True, if it is active else False.
	*******************************************************************************/
	bool Get_Active() const;

	/*!*****************************************************************************
	\brief
		Swap the framebuffer if double buffering is enabled.

	*******************************************************************************/
	void Swap_Buffers();
	/*!*****************************************************************************
	\brief
		Set the framebuffer called for the current context.

	*******************************************************************************/
	void Set_Framebuffer_Callback();


	int Get_Display_Size_X() const;
	int Get_Display_Size_Y() const;
};
#endif