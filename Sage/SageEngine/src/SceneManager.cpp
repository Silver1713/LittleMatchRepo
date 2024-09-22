/* Start Header ************************************************************************/
/*!
\file		SceneManager.cpp
\title		
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the definitions of functions relating to scene management

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "AssetLoader.hpp"
#include "Prefabs.hpp"
#include "SageMain.hpp"
#include "SageHelper.hpp"
#include "Key_Inputs.h"
#include "SplashScreen.hpp"
#include "SceneManager.hpp"
#include "GameObjects.hpp"

#include <iostream>

static bool scene_has_loaded{ false };
static bool scene_has_initialized{ false };

static bool scene_faded_in{ false };
static bool scene_faded_out{ true };

static bool game_running{ true };
static bool ignore_safety_bools{ false };

const float fade_time{ 1.f };

static GameObject fade_screen;

#pragma region Public Functions
namespace SM {	
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

	void Ignore_Safety_Bools(bool _is_ignoring)
	{
		ignore_safety_bools = _is_ignoring;
	}

	void Start_Fade_In()
	{
		scene_faded_in = false;
	}

	void Start_Fade_Out()
	{
		scene_faded_out = false;
	}

	bool const& Has_Faded_In()
	{
		return scene_faded_in;
	}

	bool const& Has_Faded_Out()
	{
		return scene_faded_out;
	}

	void Load()
	{
		SM::fp_load();

		Transform t({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { 1000.f,1000.f, 0.0f });
		fade_screen.Add_Component(std::make_unique<Transform>(t));
		Sprite2D s({ "" }, { 0.f,0.f,0.f,1.f });
		fade_screen.Add_Component(std::make_unique<Sprite2D>(s));
		Game_Objects::Add_Game_Object(&fade_screen);
	}

	void Init()
	{
		SageMain::init();
		SAGE_Input_Handler::init();

		SM::fp_init();
		Game_Objects::Init();		
	}

	void Input()
	{
		SAGE_Input_Handler::update();
		SM::fp_input();
	}

	void Update()
	{
		Fade_In();
		Fade_Out();
		SageMain::update();
		Game_Objects::Update();
		SM::fp_update();
	}

	void Draw()
	{
		SageMain::draw();
		Game_Objects::Draw();
		SM::fp_draw();
	}

	void Free()
	{
		SM::fp_free();
		SageMain::exit();		
	}

	void Unload()
	{
		SM::fp_unload();
		Game_Objects::Exit();
	}

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

	void Go_To_Next_Scene()
	{
		SM::Free();
		SM::Unload();
		SM::fp_load = fp_load_tmp;
		SM::fp_init = fp_init_tmp;
		SM::fp_input = fp_input_tmp;
		SM::fp_update = fp_update_tmp;
		SM::fp_draw = fp_draw_tmp;
		SM::fp_free = fp_free_tmp;
		SM::fp_unload = fp_unload_tmp;
		Load();
		Init();
	}

	void Restart_Scene()
	{
		SM::fp_free();
		scene_has_initialized = false;
	}

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
			Sprite2D* s = dynamic_cast<Sprite2D*>(fade_screen.Get_Component(SPRITE2D)->get());
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
			Sprite2D* s = dynamic_cast<Sprite2D*>(fade_screen.Get_Component(SPRITE2D)->get());
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


	void Exit_Game()
	{
		game_running = false;
	}

	bool* Get_Game_Running()
	{
		return &game_running;
	}
}
#pragma endregion