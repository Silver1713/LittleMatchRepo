#pragma once
#include "imgui.h"
#include <limits.h>
#include <cstdio>
#include "imgui_impl_opengl3.h"
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
    void Show_Hierarchy_Window();

    void Show_Inspector_Window();

    void Show_Project_Window();

    void Show_Scene_Window();

    void Show_Game_Window();

    void Show_Asset_Window();

    void Show_Play_Pause_Bar();

    void RenderGUI();
}