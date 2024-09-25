/* Start Header ************************************************************************/
/*!
\file		SceneManager.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the declarations of functions relating to scene management.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once

namespace SM {
	typedef void(*Function_Ptr)();

	void Ignore_Safety_Bools(bool _is_ignoring);

	void Start_Fade_In();
	void Start_Fade_Out();

	void Fade_In();
	void Fade_Out();

	bool const& Has_Faded_In();
	bool const& Has_Faded_Out();

	void Set_Next_Scene(void(*_load)(), void(*_init)(), void (*_input)(), void(*_update)(), void (*_draw)(), void (*_free)(), void (*_unload)());
	void Go_To_Next_Scene();
	void Restart_Scene();

	void Load();
	void Init();
	void Input();
	void Update();
	void Draw();
	void Free();
	void Unload();
	void Exit_Game();

	bool* Get_Game_Running();
}