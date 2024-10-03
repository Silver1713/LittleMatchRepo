#include "SageWindowImpl.hpp"
#include "SageWindowInternal.hpp"

SageWindow::SageWindowImpl::SageWindowImpl(SageWindow* prn) : parent(prn)
{
	posx = parent->Get_Pos_X();
	posy = parent->Get_Pos_Y();
	width = parent->width;
	height = parent->height;
	title = parent->Get_Title();

	window = std::make_unique<SageWindowInternal>(width, height, title.c_str());

}

void SageWindow::SageWindowImpl::Activate_Context()
{
	window->Activate_Context();
}

void SageWindow::SageWindowImpl::Deactivate_Context()
{
	window->Deactivate_Context();
}


void SageWindow::SageWindowImpl::Set_Dimensions(int w, int h)
{
	this->width = w;
	this->height = h;
	window->Set_Dims(width, height);
}

void SageWindow::SageWindowImpl::Set_Title(const char* t)
{
	this->title = t;
	window->set_title(t);
}

void SageWindow::SageWindowImpl::Toggle_Fullscreen()
{
	window->Toggle_Fullscreen();
	fullscreen = !fullscreen;
}


void SageWindow::SageWindowImpl::Set_Resizable(bool can_resize)
{
	window->Set_Resizable(can_resize);
	this->resizable = can_resize;
}

void SageWindow::SageWindowImpl::Set_Pos_X(int pos_x)
{
	posx = pos_x;
	window->Set_Pos_X(pos_x);
}


void SageWindow::SageWindowImpl::Set_Pos_Y(int pos_y)
{
	posy = pos_y;
	window->Set_Pos_Y(pos_y);
}

bool SageWindow::SageWindowImpl::Get_Should_Close() const
{
	return window->Get_Should_Close();
}

bool SageWindow::SageWindowImpl::Get_Active() const
{
	return window->Check_Active();
}

void SageWindow::SageWindowImpl::Swap_Buffers()
{
	window->Swap_Buffers();
}

void SageWindow::SageWindowImpl::Set_Framebuffer_Callback()
{
	window->Set_Fb_Callback();
}



void SageWindow::SageWindowImpl::Set_Maximize(bool can_maximize)
{
	window->Set_Maximize(can_maximize);
	this->maximize = can_maximize;
}
