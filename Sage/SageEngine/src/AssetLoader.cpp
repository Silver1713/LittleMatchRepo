/* Start Header ************************************************************************/
/*!
\file		AssetLoader.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (80%)
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (20%)
\par		b.muhammadhafiz@digipen.edu, halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the data structures and functions for managing game assets,
			including textures and prefabs. Handles deserialization and serialization of
			data.

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
#include "SageJSON.hpp"

#include "fmod.hpp"
#include "fmod_errors.h"
#include "SageAudio.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

//Every file is an asset, which is broken down into categories
namespace Assets
{
	/*!*****************************************************************************
	  \brief
		Initializes all asset categories
	*******************************************************************************/
	void Init()
	{
		Textures::Init();
		Prefabs::Init();
		Animations::Init();
		Animation_Set::Init();
		Audio::Init();
		Font::Init();
		Levels::Init();
	}

	/*!*****************************************************************************
	  \brief
		Unloads any asset category that uses allocated resources
	*******************************************************************************/
	void Unload()
	{
		Textures::Unload();
	}

	//Texture category
	namespace Textures
	{		
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
			Parsed_CSV source = Parse_CSV("../SageEngine/data/serialization/textures.csv");
			for (int i{1}; i < source.num_rows; i++)
			{
				Texture t;
				try
				{
					//Parsing a folder of textures
					if (std::stoul(source.comma_seperated_data[i].associated_data[SPRITES_NUM]) > 1)
					{
						if (std::filesystem::exists(source.comma_seperated_data[i].associated_data[FILEPATH]) && 
							std::filesystem::is_directory(source.comma_seperated_data[i].associated_data[FILEPATH])) 
						{
							// Iterate through the directory
							for (const auto& entry : std::filesystem::directory_iterator(source.comma_seperated_data[i].associated_data[FILEPATH]))
							{
								if (std::filesystem::is_regular_file(entry.status()))
								{
									// Check if the file has a .png extension
									if (entry.path().extension() == ".png") 
									{
										t.filepath = source.comma_seperated_data[i].associated_data[FILEPATH] + entry.path().filename().string();
										t.width = std::stof(source.comma_seperated_data[i].associated_data[WIDTH]);
										t.height = std::stof(source.comma_seperated_data[i].associated_data[HEIGHT]);
										textures[source.comma_seperated_data[i].associated_data[ID] + '_' + entry.path().stem().string()] = t;
									}
								}
							}
						}
						else 
						{
							std::cerr << source.comma_seperated_data[i].associated_data[FILEPATH] << "is an invalid directory path!" << std::endl;
						}

					}
					else 
					{
						t.filepath = source.comma_seperated_data[i].associated_data[FILEPATH];
						t.width = std::stof(source.comma_seperated_data[i].associated_data[WIDTH]);
						t.height = std::stof(source.comma_seperated_data[i].associated_data[HEIGHT]);
						textures[source.comma_seperated_data[i].associated_data[ID]] = t;
					}					
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
				loaded_textures[_ID].Load_Texture(textures[_ID].filepath.c_str(), SageTexture::TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
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

	//Prefabs category
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
			source = Parse_CSV("../SageEngine/data/serialization/prefabs.csv");
			for (int i{ 1 }; i < source.num_rows; i++)
			{
				Prefab p;
				try
				{
					p.prefab_ID = source.comma_seperated_data[i].associated_data[PREFAB_ID];
					p.transform_type = source.comma_seperated_data[i].associated_data[TRANSFORM_TYPE];
					p.positions.x = std::stof(source.comma_seperated_data[i].associated_data[POS_X]);
					p.positions.y = std::stof(source.comma_seperated_data[i].associated_data[POS_Y]);
					p.positions.z = std::stof(source.comma_seperated_data[i].associated_data[POS_Z]);
					p.rotations.x = std::stof(source.comma_seperated_data[i].associated_data[ROT_X]);
					p.rotations.y = std::stof(source.comma_seperated_data[i].associated_data[ROT_Y]);
					p.rotations.z = std::stof(source.comma_seperated_data[i].associated_data[ROT_Z]);
					p.scale.x = std::stof(source.comma_seperated_data[i].associated_data[SCALE_X]);
					p.scale.y = std::stof(source.comma_seperated_data[i].associated_data[SCALE_Y]);
					p.scale.z = std::stof(source.comma_seperated_data[i].associated_data[SCALE_Z]);
					p.colour.x = std::stof(source.comma_seperated_data[i].associated_data[COLOR_R]);
					p.colour.y = std::stof(source.comma_seperated_data[i].associated_data[COLOR_G]);
					p.colour.z = std::stof(source.comma_seperated_data[i].associated_data[COLOR_B]);
					p.colour.w = std::stof(source.comma_seperated_data[i].associated_data[COLOR_A]);
					p.sprite_texture_ID = source.comma_seperated_data[i].associated_data[SPRITE_TEXTURE_ID];
					p.collision_data = source.comma_seperated_data[i].associated_data[COL_D];
					p.has_physics = source.comma_seperated_data[i].associated_data[HAS_PHYSICS];
					p.velocity = std::stof(source.comma_seperated_data[i].associated_data[PHYSICS_VELOCITY]);
					p.object_shape = source.comma_seperated_data[i].associated_data[OBJ_SHAPE];
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
			std::cout << "Prefab: " + _prefab_ID + " Does not exist\n";
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

	//Animation category
	namespace Animations
	{
		Parsed_CSV source;
		std::unordered_map<std::string, Animation> animations;
		Animation sentinel;

		/*!*****************************************************************************
		  \brief
			Deserializes the animations.csv file
		*******************************************************************************/
		void Init()
		{
			source = Parse_CSV("../SageEngine/data/serialization/animations.csv");
			for (int i{ 1 }; i < source.num_rows; i++)
			{
				Animation a;
				try 
				{
					a.animation_ID = source.comma_seperated_data[i].associated_data[ANIMATION_ID];
					a.parent_texture_ID = source.comma_seperated_data[i].associated_data[PARENT_TEXTURE_ID];
					a.path_to_folder = source.comma_seperated_data[i].associated_data[PATH_TO_FOLDER];

					//count how many images are there in the folder
					if (std::filesystem::exists(a.path_to_folder) &&
						std::filesystem::is_directory(a.path_to_folder))
					{
						// Iterate through the directory
						for (const auto& entry : std::filesystem::directory_iterator(a.path_to_folder))
						{
							if (std::filesystem::is_regular_file(entry.status()))
							{
								// Check if the file has a .csv extension
								if (entry.path().extension() == ".png")
								{
									a.num_frames++;
								}
							}
						}
					}

					animations[a.animation_ID] = a;
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
			Creates a copy of the Animation with the provided ID

		  \param _anim_ID_key
			The key to look for

		  \return
			The Animation in the map with the _anim_ID_key key
		*******************************************************************************/
		Animation Get_Animation(std::string const& _anim_ID)
		{
			if (animations.find(_anim_ID) != animations.end())
			{
				return animations[_anim_ID];
			}
			else
			{
				std::cout << "Animation: " + _anim_ID + " Does Not Exist\n";
				return sentinel;
			}
		}
	}

	//Animation Set category
	namespace Animation_Set 
	{		
		std::unordered_map<std::string, Animation_Set> animation_sets;
		Animation_Set sentinel;

		/*!*****************************************************************************
		  \brief
			Deserializes all json files in animations folder
		*******************************************************************************/
		void Init()
		{
			std::string path{ "../SageEngine/data/serialization/animations/" };
			if (std::filesystem::exists(path) &&
				std::filesystem::is_directory(path))
			{
				// Iterate through the directory
				for (const auto& entry : std::filesystem::directory_iterator(path))
				{
					if (std::filesystem::is_regular_file(entry.status()))
					{
						// Check if the file has a .json extension
						if (entry.path().extension() == ".json")
						{
							SageJSON::SageJSON current_animation_set;
							std::ifstream file(entry.path());
							while (file)
							{
								file >> current_animation_set;
							}
							file.close();

							Animation_Set as;

							as.animation_set_ID = current_animation_set["Animation_Set_ID"].as<SageJSON::SageJSON::StringValue>();

							//Parse Transitions
							for (unsigned int i{}; i < current_animation_set["Num_Transitions"].as<SageJSON::SageJSON::NumberValue>(); ++i)
							{
								Transition t;
								try 
								{
									t.from_state = current_animation_set["Transitions"][i]["From_State"].as<SageJSON::SageJSON::StringValue>();
									t.to_state = current_animation_set["Transitions"][i]["To_State"].as<SageJSON::SageJSON::StringValue>();
								}								
								catch (const std::out_of_range& e)
								{
									std::cerr << "Animation_Set: Out of range " << e.what() << " at index " << i << std::endl;
								}
								catch (...)
								{
									std::cerr << "Animation_Set: Invalid argument at index " << i << std::endl;
								}

								for (unsigned int j{}; j < current_animation_set["Transitions"][i]["Num_Conditions"].as<SageJSON::SageJSON::NumberValue>(); ++j)
								{
									Condition c;
									c.parameter = current_animation_set["Transitions"][i]["Conditions"][j]["Parameter"].as<SageJSON::SageJSON::StringValue>();
									c.type = current_animation_set["Transitions"][i]["Conditions"][j]["Type"].as<SageJSON::SageJSON::StringValue>();
									c.value = static_cast<float>(current_animation_set["Transitions"][i]["Conditions"][j]["Value"].as<SageJSON::SageJSON::NumberValue>());
									t.conditions.push_back(c);
								}
								as.transitions.push_back(t);
							}
							
							//Parse States
							for (unsigned int i{}; i < current_animation_set["Num_States"].as<SageJSON::SageJSON::NumberValue>(); ++i)
							{
								State s;
								try
								{
									s.name = current_animation_set["States"][i]["Name"].as<SageJSON::SageJSON::StringValue>();
									s.animation_ID = current_animation_set["States"][i]["Animation_ID"].as<SageJSON::SageJSON::StringValue>();
									s.looping = (bool)(current_animation_set["States"][i]["Is_Looping"].as<SageJSON::SageJSON::NumberValue>());
									try
									{
										s.is_starting_state = (bool)current_animation_set["States"][i]["Is_Starting_State"].as<SageJSON::SageJSON::NumberValue>();
									}
									catch (...){}
								}
								catch (const std::out_of_range& e)
								{
									std::cerr << "Animation_Set: Out of range " << e.what() << " at index " << i << std::endl;
								}
								catch (...)
								{
									std::cerr << "Animation_Set: Invalid argument at index " << i << std::endl;
								}
								as.states.push_back(s);
							}

							//Parse Parameters
							for (unsigned int i{}; i < current_animation_set["Num_Parameters"].as<SageJSON::SageJSON::NumberValue>(); ++i)
							{
								Parameter p;
								p.name = current_animation_set["Parameters"][i]["Name"].as<SageJSON::SageJSON::StringValue>();
								p.default_value = static_cast<float>(current_animation_set["Parameters"][i]["Default_Value"].as<SageJSON::SageJSON::NumberValue>());

								as.parameters.push_back(p);
							}

							animation_sets[as.animation_set_ID] = as;
							current_animation_set.close();
						}
					}
				}
				std::cout << "hi" << std::endl;
			}
			else
			{
				std::cerr << path << "is an invalid directory path!" << std::endl;
			}
		}

		/*!*****************************************************************************
		  \brief
			Gets a copy of the Animation Set with the provided ID

		  \param _anim_set_ID
			The key to look for

		  \return
			The Animation Set in the map with the _anim_set_ID key
		*******************************************************************************/
		Animation_Set Get_Animation_Set(std::string const& _anim_set_ID)
		{
			if (animation_sets.find(_anim_set_ID) != animation_sets.end())
			{
				return animation_sets[_anim_set_ID];
			}
			else
			{
				std::cout << "Animation: " + _anim_set_ID + " Does Not Exist\n";
				return sentinel;
			}
		}
	}

	//Audio category
	namespace Audio
	{
		//Stores audio filenames
		std::unordered_map<std::string, std::vector<std::string>> audio_files;

		/*!*****************************************************************************
		  \brief
			Parses the audio asset folder and stores in a map of audio_files.
		*******************************************************************************/
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

		/*!*****************************************************************************
		  \brief
			Gets the map of audio_files that stores audio filenames

		  \return
		    Map of audio filenames
		*******************************************************************************/
		std::unordered_map<std::string, std::vector<std::string>> const& Get_Audio()
		{
			return audio_files;
		}
	}

	//Font category
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

		/*!*****************************************************************************
		  \brief
			Parses the font asset folder and loads the typeface into the graphics
			renderer.
		*******************************************************************************/
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

	//Level namespace
	namespace Levels 
	{		
		std::unordered_map<std::string, Level> levels;
		Level sentinel;

		/*!*****************************************************************************
		  \brief
			Parses all level_x.csv into a map of levels to be called upon when Get_Level
			calls a level with that key
		*******************************************************************************/
		void Init()
		{
			std::string path{ "../SageEngine/data/serialization/levels/" };

			// Iterate through the levels directory
			for (auto const& entry : std::filesystem::directory_iterator(path))
			{
				if (std::filesystem::is_regular_file(entry.status())) 
				{
					if (entry.path().extension() == ".csv")
					{
						Parsed_CSV p = Parse_CSV(entry.path().string());
						Level l;
						for (int i{ 1 }; i < p.num_rows; ++i)
						{
							try
							{
								l.prefabs.push_back(Prefabs::generated_prefabs[p.comma_seperated_data[i].associated_data[PREFAB_ID]]);
								l.identifier.push_back(p.comma_seperated_data[i].associated_data[IDENTIFIER]);

								ToastBox::Vec3 position
								{
									std::stof(p.comma_seperated_data[i].associated_data[POS_X]),
									std::stof(p.comma_seperated_data[i].associated_data[POS_Y]),
									std::stof(p.comma_seperated_data[i].associated_data[POS_Z])
								};

								l.positions.push_back(position);

								ToastBox::Vec3 rotation
								{
									std::stof(p.comma_seperated_data[i].associated_data[ROT_X]),
									std::stof(p.comma_seperated_data[i].associated_data[ROT_Y]),
									std::stof(p.comma_seperated_data[i].associated_data[ROT_Z])
								};

								l.rotations.push_back(rotation);

								ToastBox::Vec3 scale
								{
									std::stof(p.comma_seperated_data[i].associated_data[SCALE_X]),
									std::stof(p.comma_seperated_data[i].associated_data[SCALE_Y]),
									std::stof(p.comma_seperated_data[i].associated_data[SCALE_Z])
								};

								l.scale.push_back(scale);

								ToastBox::Vec4 color
								{
									std::stof(p.comma_seperated_data[i].associated_data[COLOR_R]),
									std::stof(p.comma_seperated_data[i].associated_data[COLOR_G]),
									std::stof(p.comma_seperated_data[i].associated_data[COLOR_B]),
									std::stof(p.comma_seperated_data[i].associated_data[COLOR_A])
								};

								l.color.push_back(color);
								l.z_orders.push_back(std::stoul(p.comma_seperated_data[i].associated_data[Z_ORDER]));
								levels[entry.path().stem().string()] = l;
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
				std::cout << "Level: " + _level_ID + " Does Not Exist" << std::endl;
				return sentinel;				
			}
		}
	}
}