#pragma once
#include "imgui.h"
#include <limits.h>
#include <cstdio>
#include "imgui_impl_opengl3.h"
#include "GameObjects.hpp"
#include "AssetLoader.hpp"

namespace SageEditor
{
    void Show_Hierarchy_Window();
    void Show_Console_Window();
    void Show_Inspector_Window();
    void Show_Project_Window();
    void Show_Scene_Window();
    void Show_Game_Window();
    void Show_Asset_Window();
    void RenderInspectorWindow();
    //void Hierarchy(TreeNode* root_node);
    //void Inspector();
    void RenderGUI();
}