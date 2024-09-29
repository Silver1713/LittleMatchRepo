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
#include "SplashScreen.hpp"
#include "SceneManager.hpp"
#include "GameObjects.hpp"

#include <iostream>

#include "SageMain.hpp"

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
	static Assets::Levels::Level current_level;

	static Function_Ptr fp_load = Splash_Screen::Load;
	static Function_Ptr fp_init = Splash_Screen::Init;
	static Function_Ptr fp_input = Splash_Screen::Input;
	static Function_Ptr fp_update = Splash_Screen::Update;
	static Function_Ptr fp_draw = Splash_Screen::Draw;
	static Function_Ptr fp_free = Splash_Screen::Free;
	static Function_Ptr fp_unload = Splash_Screen::Unload;

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
		for (unsigned int i{}; i < current_level.prefabs.size(); i++)
		{
			GameObject* g;
			Transform* t;
			Sprite2D* s;
			g = Game_Objects::Instantiate(current_level.prefabs[i], current_level.identifier[i]);
			t = dynamic_cast<Transform*>(g->Get_Component(TRANSFORM));
			t->Set_Positions({ current_level.positions[i][0],current_level.positions[i][1],current_level.positions[i][2] });
			t->Set_Rotations({ current_level.rotations[i][0],current_level.rotations[i][1],current_level.rotations[i][2] });
			t->Set_Scale({ current_level.scale[i][0],current_level.scale[i][1],current_level.scale[i][2] });

			s = dynamic_cast<Sprite2D*>(g->Get_Component(SPRITE2D));
			if (s)
			{
				s->Set_Colour({ current_level.color[i][0],current_level.color[i][1],current_level.color[i][2],current_level.color[i][3] });
			}
		}

		SM::fp_load();
		fade_screen = Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab("FADE_SCREEN"), "Fade_Screen");
	}

	/*!*****************************************************************************
	  \brief
		Initializes the Scene Manager
	*******************************************************************************/
	void Init()
	{
		SAGEInputHandler::init();

		SM::fp_init();
		Game_Objects::Init();
	}

	/*!*****************************************************************************
	  \brief
		Input Checks for the Scene Manager
	*******************************************************************************/
	void Input()
	{
		
		SM::fp_input();
		SAGEInputHandler::update();
	}

	/*!*****************************************************************************
	  \brief
		Updates the Scene Manager
	*******************************************************************************/
	void Update()
	{
		Fade_In();
		Fade_Out();
		Game_Objects::Update();
		SM::fp_update();
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
		Frees the current scene
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
	}

	/*!*****************************************************************************
	  \brief
		Set which level the game scene should load

	  \param _level_identifier
		The string key to set the current level to
	*******************************************************************************/
	void Set_Current_Level(std::string const& _level_identifier)
	{
		current_level = Assets::Levels::Get_Level(_level_identifier);
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
	void Set_Next_Scene(void(*_load)(), void(*_init)(), void (*_input)(), void(*_update)(), void (*_draw)(), void (*_free)(), void (*_unload)())
	{
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
	void Go_To_Next_Scene(std::string const& _level_identifier)
	{
		current_level = Assets::Levels::Get_Level(_level_identifier);
		SM::Free();
		SM::Unload();
		SM::fp_load = fp_load_tmp;
		SM::fp_init = fp_init_tmp;
		SM::fp_input = fp_input_tmp;
		SM::fp_update = fp_update_tmp;
		SM::fp_draw = fp_draw_tmp;
		SM::fp_free = fp_free_tmp;
		SM::fp_unload = fp_unload_tmp;
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
			Sprite2D* s = dynamic_cast<Sprite2D*>(fade_screen->Get_Component(SPRITE2D));
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
			Sprite2D* s = dynamic_cast<Sprite2D*>(fade_screen->Get_Component(SPRITE2D));
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