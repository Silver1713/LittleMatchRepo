#include "Asset_Loader.h"
#include "CSV_Parser.h"

//#include "AEEngine.h"
//#include "Renderer.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace Assets
{
	namespace Textures
	{
		Parsed_CSV source;
		std::unordered_map<std::string, Texture> textures;
		std::unordered_map<std::string, AEGfxTexture*> loaded_textures;

		void Init()
		{
			source = Parse_CSV("./Data/Textures.csv");
			for (int i{1}; i < source.num_rows; i++)
			{
				Texture t;
				try
				{
					t.filepath = source.comma_seperated_data[i].associated_data[FILEPATH];
					t.width = std::stof(source.comma_seperated_data[i].associated_data[WIDTH]);
					t.height = std::stof(source.comma_seperated_data[i].associated_data[HEIGHT]);
					t.sprites_per_row = std::stoul(source.comma_seperated_data[i].associated_data[SPRITES_PER_ROW]);
					t.sprites_per_col = std::stoul(source.comma_seperated_data[i].associated_data[SPRITES_PER_COL]);
					t.sprites_num = std::stoul(source.comma_seperated_data[i].associated_data[SPRITES_NUM]);
					textures[source.comma_seperated_data[i].associated_data[ID]] = t;
				}
				catch (const std::invalid_argument& e)
				{
					std::cerr << "Invalid argument: " << e.what() << " at index " << i << std::endl;
				}
				catch (const std::out_of_range& e)
				{
					std::cerr << "Out of range: " << e.what() << " at index " << i << std::endl;
				}
			}
		}

		void Load(std::string const& ID)
		{
			if (!(textures[ID].is_loaded))
			{
				//loaded_textures[ID] = AEGfxTextureLoad(textures[ID].filepath.c_str());
				textures[ID].is_loaded = true;


				if (textures[ID].sprites_num > 1)
				{
					//Renderer::Sprite_Sheet_Mesh_Init(textures[ID].sprites_per_row,textures[ID].sprites_per_col,textures[ID].sprites_num,ID);
				}
			}
		}

		AEGfxTexture* Get_AEGfxTexture(std::string const& ID)
		{
			return loaded_textures[ID];
		}

		Texture* Get_Texture(std::string const& ID)
		{
			return &textures[ID];
		}

		void Unload()
		{
			for (std::pair<std::string, AEGfxTexture*> t : loaded_textures)
			{
				//AEGfxTextureUnload(t.second);
			}

			for (std::pair <std::string, Texture> t : textures)
			{
				t.second.is_loaded = false;
			}

			loaded_textures.clear();
		}
	}
}