/* Start Header ************************************************************************/
/*!
\file		Prefabs.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the definitions of functions that is used to initialize prefabs via
			file i/o and to get specific prefabs from the map in order to order the
			instantiation of copies of specific prefabs.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "GameObjects.hpp"
#include "Prefabs.hpp"
#include "AssetLoader.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <iostream>

static std::unordered_map<std::string, Assets::Prefabs::Prefab> prefabs;

namespace Prefabs
{	
	static bool is_initialized{ false };

	void Init()
	{
		if (is_initialized)
		{
			return;
		}
		prefabs = Assets::Prefabs::Get_Prefabs();
		is_initialized = true;
	}

	Assets::Prefabs::Prefab const& Get_Prefab(std::string _ID)
	{
		if (!is_initialized)
		{
			Init();
		}
		return prefabs[_ID];
	}
}