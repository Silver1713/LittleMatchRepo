#pragma once
// GLFW_Handler Header File

#ifndef _glfw3_h_
#include <GLFW/glfw3.h>
#endif

#include <string>
#include <unordered_map>

class GLFW_Input_Handler {
public:
	static double mouse_pos_x;
	static double mouse_pos_y;

	static std::unordered_map<int, std::byte> key_map;



	static void Poll_Events(); // Function to poll events

	static bool Get_Key_Pressed(int keycode); // Check if specific key/mouse is pressed once
	static bool Get_Key(int keycode); // Check if specific key/mouse is held down

	// Key Callback function
	static void key_cb(GLFWwindow* window, int keycode, int scancode, int action, int mods);

	static void mouse_cb(GLFWwindow* window, int button, int action, int mods);

	static void mouse_pos_cb(GLFWwindow* window, double xpos, double ypos);
};
