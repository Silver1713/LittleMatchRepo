#include "SageHierarchy.hpp"
#include <iostream>
#include "../../SageEngine/src/GameObjects.cpp"

namespace SageHierarchy
{
    // Definition of the list of GameObjects.
    std::vector<GameObject*> gameObjects;
    extern GameObject* selectedObject = nullptr;

    void UpdateGameObjectsFromScene()
    {
        // Clear the current list
        gameObjects.clear();

        // Get the latest game objects from the SceneManager/Game_Objects
        auto& gameObjectMap = Game_Objects::Get_Game_Objects();

        // Populate the gameObjects vector with raw pointers to GameObject instances
        for (auto& [id, gameObjectPtr] : gameObjectMap)
        {
            gameObjects.push_back(gameObjectPtr.get());
        }

        std::cout << "Number of game objects: " << gameObjects.size() << std::endl;
    }

    void CreateNewGameObject() {
        int i = 1;
        std::string baseName = "Empty Game Object ";
        std::string newName;

        // Loop to find an unused identifier
        while (true) {
            newName = baseName + std::to_string(i);
            bool nameExists = false;

            for (const auto gameObject : gameObjects) {
                if (gameObject->Get_ID() == newName) {
                    nameExists = true;
                    break;
                }
            }

            if (!nameExists) {
                break; // Found a unique name
            }

            i++; // Increment to try the next suffix
        }

        // Create the new GameObject with a unique identifier
        Game_Objects::Instantiate(Prefabs::Get_Prefab("EMPTY"), newName);

        // Refresh the list to include the new object
        UpdateGameObjectsFromScene();
    }


    void CreateGameObjectFromPrefab(const Assets::Prefabs::Prefab& prefab) {
        // Instantiate directly adds to g_game_objects map, so no push_back needed here
        Game_Objects::Instantiate(prefab, prefab.prefab_ID);
        UpdateGameObjectsFromScene(); // Refresh the list to include the prefab object
    }

    void DrawHierarchy(GameObject* object) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        if (object->Get_Z_Order() > 0) { // Replace with actual child check if applicable
            flags |= ImGuiTreeNodeFlags_Leaf; // Mark as leaf if there are no children.
        }
        if (object == selectedObject) {
            flags |= ImGuiTreeNodeFlags_Selected; // Highlight selected object.
        }

        bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)object->Get_ID().c_str(), flags, "%s", object->Get_ID().c_str());

        // Handle selection.
        if (ImGui::IsItemClicked()) {
            selectedObject = object; // Update the selected object when clicked.
        }

        //// Handle renaming with F2.
        //if (selectedObject == object && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_F2))) {
        //    ImGui::OpenPopup("Rename GameObject");
        //}
        //// Renaming popup.
        //if (ImGui::BeginPopup("Rename GameObject")) {
        //    static char newName[64] = "";
        //    if (ImGui::InputText("New Name", newName, IM_ARRAYSIZE(newName), ImGuiInputTextFlags_EnterReturnsTrue)) {
        //        object->identifier = newName; // Assuming identifier can be directly set
        //        ImGui::CloseCurrentPopup();
        //    }
        //    ImGui::EndPopup();
        //}

        if (nodeOpen) {
            // If you have child GameObjects, you'd want to iterate and draw them here
            ImGui::TreePop();
        }
    }

    void Hierarchy() {
        if (ImGui::Button("Add GameObject")) {
            CreateNewGameObject();
        }

        for (const auto& gameObject : gameObjects) {
            DrawHierarchy(gameObject);
        }
    }
}