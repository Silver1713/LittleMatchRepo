/* Start Header ************************************************************************/
/*!
\file		AssetLoader.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (95%)
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (5%)
\par		b.muhammadhafiz@digipen.edu, halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the data structures and functions for managing game assets, 
			including textures and prefabs.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include <unordered_map>
#include <array>
#include <string>

//forward declaration
class SageTexture;

#define PATH "../SageEngine/data/assets/audio/"
#define AUDIO_EXTENSION ".ogg"

//Every file is an asset, which is broken down into categories
namespace Assets
{
	//Texture category
	namespace Textures 
	{
		//what defines a parsed texture
		struct Texture
		{
			std::string filepath{};
			float width{}, height{};
			unsigned int sprites_per_row{}, sprites_per_col{}, sprites_num{};
			bool is_loaded{ false };
		};
		//labels for the type of information in the parsed texture
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

		/*!*****************************************************************************
		  \brief
			Parses textures.csv into a map of Textures to be called upon when Get_Texture
			calls a texture with that key
		*******************************************************************************/
		void Init();

		/*!*****************************************************************************
		  \brief
			Loads a texture with the specified ID

		  \param _ID
			The ID of the texture as specified by texture.csv
		*******************************************************************************/
		void Load(std::string const& _ID);

		/*!*****************************************************************************
		  \brief
			Gets the texture with the provided ID

		  \param _ID
			The key to look for

		  \return
			The reference to the loaded texture
		*******************************************************************************/
		SageTexture& Get_Texture(std::string const& _ID);

		/*!*****************************************************************************
		  \brief
			Provides a space for any free or unloading functions that may be required
			by subsequent interation of this component
		*******************************************************************************/
		void Unload();
	}

	//Prefabs category
	namespace Prefabs
	{
		//What defines a parsed prefab
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
			std::string object_shape{};
		};
		
		//label for each type of information a parsed prefab will have
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
			OBJ_SHAPE,
			NUM_DATA_TYPES
		} Data_Type;

		/*!*****************************************************************************
		  \brief
			Parses prefabs.csv into a map of Prefabs to be called upon when Get_Prefab
			calls a texture with that key
		*******************************************************************************/
		void Init();

		/*!*****************************************************************************
		  \brief
			Gets the Prefab with the provided ID

		  \param _prefab_ID
			The key to look for

		  \return
			The Prefab in the map with the _prefab_ID key
		*******************************************************************************/
		Prefab const& Get_Prefab(std::string const& _prefab_ID);

		/*!*****************************************************************************
		  \brief
			Gets the map of prefabs

		  \return
			The reference to the map of prefabs
		*******************************************************************************/
		std::unordered_map<std::string, Prefab>const& Get_Prefabs();
	}
	
	namespace Audio
	{
		void Init();
		std::unordered_map<std::string, std::vector<std::string>> const & Get_Audio();
	}

	namespace Font
	{
		void Init();
		//return_type const& Get_Font();
	}

	//Levels category
	namespace Levels 
	{
		//what defines a deserialized Level
		struct Level
		{
			std::vector<Prefabs::Prefab> prefabs;
			std::vector<std::string> identifier;
			std::vector<std::array<float, 3>> positions;
			std::vector<std::array<float, 3>> rotations;
			std::vector<std::array<float, 3>> scale;
			std::vector<std::array<float, 4>> color;
			std::vector<unsigned int> z_orders;
		};
		//the label for each type of information in a deserialized Level
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
			Z_ORDER,
			NUM_DATA_TYPES
		} Data_Type;

		/*!*****************************************************************************
		  \brief
			Parses all level_x.csv into a map of levels to be called upon when Get_Level
			calls a level with that key
		*******************************************************************************/
		void Init();

		/*!*****************************************************************************
		  \brief
			Gets the Level with the provided ID

		  \param _level_ID
			The key to look for

		  \return
			The Prefab in the map with the _level_ID key
		*******************************************************************************/
		Level const& Get_Level(std::string const& _level_ID);
	}
}