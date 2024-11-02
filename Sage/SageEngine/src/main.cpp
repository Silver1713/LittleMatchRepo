/* Start Header ************************************************************************/
/*!
\file		Prefabs.cpp
\title		Memory's Flame
\authors	Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (40%)
            Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (20%)
            Jia Hao (40%)
\par		b.muhammadhafiz@digipen.edu, halisilyasa.b@digipen.edu, jia hao digipen
\date		10 September 2024
\brief		This is the main entry point for the engine.
            It include libraries and manages life cycle of the engine.

            All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

/*
 *	@note: You may test your components here. This is where
 *	all the libs is being compiled and run.
 *
 *	Just include your header file for the stuff you want to test.
 *
 *	Private (internal) headers cannot be included.
 *
 */

#include <iostream>
#include <backward.hpp>
#include "SageHelper.hpp"
#include "SageEngine.hpp"
// Forward declaration
void init();
void update();
void PhysicsUpdate();
void draw();
void exit();



#define ENABLE_NVIDIA_OPTIMUS 1

#if ENABLE_NVIDIA_OPTIMUS == 1
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

/*!*****************************************************************************
  \brief
    Entry point for SageEngine
*******************************************************************************/
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	init();

	while (!SageHelper::sage_ptr_window->Should_Window_Close())
	{
		SageEngine::Input();
		       
		SageEngine::Update();

		SageEngine::Draw(false);

		SageHelper::sage_ptr_window->Swap_Buffers();


	}
	SageEngine::Exit();
	return 0;
}

/*!*****************************************************************************
  \brief
    Initializes the window, assets and scenes
*******************************************************************************/
void init()
{
	SageEngine::Init();
}

/*!*****************************************************************************
  \brief
    Updates SageEngine
*******************************************************************************/
void update()
{
	SageEngine::Update();
}

/*!*****************************************************************************
  \brief
    Updates the Physics of SageEngine
*******************************************************************************/
void PhysicsUpdate()
{
	// Do you want a fixed physics update? - JH
}

/*!*****************************************************************************
  \brief
    Draws the scene
*******************************************************************************/
void draw()
{
	SageEngine::Draw(false);
}

/*!*****************************************************************************
  \brief
    Exits SageEngine
*******************************************************************************/
void exit()
{
    SageEngine::Exit();
}
