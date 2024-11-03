#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "GameObjects.hpp"
#include "AssetLoader.hpp"
#include "Prefabs.hpp"

namespace SageHierarchy
{
    // List of all top-level GameObjects (no single root).
    //extern std::vector<GameObject*> gameObjects;
    extern GameObject* selected_object; // Pointer to the selected object.
    extern bool scene_change;
    
    void Update_Hierarchy();
    void Create_Empty();
    void Create_Prefab(const Assets::Prefabs::Prefab& _prefab);
    void Draw_Node(GameObject* _object);
    void Hierarchy();
}