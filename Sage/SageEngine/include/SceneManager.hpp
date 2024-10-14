/* Start Header ************************************************************************/
/*!
\file		SceneManager.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the declarations of functions relating to scene management.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once

//Scene Manager
namespace SM {
	typedef void(*Function_Ptr)();

	/*!*****************************************************************************
	  \brief
		This function specifies if the scene should ignore safety checks just in case
		some systems havent fully loaded before accepting inputs

	  \param _is_ignoring
		Whether the scene manager should accept inputs
	*******************************************************************************/
	void Ignore_Safety_Bools(bool _is_ignoring);

	/*!*****************************************************************************
	  \brief
		Begins the fading in animation
	*******************************************************************************/
	void Start_Fade_In();
	/*!*****************************************************************************
	  \brief
		Begins the fading out animation
	*******************************************************************************/
	void Start_Fade_Out();

	/*!*****************************************************************************
	  \brief
		Calculates the current alpha for the transition screen depending on time that
		has passed
	*******************************************************************************/
	void Fade_In();
	/*!*****************************************************************************
	  \brief
		Calculates the current alpha for the transition screen depending on time that
		has passed
	*******************************************************************************/
	void Fade_Out();

	/*!*****************************************************************************
	  \brief
		Gets the state of the faded_in flag
	  \return
		the faded_in flag
	*******************************************************************************/
	bool const& Has_Faded_In();
	/*!*****************************************************************************
	  \brief
		Gets the state of the faded_out flag
	  \return
		the faded_out flag
	*******************************************************************************/
	bool const& Has_Faded_Out();

	/*!*****************************************************************************
	  \brief
		Set which level the game scene should load

	  \param _level_identifier
		The string key to set the current level to
	*******************************************************************************/
	void Set_Current_Level(std::string const& _level_identifier);

	/*!*****************************************************************************
	  \brief
		Sets what function pointers to turn the current scene's one into when 
		Go_To_Next_Scene is called

	  \param _load
		the load function that the scene manager will use

	  \param _init
		the init function that the scene manager will use

	  \param _input
		the input function that the scene manager will use

	  \param _update
		the update function that the scene manager will use

	  \param _draw
		the draw function that the scene manager will use

	  \param _free
		the free function that the scene manager will use

	  \param _unload
		the unload function that the scene manager will use
	*******************************************************************************/
	void Set_Next_Scene(void(*_load)(), void(*_init)(), void (*_input)(), void(*_update)(), void (*_draw)(), void (*_free)(), void (*_unload)(), std::string const& new_level_ID = "Level_1");
	/*!*****************************************************************************
	  \brief
		Goes to the next scene as specified by Set_Next_Scene

	  \param _level_identifier
		The string key for what level should be next scene
	*******************************************************************************/
	void Go_To_Next_Scene();
	/*!*****************************************************************************
	  \brief
		Sets up startup scene for when the engine is run

	  \param _level_identifier
		The string key for what level should be next scene
	*******************************************************************************/
	void Startup_Scene(std::string const& new_level_ID = "Level_1");
	/*!*****************************************************************************
	  \brief
		Restarts the scene
	*******************************************************************************/
	void Restart_Scene();

	/*!*****************************************************************************
	  \brief
		Loads the Scene Manager
	*******************************************************************************/
	void Load();

	/*!*****************************************************************************
	  \brief
		Initializes the Scene Manager
	*******************************************************************************/
	void Init();
	/*!*****************************************************************************
	  \brief
		Input Checks for the Scene Manager
	*******************************************************************************/
	void Input();
	/*!*****************************************************************************
	  \brief
		Updates the Scene Manager
	*******************************************************************************/
	void Update();
	/*!*****************************************************************************
	  \brief
		Draws the current scene
	*******************************************************************************/
	void Draw();
	/*!*****************************************************************************
	  \brief
		Frees the current scene
	*******************************************************************************/
	void Free();
	/*!*****************************************************************************
	  \brief
		Unloads the current scene
	*******************************************************************************/
	void Unload();
	/*!*****************************************************************************
	  \brief
		Exits the loop
	*******************************************************************************/
	void Exit_Game();
	/*!*****************************************************************************
	  \brief
		Gets the game running flag
	*******************************************************************************/
	bool* Get_Game_Running();
}