#include <iostream>
#include <KeyInputs.h>
#include <backward.hpp>

#include "GLFWHandler.h"
#include "SageScriptCompiler.hpp"
#include "SageScriptLoader.hpp"

GLFWwindow* window;
// Welcome to your main file.
#define BACKWARD_STACK_TRACE 0

#if BACKWARD_STACK_TRACE
backward::SignalHandling sh;
#endif


//Set this to show what happen if the hidden implementation is accessed directly
SageAssembler assembler{};
SageLoader loader{};
#define USE_INTERNAL 0
int main(){
	//Initialize the GLFW library
	if (!glfwInit())
		return -1;

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "Sage Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	


	assembler.Init("..\\MONO\\bin\\", "..\\CoreComponents\\SageLogic\\programs");
	loader.Init("../MONO/lib", "../MONO/etc");
	SAGEInputHandler::init();
	assembler.Set_Command("mcs");
	assembler.Set_Compile_Flags("/target:library");

	assembler.Add_Script(SageAssembler::FILE_MODE, "../CoreComponents/SageLogic/scripts/Input.cs");

	assembler.StartCompilation(false);
	std::cout << "Compiling C# Code...\n";
	assembler.Wait_For_Compile();
	std::cout << "C# code compiled successfully\n";


	loader.Load_Assembly("Input", assembler.Get_Assembly("Input").path_to_assembly.c_str());

	



	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap front and back buffers
		glfwSwapBuffers(window);
		loader.Run_Main("Input");
		// Poll for and process events
		glfwPollEvents();

	}

	loader.Exit();
	



	
	return 0;
}

