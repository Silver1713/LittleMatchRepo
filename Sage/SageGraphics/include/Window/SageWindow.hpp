/* Start Header ************************************************************************/
/*!
\file		SageWindow.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		Contains the declaration for the public interface of the window class. This
			expose the API use to create and manage openGL window.

			The window interface provide the public interface which will be delegated
			to the internal interface by PIMPL. It provide methods and configuration for
			OpenGL window. It also manages the window lifecycle.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef Sage_Window_HPP
#define Sage_Window_HPP
#include <memory>
#include <string>

/*!*****************************************************************************
	\brief
		Encapsulate the openGL window.

		This class represent the application window. It contain functions and
		algorithm used to create and modify the window.
*******************************************************************************/
class SageWindow
{
	static SageWindow* Active_Window; //!< A static pointer to the current active window.
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
	SageWindow(int width, int height, const char* title);
	/*!*****************************************************************************
	\brief
		Destructor for the window class

		This destructor ensure that memory is freed when the window class goes out
		of scope by setting the unique pointer to null, trigger the PIMPL destructor.
	*******************************************************************************/
	~SageWindow();
	/*!*****************************************************************************
	\brief
		Check if window should close.

	\return
		True, if window should close else false.
	*******************************************************************************/
	bool Should_Window_Close() const;
	/*!*****************************************************************************
	\brief
		Get the window.

	\return
		The Window class
	*******************************************************************************/
	SageWindow const& Get_Window() const;
private:
	class SageWindowImpl; //!< PIMPL implementation for the window.
	std::unique_ptr<SageWindowImpl> window_internal_impl; //!< Pointer to the internal window class.

	int posx, posy; //!< Window positions
	
	int width,height; //!< Window dimensions
	

	std::string title; //!< Window title

	// Window properties
	bool should_close; //!< set to true when window should close
	bool is_fullscreen; //!< set to true when window is fullscreen
	bool is_resizable; //!< set to true when window is resizable
	bool enable_maximize; //!< set to true when window is maximizable


	bool is_active; //!< set to true when window is active

public:
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
	void Set_Title(const char* title);
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
		Set the framebuffer called for the current context.
	
	*******************************************************************************/
	void Set_Framebuffer_Callback();
	/*!*****************************************************************************
	\brief
		Swap the framebuffer if double buffering is enabled.
	
	*******************************************************************************/
	void Swap_Buffers();

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
	bool check_active() const;

	/*!*****************************************************************************
	\brief
		Get the x position of the window
	\return
		The x position of the window.
	*******************************************************************************/
	int Get_Pos_X() const;
	/*!*****************************************************************************
	\brief
		Get the y position of the window
	\return
		The y position of the window.
	*******************************************************************************/
	int Get_Pos_Y() const;
	/*!*****************************************************************************
	\brief
		Get the x scale of the window
	\return
		The X scale of the window.
	*******************************************************************************/
	int Get_Size_X() const;
	/*!*****************************************************************************
	\brief
		Get the y scale of the window
	\return
		The Y scale of the window.
	*******************************************************************************/
	int Get_Size_Y() const;
	/*!*****************************************************************************
	\brief
		Get the title of the window.
	\return
		The title of the window.
	*******************************************************************************/
	std::string Get_Title() const;

	/*!*****************************************************************************
	\brief
		Get the active window
		This function retrieve a pointer to the current active window allowing modification
		and handling outside of the window class.
	\return
		The pointer to the active window.
	*******************************************************************************/
	static SageWindow* Get_Active_Window();


};


#endif