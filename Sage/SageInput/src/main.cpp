#include <iostream>
#include "ClientPerson.hpp"
#include <Key_Inputs.h>

// Welcome to your main file.

//Set this to show what happen if the hidden implementation is accessed directly
#define USE_INTERNAL 0
int main(){
#if USE_INTERNAL
	ClientPerson::PIML_Person::greet();
	glm::vec2 vector2 = { 1.0,2.0 }; //  access to opengl functions will be highlighted as error.
	#else
	ClientPerson::greet();
	ClientPerson::greet("John Doe");
	ClientPerson::say("Hello World!");
	// 1st layer (client) call the 2nd layer (ClientPerson Interface)
	// which calls the 3rd layer (internal)
	// 1st layer have only access and only find functions in the 2nd layer
	// It cannot find variables or functions in the 3rd layer

#endif
	

	std::cout << SAGE_Input_Handler::Get_Key_Pressed(0);
	return 0;
}

