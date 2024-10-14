/* Start Header ************************************************************************/
/*!
\file		Prefabs.cpp
\title		Memory's Flame
\authors	Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (40%)
            Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (20%)
            Jia Hao (40%)
\par		b.muhammadhafiz@digipen.edu, halisilyasa.b@digipen.edu, jia hao digipen
\date		10 September 2024
\brief		This is the main entry point for the engine.
            It include libraries and manages life cycle of the engine.

            All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
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
#include "SageJSON.hpp"

#include "Game.hpp"

// Forward declaration
void init();
void update();
void PhysicsUpdate();
void draw();
void exit();
int loop = 60;
int window = 3;
 const std::string window_config_path = "../SageEngine/data/configuration/project_config.json";
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
    SageTimer::Init();
	SageJSON::SageJSON config;

	std::ifstream file(window_config_path);

      
    while (file)
    {
		file >> config;
    }

    config.print();

    file.close();

	int window_width = static_cast<int>(config["Window"]["Width"].as<SageJSON::SageJSON::NumberValue>());
	int window_height = static_cast<int>(
        config["Window"]["Height"].as<SageJSON::SageJSON::NumberValue>());

	std::string window_title = config["Window"]["Title"].as<SageJSON::SageJSON::StringValue>();
    std::string editor_startup_scene = config["Other_Configurations"]["Editor_Startup_Scene"].as<SageJSON::SageJSON::StringValue>();
    std::string game_startup_scene = config["Other_Configurations"]["Game_Startup_Scene"].as<SageJSON::SageJSON::StringValue>();

    config.close();
    
    int status = SageHelper::Init(window_width, window_height, window_title.c_str());
    SageShaderManager::Add_Shader_Include("graphic_lib", "../SageGraphics/shaders/");
	SageRenderer::Init();
    SageTimer::Init();

    if (status)
    {
        std::cerr << "Sage failed to create OpenGL context.";

        std::exit(EXIT_FAILURE);
    }
    Assets::Init();
    Prefabs::Init();
    SageAudio::Init();
    if (1) // to be changed with some sort of flag to detect if running through editor or as built game
    {
        SM::Startup_Scene(editor_startup_scene);
    }
    else 
    {
        SM::Startup_Scene(game_startup_scene);
    }
}

/*!*****************************************************************************
  \brief
    Updates SageEngine
*******************************************************************************/
void update()
{
    SageTimer::Update();
    SageHelper::Update();
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
    //SageHelper::Draw();
    std::string s = "Scene 1 | FPS: " + std::to_string(SageHelper::FPS)  + "| Game Objects: " +std::to_string(Game_Objects::Get_Game_Objects().size());
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
    Assets::Unload();
    SM::Unload();
    SageHelper::Exit();
    SageAudio::Exit();
}
