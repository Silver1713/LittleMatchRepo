/* Start Header ************************************************************************/
/*!
\file		Scene.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		20 October 2024
\brief		Contains the definitions of functions that define a scene

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "AssetLoader.hpp"
#include "Prefabs.hpp"
#include "SageRenderer.hpp"
#include "SageHelper.hpp"
#include "SageAudio.hpp"
#include "Scene.hpp"

#include <iostream>
#include <random>

//FOR TESTING PURPOSES
#include <cstdlib> // for srand()
#include <memory>	


namespace Scene {

	static SageCamera camera;
	static SageViewport vp;

	static bool enable_collider_view{ false };

	/*!*****************************************************************************
	  \brief
		Loads data the scene may need
	*******************************************************************************/
	void Load()
	{
	}

	/*!*****************************************************************************
	  \brief
		Initializes the scene
	*******************************************************************************/
	void Init()
	{
		camera.init({ 50,0 }, { static_cast<float>(SageHelper::WINDOW_WIDTH),  static_cast<float>(SageHelper::WINDOW_HEIGHT) }, 0.f, SageCamera::SageCameraType::SAGE_ORTHO);
		vp.set_dims({ static_cast<float>(SageHelper::WINDOW_WIDTH),  static_cast<float>(SageHelper::WINDOW_HEIGHT) });
		vp.calculate_viewport_xform();

		SageRenderer::Set_Current_View(&camera);
		SageRenderer::Set_Current_View(vp);

		vp.setViewport();

		SageAudio::Play_Sound("bgm_main_menu", LOOP);
		SageAudio::Play_Sound("ambient_rain", LOOP);
	}

	/*!*****************************************************************************
	  \brief
		Handles input checks in the scene
	*******************************************************************************/
	void Input()
	{
	}

	/*!*****************************************************************************
	  \brief
		Updates the scene
	*******************************************************************************/
	void Update()
	{
	}

	/*!*****************************************************************************
	  \brief
		Draws the scene
	*******************************************************************************/
	void Draw()
	{
	}

	/*!*****************************************************************************
	  \brief
		Frees the scene
	*******************************************************************************/
	void Free()
	{
	}

	/*!*****************************************************************************
	  \brief
		Unloads the scene
	*******************************************************************************/
	void Unload()
	{
	}
}
