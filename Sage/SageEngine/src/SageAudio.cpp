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
	/*!*****************************************************************************
	  \brief
		Prints the type of error in FMOD.

	  \param _result
	    The enum type FMOD_RESULT.
	*******************************************************************************/
	void FMOD_ErrorCheck(FMOD_RESULT _result)
	{
		if (_result != FMOD_OK)
		{
			
			std::cerr << "FMOD ERROR! " << FMOD_ErrorString(_result);
			assert(false);
			exit(-1);
		}
	}

	/*!*****************************************************************************
	  \brief
		Prints the sound mode that will be set from FMOD.

	  \param _mode
		The enum type Sound_Mode.

	  \return
	    The name of the mode.
	*******************************************************************************/
	static const char* Mode_Getter(Sound_Mode _mode)
	{
		switch (_mode)
		{
		case LOOP:      return "LOOP";
		case NO_LOOP:	return "NO LOOP";
		default:        return "FMOD_DEFAULT";
		};
	}
#pragma endregion

#pragma region Private Functions
	/*!*****************************************************************************
	  \brief
		Plays a sound from the audio assets folder and sets the mode that it will
		play at. The function also funnels which channel goup the sound will play at.

	  \param _filename
		The name of the audio file.

	  \param _mode
		The mode that the audio will at. Either LOOP or NO_LOOP.
	*******************************************************************************/
	void Play_Sound(const std::string& _filename, Sound_Mode _mode)
	{
		if (!paused)
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
		else
		{
			std::cout << "WARNING: Playing audio on a paused channel!" << std::endl;
		}
	}

	/*!*****************************************************************************
	  \brief
		Pauses all game audio excluding user interface sounds.
	*******************************************************************************/
	void Pause_Audio()
	{
		paused = !paused;
		channel_group[0]->setPaused(paused);
		channel_group[1]->setPaused(paused);
		channel_group[3]->setPaused(paused);
	}

	/*!*****************************************************************************
	  \brief
		Stops all game audio currently playing.
	*******************************************************************************/
	void Stop_All_Audio()
	{
		channel_group[4]->stop();
	}

	/*!*****************************************************************************
	  \brief
		Retrieves the channel group to allow control of it.

	  \param _channel
		The name of the channel.

	  \return
		The channel group.
	*******************************************************************************/
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
			}
		}
		return nullptr;
	}

	/*!*****************************************************************************
	  \brief
		Sets the volume of the specified channel to the desired volume.

	  \param _channel
		The name of the channel. Used with Get_Channel().

	  \param _volume
		The desired volume from 0.0f to 1.0f
	*******************************************************************************/
	void Set_Volume(FMOD::ChannelGroup* _channel, float _volume)
	{
		_channel->setVolume(_volume);
	}

	/*!*****************************************************************************
	  \brief
		Sets the mode of how the audio will be played.

	  \param _mode
		The desired mode to set. Either LOOP or NO_LOOP.

	  \return
	    The defined FMOD_MODE.
	*******************************************************************************/
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

	/*!*****************************************************************************
	  \brief
		Initializes the FMOD System (set at 512 playable audio at a time) and creates
		4 channel groups for Background Music (bgm), Sound Effects (sfx), User
		Interface (ui) and Ambience (ambient). It also sets the Master Channel for
		the 4 channel groups to balance the Game Audio. The function also processes
		a map of audio filenames generated from AssetLoader.cpp and turns them into
		a FMOD Sound that can be played using Play_Sound().
	*******************************************************************************/
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
		result = channel_group[0]->setVolume(.75f);
		FMOD_ErrorCheck(result);
		result = channel_group[1]->setVolume(1.f);
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

	/*!*****************************************************************************
	  \brief
		Updates the FMOD system to handle audio playback.
	*******************************************************************************/
	void Update()
	{
		result = p_system->update();
		FMOD_ErrorCheck(result);
	}

	/*!*****************************************************************************
	  \brief
		Releases all generated sound files, audio channel groups and the FMOD system.
	*******************************************************************************/
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