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

#include <iostream>
#include <cstdlib>

static std::unordered_map<std::string, GameObject> game_objects;
static std::unordered_map<std::string, Transform*> transform_cache;

//FOR TESTING PURPOSES
static int const game_objects_to_create{ 2500 };

namespace Game {

	void Load()
	{
		game_objects.clear();
		transform_cache.clear();

		game_objects["Player"] = Red();
		Game_Objects::Add_Game_Object(&game_objects["Player"]);
		transform_cache["Player"] = dynamic_cast<Transform*>(game_objects["Player"].Get_Component(TRANSFORM)->get());

		for (int i{}; i < game_objects_to_create; ++i)
		{
			game_objects[std::to_string(i)] = White();
			Game_Objects::Add_Game_Object(&game_objects[std::to_string(i)]);
			transform_cache[std::to_string(i)] = dynamic_cast<Transform*>(game_objects[std::to_string(i)].Get_Component(TRANSFORM)->get());
		}
	}

	void Init()
	{
		
	}

	void Input()
	{
	}

	void Update()
	{
		transform_cache["Player"]->Translate({ (float)SageHelper::delta_time * 5.0f,0.f });
		transform_cache["Player"]->Rotate({ (float)SageHelper::delta_time * 5.0f,0.f });


		for (int i{}; i < game_objects_to_create; ++i)
		{
			transform_cache[std::to_string(i)]->Translate({ 0.f,0.f });
			transform_cache[std::to_string(i)]->Rotate({ (float)SageHelper::delta_time * 5.0f,0.f });
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