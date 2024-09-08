/* Start Header ************************************************************************/
/*!
\file		Scene_Manager.h
\title		Battle Knights
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		09 January 2024
\brief		Contains the declarations of functions relating to scene management

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "AEEngine.h"
namespace SM {
	typedef void(*Function_Ptr)();

	void Ignore_Safety_Bools(bool _is_ignoring);

	void Reset_Fade_In();
	void Reset_Fade_Out();

	void Fade_In(f32 transition_period);
	void Fade_Out(f32 transition_period);

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