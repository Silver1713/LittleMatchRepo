/* Start Header ************************************************************************/
/*!
\file		SageAudio.cpp
\title		Memory's Flame
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (100%)
\par		halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the functions for creating, managing and playing audio.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "SageAudio.hpp"
#include <backward.hpp>
#include <cassert>

namespace SageAudio
{
	FMOD_RESULT result;
	FMOD::System* p_system;
	FMOD::ChannelGroup* audio_bgm_group, * audio_sfx_group, * audio_ui_group, * audio_ambient_group, * master_audio_group;
	std::vector<FMOD::ChannelGroup*> channel_group = { audio_bgm_group, audio_sfx_group, audio_ui_group, audio_ambient_group, master_audio_group };
	std::vector<FMOD::Sound*> p_sound;
	size_t p_sound_index{};
	bool paused{ false };

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
		for (const auto& [category, filenames] : Assets::Audio::Get_Audio())
		{
			for (const auto& filename : filenames)
			{
				if (filename == _filename)
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
		for (size_t i{ 0 }; i < Assets::Audio::Get_Audio().size(); ++i)
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
	void Init()
	{
		std::cout << "Creating audio system\n";
		result = FMOD::System_Create(&p_system);
		FMOD_ErrorCheck(result);

		std::cout << "Initializing FMOD\n";
		result = p_system->init(512, FMOD_INIT_NORMAL, 0);
		FMOD_ErrorCheck(result);

		result = p_system->createChannelGroup("bgm", &channel_group[0]);
		FMOD_ErrorCheck(result);
		result = p_system->createChannelGroup("sfx", &channel_group[1]);
		FMOD_ErrorCheck(result);
		result = p_system->createChannelGroup("ui", &channel_group[2]);
		FMOD_ErrorCheck(result);
		result = p_system->createChannelGroup("ambient", &channel_group[3]);
		FMOD_ErrorCheck(result);

		result = p_system->getMasterChannelGroup(&channel_group.back());
		FMOD_ErrorCheck(result);
		for (size_t i{ 0 }; i < Assets::Audio::Get_Audio().size(); i++)
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


		for (const auto& [channel, filenames] : Assets::Audio::Get_Audio())
		{
			p_sound_index += filenames.size();
		}
		p_sound.resize(p_sound_index);
		p_sound_index = 0;

		for (const auto& [channel, filenames] : Assets::Audio::Get_Audio())
		{
			for (const auto& filename : filenames)
			{
				std::string full_path = PATH + filename + AUDIO_EXTENSION;
				std::cout << "Creating sound from " << full_path << '\n';
				result = p_system->createSound(full_path.c_str(), FMOD_DEFAULT, nullptr, &p_sound[p_sound_index++]);
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
		std::cout << "Exiting" << std::endl;
		for (size_t i{ 0 }; i < p_sound.size(); i++)
		{
			result = p_sound[i]->release();
			FMOD_ErrorCheck(result);
		}
		for (size_t i{ 0 }; i < Assets::Audio::Get_Audio().size(); i++)
		{
			result = channel_group[i]->release();
			FMOD_ErrorCheck(result);
		}
		result = p_system->release();
		FMOD_ErrorCheck(result);
	}
#pragma endregion
}