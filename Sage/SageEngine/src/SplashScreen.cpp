/* Start Header ************************************************************************/
/*!
\file		SplashScreen.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the definitions of functions that define the splash screen scene.
			Called by SceneManager as function pointers to determine which scene the game
			is in currently.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageRenderer.hpp"
#include "AssetLoader.hpp"
#include "Prefabs.hpp"
#include "KeyInputs.h"
#include "SageHelper.hpp"

#include "SceneManager.hpp"
#include "Game.hpp"

#include <string>
#include <iostream>
#include <memory>

#include "SageCamera.hpp"
#include "SageViewport.hpp"
namespace Splash_Screen {
	static float time_elapsed{};
	static float const wait_time{ 1.f };
	static GameObject* digipen_splash_screen;

	static SageCamera camera;
	static SageViewport vp;

	/*!*****************************************************************************
	  \brief
		Loads the Splash Screen
	*******************************************************************************/
	void Load()
	{
		digipen_splash_screen = Game_Objects::Instantiate(Prefabs::Get_Prefab("DIGIPEN_SPLASH_SCREEN"),"Digipen_Splash_Screen");
	}

	/*!*****************************************************************************
	  \brief
		Initializes the Splash Screen
	*******************************************************************************/
	void Init()
	{
		time_elapsed = 0.f;
		vp.set_position({ 0,0 });
		vp.set_dims({ static_cast<float>(SageHelper::WINDOW_WIDTH), static_cast<float>(SageHelper::WINDOW_HEIGHT)});
		vp.calculate_viewport_xform();
		vp.setViewport();

		camera.init({ 0,0 }, { SageHelper::WINDOW_WIDTH / 1.f, SageHelper::WINDOW_HEIGHT / 1.f }, 0.f, SageCamera::SageCameraType::SAGE_ORTHO);

		SageRenderer::Set_Current_View(&camera);
		SageRenderer::Set_Current_View(vp);
	}

	/*!*****************************************************************************
	  \brief
		Input functions required by the Splash Screen
	*******************************************************************************/
	void Input()
	{	
	}

	/*!*****************************************************************************
	  \brief
		Updates the Splash Screen
	*******************************************************************************/
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

	/*!*****************************************************************************
	  \brief
		Draws the Splash Screen
	*******************************************************************************/
	void Draw()
	{

	}

	/*!*****************************************************************************
	  \brief
		Frees the Splash Screen
	*******************************************************************************/
	void Free()
	{

	}

	/*!*****************************************************************************
	  \brief
		Unloads the Splash Screen
	*******************************************************************************/
	void Unload()
	{
	}
}
