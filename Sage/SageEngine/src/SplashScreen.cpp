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
#include "AssetLoader.hpp"
#include "Prefabs.hpp"
#include "Key_Inputs.h"
#include "SageHelper.hpp"

#include "SceneManager.hpp"
#include "Game.hpp"

#include <string>
#include <iostream>

static float time_elapsed{};
static float const wait_time{ 2.f };
static GameObject digipen_splash_screen;

namespace Splash_Screen {

	void Load()
	{
		Assets::Textures::Load("DIGIPEN_SPLASH_SCREEN");

		Transform t({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { 5000.f,5000.f, 0.0f });
		digipen_splash_screen.Add_Component(std::make_unique<Transform>(t));
		Sprite2D s({ "DIGIPEN_SPLASH_SCREEN" }, {1.f,1.f,1.f,1.f});
		digipen_splash_screen.Add_Component(std::make_unique<Sprite2D>(s));
		Game_Objects::Add_Game_Object(&digipen_splash_screen);
	}

	void Init()
	{
		time_elapsed = 0.f;
	}

	void Input()
	{
		if (SAGE_Input_Handler::Get_Mouse_Clicked(SAGE_MOUSE_BUTTON_LEFT))
		{
			//Test_GO test;
			//Test_GO_2 test_go_2;

			//Transform* t = dynamic_cast<Transform*>(test.Get_Component(TRANSFORM).get());
			//Sprite2D* s = dynamic_cast<Sprite2D*>(test.Get_Component(SPRITE2D).get());
			//Collision2D* c = dynamic_cast<Collision2D*>(test.Get_Component(COLLISION2D).get());

			//float a[3]{ t->Get_Positions()[0],t->Get_Positions()[1] ,t->Get_Positions()[2] };
			//a[0]++;
			//a[1]++;
			//a[2]++;
			//t->Set_Positions(a);

			//std::string str{ "s" };
			//s->Set_Texture_ID(str);
		}		
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
		Assets::Textures::Unload();
	}
}