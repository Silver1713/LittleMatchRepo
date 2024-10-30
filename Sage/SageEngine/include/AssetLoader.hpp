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
#include <functional>

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
			IS_FOLDER,
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
			FRAME_TIME,
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
		struct Condition 
		{
			std::string parameter;
			std::string type; // Greater, Less, Equals			
			std::function<bool(float, float)> comparator;
			float value{};
		};

		// Represents an animation state
		struct State 
		{
			std::string name;
			Assets::Animations::Animation animation;
			float speed_multiplier{};
			bool looping{ true };
			bool is_starting_state{ false };
		};

		// Represents a transition between states
		struct Transition 
		{
			std::string from_state;
			std::string to_state;
			std::vector<Condition> conditions;
			float duration{};
		};

		// Represents a parameter in the animation system
		struct Parameter 
		{
			std::string name;
			float value{};
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
			std::string prefab_ID{""};
			std::string transform_type{"World"};
			std::string object_shape{ "Rect" };
			ToastBox::Vec3 positions{ 0,0,0 };
			ToastBox::Vec3 rotations{0,0,0};
			ToastBox::Vec3 scale{100.f,100.f,0};
			ToastBox::Vec4 colour{1.f,1.f,1.f,1.f};
			ToastBox::Vec3 velocity{0,0,0};
			std::string sprite_texture_ID{""};
			bool has_collider{false};
			bool has_physics{false};

			bool has_animator{ false };
			std::string animation_set_ID{ "" };

			bool is_button{ false };
			std::string on_click{ "Default_Click" };
			std::string on_click_hold{ "" };
			std::string on_click_release{ "" };
			std::string on_hover_enter{ "Default_Button_Update" };
			std::string on_hover{ "Default_Button_Update" };
			std::string on_hover_exit{ "Default_Button_Update" };

			bool has_children{ false };
			unsigned int num_children{};
			std::vector<std::string> children_IDs;

			bool is_slider{ false };
			//elements are Frame, Fill, BG
			std::unordered_map<std::string, std::string> slider_children_ID;
			std::string slider_init{ "" };
			std::string slider_update{ "" };

			bool has_behaviour{ false };
			unsigned int num_behaviour{};
			std::vector<std::string> cs_class_name{ "" };
			std::vector<std::string> cs_namespace{ "" };
			
		};

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

		//[HALIS]
		void Save_Prefabs(const std::string& file_path);
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
			std::string level_name;
			std::vector<Prefabs::Prefab> prefabs;
			std::vector<unsigned int> counts;
			std::vector<std::string> identifier;
			std::vector<ToastBox::Vec3> positions;
			std::vector<ToastBox::Vec3> rotations;
			std::vector<ToastBox::Vec3> scale;
			std::vector<ToastBox::Vec4> colour;
			std::vector<unsigned int> z_orders;
		};

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