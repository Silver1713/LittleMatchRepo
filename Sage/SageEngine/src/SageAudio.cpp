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

FMOD_RESULT result;
FMOD::System* p_system;
FMOD::Sound* p_sound[g_maxAudio]; // WARNING: This design creates an additional array index to avoid NUM_AUDIO_BGM enum
FMOD::Channel* p_channel[g_maxAudio];
FMOD::ChannelGroup* master_audio_group, * audio_bgm_group, * audio_sfx_group, * audio_ui_group, * audio_ambient_group;

namespace SageAudio
{
#pragma region Helper Functions
	void FMOD_ErrorCheck(FMOD_RESULT _result)
	{
		if (_result != FMOD_OK)
		{
			std::cout << "FMOD error! " << FMOD_ErrorString(_result);
			exit(-1);
		}
	}

	void Filesystem_Implementation()
	{
		std::string path = PATH;
		for (const auto &entry : std::filesystem::directory_iterator(path))
		{
			if(entry.is_directory())
			{
				std::cout << "Folder: " << entry.path() << std::endl;
			}
			else
			{
				std::cout << "File: " << entry.path() << std::endl;
			}
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
		case LOOP:      return "FMOD_LOOP_NORMAL";
		case NO_LOOP:	return "FMOD_LOOP_OFF";
		default:        return "FMOD_DEFAULT";
		};
	}
#pragma endregion

#pragma region Private Functions

	void Play_Sound(size_t _audio_name, Sound_Mode _mode)
	{
		result = p_sound[_audio_name]->setMode(Mode_Selector(_mode));
		FMOD_ErrorCheck(result);
		std::cout << "Setting mode to " << Mode_Getter(_mode) << " for " << Filepath_Getter(_audio_name) << '\n';
		result = p_system->playSound(p_sound[_audio_name], nullptr, false, nullptr);
		FMOD_ErrorCheck(result);
		std::cout << "Playing " << Filepath_Getter(_audio_name) << '\n';
	}
#pragma endregion

#pragma region Public Functions
	void Init()
	{
		std::cout << "Creating audio system\n";
		result = FMOD::System_Create(&p_system);
		FMOD_ErrorCheck(result);

		std::cout << "Initializing FMOD\n";
		result = p_system->init(g_maxAudio, FMOD_INIT_NORMAL, 0);
		FMOD_ErrorCheck(result);

		for (size_t i{ 0 }; i < g_maxAudio; i++)
		{
			if (i == NUM_AUDIO_BGM || i == NUM_AUDIO_SFX || i == NUM_AUDIO_UI || i == NUM_AUDIO_AMBIENT)
			{
				continue;
			}
			std::cout << "Creating sound from " << Filepath_Getter(i) << '\n';
			result = p_system->createSound(Filepath_Getter(i), FMOD_DEFAULT, nullptr, &p_sound[i]);
			FMOD_ErrorCheck(result);
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
		for (size_t i{ 0 }; i < g_maxAudio; i++)
		{
			if (i == NUM_AUDIO_BGM)
			{
				continue;
			}
			result = p_sound[i]->release();
			FMOD_ErrorCheck(result);
		}
		result = p_system->release();
		FMOD_ErrorCheck(result);
	}
#pragma endregion
}