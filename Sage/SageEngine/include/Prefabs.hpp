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

//Prefabs category serving as middleman between assets and gameobjects
namespace Prefabs
{
	/*!*****************************************************************************
	  \brief
		Initializes all components of all gameobjects
	*******************************************************************************/
	void Init();
	/*!*****************************************************************************
	  \brief
		Gets the Prefab with the provided ID

	  \param _ID
		The key to look for

	  \return
		The Prefab in the map with the _ID key
	*******************************************************************************/
	Assets::Prefabs::Prefab const& Get_Prefab(std::string _ID);
}
