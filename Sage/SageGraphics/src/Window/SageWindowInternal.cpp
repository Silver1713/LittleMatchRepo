#include "SageWindowInternal.hpp"

#include <iostream>
#include <ostream>

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); //Enable compability profiles
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

void SageWindowInternal::set_dims(int width, int height)
{
	this->width = width;
	this->height = height;
	if (!is_fullscreen)
	glfwSetWindowSize(window, width, height);
}

void SageWindowInternal::set_title(const char* title)
{
	this->title = title;
	glfwSetWindowTitle(window, title);
}

void SageWindowInternal::toggle_fullscreen()
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



void SageWindowInternal::set_resizable(bool resizable)
{
	is_resizable = resizable;
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);
}

void SageWindowInternal::set_maximize(bool maximize)
{
	enable_maximize = maximize;
	glfwSetWindowAttrib(window, GLFW_MAXIMIZED, maximize);
}


void SageWindowInternal::set_should_close(bool close)
{
	this->should_close = close;
	
}

bool SageWindowInternal::get_fullscreen() const
{
	return is_fullscreen;
}

bool SageWindowInternal::get_should_close() const
{
	return glfwWindowShouldClose(window);
}

bool SageWindowInternal::get_maximize() const
{
	return enable_maximize;
}

bool SageWindowInternal::get_resizable() const
{
	return is_resizable;
}


void SageWindowInternal::set_pos_x(int pos_x)
{
	posx = pos_x;
	glfwSetWindowPos(window, pos_x, posy);
}

void SageWindowInternal::set_pos_y(int pos_y)
{
	posy = pos_y;
	glfwSetWindowPos(window, posx, pos_y);
}

int SageWindowInternal::get_pos_x()
{
	return posx;
}


int SageWindowInternal::get_pos_y()
{
	return posy;
}

std::string SageWindowInternal::get_title() const
{
	return title;
}



void SageWindowInternal::swap_buffers()
{
	glfwSwapBuffers(window);
}












