#include "AssetLoader.hpp"
#include "CSVParser.hpp"

#include "SageEngine.hpp"

#include <unordered_map>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>
#include "SOIL.H"

namespace Assets
{
	namespace Textures
	{
		Parsed_CSV source;
		std::unordered_map<std::string, Texture> textures;
		std::unordered_map<std::string, SageTexture> loaded_textures;

		void Init()
		{
			source = Parse_CSV("../SageEngine/data/assets/textures.csv");
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

		void Load(std::string const& _ID)
		{
			if (!(textures[_ID].is_loaded))
			{
				loaded_textures[_ID].load_texture(textures[_ID].filepath.c_str(), SageTexture::TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
				textures[_ID].is_loaded = true;

				if (textures[_ID].sprites_num > 1)
				{
					//Renderer::Sprite_Sheet_Mesh_Init(textures[ID].sprites_per_row,textures[ID].sprites_per_col,textures[ID].sprites_num,ID);
				}
			}
		}

		SageTexture& Get_Texture(std::string const& _ID)
		{
			if (textures[_ID].is_loaded)
			{
				return loaded_textures[_ID];
			}
			else 
			{
				Load(_ID);
				return loaded_textures[_ID];
			}
		}

		void Unload()
		{
			for (auto& t : textures)
			{
				t.second.is_loaded = false;
			}

			loaded_textures.clear();
		}
	}

	namespace Prefabs 
	{
		Parsed_CSV source;
		std::unordered_map<std::string, Prefab> generated_prefabs;
		static bool has_initialized{ false };

		void Init()
		{
			source = Parse_CSV("../SageEngine/data/prefabs/prefabs.csv");
			for (int i{ 1 }; i < source.num_rows; i++)
			{
				Prefab p;
				try
				{
					p.prefab_ID = source.comma_seperated_data[i].associated_data[PREFAB_ID];
					p.positions[0] = std::stof(source.comma_seperated_data[i].associated_data[POS_X]);
					p.positions[1] = std::stof(source.comma_seperated_data[i].associated_data[POS_Y]);
					p.positions[2] = std::stof(source.comma_seperated_data[i].associated_data[POS_Z]);
					p.rotations[0] = std::stof(source.comma_seperated_data[i].associated_data[ROT_X]);
					p.rotations[1] = std::stof(source.comma_seperated_data[i].associated_data[ROT_Y]);
					p.rotations[2] = std::stof(source.comma_seperated_data[i].associated_data[ROT_Z]);
					p.scale[0] = std::stof(source.comma_seperated_data[i].associated_data[SCALE_X]);
					p.scale[1] = std::stof(source.comma_seperated_data[i].associated_data[SCALE_Y]);
					p.scale[2] = std::stof(source.comma_seperated_data[i].associated_data[SCALE_Z]);
					p.colour[0] = std::stof(source.comma_seperated_data[i].associated_data[COLOR_R]);
					p.colour[1] = std::stof(source.comma_seperated_data[i].associated_data[COLOR_G]);
					p.colour[2] = std::stof(source.comma_seperated_data[i].associated_data[COLOR_B]);
					p.colour[3] = std::stof(source.comma_seperated_data[i].associated_data[COLOR_A]);
					p.sprite_texture_ID = source.comma_seperated_data[i].associated_data[SPRITE_TEXTURE_ID];
					p.collision_data = source.comma_seperated_data[i].associated_data[COL_D];
					p.audio_data = source.comma_seperated_data[i].associated_data[AUDIO_D];

					generated_prefabs[p.prefab_ID] = p;
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
			has_initialized = true;
		}

		std::unordered_map<std::string, Prefab> const& Get_Prefabs()
		{
			if (!has_initialized)
			{
				Init();
			}
			return generated_prefabs;
		}
	}
}