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
#include <backward.hpp>
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
	init();
    SageAudio::Play_Sound("bgm_main_menu", LOOP);
    SageAudio::Play_Sound("ambient_rain", LOOP);

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
    
    Assets::Textures::Init();
    Assets::Prefabs::Init();
    Assets::Audio::Init();
    Prefabs::Init();
    SM::Load();
    SM::Init();
    //SageAudio::Init();

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
    Assets::Textures::Unload();
    SM::Unload();
    SageHelper::exit();
    //SageMain::exit();
    SageAudio::Exit();

}
