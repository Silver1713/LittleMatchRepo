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



class SageWindowInternal;


class SageWindow::SageWindowImpl
{

	int posx, posy;
	int width{}, height{};

	std::string title{};
	std::unique_ptr<SageWindowInternal> window;
	SageWindow* parent;

	bool fullscreen{ false };
	bool resizable{ false };
	bool maximize{ false };
	bool should_close{ false };
public:
	SageWindowImpl(SageWindow* prn);

	void Activate_Context();
	void Deactivate_Context();

	void Set_Dimensions(int w, int h);

	void Set_Title(const char* t);
	void Toggle_Fullscreen();

	void Set_Resizable(bool can_resize);
	void Set_Maximize(bool can_maximize);


	void Set_Pos_X(int pos_x);

	void Set_Pos_Y(int pos_y);

	bool Get_Should_Close() const;


	bool Get_Active() const;


	void Swap_Buffers();

	void Set_Framebuffer_Callback();
};
#endif