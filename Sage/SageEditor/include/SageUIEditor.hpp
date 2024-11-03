/* Start Header ************************************************************************/
/*!
\file		SageUIEditor.hpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301325 (100%)
\par		neo.h@digipen.edu
\date		17 October 2024
\brief		This file contain the declaration for the Sage UI Editor.
*/
/* End Header **************************************************************************/
#pragma once
#include "imgui.h"
#include <limits.h>
#include <cstdio>
#include "imgui_impl_opengl3.h"

/*!*****************************************************************************
\brief Encapsulate the SageUIEditor in a namespace

This namespace contain the relevant functions, bools and namespaces for
SageUIEditor
*******************************************************************************/
namespace SageUIEditor
{   
    extern bool play_select;
    extern bool pause_select;
    extern bool is_playing;

	// JH: Encapsulate IMGUI into more OOP like structure

    namespace IMGUI_Elements {
        struct IMGUI_Vector2
        {
            bool active;
            bool hovered;
            bool onChanged;
            bool onClick;

            IMGUI_Vector2(float* _value);

        };
    }

    /*!*****************************************************************************
    \brief Show the hierarchy window in IMGUI editor

    This function shows the heirarchy window in the IMGUI editor which contains
    the game objects.
    *******************************************************************************/
    void Show_Hierarchy_Window();

    /*!*****************************************************************************
    \brief Show the inspector window in IMGUI editor

    This function shows the inspector window in the IMGUI editor which contains the
    components in the inspector window.
    *******************************************************************************/
    void Show_Inspector_Window();

    /*!*****************************************************************************
    \brief Show the project window in IMGUI editor

    This function shows the project window in the IMGUI editor.
    *******************************************************************************/
    void Show_Project_Window();

    /*!*****************************************************************************
    \brief Show the scene window in IMGUI editor

    This function shows the scene window in the IMGUI editor.
    *******************************************************************************/
    void Show_Scene_Window();

    /*!*****************************************************************************
    \brief Show the game window in IMGUI editor

    This function shows the game window in the IMGUI editor.
    *******************************************************************************/
    void Show_Game_Window();

    void Show_Asset_Window();

    //void Show_Play_Pause_Bar();
    /*!*****************************************************************************
    \brief Show the engine editor UI

    This function shows the engine with its' relevant UI using IMGUI
    *******************************************************************************/
    void RenderGUI();
}