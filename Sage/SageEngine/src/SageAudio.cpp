/* Start Header ************************************************************************/
/*!
\file		Game.cpp
\title		
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		15 September 2024
\brief		Contains the declarations of functions handling the game scene.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.						
*/
/* End Header **************************************************************************/
#include "SageAudio.hpp"

//FMOD_RESULT result;
//FMOD::System* p_system;
//FMOD::ChannelGroup* audio_bgm_group, * audio_sfx_group, * audio_ui_group, * audio_ambient_group, * master_audio_group;
//std::vector<FMOD::ChannelGroup*> channel_group = { audio_bgm_group, audio_sfx_group, audio_ui_group, audio_ambient_group, master_audio_group };
//std::unordered_map<std::string, std::vector<std::string>> audio_files;
//std::vector<FMOD::Sound*> p_sound;
//size_t p_sound_index{ 0 };
bool paused{ false };

namespace SageAudio
{
#pragma region Helper Functions
	void FMOD_ErrorCheck(FMOD_RESULT _result)
	{
		if (_result != FMOD_OK)
		{
			std::cerr << "FMOD ERROR! " << FMOD_ErrorString(_result);
			exit(-1);
		}
	}

	static const char* Mode_Getter(Sound_Mode _index)
	{
		switch (_index)
		{
		case LOOP:      return "LOOP";
		case NO_LOOP:	return "NO LOOP";
		default:        return "FMOD_DEFAULT";
		};
	}
#pragma endregion

#pragma region Private Functions
	void Play_Sound(const std::string& _filename, Sound_Mode _mode)
	{
		size_t i{ 0 };
		for (const auto& [category, files] : audio_files)
		{
			for (const auto& file : files)
			{
				if (file == _filename)
				{
					result = p_sound[i]->setMode(Mode_Selector(_mode));
					FMOD_ErrorCheck(result);
					if (_filename.starts_with("bgm_"))
					{
						result = p_system->playSound(p_sound[i], channel_group[0], false, nullptr);
						FMOD_ErrorCheck(result);
						std::cout << "Playing BGM: " << _filename << " with " << Mode_Getter(_mode) << std::endl;
						return;
					}
					else if (_filename.starts_with("sfx_"))
					{
						result = p_system->playSound(p_sound[i], channel_group[1], false, nullptr);
						FMOD_ErrorCheck(result);
						std::cout << "Playing SFX: " << _filename << " with " << Mode_Getter(_mode) << std::endl;
						return;
					}
					else if (_filename.starts_with("ui_"))
					{
						result = p_system->playSound(p_sound[i], channel_group[2], false, nullptr);
						FMOD_ErrorCheck(result);
						std::cout << "Playing UI sound: " << _filename << " with " << Mode_Getter(_mode) << std::endl;
						return;
					}
					else if (_filename.starts_with("ambient_"))
					{
						result = p_system->playSound(p_sound[i], channel_group[3], false, nullptr);
						FMOD_ErrorCheck(result);
						std::cout << "Playing Ambient sound: " << _filename << " with " << Mode_Getter(_mode) << std::endl;
						return;
					}
				}
				++i;
			}
		}
		std::cerr << "ERROR: " << _filename << " doesn't exist!" << std::endl;
		exit(-1);
	}

	void Set_Pause(bool _is_paused)
	{
		channel_group[0]->setPaused(_is_paused);
		channel_group[1]->setPaused(_is_paused);
		channel_group[3]->setPaused(_is_paused);
	}

	FMOD::ChannelGroup* Get_Channel(std::string _channel)
	{
		char name[4];
		for (size_t i{ 0 }; i < audio_files.size(); ++i)
		{
			result = channel_group[i]->getName(name, sizeof(name));
			FMOD_ErrorCheck(result);
			if (std::string(name) == _channel)
			{
				return channel_group[i];
			}
			else
			{
				std::cerr << "ERROR: Channel " << _channel << " doesn't exist!" << std::endl;
				exit(-1);
			}
		}
	}

	void Set_Volume(FMOD::ChannelGroup* _channel, float _volume)
	{
		_channel->setVolume(_volume);
	}

