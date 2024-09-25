/* Start Header ************************************************************************/
/*!
\file		AssetLoader.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the data structures and functions for managing game assets,
			including textures and prefabs. Currently includes the map of textures 
			and created loaded_textures and loaded prefabs to be used as assets for the engine.
			Calls the CSV parser to get data from files that is used here.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "AssetLoader.hpp"
#include "CSVParser.hpp"

#include "SageEngine.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <array>
#include <filesystem>


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
		Prefab sentinel;
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

		Prefab const& Get_Prefab( std::string const& _prefab_ID)
		{
			if (!has_initialized)
			{
				Init();
			}
			if (generated_prefabs.find(_prefab_ID) != generated_prefabs.end())
			{
				return generated_prefabs[_prefab_ID];
			}
			std::cout << "Prefab Does not exist\n";
			return sentinel;
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


	namespace Levels 
	{
		std::vector<Parsed_CSV>sources;
		std::unordered_map<std::string, Level> levels;
		Level sentinel;

		void Init()
		{
			unsigned int num_levels{};

			// Iterate through the levels directory
			for (const auto& entry : std::filesystem::directory_iterator("../SageEngine/data/levels")) 
			{
				if (std::filesystem::is_regular_file(entry.status())) 
				{
					++num_levels;
				}
			}

			for (unsigned int i{}; i < num_levels; i++)
			{
				sources.push_back(Parse_CSV("../SageEngine/data/levels/level_" + std::to_string(i+1) + ".csv"));
			}

			for (unsigned int i{}; i < num_levels; i++)
			{
				try
				{
					Level l;
					for (int j{1}; j < sources[i].num_rows; j++)
					{
						l.prefabs.push_back(Prefabs::generated_prefabs[sources[i].comma_seperated_data[j].associated_data[PREFAB_ID]]);
						l.identifier.push_back(sources[i].comma_seperated_data[j].associated_data[IDENTIFIER]);

						std::array<float, 3> position
						{
							std::stof(sources[i].comma_seperated_data[j].associated_data[POS_X]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[POS_Y]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[POS_Z])
						};

						l.positions.push_back(position);

						std::array<float, 3> rotation
						{
							std::stof(sources[i].comma_seperated_data[j].associated_data[ROT_X]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[ROT_Y]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[ROT_Z])
						};

						l.rotations.push_back(rotation);

						std::array<float, 3> scale
						{
							std::stof(sources[i].comma_seperated_data[j].associated_data[SCALE_X]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[SCALE_Y]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[SCALE_Z])
						};

						l.scale.push_back(scale);

						std::array<float, 4> color
						{
							std::stof(sources[i].comma_seperated_data[j].associated_data[COLOR_R]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[COLOR_G]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[COLOR_B]),
							std::stof(sources[i].comma_seperated_data[j].associated_data[COLOR_A])
						};

						l.color.push_back(color);
					}
					levels["Level_" + std::to_string(i+1)] = l;
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

		Level const& Get_Level(std::string const& _level_ID)
		{
			if (levels.find(_level_ID) != levels.end())
			{
				return levels[_level_ID];
			}
			else 
			{
				std::cout << "Level Does Not Exist\n";
				return sentinel;				
			}
		}
	}
}