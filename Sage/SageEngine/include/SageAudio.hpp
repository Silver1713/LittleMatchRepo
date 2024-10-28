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

//Defines the audio asset folder.
#define PATH "../SageEngine/data/assets/audio/"

//Defines the available audio extension types.
#define AUDIO_EXTENSION ".ogg"

//Enumerator to handle available sound modes.
typedef enum
{
	LOOP,
	NO_LOOP
}Sound_Mode;

namespace SageAudio
{
#pragma region Helper Functions
	/*!*****************************************************************************
	  \brief
		Prints the type of error in FMOD.

	  \param _result
		The enum type FMOD_RESULT.
	*******************************************************************************/
	void FMOD_ErrorCheck(FMOD_RESULT _result);

	/*!*****************************************************************************
	  \brief
		Prints the sound mode that will be set from FMOD.

	  \param _mode
		The enum type Sound_Mode.

	  \return
		The name of the mode.
	*******************************************************************************/
	static const char* Mode_Getter(Sound_Mode _mode);
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
	void Play_Sound(const std::string& _filename, Sound_Mode _mode);

	/*!*****************************************************************************
	  \brief
		Pauses all game audio excluding user interface sounds.
	*******************************************************************************/
	void Pause_Audio();

	/*!*****************************************************************************
	  \brief
		Stops all game audio currently playing.
	*******************************************************************************/
	void Stop_All_Audio();

	/*!*****************************************************************************
	  \brief
		Retrieves the channel group to allow control of it.

	  \param _channel
		The name of the channel.

	  \return
		The channel group.
	*******************************************************************************/
	void Set_Volume(FMOD::ChannelGroup* _channel, float _volume);

	/*!*****************************************************************************
	  \brief
		Sets the volume of the specified channel to the desired volume.

	  \param _channel
		The name of the channel. Used with Get_Channel().

	  \param _volume
		The desired volume from 0.0f to 1.0f
	*******************************************************************************/
	FMOD::ChannelGroup* Get_Channel(std::string _channel);

	/*!*****************************************************************************
	  \brief
		Sets the mode of how the audio will be played.

	  \param _mode
		The desired mode to set. Either LOOP or NO_LOOP.

	  \return
		The defined FMOD_MODE.
	*******************************************************************************/
	FMOD_MODE Mode_Selector(Sound_Mode _mode);
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
	void Init();

	/*!*****************************************************************************
	  \brief
		Updates the FMOD system to handle audio playback.
	*******************************************************************************/
	void Update();

	/*!*****************************************************************************
	  \brief
		Releases all generated sound files, audio channel groups and the FMOD system.
	*******************************************************************************/
	void Exit();
#pragma endregion
}