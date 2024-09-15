#include "SageWindow.hpp"

#include "SageWindowInternal.hpp"

#include <memory>

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
	SageWindowImpl(SageWindow* prn) : parent(prn) 
	{
		posx = parent->get_pos_x();
		posy = parent->get_pos_y();
		width = parent->width;
		height = parent->height;
		title = parent->get_title();
		
		window = std::make_unique<SageWindowInternal>(width, height, title.c_str());

	}

	void Activate_Context()
	{
		window->Activate_Context();
	}

	void Deactivate_Context()
	{
		window->Deactivate_Context();
	}

	void set_dimensions(int w, int h)
	{
		this->width = w;
		this->height = h;
		window->set_dims(width, height);
	}


	void set_title(const char* t)
	{
		this->title = t;
		window->set_title(t);
	}

	void toggle_fullscreen()
	{
		window->toggle_fullscreen();
		fullscreen = !fullscreen;
	}

	void set_resizable(bool can_resize)
	{
		window->set_resizable(can_resize);
		this->resizable = can_resize;
	}

	void set_maximize(bool can_maximize)
	{
		window->set_maximize(can_maximize);
		this->maximize = can_maximize;
	}
	

	void set_pos_x(int pos_x)
	{
		posx = pos_x;
		window->set_pos_x(pos_x);
	}

	void set_pos_y(int pos_y)
	{
		posy = pos_y;
		window->set_pos_y(pos_y);
	}

	bool get_should_close() const
	{
		return window->get_should_close();
	}


	bool get_active() const
	{
		return window->check_active();
	}


	void swap_buffers()
	{
		window->swap_buffers();
	}
};


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
	window_internal_impl->Activate_Context();
}

void SageWindow::Deactivate_Context()
{
	is_active = false;
	window_internal_impl->Deactivate_Context();
}

void SageWindow::set_dims(int _width, int _height)
{
	width = _width;
	height = _height;
	window_internal_impl->set_dimensions(width, height);

}

void SageWindow::set_title(const char* current_title)
{
	this->title = current_title;
	window_internal_impl->set_title(current_title);
}

void SageWindow::toggle_fullscreen()
{
	is_fullscreen = !is_fullscreen;
	window_internal_impl->toggle_fullscreen();
}

void SageWindow::set_resizable(bool resizable)
{
	is_resizable = resizable;
	window_internal_impl->set_resizable(resizable);
}

void SageWindow::set_maximize(bool maximize)
{
	enable_maximize = maximize;
	window_internal_impl->set_maximize(maximize);
}





bool SageWindow::get_fullscreen() const
{
	return is_fullscreen;
}

bool SageWindow::get_maximize() const
{
	return enable_maximize;
}

SageWindow const& SageWindow::GetWindow() const
{
	return *this;
}

bool SageWindow::get_resizable() const
{
	return is_resizable;
}

int SageWindow::get_pos_x() const
{
	return posx;
}

int SageWindow::get_pos_y() const
{
	return posy;
}

void SageWindow::set_pos_x(int pos_x)
{
	posx = pos_x;
	window_internal_impl->set_pos_x(pos_x);
}


void SageWindow::set_pos_y(int pos_y)
{
	posy = pos_y;
	window_internal_impl->set_pos_y(pos_y);
}


std::string SageWindow::get_title() const
{
	return title;
}

bool SageWindow::should_window_close() const
{
	return window_internal_impl->get_should_close();
}

bool SageWindow::check_active() const
{
	return window_internal_impl->get_active();
}




void SageWindow::swap_buffers()
{
	window_internal_impl->swap_buffers();
}

int SageWindow::get_size_x() const
{
	return width;
}

int SageWindow::get_size_y() const
{
	return height;
}





