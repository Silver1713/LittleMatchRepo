#pragma once
#include <unordered_map>
#include <string>
#include "AEEngine.h"

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
		void Load(std::string const& ID);
		AEGfxTexture* Get_AEGfxTexture(std::string const& ID);
		Texture* Get_Texture(std::string const& ID);
		void Unload();
	}
}