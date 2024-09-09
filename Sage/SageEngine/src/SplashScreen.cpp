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

#define FADE_TIME 0.75f
#define WAIT_TIME 1.5f

float time_elapsed{};

namespace Splash_Screen {

	void Load()
	{
		//Assets::Textures::Load("DIGIPEN_SPLASH_SCREEN");
		//Textures::Load(TEXTURE_DIGIPEN_SPLASH_SCREEN);
		//Audio::Load_SFX(SFX_BUTTON_CLICK);
	}

	void Init()
	{
		//SM::Reset_Fade_In();
		//SM::Reset_Fade_Out();
		//SM::Set_Next_Scene(Main_Menu::Load, Main_Menu::Init, Main_Menu::Input, Main_Menu::Update, Main_Menu::Draw, Main_Menu::Free, Main_Menu::Unload);
		//SM::Ignore_Safety_Bools(true);
	}

	void Input()
	{
		//if (AEInputCheckReleased(AEVK_ESCAPE) || AEInputCheckReleased(AEVK_SPACE) || AEInputCheckReleased(AEVK_RETURN))
		//{
		//	SM::Ignore_Safety_Bools(false);
		//	Audio::Play_SFX(SFX_BUTTON_CLICK);
		//	time_elapsed = 5.0f;
		//}

		//if (AEInputCheckReleased(AEVK_LBUTTON) || AEInputCheckReleased(AEVK_RBUTTON))
		//{
		//	SM::Ignore_Safety_Bools(false);
		//	Audio::Play_SFX(SFX_BUTTON_CLICK);
		//	time_elapsed = 5.0f;
		//}
	}

	void Update()
	{						
		float dt = 0.0f; //(float)AEFrameRateControllerGetFrameTime();
		time_elapsed += dt;		
	}

	void Draw()
	{		
		//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);		
		//Renderer::Set_Modes(AE_GFX_RM_TEXTURE, AE_GFX_BM_BLEND, AE_GFX_TM_AVERAGE, RENDER_CONFIG_DEFAULT);
		//Renderer::Draw_Sprite(TEXTURE_DIGIPEN_SPLASH_SCREEN, 0.0f, 0.0f, (float)(*Settings::Get_Screen_Width()), (float)(*Settings::Get_Screen_Height()), 0.0f, 255.0f);

		//SM::Fade_In(FADE_TIME);
		//if (time_elapsed > FADE_TIME + WAIT_TIME)
		//{
		//	SM::Fade_Out(FADE_TIME);
		//}
	}

	void Free()
	{

	}

	void Unload()
	{
		Assets::Textures::Unload();
	}
}