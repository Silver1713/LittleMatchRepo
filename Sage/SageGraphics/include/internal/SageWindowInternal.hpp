#ifndef Sage_Window_INTERNAL_HPP
#define Sage_Window_INTERNAL_HPP
#pragma once
#include <string>
#include "GLFW/glfw3.h"

class SageWindowInternal
{
	int posx, posy;
	int width, height;
	std::string title;
	GLFWwindow* window;

	// Window properties

	bool should_close; // set to true when window should close
	bool is_fullscreen; // set to true when window is fullscreen
	bool is_resizable; // set to true when window is resizableble
	bool enable_maximize; // set to true when window is maximizable


	bool is_active; // set to true when window is active

public:

	// Constructor
	SageWindowInternal(int width, int height, const char* title);
	// Destructor
	~SageWindowInternal();

	// Copy constructor
	SageWindowInternal(const SageWindowInternal& other) = delete;

	// Assignment operator
	SageWindowInternal& operator=(const SageWindowInternal& other) = delete;

	// Move assignment operator
	SageWindowInternal&& operator=(SageWindowInternal&& other) = delete;

	// Move constructor
	SageWindowInternal(SageWindowInternal&& other) = delete;


	void Activate_Context();
	void Deactivate_Context();
	void set_dims(int width, int height);
	void set_title(const char* title);
	void Toggle_Fullscreen();
	void set_resizable(bool resizable);
	void set_maximize(bool maximize);
	void set_should_close(bool should_close);


	void set_pos_x(int pos_x);
	void set_pos_y(int pos_y);

	void swap_buffers();


	int get_pos_x();
	int get_pos_y();



	bool get_should_close() const;
	bool get_fullscreen() const;
	bool get_resizable() const;
	bool get_maximize() const;

	bool check_active() const { return is_active; }




	std::string get_title() const;

	


	void set_fb_callback();

	static void frame_buffersize_cb(GLFWwindow* window, int width, int height);


};

#endif