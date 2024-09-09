#ifndef Internal_Person_HPP
#define Internal_Person_HPP
#include <map>

#include "GLFW/glfw3.h"

// This is the 3rd layer of abstraction
struct InternalPerson
{
	//EXAMPLE
	static std::map<int, int> keyMap;


		static void greet();
	static void greet(const char* name);
	static void say(const char* message);
	//EXAMPLE
	static bool getKeyPress(int key);
	static bool getKey(int key);

	//TEST FUNCTIONS
	static void Press(int key , int count=0);
	static void Release(int key);

	static void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif