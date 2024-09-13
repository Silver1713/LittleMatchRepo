#include "InternalPerson.hpp"
#include <GLFW/glfw3.h> // including gls;
#include <glm/glm.hpp>
#include <iostream>
// This is the 3rd layer of abstraction - no hiding of implementation details
std::map<int, int> InternalPerson::keyMap{};

void InternalPerson::greet()
{
	
	std::cout << "Hello World!" << std::endl;

}

void InternalPerson::greet(const char* name)
{
	std::cout << "Hello " << name << "!" << std::endl;

}


void InternalPerson::say(const char* message)
{
	std::cout << message << std::endl;
	
}

bool InternalPerson::getKeyPress(int key)
{
	if (keyMap[key] == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InternalPerson::getKey(int key)
{
	if (keyMap[key] == GLFW_REPEAT || keyMap[key] == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void InternalPerson::Press(int key, int count)
{
	keyMap[key] = count > 0 ? GLFW_REPEAT : GLFW_PRESS;
}

void InternalPerson::Release(int key)
{
	keyMap[key] = GLFW_RELEASE;
}

void InternalPerson::key_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	keyMap[key] = action;
	std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << std::endl;

}

// TEST FUNCTIONS





