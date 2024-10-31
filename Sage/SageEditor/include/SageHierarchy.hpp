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
    extern GameObject* selectedObject; // Pointer to the selected object.

    void UpdateGameObjectsFromScene();
    void CreateNewGameObject();
    void CreateGameObjectFromPrefab(const Assets::Prefabs::Prefab& prefab);
    void DrawHierarchy(GameObject* object);
    void Hierarchy();
}