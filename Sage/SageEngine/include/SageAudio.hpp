#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unordered_map>
#include "fmod.hpp"
#include "fmod_errors.h"

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
	FMOD_MODE Mode_Selector(Sound_Mode _mode);
	static const char* Mode_Getter(Sound_Mode _mode);
#pragma endregion

#pragma region Private Functions
	void Play_Sound(std::string _filename);
#pragma endregion

#pragma region Public Functions
	void Init();
	void Update();
	void Exit();
#pragma endregion
}