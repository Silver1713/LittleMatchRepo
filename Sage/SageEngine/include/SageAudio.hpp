#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include "fmod.hpp"
#include "fmod_errors.h"
#include "SageAudioFiles.hpp";

#define PATH "Sage/build"

namespace fs = std::filesystem;

typedef enum
{
	LOOP,
	NO_LOOP
}Sound_Mode;

namespace SageAudio
{
#pragma region Helper Functions
	void FMOD_ErrorCheck(FMOD_RESULT _result);
	void Filesystem_Implementation();
	FMOD_MODE Mode_Selector(Sound_Mode _mode);
	static const char* Mode_Getter(Sound_Mode _mode);
#pragma endregion

#pragma region Private Functions
	void Play_Sound(size_t _index, Sound_Mode _mode);
#pragma endregion

#pragma region Public Functions
	void Init();
	void Update();
	void Exit();
#pragma endregion
}