	FMOD_MODE Mode_Selector(Sound_Mode _mode)
	{
		switch (_mode)
		{
		case LOOP:		return FMOD_LOOP_NORMAL;
		case NO_LOOP:	return FMOD_LOOP_OFF;
		default:		return FMOD_DEFAULT;
		}
	}
#pragma endregion

#pragma region Public Functions
	//void Init()
	//{
	//	std::cout << "Creating audio system\n";
	//	result = FMOD::System_Create(&p_system);
	//	FMOD_ErrorCheck(result);

	//	std::cout << "Initializing FMOD\n";
	//	result = p_system->init(512, FMOD_INIT_NORMAL, 0);
	//	FMOD_ErrorCheck(result);

	//	result = p_system->createChannelGroup("bgm", &channel_group[0]);
	//	FMOD_ErrorCheck(result);
	//	result = p_system->createChannelGroup("sfx", &channel_group[1]);
	//	FMOD_ErrorCheck(result);
	//	result = p_system->createChannelGroup("ui", &channel_group[2]);
	//	FMOD_ErrorCheck(result);
	//	result = p_system->createChannelGroup("ambient", &channel_group[3]);
	//	FMOD_ErrorCheck(result);

	//	result = p_system->getMasterChannelGroup(&channel_group.back());
	//	FMOD_ErrorCheck(result);
	//	for (size_t i{ 0 }; i < audio_files.size(); i++)
	//	{
	//		result = channel_group.back()->addGroup(channel_group[i]);
	//		FMOD_ErrorCheck(result);
	//	}

	//	result = channel_group[4]->setVolume(1.f);
	//	FMOD_ErrorCheck(result);
	//	result = channel_group[0]->setVolume(.7f);
	//	FMOD_ErrorCheck(result);
	//	result = channel_group[1]->setVolume(.15f);
	//	FMOD_ErrorCheck(result);
	//	result = channel_group[2]->setVolume(.1f);
	//	FMOD_ErrorCheck(result);
	//	result = channel_group[3]->setVolume(.4f);
	//	FMOD_ErrorCheck(result);

	//	audio_files.clear();
	//	for (const auto& entry : std::filesystem::directory_iterator(PATH))
	//	{
	//		if (entry.is_regular_file() && entry.path().extension() == AUDIO_EXTENSION)
	//		{
	//			std::string filename = entry.path().stem().string();
	//			if (filename.rfind("bgm_", 0) == 0)
	//			{
	//				audio_files["bgm"].push_back(filename);
	//			}
	//			else if (filename.rfind("sfx_", 0) == 0)
	//			{
	//				audio_files["sfx"].push_back(filename);
	//			}
	//			else if (filename.rfind("ui_", 0) == 0)
	//			{
	//				audio_files["ui"].push_back(filename);
	//			}
	//			else if (filename.rfind("ambient_", 0) == 0)
	//			{
	//				audio_files["ambient"].push_back(filename);
	//			}
	//			else
	//			{
	//				std::cerr << "Unrecognized channel group for " << filename << std::endl;
	//				exit(-1);
	//			}
	//			++p_sound_index;
	//		}
	//		else
	//		{
	//			std::cerr << "WARNING: File extension for " << entry.path().filename().string() << " is not " << AUDIO_EXTENSION << "!" << std::endl;
	//		}
	//	}
	//	p_sound.resize(p_sound_index);
	//	p_sound_index = 0;

	//	for (const auto& [channel, files] : audio_files)
	//	{
	//		for (const auto& file : files)
	//		{
	//			std::string full_path = PATH + file + AUDIO_EXTENSION;
	//			std::cout << "Creating sound from " << full_path << '\n';
	//			result = p_system->createSound(full_path.c_str(), FMOD_DEFAULT, nullptr, &p_sound[p_sound_index++]);
	//			FMOD_ErrorCheck(result);
	//		}
	//	}
	//}

	void Update()
	{
		result = p_system->update();
		FMOD_ErrorCheck(result);
	}

	//void Exit()
	//{
	//	std::cout << "Exiting" << std::endl;

	//	for (size_t i{ 0 }; i < p_sound.size(); i++)
	//	{
	//		result = p_sound[i]->release();
	//		FMOD_ErrorCheck(result);
	//	}
	//	for (size_t i{ 0 }; i < audio_files.size(); i++)
	//	{
	//		result = channel_group[i]->release();
	//		FMOD_ErrorCheck(result);
	//	}
	//	result = p_system->release();
	//	FMOD_ErrorCheck(result);
	//}
#pragma endregion
}