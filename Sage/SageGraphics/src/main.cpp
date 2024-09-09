
#include <iostream>
#include <numeric>


#include "SageMain.hpp"
#include "SageHelper.hpp"

// Forward declaration
void init();
void update();
void draw();
void exit();
int loop = 60;
int window = 3;
#define ENABLE_NVIDIA_OPTIMUS 1

#if ENABLE_NVIDIA_OPTIMUS == 0
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

int main()
{
	init();
	
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
	int status = SageHelper::init(1920, 1080, "Hello World");

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



