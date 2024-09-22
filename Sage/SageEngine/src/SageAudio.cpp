/* Start Header ************************************************************************/
/*!
\file		Game.cpp
\title		
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		15 September 2024
\brief		Contains the declarations of functions handling the game scene.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.						
*/
/* End Header **************************************************************************/
#include "SageAudio.hpp"
#include <backward.hpp>
#include <cassert>
FMOD_RESULT result;
FMOD::System* p_system;
FMOD::ChannelGroup* audio_bgm_group, * audio_sfx_group, * audio_ui_group, * audio_ambient_group, * master_audio_group;
std::vector<FMOD::ChannelGroup*> channel_group = { audio_bgm_group, audio_sfx_group, audio_ui_group, audio_ambient_group, master_audio_group };
std::vector<std::string> audio_group = { "bgm", "sfx", "ui", "ambient" };
std::vector<std::vector<std::string>> filename;
std::vector<FMOD::Sound*> p_sound;

backward::SignalHandling sh;

namespace SageAudio
{
#pragma region Helper Functions
	void FMOD_ErrorCheck(FMOD_RESULT _result)
	{
		if (_result != FMOD_OK)
		{
			
			std::cerr << "FMOD ERROR! " << FMOD_ErrorString(_result);
			assert(false);
			exit(-1);
		}
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
	void Play_Sound(std::string _filename)
	{
		for (size_t i{ 0 }; i < audio_group.size(); i++)
		{
			//std::cout << "Searching in " << audio_group[i] << std::endl;
			for (const auto& filename : filename[i])
			{
				//std::cout << "Seeking " << filename << std::endl;
				if (filename == _filename)
				{
					result = p_system->playSound(p_sound[i], channel_group[i], false, nullptr);
					FMOD_ErrorCheck(result);
					std::cout << "Playing " << filename << std::endl;
					return;
				}
			}
		}
		std::cout << "ERROR: " << _filename << " doesn't exist!" << std::endl;
	}
#pragma endregion

#pragma region Public Functions
	void Init()
	{
		std::cout << "Creating audio system\n";
		result = FMOD::System_Create(&p_system);
		FMOD_ErrorCheck(result);

		std::cout << "Initializing FMOD\n";
		result = p_system->init(512, FMOD_INIT_NORMAL, 0);
		FMOD_ErrorCheck(result);

		std::cout << "Creating music channel\n";
		result = p_system->createChannelGroup("Music", &channel_group[0]);
		FMOD_ErrorCheck(result);
		std::cout << "Creating sound effects channel\n";
		result = p_system->createChannelGroup("Sound Effects", &channel_group[1]);
		FMOD_ErrorCheck(result);
		std::cout << "Creating user interface channel\n";
		result = p_system->createChannelGroup("User Interface", &channel_group[2]);
		FMOD_ErrorCheck(result);
		std::cout << "Creating ambience channel\n";
		result = p_system->createChannelGroup("Ambience", &channel_group[3]);
		FMOD_ErrorCheck(result);

		std::cout << "Creating master channel\n";
		result = p_system->getMasterChannelGroup(&channel_group.back());
		FMOD_ErrorCheck(result);
		for (size_t i{ 0 }; i < channel_group.size() - 1; i++)
		{
			result = channel_group.back()->addGroup(channel_group[i]);
			FMOD_ErrorCheck(result);
		}

		result = channel_group[4]->setVolume(1.f);
		FMOD_ErrorCheck(result);
		result = channel_group[0]->setVolume(.7f);
		FMOD_ErrorCheck(result);
		result = channel_group[1]->setVolume(.15f);
		FMOD_ErrorCheck(result);
		result = channel_group[2]->setVolume(.1f);
		FMOD_ErrorCheck(result);
		result = channel_group[3]->setVolume(.4f);
		FMOD_ErrorCheck(result);

		filename.clear();
		for (const auto& subfolder : audio_group)
		{
			std::vector<std::string> file;
			for (const auto& entry : std::filesystem::directory_iterator(PATH + subfolder))
			{
				if (entry.is_regular_file() && entry.path().extension() == AUDIO_EXTENSION)
				{
					file.push_back(entry.path().stem().string());
				}
				else
				{
					std::cerr << "WARNING: File extension for " << entry.path().stem().string() << " is not " << AUDIO_EXTENSION "!" << std::endl;
				}
			}
			std::sort(file.begin(), file.end());
			filename.push_back(file);
		}
		p_sound.resize(filename.size());

		for (size_t i{ 0 }; i < audio_group.size(); ++i)
		{
			std::string folder_path = PATH + std::string(audio_group[i]);
			for (const auto& name : filename[i])
			{
				std::string full_path = folder_path + '/' + name + AUDIO_EXTENSION;
				std::cout << "Creating sound from " << full_path << '\n';
				result = p_system->createSound(full_path.c_str(), FMOD_DEFAULT, nullptr, &p_sound[i]);
				FMOD_ErrorCheck(result);
			}
		}
	}

	void Update()
	{
		result = p_system->update();
		FMOD_ErrorCheck(result);
	}

	void Exit()
	{
		std::cout << "Exiting";

		for (size_t i{ 0 }; i < p_sound.size(); i++)
		{
			if (p_sound[i] != nullptr) {
				result = p_sound[i]->release();
				FMOD_ErrorCheck(result);
			}
		}
		for (size_t i{ 0 }; i < channel_group.size() -1 ; i++)
		{
			if (channel_group[i] != nullptr) {
				result = channel_group[i]->release();
				FMOD_ErrorCheck(result);
			}
		}

		result = p_system->release();
		FMOD_ErrorCheck(result);
	}
#pragma endregion
}