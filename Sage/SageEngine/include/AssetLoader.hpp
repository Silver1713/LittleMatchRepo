#pragma once
#include <unordered_map>
#include <string>

class SageTexture;

#define PATH "../SageEngine/data/assets/audio/"
#define AUDIO_EXTENSION ".ogg"

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
			float positions[3] = {};
			float rotations[3] = {};
			float scale[3] = {};
			float colour[4] = {};
			std::string sprite_texture_ID{};
			std::string collision_data{};
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
			AUDIO_D,
			NUM_DATA_TYPES
		} Data_Type;

		void Init();
		std::unordered_map<std::string, Prefab>const& Get_Prefabs();
	}
	
	namespace Audio
	{
		void Init();
		void Unload();
	}

	//namespace Font
	//{
	//	void Init();
	//	void Load();
	//	void Unload();
	//}
}