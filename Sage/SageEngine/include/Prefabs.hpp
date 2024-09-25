/* Start Header ************************************************************************/
/*!
\file		Prefabs.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the declarations of functions that is going to be shared to facilitate
			the use of prefabs to create copies of gameobjects.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "AssetLoader.hpp"
#include "GameObjects.hpp"

namespace Prefabs
{
	void Init();
	Assets::Prefabs::Prefab const& Get_Prefab(std::string _ID);
}
