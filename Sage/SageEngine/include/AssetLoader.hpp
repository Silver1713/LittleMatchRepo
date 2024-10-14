/* Start Header ************************************************************************/
/*!
\file		AssetLoader.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (95%)
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (5%)
\par		b.muhammadhafiz@digipen.edu, halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the data structures and functions for managing game assets, 
			including textures and prefabs. Handles deserialization and serialization of
			data.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include <unordered_map>
#include <array>
#include <string>

//forward declaration
class SageTexture;

//Defines the audio asset folder.
#define PATH "../SageEngine/data/assets/audio/"

//Defines the available audio extension types.
#define AUDIO_EXTENSION ".ogg"

//Every file is an asset, which is broken down into categories
namespace Assets
{
	/*!*****************************************************************************
	  \brief
		Initializes all asset categories
	*******************************************************************************/
	void Init();

	/*!*****************************************************************************
	  \brief
		Unloads any asset category that uses allocated resources
	*******************************************************************************/
	void Unload();

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

	//Animation category
	namespace Animations
	{
		//what defines an animation
		struct Animation
		{
			std::string animation_ID{};
			std::string parent_texture_ID{};
			std::string path_to_folder{};
			unsigned int num_frames{};
			float frame_time{};
		};
		//the label of each data type in an animation when deserializing
		typedef enum
		{
			ANIMATION_ID,
			PARENT_TEXTURE_ID,
			PATH_TO_FOLDER,			
			NUM_DATA_TYPES
		} Data_Type;
		/*!*****************************************************************************
		  \brief
			Deserializes the animations.csv file
		*******************************************************************************/
		void Init();

		/*!*****************************************************************************
		  \brief
			Gets the Animation with the provided ID

		  \param _anim_ID_key
			The key to look for

		  \return
			The Animation in the map with the _anim_ID_key key
		*******************************************************************************/
		Animation Get_Animation(std::string const& _anim_ID);
	}

	//Animation Set category
	namespace Animation_Set
	{
		struct Condition {
			std::string parameter;
			std::string type; // Greater, Less, Equals
			float value;
		};

		// Represents an animation state
		struct State {
			std::string name;
			std::string animation_ID;
			bool looping;
			bool is_starting_state;
		};

		// Represents a transition between states
		struct Transition {
			std::string from_state;
			std::string to_state;
			std::vector<Condition> conditions;
			float duration;
		};

		// Represents a parameter in the animation system
		struct Parameter {
			std::string name;
			float default_value;
		};

		//what defines an animation set
		struct Animation_Set
		{
			std::string animation_set_ID{};
			std::vector<State> states;
			std::vector<Transition> transitions;
			std::vector<Parameter> parameters;
		};
		//the label of each data type in an animation set
		typedef enum
		{
			ANIMATION_SET_ID,			
			ANIMATION_IDS,
			FLAGS,
			NUM_DATA_TYPES
		} Data_Type;

		/*!*****************************************************************************
		  \brief
			Deserializes all csv files in animations folder
		*******************************************************************************/
		void Init();

		/*!*****************************************************************************
		  \brief
			Gets a copy of the Animation Set with the provided ID

		  \param _anim_set_ID
			The key to look for

		  \return
			The Animation Set in the map with the _anim_set_ID key
		*******************************************************************************/
		Animation_Set Get_Animation_Set(std::string const& _anim_set_ID);
	}

	//Prefabs category
	namespace Prefabs
	{
		//What defines a parsed prefab
		struct Prefab
		{
			std::string prefab_ID{};
			std::string transform_type{};
			ToastBox::Vec3 positions{};
			ToastBox::Vec3 rotations{};
			ToastBox::Vec3 scale{};
			ToastBox::Vec4 colour{};
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
			TRANSFORM_TYPE,
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
	
	//Audio category
	namespace Audio
	{
		/*!*****************************************************************************
		  \brief
			Parses the audio asset folder and stores in a map of audio_files.
		*******************************************************************************/
		void Init();

		/*!*****************************************************************************
		  \brief
			Gets the map of audio_files that stores audio filenames

		  \return
			Map of audio filenames
		*******************************************************************************/
		std::unordered_map<std::string, std::vector<std::string>> const & Get_Audio();
	}
	
	//Font category
	namespace Font
	{
		/*!*****************************************************************************
		  \brief
			Parses the font asset folder and loads the typeface into the graphics
			renderer.
		*******************************************************************************/
		void Init();
	}

	//Levels category
	namespace Levels 
	{
		//what defines a deserialized Level
		struct Level
		{
			std::vector<Prefabs::Prefab> prefabs;
			std::vector<std::string> identifier;
			std::vector<ToastBox::Vec3> positions;
			std::vector<ToastBox::Vec3> rotations;
			std::vector<ToastBox::Vec3> scale;
			std::vector<ToastBox::Vec4> color;
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