/* Start Header ************************************************************************/
/*!
\file		SageWindowInternal.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		Contains the definition for the private interface of the window class. This
			contain direct calls to OpenGL and GLFW.

			This window interface provide the private interface containing calls to
			OpenGL and GLFW, allowing window behaviours and attributes to be setup, configured
			and managed. THis allow the window to be manage by the internal class.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageWindowInternal.hpp"

#include <iostream>
#include <ostream>

#include "SageHelper.hpp"

SageWindowInternal::SageWindowInternal(int width, int height, const char* title) : posx{}, posy{}, width(width), height(height), title(title), window(nullptr),
                                                                                   should_close(false), is_fullscreen(false), is_resizable(false), enable_maximize(false), is_active(false)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << '\n';
	}
	// Create a windowed mode window and its OpenGL context
	// Forward compatibility with OpenGL 4.5
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//Specify minimum OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //Enable compability profiles
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);

	

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		std::cerr << "Failed to create window" << '\n';
	}


	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);


}

SageWindowInternal::~SageWindowInternal()
{
	glfwDestroyWindow(window);
	window = nullptr;
}

void SageWindowInternal::Activate_Context()
{
	glfwMakeContextCurrent(window);
	is_active = true;

}

void SageWindowInternal::Deactivate_Context()
{
	glfwMakeContextCurrent(nullptr);
	is_active = false;
}

void SageWindowInternal::Set_Dims(int _width, int _height)
{
	this->width = _width;
	this->height = _height;
	if (!is_fullscreen)
	glfwSetWindowSize(window, width, height);
}

void SageWindowInternal::set_title(const char* _title)
{
	this->title = _title;
	glfwSetWindowTitle(window, _title);
}

void SageWindowInternal::Toggle_Fullscreen()
{
	
	if (!is_fullscreen)
	{
		glfwGetWindowPos(window, &posx, &posy);
		glfwGetWindowSize(window, &width, &height);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, posx, posy, width, height, 0);
	}

	is_fullscreen = !is_fullscreen;

	
}



void SageWindowInternal::Set_Resizable(bool resizable)
{
	is_resizable = resizable;
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);
}

void SageWindowInternal::Set_Maximize(bool maximize)
{
	enable_maximize = maximize;
	glfwSetWindowAttrib(window, GLFW_MAXIMIZED, maximize);
}


void SageWindowInternal::Set_Should_Close(bool close)
{
	this->should_close = close;
	
}

bool SageWindowInternal::Get_Fullscreen() const
{
	return is_fullscreen;
}

bool SageWindowInternal::Get_Should_Close() const
{
	return glfwWindowShouldClose(window);
}

bool SageWindowInternal::Get_Maximize() const
{
	return enable_maximize;
}

bool SageWindowInternal::Get_Resizable() const
{
	return is_resizable;
}


void SageWindowInternal::Set_Pos_X(int _pos_x)
{
	posx = _pos_x;
	glfwSetWindowPos(window, _pos_x, posy);
}

void SageWindowInternal::Set_Pos_Y(int _pos_y)
{
	posy = _pos_y;
	glfwSetWindowPos(window, posx, _pos_y);
}

int SageWindowInternal::Get_Pos_X()
{
	return posx;
}


int SageWindowInternal::Get_Pos_Y()
{
	return posy;
}

std::string SageWindowInternal::Get_Title() const
{
	return title;
}



void SageWindowInternal::Swap_Buffers()
{
	glfwSwapBuffers(window);
}


void SageWindowInternal::Set_Fb_Callback()
{
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h)
	{
		SageWindowInternal* internal_win = static_cast<SageWindowInternal*>(glfwGetWindowUserPointer(win));
		internal_win->height = h;
		internal_win->width = w;
		std::cout << "Width: " << w << " Height: " << h << '\n';
		
	});
}

bool SageWindowInternal::Check_Active() const
{
	return  is_active;
}


void SageWindowInternal::Frame_Buffersize_Cb(GLFWwindow* window, int width, int height)
{
	window;
	width;
	height;
	return;
}


int SageWindowInternal::Get_Display_Size_X() const
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	return mode->width;

}


int SageWindowInternal::Get_Display_Size_Y() const
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	return mode->height;
}











