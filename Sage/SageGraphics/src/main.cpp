#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <crtdbg.h>
#include <iostream>
#include <numeric>


#include "SageHelper.hpp"
#include "Scene/ExampleScene.h"
// Forward declaration
void init();
void update();
void draw();
void exit();
int loop = 60;
int window = 3;
#define ENABLE_HIGH_PERFORMANCE_GPU 1

#if ENABLE_HIGH_PERFORMANCE_GPU == 1
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	init();
	// SceneMain: A example of a scene that can be used in the main loop
	// SageHelper: A utility class that enable compiling of sjhaders and the calculation of deltatime	
	while (!SageHelper::sage_ptr_window->Should_Window_Close())
	{
		glfwPollEvents();
		update();
		draw();


		SageHelper::sage_ptr_window->Swap_Buffers();
		
		
	}
	exit();
	return 0;
}


void init()
{

	int status = SageHelper::Init(1000, 1000, "Hello World");

	if (status)
	{
		std::cerr << "Sage failed to create OpenGL context.";
		std::exit(EXIT_FAILURE);
	}

	ExampleScene::init();

	


}


void update()
{
	SageHelper::Update();
	ExampleScene::update();
}

void draw()
{
	SageHelper::Draw();
	ExampleScene::draw();
}


void exit()
{
	SageHelper::Exit();
	ExampleScene::exit();
	
}



