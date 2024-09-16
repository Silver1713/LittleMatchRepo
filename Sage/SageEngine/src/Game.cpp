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
#include "Prefabs.hpp"
#include "Key_Inputs.h"

#include <iostream>

static std::vector<GameObject> game_objects;

namespace Game {

	void Load()
	{
		//Red r;
		//game_objects.push_back(std::move(r));
		/*GameObject g;
		Transform t({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { 100.f,100.f, 0.0f });
		Sprite2D s({ "" }, { 1.f,1.f,1.f,1.f });
		g.Add_Component(std::make_unique<Transform>(t));
		g.Add_Component(std::make_unique<Sprite2D>(s));
		game_objects.push_back(std::move(g));

		Game_Objects::Add_Game_Object(&game_objects[0]);*/
		

		//Transform t({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { 100.f,100.f, 0.0f });
		//game_objects[0].Add_Component(std::make_unique<Transform>(t));
		//Sprite2D s({ "" }, { 1.f,1.f,1.f,1.f });
		//game_objects[0].Add_Component(std::make_unique<Sprite2D>(s));
		//Game_Objects::Add_Game_Object(&game_objects[0]);
	}

	void Init()
	{	
		std::cout << Game_Objects::Get_Game_Objects().size() << std::endl;

		//dynamic_cast<Transform*>(game_objects[0].Get_Component(TRANSFORM)->get())->Set_Positions({ 110.f,0.f,0.f });
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
	}
}