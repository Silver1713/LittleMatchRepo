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
#include "SplashScreen.hpp"
#include "SceneManager.hpp"

//#include "LevelSelect.hpp"

static bool scene_has_loaded{ false };
static bool scene_has_initialized{ false };
static bool scene_faded_in{ true };
static bool scene_faded_out{ true };

static bool game_running{ true };
static bool ignore_safety_bools{ false };

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

	void Reset_Fade_In()
	{
		scene_faded_in = false;
	}

	void Reset_Fade_Out()
	{
		scene_faded_out = false;
	}

	void Load()
	{
		if (!scene_has_loaded)
		{
			SM::fp_load();
			scene_has_loaded = true;
		}
	}

	void Init()
	{
		if (!scene_has_initialized)
		{
			SM::fp_init();
			scene_has_initialized = true;
		}
	}

	void Input()
	{
		if (scene_faded_out && scene_has_initialized)
		{
			//Input::Update();
			SM::fp_input();
		}
		else if (ignore_safety_bools && scene_has_initialized)
		{
			//Input::Update();
			SM::fp_input();
		}
	}

	void Update()
	{
		
		SM::fp_update();
	}

	void Draw()
	{
		SM::fp_draw();
	}

	void Free()
	{
		SM::fp_free();			
	}

	void Unload()
	{
		SM::fp_unload();
		//Renderer::Exit();
		//Textures::Exit();
		//Fonts::Exit();
		//Audio::Exit();
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
		//AESysFrameEnd();
		SM::Free();
		SM::Unload();
		SM::fp_load = fp_load_tmp;
		SM::fp_init = fp_init_tmp;
		SM::fp_input = fp_input_tmp;
		SM::fp_update = fp_update_tmp;
		SM::fp_draw = fp_draw_tmp;
		SM::fp_free = fp_free_tmp;
		SM::fp_unload = fp_unload_tmp;
		scene_has_initialized = false;
		scene_has_loaded = false;
		//AESysReset();
	}

	void Restart_Scene()
	{
		//AESysFrameEnd();
		SM::fp_free();
		scene_has_initialized = false;
		//AESysReset();
	}

	void Fade_In(float transition_period)
	{
		if (scene_faded_in) { return; }

		if (transition_period <= 0.0f) { return; }

		static float alpha = 255.0f;
		float dt = 0.0f; //(float)AEFrameRateControllerGetFrameTime();

		if (alpha > 0.0f)
		{
			alpha -= dt * (255.0f / transition_period);
			//Renderer::Set_Modes(AE_GFX_RM_TEXTURE, AE_GFX_BM_BLEND, AE_GFX_TM_PRECISE, RENDER_CONFIG_CUSTOM);
			//AEGfxSetColorToAdd(-1.f, -1.f, -1.f, 0.0f);
			//Renderer::Draw_Sprite(TEXTURE_PRIMITIVE_SQUARE, 0.0f, 0.0f, (float)*Settings::Get_Screen_Width(), (float)*Settings::Get_Screen_Height(), 0.0f, alpha);
			//AEGfxSetColorToAdd(0.f, 0.f, 0.f, 0.0f);
			return;
		}
		else
		{
			alpha = 0.0f;
			//Renderer::Set_Modes(AE_GFX_RM_TEXTURE, AE_GFX_BM_BLEND, AE_GFX_TM_PRECISE, RENDER_CONFIG_CUSTOM);
			//AEGfxSetColorToAdd(-1.f, -1.f, -1.f, 0.0f);
			//Renderer::Draw_Sprite(TEXTURE_PRIMITIVE_SQUARE, 0.0f, 0.0f, (float)*Settings::Get_Screen_Width(), (float)*Settings::Get_Screen_Height(), 0.0f, alpha);
			//AEGfxSetColorToAdd(0.f, 0.f, 0.f, 0.0f);
			scene_faded_in = true;
			alpha = 255.0f;
			return;
		}
	}

	void Fade_Out(float transition_period)
	{
		if (scene_faded_out) { return; }

		if (transition_period <= 0.0f) { return; }

		static float alpha = 0.0f;
		float dt = 0.0f; //(float)AEFrameRateControllerGetFrameTime();

		if (alpha < 255.0f)
		{
			alpha += dt * (255.0f / transition_period);
			//Renderer::Set_Modes(AE_GFX_RM_TEXTURE, AE_GFX_BM_BLEND, AE_GFX_TM_PRECISE, RENDER_CONFIG_CUSTOM);
			//AEGfxSetColorToAdd(-1.f, -1.f, -1.f, 0.0f);
			//Renderer::Draw_Sprite(TEXTURE_PRIMITIVE_SQUARE, 0.0f, 0.0f, (float)*Settings::Get_Screen_Width(), (float)*Settings::Get_Screen_Width(), 0.0f, alpha);
			//AEGfxSetColorToAdd(0.f, 0.f, 0.f, 0.0f);
			return;
		}
		else
		{
			//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
			alpha = 255.0f;
			//Renderer::Set_Modes(AE_GFX_RM_TEXTURE, AE_GFX_BM_BLEND, AE_GFX_TM_PRECISE, RENDER_CONFIG_CUSTOM);
			//AEGfxSetColorToAdd(-1.f, -1.f, -1.f, 0.0f);
			//Renderer::Draw_Sprite(TEXTURE_PRIMITIVE_SQUARE, 0.0f, 0.0f, (float)*Settings::Get_Screen_Width(), (float)*Settings::Get_Screen_Width(), 0.0f, alpha);
			//AEGfxSetColorToAdd(0.f, 0.f, 0.f, 0.0f);
			scene_faded_out = true;
			alpha = 0.0f;
			SM::Go_To_Next_Scene();
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