/* Start Header ************************************************************************/
/*!
\file		Game.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		12 September 2024
\brief		Contains the declarations of functions that defines the game scene.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
//Game Scene serving as testbed for level implementation
namespace Game {

	struct SpawnProperties {
		std::string prefab_name;
		std::string object_name;
		ToastBox::Vec3 position_range_min = { -960.0f, -540.0f, 0.0f };
		ToastBox::Vec3 position_range_max = { 1920.0f, 1080.0f, 0.0f };
		ToastBox::Vec3 rotation_range_min = { 0.0f, 0.0f, 0.0f };
		ToastBox::Vec3 rotation_range_max = { 360.0f, 360.0f, 0.0f };
		ToastBox::Vec3 scale_range_min = { 1.0f, 1.0f, 0.0f };
		ToastBox::Vec3 scale_range_max = { 10.0f, 10.0f, 0.0f };
		bool enable_physics = false;
		bool enable_collider = true;
		bool show_collider_debug = false;
	};

	// Add the function declaration for Spawn_Dynamic_Object
	GameObject* Spawn_Dynamic_Object(const SpawnProperties& props);

	/*!*****************************************************************************
	  \brief
		Loads data the scene may need
	*******************************************************************************/
	void Load();
	/*!*****************************************************************************
	  \brief
		Initializes the scene
	*******************************************************************************/
	void Init();
	/*!*****************************************************************************
	  \brief
		Handles input checks in the scene
	*******************************************************************************/
	void Input();
	/*!*****************************************************************************
	  \brief
		Updates the game scene
	*******************************************************************************/
	void Update();
	/*!*****************************************************************************
	  \brief
		Draws the game scene
	*******************************************************************************/
	void Draw();
	/*!*****************************************************************************
	  \brief
		Frees the game scene
	*******************************************************************************/
	void Free();
	/*!*****************************************************************************
	  \brief
		Unloads the game scene
	*******************************************************************************/
	void Unload();
}