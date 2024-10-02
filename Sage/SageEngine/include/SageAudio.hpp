/* Start Header ************************************************************************/
/*!
\file		SageAudio.hpp
\title		Memory's Flame
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (100%)
\par		halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the functions for creating, managing and playing audio.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include "fmod.hpp"
#include "fmod_errors.h"
#include "AssetLoader.hpp"

#define PATH "../SageEngine/data/assets/audio/"
#define AUDIO_EXTENSION ".ogg"

typedef enum
{
	LOOP,
	NO_LOOP
}Sound_Mode;

namespace SageAudio
{
#pragma region Helper Functions
	void FMOD_ErrorCheck(FMOD_RESULT _result);
	static const char* Mode_Getter(Sound_Mode _mode);
#pragma endregion

#pragma region Private Functions
	void Play_Sound(const std::string& _filename, Sound_Mode _mode);
	void Set_Pause(bool _is_paused);
	void Set_Volume(FMOD::ChannelGroup* _channel, float _volume);
	FMOD::ChannelGroup* Get_Channel(std::string _channel);
	FMOD_MODE Mode_Selector(Sound_Mode _mode);
#pragma endregion

#pragma region Public Functions
	void Init();
	void Update();
	void Exit();
#pragma endregion
}