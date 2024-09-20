/* Start Header ************************************************************************/
/*!
\file		Game.cpp
\title		
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		15 September 2024
\brief		Contains the declarations of functions handling the game scene.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.						
*/
/* End Header **************************************************************************/
#include "AssetLoader.hpp"
#include "SageHelper.hpp"
#include "Prefabs.hpp"
#include "Key_Inputs.h"

#include "SceneManager.hpp"
#include "SplashScreen.hpp"

#include <iostream>
#include <random>

static std::unordered_map<std::string, GameObject> game_objects;
static std::unordered_map<std::string, Transform*> transform_cache;
static GameObject background;

//FOR TESTING PURPOSES
#include <cstdlib> // for srand()
static int const game_objects_to_create{ 2500 };
static float const min_pos[3]{ -960.0f,-540.0f,0.0f }, max_pos[3]{ 1920.0f,1080.0f,0.0f };
static float const min_rot[3]{ 0.0f,0.0f,0.0f }, max_rot[3]{ 360.0f,360.0f,0.0f };
static float const min_scale[3]{ 1.0f,1.0f,0.0f }, max_scale[3]{ 10.0f,10.0f,0.0f };
static float const min_col[3]{ 0.0f,0.0f,0.0f }, max_col[3]{100.0f,100.0f,100.0f };

namespace Game {

	void Load()
	{
		game_objects.clear();
		transform_cache.clear();

		Assets::Textures::Load("BLUE_SKY");

		Transform t({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { 960.f,540.f, 0.0f });
		background.Add_Component(std::make_unique<Transform>(t));
		Sprite2D s({ "BLUE_SKY" }, { 1.f,1.f,1.f,1.f });
		background.Add_Component(std::make_unique<Sprite2D>(s));
		Game_Objects::Add_Game_Object(&background);

		game_objects["Player"] = Red();
		Game_Objects::Add_Game_Object(&game_objects["Player"]);
		transform_cache["Player"] = dynamic_cast<Transform*>(game_objects["Player"].Get_Component(TRANSFORM)->get());
		//transform_cache["Player"]->Set_Positions({ 0.0f,0.0f,0.0f });
		//transform_cache["Player"]->Set_Scale({ 50.0f,50.0f,0.0f });

		//2.5k objects test
		for (int i{}; i < game_objects_to_create; ++i)
		{
			game_objects[std::to_string(i)] = White();
			Game_Objects::Add_Game_Object(&game_objects[std::to_string(i)]);
			transform_cache[std::to_string(i)] = dynamic_cast<Transform*>(game_objects[std::to_string(i)].Get_Component(TRANSFORM)->get());

			float pos[3]{ (float)(std::rand() % (int)max_pos[0] + (int)min_pos[0]), (float)(std::rand() % (int)max_pos[1] + (int)min_pos[1]),0.0f };
			float rot[3]{ (float)(std::rand() % (int)max_rot[0] + (int)min_rot[0]), (float)(std::rand() % (int)max_rot[1] + (int)min_rot[1]),0.0f };
			float scale[3]{ (float)(std::rand() % (int)max_scale[0] + (int)min_scale[0]), (float)(std::rand() % (int)max_scale[1] + (int)min_scale[1]),0.0f };
			float col[3]{ (float)(std::rand() % (int)max_col[0] + (int)min_col[0]) / 100.0f, (float)(std::rand() % (int)max_col[1] + (int)min_col[1]) / 100.0f,(float)(std::rand() % (int)max_col[2] + (int)min_col[2])/100.0f };

			transform_cache[std::to_string(i)]->Set_Positions({ pos[0],pos[1],pos[2]});
			transform_cache[std::to_string(i)]->Set_Rotations({ rot[0],rot[1],rot[2]});
			transform_cache[std::to_string(i)]->Set_Scale({ scale[0],scale[1],scale[2]});

			Sprite2D* s = dynamic_cast<Sprite2D*>(game_objects[std::to_string(i)].Get_Component(SPRITE2D)->get());
			s->Set_Colour({col[0],col[1],col[2]});

			game_objects[std::to_string(i)].Disable();
		}
	}

	void Init()
	{
		
	}

	void Input()
	{
		//tests

		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_W))
		{
			transform_cache["Player"]->Translate({ 0.f,(float)SageHelper::delta_time * 100.0f,0.f });
		}
		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_A))
		{
			transform_cache["Player"]->Translate({ (float)SageHelper::delta_time * (-100.0f),0.f,0.f });
		}
		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_S))
		{
			transform_cache["Player"]->Translate({ 0.f,(float)SageHelper::delta_time * (-100.0f),0.f });
		}
		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_D))
		{
			transform_cache["Player"]->Translate({ (float)SageHelper::delta_time * 100.0f,0.f,0.f });
		}
		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_Q))
		{
			transform_cache["Player"]->Rotate({ (float)SageHelper::delta_time * 10.0f,0.0f,0.f });
		}
		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_E))
		{
			transform_cache["Player"]->Rotate({ (float)SageHelper::delta_time * (-10.0f),0.0f,0.f });
		}
		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_Z))
		{
			transform_cache["Player"]->Scale({ (float)SageHelper::delta_time * 100.0f,(float)SageHelper::delta_time * 100.0f,0.f });
		}
		if (SAGE_Input_Handler::Get_Key(SAGE_KEY_X))
		{
			transform_cache["Player"]->Scale({ (float)SageHelper::delta_time * (-100.0f),(float)SageHelper::delta_time * (-100.0f),0.f });
		}

		if (SAGE_Input_Handler::Get_Key_Pressed(SAGE_KEY_1))
		{
			if (game_objects["0"].Is_Enabled())
			{
				return;
			}

			for (int i{}; i < game_objects_to_create; ++i)
			{
				game_objects[std::to_string(i)].Enable();
			}
		}
		if (SAGE_Input_Handler::Get_Key_Pressed(SAGE_KEY_2))
		{
			if (!(game_objects["0"].Is_Enabled()))
			{
				return;
			}

			for (int i{}; i < game_objects_to_create; ++i)
			{
				game_objects[std::to_string(i)].Disable();
			}
		}
		if (SAGE_Input_Handler::Get_Key_Pressed(SAGE_KEY_3))
		{
			//other tests
		}
	}

	void Update()
	{
		//transform_cache["Player"]->Rotate({ (float)SageHelper::delta_time * 5.0f,0.f });


		for (int i{}; i < game_objects_to_create; ++i)
		{
			//transform_cache[std::to_string(i)]->Translate({ (float)SageHelper::delta_time * 50.0f,0.f });
			transform_cache[std::to_string(i)]->Rotate({ (float)SageHelper::delta_time * 5.0f,0.f,0.0f });
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