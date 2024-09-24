/* Start Header ************************************************************************/
/*!
\file		SplashScreen.cpp
\title		
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the declarations of functions handling the splash screen scene.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.						
*/
/* End Header **************************************************************************/
#include "SageRenderer.hpp"
#include "AssetLoader.hpp"
#include "Prefabs.hpp"
#include "Key_Inputs.h"
#include "SageHelper.hpp"

#include "SceneManager.hpp"
#include "Game.hpp"

#include <string>
#include <iostream>

#include "SageCamera.hpp"
#include "SageViewport.hpp"
namespace Splash_Screen {
	static float time_elapsed{};
	static float const wait_time{ 2.f };
	static GameObject digipen_splash_screen;

	static SageCamera camera;
	static SageViewport vp;


	void Load()
	{
		Assets::Textures::Load("DIGIPEN_SPLASH_SCREEN");

		digipen_splash_screen = GameObject(Prefabs::Get_Prefab("DIGIPEN_SPLASH_SCREEN"));
		Game_Objects::Add_Game_Object(&digipen_splash_screen);
	}

	void Init()
	{
		time_elapsed = 0.f;
		vp.set_position({ 0,0 });
		vp.set_dims({ static_cast<float>(SageHelper::WINDOW_WIDTH), static_cast<float>(SageHelper::WINDOW_HEIGHT)});
		vp.calculate_viewport_xform();
		vp.setViewport();

		camera.init({ 0,0 }, { SageHelper::WINDOW_WIDTH / 1.f, SageHelper::WINDOW_HEIGHT / 1.f }, 0.f, SageCamera::SageCameraType::SAGE_ORTHO);

		SageRenderer::SetCurrentView(&camera);
		SageRenderer::SetCurrentView(vp);

	
	}

	void Input()
	{	
	}

	void Update()
	{
		time_elapsed += (float)SageHelper::delta_time;

		static bool is_triggered{ false };

		if (time_elapsed > wait_time)
		{
			if (!is_triggered)
			{
				SM::Start_Fade_Out();
				SM::Set_Next_Scene(Game::Load, Game::Init, Game::Input, Game::Update, Game::Draw, Game::Free, Game::Unload);
				is_triggered = true;
			}			
			if (SM::Has_Faded_Out())
			{
				is_triggered = false;				
				SM::Go_To_Next_Scene();
				SM::Start_Fade_In();
			}
		}
	}

	void Draw()
	{

	}

	void Free()
	{

	}

	void Unload()
	{
	}
}
