#include "AssetLoader.hpp"
#include "CSVParser.hpp"

#include "SageEngine.hpp"

#include <unordered_map>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>
#include "SOIL.H"

#include <filesystem>
#include "fmod.hpp"
#include "fmod_errors.h"
#include "SageAudio.hpp"

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

	namespace Audio
	{
		FMOD_RESULT result;
		FMOD::System* p_system;
		FMOD::ChannelGroup* audio_bgm_group, * audio_sfx_group, * audio_ui_group, * audio_ambient_group, * master_audio_group;
		std::vector<FMOD::ChannelGroup*> channel_group = { audio_bgm_group, audio_sfx_group, audio_ui_group, audio_ambient_group, master_audio_group };
		std::unordered_map<std::string, std::vector<std::string>> audio_files;
		std::vector<FMOD::Sound*> p_sound;
		size_t p_sound_index{ 0 };
		bool paused{ false };

		void Init()
		{
			std::cout << "Creating audio system\n";
			result = FMOD::System_Create(&p_system);
			SageAudio::FMOD_ErrorCheck(result);

			std::cout << "Initializing FMOD\n";
			result = p_system->init(512, FMOD_INIT_NORMAL, 0);
			SageAudio::FMOD_ErrorCheck(result);

			result = p_system->createChannelGroup("bgm", &channel_group[0]);
			SageAudio::FMOD_ErrorCheck(result);
			result = p_system->createChannelGroup("sfx", &channel_group[1]);
			SageAudio::FMOD_ErrorCheck(result);
			result = p_system->createChannelGroup("ui", &channel_group[2]);
			SageAudio::FMOD_ErrorCheck(result);
			result = p_system->createChannelGroup("ambient", &channel_group[3]);
			SageAudio::FMOD_ErrorCheck(result);

			result = p_system->getMasterChannelGroup(&channel_group.back());
			SageAudio::FMOD_ErrorCheck(result);
			for (size_t i{ 0 }; i < audio_files.size(); i++)
			{
				result = channel_group.back()->addGroup(channel_group[i]);
				SageAudio::FMOD_ErrorCheck(result);
			}

			result = channel_group[4]->setVolume(1.f);
			SageAudio::FMOD_ErrorCheck(result);
			result = channel_group[0]->setVolume(.7f);
			SageAudio::FMOD_ErrorCheck(result);
			result = channel_group[1]->setVolume(.15f);
			SageAudio::FMOD_ErrorCheck(result);
			result = channel_group[2]->setVolume(.1f);
			SageAudio::FMOD_ErrorCheck(result);
			result = channel_group[3]->setVolume(.4f);
			SageAudio::FMOD_ErrorCheck(result);

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
					++p_sound_index;
				}
				else
				{
					std::cerr << "WARNING: File extension for " << entry.path().filename().string() << " is not " << AUDIO_EXTENSION << "!" << std::endl;
				}
			}
			p_sound.resize(p_sound_index);
			p_sound_index = 0;

			for (const auto& [channel, files] : audio_files)
			{
				for (const auto& file : files)
				{
					std::string full_path = PATH + file + AUDIO_EXTENSION;
					std::cout << "Creating sound from " << full_path << '\n';
					result = p_system->createSound(full_path.c_str(), FMOD_DEFAULT, nullptr, &p_sound[p_sound_index++]);
					SageAudio::FMOD_ErrorCheck(result);
				}
			}
		}

		void Unload()
		{
			std::cout << "Exiting" << std::endl;

			for (size_t i{ 0 }; i < p_sound.size(); i++)
			{
				result = p_sound[i]->release();
				SageAudio::FMOD_ErrorCheck(result);
			}
			for (size_t i{ 0 }; i < audio_files.size(); i++)
			{
				result = channel_group[i]->release();
				SageAudio::FMOD_ErrorCheck(result);
			}
			result = p_system->release();
			SageAudio::FMOD_ErrorCheck(result);
		}
	}

	//namespace Font
	//{
	//	void Init()
	//	{

	//	}

	//	void Load()
	//	{

	//	}

	//	void Unload()
	//	{

	//	}
	//}
}