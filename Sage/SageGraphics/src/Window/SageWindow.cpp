/* Start Header ************************************************************************/
/*!
\file		SageWindow.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		Defines the public interface of the window class. This
			expose the API use to create and manage openGL window.

			The window interface provide the public interface which will be delegated
			to the internal interface by PIMPL. It provide methods and configuration for
			OpenGL window. It also manages the window lifecycle.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
#include "SageWindow.hpp"
#include "SageWindowImpl.hpp"
#include <memory>

SageWindow* SageWindow::Active_Window{ nullptr };

SageWindow::SageWindow(int width, int height, const char* title) : posx{}, posy{}, width{ width }, height{ height }, title{ title }
, should_close{ false }, is_fullscreen{ false }, is_resizable{ false }, enable_maximize{ false }, is_active{ false }
{
	window_internal_impl = std::make_unique<SageWindowImpl>(this);
}

SageWindow::~SageWindow()
{
	window_internal_impl = nullptr;
}

void SageWindow::Activate_Context()
{
	is_active = true;
	Active_Window = this;
	window_internal_impl->Activate_Context();
}

void SageWindow::Deactivate_Context()
{
	is_active = false;
	Active_Window = nullptr;
	window_internal_impl->Deactivate_Context();
}

void SageWindow::Set_Dims(int _width, int _height)
{
	width = _width;
	height = _height;
	window_internal_impl->Set_Dimensions(width, height);

}

void SageWindow::Set_Title(const char* current_title)
{
	this->title = current_title;
	window_internal_impl->Set_Title(current_title);
}

void SageWindow::Toggle_Fullscreen()
{
	is_fullscreen = !is_fullscreen;
	window_internal_impl->Toggle_Fullscreen();
}

void SageWindow::Set_Resizable(bool resizable)
{
	is_resizable = resizable;
	window_internal_impl->Set_Resizable(resizable);
}

void SageWindow::Set_Maximize(bool maximize)
{
	enable_maximize = maximize;
	window_internal_impl->Set_Maximize(maximize);
}





bool SageWindow::Get_Fullscreen() const
{
	return is_fullscreen;
}

bool SageWindow::Get_Maximize() const
{
	return enable_maximize;
}

SageWindow const& SageWindow::Get_Window() const
{
	return *this;
}

bool SageWindow::Get_Resizable() const
{
	return is_resizable;
}

int SageWindow::Get_Pos_X() const
{
	return posx;
}

int SageWindow::Get_Pos_Y() const
{
	return posy;
}

void SageWindow::Set_Pos_X(int pos_x)
{
	posx = pos_x;
	window_internal_impl->Set_Pos_X(pos_x);
}


void SageWindow::Set_Pos_Y(int pos_y)
{
	posy = pos_y;
	window_internal_impl->Set_Pos_Y(pos_y);
}


std::string SageWindow::Get_Title() const
{
	return title;
}

bool SageWindow::Should_Window_Close() const
{
	return window_internal_impl->Get_Should_Close();
}

bool SageWindow::check_active() const
{
	return window_internal_impl->Get_Active();
}




void SageWindow::Swap_Buffers()
{
	window_internal_impl->Swap_Buffers();
}

int SageWindow::Get_Size_X() const
{
	return width;
}

int SageWindow::Get_Size_Y() const
{
	return height;
}

void SageWindow::Set_Framebuffer_Callback()
{
	window_internal_impl->Set_Framebuffer_Callback();
}


SageWindow* SageWindow::Get_Active_Window()
{
	return Active_Window;
}

int SageWindow::Get_Display_Size_X() const
{
	return window_internal_impl->Get_Display_Size_X();
}

int SageWindow::Get_Display_Size_Y() const
{
	return window_internal_impl->Get_Display_Size_Y();
}


