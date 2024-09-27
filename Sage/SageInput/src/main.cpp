#include <iostream>
#include <KeyInputs.h>
#include <backward.hpp>

// Welcome to your main file.
#define BACKWARD_STACK_TRACE 0

#if BACKWARD_STACK_TRACE
backward::SignalHandling sh;
#endif


//Set this to show what happen if the hidden implementation is accessed directly
#define USE_INTERNAL 0
int main(){


	std::cout << SAGEInputHandler::Get_Key_Pressed(0);
	return 0;
}

