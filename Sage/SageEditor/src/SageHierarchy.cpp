#include "SageHierarchy.hpp"
#include <iostream>

namespace SageHierarchy
{
    // Definition of the list of GameObjects.
    std::vector<GameObject*> gameObjects;
    GameObject* selectedObject = nullptr;

    void UpdateGameObjectsFromScene()
    {
        // Clear the current list
        gameObjects.clear();

        // Get the game objects from the scene manager
        auto& gameObjectMap = Game_Objects::Get_Game_Objects();

        // Iterate through the map and add pointers to the gameObjects vector
        for (auto& [id, gameObjectPtr] : gameObjectMap)
        {
            gameObjects.push_back(gameObjectPtr.get());
        }
    }

    // Function to create a new empty GameObject
    //void CreateNewGameObject() {
    //    auto* newObject = Game_Objects::Instantiate(/* Pass a default prefab or create an empty instance */);
    //    gameObjects.push_back(newObject); // Add to the list of GameObjects
    //}

    // Function to create a GameObject from a prefab
    void CreateGameObjectFromPrefab(const Assets::Prefabs::Prefab& prefab) {
        // Create GameObject logic here, e.g.:
        auto* prefabObject = Game_Objects::Instantiate(prefab, prefab.prefab_ID);
        gameObjects.push_back(prefabObject); // Add to the list of GameObjects
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
        // Button to create a new empty GameObject
        if (ImGui::Button("Add GameObject")) {
            //CreateNewGameObject(); // Call to create a new empty GameObject
        }

        //std::cout << "Loading Game Objects..." << std::endl;
        for (const auto& gameObject : gameObjects) {
            //std::cout << "Loading " << gameObject->Get_ID() << std::endl;
            DrawHierarchy(gameObject);
        }
    }
}