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

namespace Game {

	void Load()
	{
	}

	void Init()
	{	
		std::cout << Game_Objects::Get_Game_Objects().size() << std::endl;

		Red r;
		//Green g;
		//Blue b;

		//dynamic_cast<Transform*>(r.Get_Component(TRANSFORM).get())->Set_Positions({ 0.f,0.f,0.f });
		//dynamic_cast<Transform*>(g.Get_Component(TRANSFORM).get())->Set_Positions({ 100.f,100.f,0.f });
		//dynamic_cast<Transform*>(b.Get_Component(TRANSFORM).get())->Set_Positions({ -100.f,-100.f,0.f });
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