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

#include <string>

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
		Test_GO test;
		Test_GO_2 test_go_2;
		Test_GO test2;

		Transform* t = dynamic_cast<Transform*>(test.Get_Component(TRANSFORM).get());
		Sprite2D* s = dynamic_cast<Sprite2D*>(test.Get_Component(SPRITE2D).get());
		Collision2D* c = dynamic_cast<Collision2D*>(test.Get_Component(COLLISION2D).get());

		Game_Objects::Init();

		float a[3]{ 9.0f,9.0f,9.0f };
		t->Set_Positions(a);

		std::string str{ "s" };
		s->Set_Texture_ID(str);

		Game_Objects::Init();
	}

	void Input()
	{

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