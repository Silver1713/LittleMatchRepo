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
#include "Systems/SageScripting.hpp"
#include "Game.hpp"
#include "SageMonoManager.hpp"
#include "SageFrameBuffer.hpp"
#include "SageEngine.hpp"
#include <SageSystemManager.hpp>

const GLFWvidmode* mode;
namespace {
    SageFrameBuffer frame_buffer;
    int loop = 60;
    int window = 3;
    const std::string window_config_path = "../SageEngine/data/configuration/project_config.json";
    constexpr double physics_update_target = 0.02;
    static double accumulator = 0;

}

void SageEngine::Init()
{
    SageMonoManager::Initialize();
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
    frame_buffer.Init(window_width, window_height);
    SageRenderer::Set_Framebuffer(&frame_buffer);
    SageTimer::Init();

    if (status)
    {
        std::cerr << "Sage failed to create OpenGL context.";

        std::exit(EXIT_FAILURE);
    }
    Assets::Init();
    Prefabs::Init();
    SageAudio::Init();
    SAGEInputHandler::init();
    SageSystemManager::Init();
    if (1) // to be changed with some sort of flag to detect if running through editor or as built game
    {
        SM::Startup_Scene(editor_startup_scene);
    }
    else
    {
        SM::Startup_Scene(game_startup_scene);
    }
}


void SageEngine::Init(const char* editor_config_path)
{
    SageMonoManager::Initialize();
    SageTimer::Init();
    SAGEInputHandler::init();
    SageSystemManager::Init();

    SageJSON::SageJSON editor_config;
  

	std::ifstream editorfile(editor_config_path);


    while (editorfile)
    {
		editorfile >> editor_config;
    }


	editorfile.close();

	bool useWindowedFullScreen = editor_config["Window"]["UseWindowedFullScreen"].as<SageJSON::SageJSON::BoolValue>();


	int window_width = static_cast<int>(editor_config["Window"]["Width"].as<SageJSON::SageJSON::NumberValue>());
    int window_height = static_cast<int>(
        editor_config["Window"]["Height"].as<SageJSON::SageJSON::NumberValue>());
    if (useWindowedFullScreen)
    {
        if (!glfwInit()) return;
		mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		window_width = mode->width;
		window_height = mode->height;


    }







    std::string window_title = editor_config["Window"]["Title"].as<SageJSON::SageJSON::StringValue>();
    std::string editor_startup_scene = editor_config["Other_Configurations"]["Editor_Startup_Scene"].as<SageJSON::SageJSON::StringValue>();
    std::string game_startup_scene = editor_config["Other_Configurations"]["Game_Startup_Scene"].as<SageJSON::SageJSON::StringValue>();

	editor_config.close();

    int status = SageHelper::Init(window_width, window_height, window_title.c_str());
    SageShaderManager::Add_Shader_Include("graphic_lib", "../SageGraphics/shaders/");
    SageRenderer::Init();
    frame_buffer.Init(window_width, window_height);
    SageRenderer::Set_Framebuffer(&frame_buffer);
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
}

void SageEngine::Input()
{
    SM::Input();
}


void SageEngine::Update()
{
    SageTimer::Update();
    std::cout << SageTimer::delta_time << std::endl;
    SageHelper::Update();
    accumulator += SageTimer::delta_time;
    if (accumulator >= physics_update_target)
    {
        PhysicsUpdate();
        accumulator -= physics_update_target;
    }
    
    SM::Update();

    SageAudio::Update();
}


void SageEngine::PhysicsUpdate()
{
}

void SageEngine::Draw(bool inEditor)
{
    if (inEditor) SageRenderer::Enable_OffScreenRender(); else SageRenderer::Enable_OnScreenRender();
    std::string s = "Scene 1 | FPS: " + std::to_string(SageHelper::FPS) + "| Game Objects: " + std::to_string(Game_Objects::Get_Game_Objects().size());
    SageHelper::sage_ptr_window->Set_Title(s.c_str());
    SageRenderer::Clear_Color({1, 1, 1, 1});
    SM::Draw();
    SageRenderer::Enable_OnScreenRender();
}



void SageEngine::Exit()
{
    Game_Objects::Exit();
    SM::Free();
    Assets::Unload();
    SM::Unload();
    SageHelper::Exit();
    SageAudio::Exit();
}