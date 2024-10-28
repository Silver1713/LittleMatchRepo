/* Start Header ************************************************************************/
/*!
\file		SceneManager.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the definitions of functions that defines the scene management aspect
			of the engine. Stores the function pointers to determine which scene is being
			loaded, including the fadescreen used to transition between scenes.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "AssetLoader.hpp"
#include "Prefabs.hpp"

#include "SageRenderer.hpp"
#include "SageHelper.hpp"
#include "KeyInputs.h"
#include "SceneManager.hpp"
#include "GameObjects.hpp"

#include <iostream>

#include "EditorScene.hpp"
#include "SplashScreen.hpp"
#include "Scene.hpp"
#include "Game.hpp"

#include "SageMain.hpp"
#include "SageSystemManager.hpp"

#pragma region Public Functions
namespace SM {	
	static bool scene_has_loaded{ false };
	static bool scene_has_initialized{ false };

	static bool scene_faded_in{ false };
	static bool scene_faded_out{ true };

	static bool game_running{ true };
	static bool ignore_safety_bools{ false };

	const float fade_time{ 0.5f };

	static GameObject* fade_screen{ nullptr };
	static std::string prev_level_ID{};
	static std::string level_ID{};
	static Assets::Levels::Level current_level;	

	static Function_Ptr fp_load;
	static Function_Ptr fp_init;
	static Function_Ptr fp_input;
	static Function_Ptr fp_update;
	static Function_Ptr fp_draw;
	static Function_Ptr fp_free;
	static Function_Ptr fp_unload;

	static Function_Ptr fp_load_tmp;
	static Function_Ptr fp_init_tmp;
	static Function_Ptr fp_input_tmp;
	static Function_Ptr fp_update_tmp;
	static Function_Ptr fp_draw_tmp;
	static Function_Ptr fp_free_tmp;
	static Function_Ptr fp_unload_tmp;

	/*!*****************************************************************************
	  \brief
		This function specifies if the scene should ignore safety checks just in case
		some systems havent fully loaded before accepting inputs

	  \param _is_ignoring
		Whether the scene manager should accept inputs
	*******************************************************************************/
	void Ignore_Safety_Bools(bool _is_ignoring)
	{
		ignore_safety_bools = _is_ignoring;
	}

	/*!*****************************************************************************
	  \brief
		Begins the fading in animation
	*******************************************************************************/
	void Start_Fade_In()
	{
		scene_faded_in = false;
	}

	/*!*****************************************************************************
	  \brief
		Begins the fading out animation
	*******************************************************************************/
	void Start_Fade_Out()
	{
		scene_faded_out = false;
	}

	/*!*****************************************************************************
	  \brief
		Gets the state of the faded_in flag
	  \return
		the faded_in flag
	*******************************************************************************/
	bool const& Has_Faded_In()
	{
		return scene_faded_in;
	}

	/*!*****************************************************************************
	  \brief
		Gets the state of the faded_out flag
	  \return
		the faded_out flag
	*******************************************************************************/
	bool const& Has_Faded_Out()
	{
		return scene_faded_out;
	}

	/*!*****************************************************************************
	  \brief
		Loads the Scene Manager
	*******************************************************************************/
	void Load()
	{
		//Creates all prefabs that are supposed to exist in current level scene
		for (unsigned int i{}; i < current_level.prefabs.size(); ++i)
		{
			for (unsigned int j{}; j < current_level.counts[i]; ++j)
			{
				GameObject* g{ nullptr };
				Transform* t{ nullptr };
				UITransform* ut{ nullptr };
				Sprite2D* s{ nullptr };
				Image* img{ nullptr };
				std::string identifier{};
				if (current_level.counts[i] > 1u)
				{
					identifier = current_level.identifier[i] + '_' + std::to_string(j);
				}
				else 
				{
					identifier = current_level.identifier[i];
				}

				g = Game_Objects::Instantiate(current_level.prefabs[i], identifier, current_level.z_orders[i]);
				t = static_cast<Transform*>(g->Get_Component<Transform>());
				ut = static_cast<UITransform*>(g->Get_Component<UITransform>());
				if (ut)
				{
					ut->Set_Position(current_level.positions[i]);
					ut->Set_Rotation(current_level.rotations[i]);
					ut->Set_Scale(current_level.scale[i]);
				}
				else if (t)
				{
					t->Set_Position(current_level.positions[i]);
					t->Set_Rotation(current_level.rotations[i]);
					t->Set_Scale(current_level.scale[i]);
				}

				s = static_cast<Sprite2D*>(g->Get_Component<Sprite2D>());
				img = static_cast<Image*>(g->Get_Component<Image>());
				if (s)
				{
					s->Set_Colour(current_level.colour[i]);
				}
				else if (img)
				{
					img->Set_Colour(current_level.colour[i]);
				}
			}
		}
		
		fade_screen = Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab("FADE_SCREEN"), "Fade_Screen",2U);
		scene_faded_in = false;
		SM::fp_load();
	}

	/*!*****************************************************************************
	  \brief
		Initializes the Scene Manager
	*******************************************************************************/
	void Init()
	{
		SAGEInputHandler::init();
		SageSystemManager::Init();
		Game_Objects::Init();
		SM::fp_init();
	}

	/*!*****************************************************************************
	  \brief
		Input Checks for the Scene Manager
	*******************************************************************************/
	void Input()
	{
		
		
		SM::fp_input();
	}

	/*!*****************************************************************************
	  \brief
		Updates the Scene Manager
	*******************************************************************************/
	void Update()
	{
		SAGEInputHandler::update();
		Fade_In();
		Fade_Out();
		SM::fp_update();
		Game_Objects::Update();

		if (level_ID != prev_level_ID)
		{
			Go_To_Next_Scene();
		}
		prev_level_ID = level_ID;
	}

	/*!*****************************************************************************
	  \brief
		Draws the current scene
	*******************************************************************************/
	void Draw()
	{		
		Game_Objects::Draw();
		SM::fp_draw();
	}

	/*!*****************************************************************************
	  \brief
		Frees the current sceneas
	*******************************************************************************/
	void Free()
	{
		SM::fp_free();	
	}

	/*!*****************************************************************************
	  \brief
		Unloads the current scene
	*******************************************************************************/
	void Unload()
	{
		SM::fp_unload();
		
		Game_Objects::Exit();
		SageSystemManager::Exit();
	}

	/*!*****************************************************************************
	  \brief
		Set which level the game scene should load

	  \param _level_identifier
		The string key to set the current level to
	*******************************************************************************/
	void Set_Current_Level(std::string const& _level_identifier)
	{
		level_ID = _level_identifier;
	}

	/*!*****************************************************************************
	  \brief
		Sets what function pointers to turn the current scene's one into when
		Go_To_Next_Scene is called

	  \param _load
		the load function that the scene manager will use

	  \param _init
		the init function that the scene manager will use

	  \param _input
		the input function that the scene manager will use

	  \param _update
		the update function that the scene manager will use

	  \param _draw
		the draw function that the scene manager will use

	  \param _free
		the free function that the scene manager will use

	  \param _unload
		the unload function that the scene manager will use
	*******************************************************************************/
	void Set_Next_Scene(void(*_load)(), void(*_init)(), void (*_input)(), void(*_update)(), void (*_draw)(), void (*_free)(), void (*_unload)(), std::string const& new_level_ID)
	{
		level_ID = new_level_ID;
		SM::fp_load_tmp = _load;
		SM::fp_init_tmp = _init;
		SM::fp_input_tmp = _input;
		SM::fp_update_tmp = _update;
		SM::fp_draw_tmp = _draw;
		SM::fp_free_tmp = _free;
		SM::fp_unload_tmp = _unload;
	}

	/*!*****************************************************************************
	  \brief
		Goes to the next scene as specified by Set_Next_Scene

	  \param _level_identifier
		The string key for what level should be next scene
	*******************************************************************************/
	void Go_To_Next_Scene()
	{
		current_level = Assets::Levels::Get_Level(level_ID);
		if (level_ID == "level_1")
		{
			SM::fp_load = Game::Load;
			SM::fp_init = Game::Init;
			SM::fp_draw = Game::Draw;
			SM::fp_input = Game::Input;
			SM::fp_update = Game::Update;
			SM::fp_draw = Game::Draw;
			SM::fp_free = Game::Free;
			SM::fp_unload = Game::Unload;
		}
		else
		{
			SM::fp_load = Scene::Load;
			SM::fp_init = Scene::Init;
			SM::fp_draw = Scene::Draw;
			SM::fp_input = Scene::Input;
			SM::fp_update = Scene::Update;
			SM::fp_draw = Scene::Draw;
			SM::fp_free = Scene::Free;
			SM::fp_unload = Scene::Unload;
		}
		SM::Free();
		SM::Unload();
		SM::Load();
		SM::Init();

		std::cout << "Moving to next scene: " << level_ID << std::endl;
	}
	/*!*****************************************************************************
	  \brief
		Sets up startup scene for when the engine is run

	  \param _level_identifier
		The string key for what level should be next scene
	*******************************************************************************/
	void Startup_Scene(std::string const& _new_level_ID)
	{
		level_ID = _new_level_ID;
		prev_level_ID = level_ID;
		current_level = Assets::Levels::Get_Level(_new_level_ID);
		if (level_ID == "splash_screen")
		{
			SM::fp_load = Splash_Screen::Load;
			SM::fp_init = Splash_Screen::Init;
			SM::fp_draw = Splash_Screen::Draw;
			SM::fp_input = Splash_Screen::Input;
			SM::fp_update = Splash_Screen::Update;
			SM::fp_draw = Splash_Screen::Draw;
			SM::fp_free = Splash_Screen::Free;
			SM::fp_unload = Splash_Screen::Unload;
		}
		else if (level_ID == "level_1")
		{
			SM::fp_load = Game::Load;
			SM::fp_init = Game::Init;
			SM::fp_draw = Game::Draw;
			SM::fp_input = Game::Input;
			SM::fp_update = Game::Update;
			SM::fp_draw = Game::Draw;
			SM::fp_free = Game::Free;
			SM::fp_unload = Game::Unload;
		}
		else if (level_ID == "editor_scene")
		{
			SM::fp_load = EditorScene::Load;
			SM::fp_init = EditorScene::Init;
			SM::fp_draw = EditorScene::Draw;
			SM::fp_input = EditorScene::Input;
			SM::fp_update = EditorScene::Update;
			SM::fp_draw = EditorScene::Draw;
			SM::fp_free = EditorScene::Free;
			SM::fp_unload = EditorScene::Unload;
		}
		else
		{
			SM::fp_load = Scene::Load;
			SM::fp_init = Scene::Init;
			SM::fp_draw = Scene::Draw;
			SM::fp_input = Scene::Input;
			SM::fp_update = Scene::Update;
			SM::fp_draw = Scene::Draw;
			SM::fp_free = Scene::Free;
			SM::fp_unload = Scene::Unload;
		}
		SM::Load();
		SM::Init();
	}

	/*!*****************************************************************************
	  \brief
		Restarts the scene
	*******************************************************************************/
	void Restart_Scene()
	{
		SM::fp_free();
		scene_has_initialized = false;
	}

	/*!*****************************************************************************
	  \brief
		Calculates the current alpha for the transition screen depending on time that
		has passed
	*******************************************************************************/
	void Fade_In()
	{
		static float alpha{ 1.f };

		if ((fade_time <= 0.f) || scene_faded_in)
		{
			return;
		}
		
		float dt = (float)SageHelper::delta_time;

		if (alpha > 0.0f)
		{
			alpha -= dt * (1.0f / fade_time);
			Image* s = static_cast<Image*>(fade_screen->Get_Component<Image>());
			s->Set_Transparency(alpha);
			return;
		}
		else
		{
			alpha = 1.f;
			scene_faded_in = true;
			return;
		}
	}

	/*!*****************************************************************************
	  \brief
		Calculates the current alpha for the transition screen depending on time that
		has passed
	*******************************************************************************/
	void Fade_Out()
	{
		static float alpha{ 0.f };

		if ((fade_time <= 0.f) || scene_faded_out)
		{
			return;
		}

		float dt = (float)SageHelper::delta_time;

		if (alpha < 1.0f)
		{
			alpha += dt * (1.0f / fade_time);
			Sprite2D* s = static_cast<Sprite2D*>(fade_screen->Get_Component<Sprite2D>());
			s->Set_Transparency(alpha);
			return;
		}
		else
		{
			alpha = 0.f;
			scene_faded_out = true;
			return;
		}
	}

	/*!*****************************************************************************
	  \brief
		Exits the loop
	*******************************************************************************/
	void Exit_Game()
	{
		game_running = false;
	}

	/*!*****************************************************************************
	  \brief
		Gets the game running flag
	*******************************************************************************/
	bool* Get_Game_Running()
	{
		return &game_running;
	}
}
#pragma endregion