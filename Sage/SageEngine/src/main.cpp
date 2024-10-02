/* Start Header ************************************************************************/
/*!
\file		Prefabs.cpp
\title		Memory's Flame
\authors	Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (40%)
            Halis (20%)
            Jia Hao (40%)
\par		b.muhammadhafiz@digipen.edu, halis digipen, jia hao digipen
\date		10 September 2024
\brief		This is the main entry point for the engine.
            It include libraries and manages life cycle of the engine.

            All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

/*
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
#include "SageRenderer.hpp"
#include "SageHelper.hpp"
#include "KeyInputs.h"

#include "AssetLoader.hpp"
#include "Prefabs.hpp"
#include "SceneManager.hpp"
#include "SageAudio.hpp"
#include "SageShaderManager.hpp"
#include "SageTimer.hpp"


// Forward declaration
void init();
void update();
void PhysicsUpdate();
void draw();
void exit();
int loop = 60;
int window = 3;

constexpr double physics_update_target = 0.02;
namespace
{
    static double accumulator = 0;
}



#define ENABLE_NVIDIA_OPTIMUS 1

#if ENABLE_NVIDIA_OPTIMUS == 1
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

/*!*****************************************************************************
  \brief
    Entry point for SageEngine
*******************************************************************************/
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	init();
    //SageAudio::Play_Sound("HALO_2");
    SageAudio::Play_Sound("MAIN_MENU");
    //SageAudio::Play_Sound("RAIN");

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

/*!*****************************************************************************
  \brief
    Initializes the window, assets and scenes
*******************************************************************************/
void init()
{
    int status = SageHelper::init(1920, 1080, "Hello World");
    SageShaderManager::add_shader_include("graphic_lib", "../SageGraphics/shaders/");
	SageRenderer::init();
    SageTimer::init();

    if (status)
    {
        std::cerr << "Sage failed to create OpenGL context.";

        std::exit(EXIT_FAILURE);
    }    
    Assets::Textures::Init();
    Assets::Prefabs::Init();
    Assets::Levels::Init();
    Prefabs::Init();
    SM::Load();
    SM::Init();
    SageAudio::Init();

}

/*!*****************************************************************************
  \brief
    Updates SageEngine
*******************************************************************************/
void update()
{
    SageTimer::Update();
    SageHelper::update();
	accumulator += SageTimer::delta_time;
	if (accumulator >= physics_update_target)
	{
        PhysicsUpdate();
		accumulator -= physics_update_target;
	}
	SM::Input();
    SM::Update();
    
    SageAudio::Update();
}

/*!*****************************************************************************
  \brief
    Updates the Physics of SageEngine
*******************************************************************************/
void PhysicsUpdate()
{
	// Do you want a fixed physics update? - JH
}

/*!*****************************************************************************
  \brief
    Draws the scene
*******************************************************************************/
void draw()
{
    SageHelper::draw();
    std::string s = "Scene 1 | FPS: " + std::to_string(SageHelper::FPS);
    SageHelper::sage_ptr_window->Set_Title(s.c_str());
    SM::Draw();
	
}

/*!*****************************************************************************
  \brief
    Exits SageEngine
*******************************************************************************/
void exit()
{
    Game_Objects::Exit();
    SM::Free();
    Assets::Textures::Unload();
    SM::Unload();
    SageHelper::exit();
    SageAudio::Exit();
}
