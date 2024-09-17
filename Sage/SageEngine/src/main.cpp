/*
 * This is the main entry point for the engine,
 *	It include libraries and manages life cycle of the engine.
 *
 *	@note: You may test your components here. This is where
 *	all the libs is being compiled and run.
 *
 *	Just include your header file for the stuff you want to test.
 *
 *	Private (internal) headers cannot be included.
 *
 */

#include <iostream>
#include <numeric>

#include "SageMain.hpp"
#include "SageHelper.hpp"

#include "AssetLoader.hpp"
#include "SceneManager.hpp"
#include "Prefabs.hpp"
#include "SageAudio.hpp";



// Forward declaration
void init();
void update();
void draw();
void exit();
int loop = 60;
int window = 3;
#define ENABLE_NVIDIA_OPTIMUS 1

#if ENABLE_NVIDIA_OPTIMUS == 1
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

int main()
{


    Assets::Textures::Init();
    Assets::Prefabs::Init();
    Prefabs::Init();
	init();
    SageAudio::Play_Sound(HALO_2, NO_LOOP);
    SageAudio::Play_Sound(BABABOOEY, LOOP);

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
    const GLubyte* a = glGetString(GL_EXTENSIONS);

    if (status)
    {
        std::cerr << "Sage failed to create OpenGL context.";

        std::exit(EXIT_FAILURE);
    }
    
    SM::Load();
    SM::Init();
    SageAudio::Init();

}


void update()
{
    SageHelper::update();
    //SageMain::update();
    SM::Input();
    SM::Update();
    SageAudio::Update();
}

void draw()
{
    SageHelper::draw();
    //SageMain::draw();
    SM::Draw();
}


void exit()
{
    SM::Free();
    SM::Unload();
    SageHelper::exit();
    //SageMain::exit();
    SageAudio::Exit();

}
