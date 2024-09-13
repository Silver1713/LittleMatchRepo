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

#include <string>
#include <iostream>

#define FADE_TIME 0.75f
#define WAIT_TIME 1.5f

float time_elapsed{};

namespace Splash_Screen {

	void Load()
	{
		Assets::Textures::Load("DIGIPEN_SPLASH_SCREEN");		
	}

	void Init()
	{		
		Game_Objects::Init();
		SAGE_Input_Handler::init();
	}

	void Input()
	{
		SAGE_Input_Handler::update();
		

		if (SAGE_Input_Handler::Get_Mouse_Clicked(SAGE_MOUSE_BUTTON_LEFT))
		{
			Test_GO test;
			Test_GO_2 test_go_2;

			Transform* t = dynamic_cast<Transform*>(test.Get_Component(TRANSFORM).get());
			Sprite2D* s = dynamic_cast<Sprite2D*>(test.Get_Component(SPRITE2D).get());
			Collision2D* c = dynamic_cast<Collision2D*>(test.Get_Component(COLLISION2D).get());

			float a[3]{ t->Get_Positions()[0],t->Get_Positions()[1] ,t->Get_Positions()[2] };
			a[0]++;
			a[1]++;
			a[2]++;
			t->Set_Positions(a);

			std::string str{ "s" };
			s->Set_Texture_ID(str);

			Game_Objects::Init();
		}
	}

	void Update()
	{
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