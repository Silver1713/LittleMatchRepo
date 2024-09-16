
#include <iostream>
#include <numeric>

#include "SageMain.hpp"
#include "SageHelper.hpp"
#include "Test.h"
// Forward declaration
void init();
void update();
void draw();
void exit();
int loop = 60;
int window = 3;
#define ENABLE_HIGH_PERFORMANCE_GPU 1 // IDK why SOIL DOESNT WORK WITHOUT THIS :< does not work with iGPU

#if ENABLE_HIGH_PERFORMANCE_GPU == 1
extern "C"
{
	_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

int main()
{
	
	init();
	// SceneMain: A example of a scene that can be used in the main loop
	// SageHelper: A utility class that enable compiling of sjhaders and the calculation of deltatime	
	while (!SageHelper::sage_ptr_window->should_window_close())
	{
		glfwPollEvents();
		update();
		draw();

		SageHelper::sage_ptr_window->swap_buffers();
		
		
	}
	exit();
	return 0;
}


void init()
{
	int status = SageHelper::init(2560, 1080, "Hello World");
	const GLubyte* a = glGetString(GL_EXTENSIONS);

	if (status)
	{
		std::cerr << "Sage failed to create OpenGL context.";
		std::exit(EXIT_FAILURE);
	}

	SageMain::init();

	


}


void update()
{
	SageHelper::update();
	SageMain::update();
}

void draw()
{
	SageHelper::draw();
	SageMain::draw();
}


void exit()
{
	SageHelper::exit();
	SageMain::exit();
	
}



