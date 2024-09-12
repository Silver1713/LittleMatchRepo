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
#include "GameObject.hpp"

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
		
	}

	void Input()
	{

	}

	void Update()
	{						
		float dt = 0.0f; //(float)AEFrameRateControllerGetFrameTime();
		time_elapsed += dt;		
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