/* Start Header ************************************************************************/
/*!
\file		AssetLoader.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (75%)
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (25%)
\par		b.muhammadhafiz@digipen.edu, halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the data structures and functions for managing game assets,
			including textures and prefabs.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
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


#include "fmod.hpp"
#include "fmod_errors.h"
#include "SageAudio.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

//Every file is an asset, which is broken down into categories
namespace Assets
{
	//Texture category
	namespace Textures
	{		
		Parsed_CSV source;
		std::unordered_map<std::string, Texture> textures;
		std::unordered_map<std::string, SageTexture> loaded_textures;

		/*!*****************************************************************************
		  \brief
			Parses textures.csv into a map of Textures to be called upon when Get_Texture
			calls a texture with that key
		*******************************************************************************/
		void Init()
		{
			//data from the csv is stored into the textures map
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

		/*!*****************************************************************************
		  \brief
			Loads a texture with the specified ID

		  \param _ID
			The ID of the texture as specified by texture.csv
		*******************************************************************************/
		void Load(std::string const& _ID)
		{
			if (!(textures[_ID].is_loaded))
			{
				loaded_textures[_ID].load_texture(textures[_ID].filepath.c_str(), SageTexture::TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
				textures[_ID].is_loaded = true;

				//reserved for sprite sheet support
				if (textures[_ID].sprites_num > 1)
				{
					//Renderer::Sprite_Sheet_Mesh_Init(textures[ID].sprites_per_row,textures[ID].sprites_per_col,textures[ID].sprites_num,ID);
				}
			}
		}

		/*!*****************************************************************************
		  \brief
			Gets the texture with the provided ID

		  \param _ID
			The key to look for

		  \return
			The reference to the loaded texture
		*******************************************************************************/
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

		/*!*****************************************************************************
		  \brief
			Provides a space for any free or unloading functions that may be required
			by subsequent interation of this component
		*******************************************************************************/
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

		/*!*****************************************************************************
		  \brief
			Parses prefabs.csv into a map of Prefabs to be called upon when Get_Prefab
			calls a texture with that key
		*******************************************************************************/
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
					p.has_physics = source.comma_seperated_data[i].associated_data[HAS_PHYSICS];
					p.velocity = std::stof(source.comma_seperated_data[i].associated_data[PHYSICS_VELOCITY]);
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

		/*!*****************************************************************************
		  \brief
			Gets the Prefab with the provided ID

		  \param _prefab_ID
			The key to look for

		  \return
			The Prefab in the map with the _prefab_ID key
		*******************************************************************************/
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

		/*!*****************************************************************************
		  \brief
			Gets the map of prefabs

		  \return
			The reference to the map of prefabs
		*******************************************************************************/
		std::unordered_map<std::string, Prefab> const& Get_Prefabs()
		{
			if (!has_initialized)
			{
				Init();
			}
			return generated_prefabs;
		}
	}

	namespace Audio
	{
		std::unordered_map<std::string, std::vector<std::string>> audio_files;
		void Init()
		{
			audio_files.clear();
			for (const auto& entry : std::filesystem::directory_iterator(PATH))
			{
				if (entry.is_regular_file() && entry.path().extension() == AUDIO_EXTENSION)
				{
					std::string filename = entry.path().stem().string();
					if (filename.rfind("bgm_", 0) == 0)
					{
						audio_files["bgm"].push_back(filename);
					}
					else if (filename.rfind("sfx_", 0) == 0)
					{
						audio_files["sfx"].push_back(filename);
					}
					else if (filename.rfind("ui_", 0) == 0)
					{
						audio_files["ui"].push_back(filename);
					}
					else if (filename.rfind("ambient_", 0) == 0)
					{
						audio_files["ambient"].push_back(filename);
					}
					else
					{
						std::cerr << "Unrecognized channel group for " << filename << std::endl;
						exit(-1);
					}
				}
				else
				{
					std::cerr << "WARNING: File extension for " << entry.path().filename().string() << " is not " << AUDIO_EXTENSION << "!" << std::endl;
				}
			}
		}
		std::unordered_map<std::string, std::vector<std::string>> const& Get_Audio()
		{
			return audio_files;
		}
	}

	namespace Font 
	{
		FT_Library library;
		FT_Error error;
		FT_Face face;
		FT_UInt glyph_index;
		FT_Int32 load_flags;
		FT_ULong charcode;
		FT_CharMap charmap;
		FT_Render_Mode render_mode;

		void Init()
		{
			error = FT_Init_FreeType(&library);
			error = FT_New_Face(library, "../SageEngine/data/assets/fonts/swapgoats.ttf", 0, &face);
			if (error == FT_Err_Unknown_File_Format)
			{
				std::cerr << "ERROR: Wrong file format!" << std::endl;
			}

			error = FT_Set_Pixel_Sizes(face, 16, 16);
			glyph_index = FT_Get_Char_Index(face, charcode);
			error = FT_Load_Glyph(face, glyph_index, load_flags);
			error = FT_Render_Glyph(face->glyph, render_mode);
		}
	}

	namespace Levels 
	{
		std::vector<Parsed_CSV>sources;
		std::unordered_map<std::string, Level> levels;
		Level sentinel;

		/*!*****************************************************************************
		  \brief
			Parses all level_x.csv into a map of levels to be called upon when Get_Level
			calls a level with that key
		*******************************************************************************/
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

			//for each level_x.csv, maps the level's details to a Level and adds it to the levels map
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
						l.z_orders.push_back(std::stoul(sources[i].comma_seperated_data[j].associated_data[Z_ORDER]));
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

		/*!*****************************************************************************
		  \brief
			Gets the Level with the provided ID

		  \param _level_ID
			The key to look for

		  \return
			The Prefab in the map with the _level_ID key
		*******************************************************************************/
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