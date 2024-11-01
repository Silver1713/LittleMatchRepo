#pragma once
#include "imgui.h"
#include <limits.h>
#include <cstdio>
#include "imgui_impl_opengl3.h"
namespace SageUIEditor
{

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

    void RenderGUI();
}