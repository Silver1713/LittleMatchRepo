/* Start Header ************************************************************************/
/*!
\file		AssetLoader.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the data structures and functions for managing game assets, 
			including textures and prefabs.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include <unordered_map>
#include <array>
#include <string>

class SageTexture;

namespace Assets
{
	namespace Textures 
	{
		struct Texture
		{
			std::string filepath{};
			float width{}, height{};
			unsigned int sprites_per_row{}, sprites_per_col{}, sprites_num{};
			bool is_loaded{ false };
		};

		typedef enum
		{
			ID,
			FILEPATH,
			WIDTH,
			HEIGHT,
			SPRITES_PER_ROW,
			SPRITES_PER_COL,
			SPRITES_NUM,
			NUM_DATA_TYPES
		} Data_Type;

		void Init();
		void Load(std::string const& _ID);
		SageTexture& Get_Texture(std::string const& _ID);
		void Unload();
	}

	namespace Prefabs
	{
		struct Prefab
		{
			std::string prefab_ID{};
			float positions[3]{};
			float rotations[3]{};
			float scale[3]{};
			float colour[4]{};
			std::string sprite_texture_ID{};
			std::string collision_data{};
			std::string has_physics{};
			float velocity{};
			std::string audio_data{};
		};

		typedef enum
		{
			PREFAB_ID,
			POS_X,
			POS_Y,
			POS_Z,
			ROT_X,
			ROT_Y,
			ROT_Z,
			SCALE_X,
			SCALE_Y,
			SCALE_Z,
			COLOR_R,
			COLOR_G,
			COLOR_B,
			COLOR_A,
			SPRITE_TEXTURE_ID,
			COL_D,
			HAS_PHYSICS,
			PHYSICS_VELOCITY,
			AUDIO_D,
			NUM_DATA_TYPES
		} Data_Type;

		void Init();
		Prefab const& Get_Prefab(std::string const& _prefab_ID);
		std::unordered_map<std::string, Prefab>const& Get_Prefabs();
	}

	namespace Levels 
	{
		struct Level
		{
			std::vector<Prefabs::Prefab> prefabs;
			std::vector<std::string> identifier;
			std::vector<std::array<float, 3>> positions;
			std::vector<std::array<float, 3>> rotations;
			std::vector<std::array<float, 3>> scale;
			std::vector<std::array<float, 4>> color;
		};
		typedef enum
		{
			PREFAB_ID,
			IDENTIFIER,
			POS_X,
			POS_Y,
			POS_Z,
			ROT_X,
			ROT_Y,
			ROT_Z,
			SCALE_X,
			SCALE_Y,
			SCALE_Z,
			COLOR_R,
			COLOR_G,
			COLOR_B,
			COLOR_A,
			NUM_DATA_TYPES
		} Data_Type;

		void Init();
		Level const& Get_Level(std::string const& _level_ID);
	}
}