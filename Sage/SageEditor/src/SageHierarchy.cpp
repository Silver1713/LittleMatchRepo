#include "SageHierarchy.hpp"
#include <iostream>
#include "GameObjects.hpp"

namespace SageHierarchy
{
    // Definition of the list of GameObjects.
    std::vector<GameObject*> game_object_list;
    extern GameObject* selected_object = nullptr;
	bool scene_change = true;

    void Update_Hierarchy()
    {
        game_object_list.clear();
        auto& game_object_map = Game_Objects::Get_Game_Objects();
        for (auto& [id, game_object] : game_object_map)
        {
            game_object_list.push_back(game_object.get());
        }
    }

    void Create_Empty() {
        int i = 1;
        std::string base_name = "Empty Game Object ";
        std::string new_name;

        while (true)
        {
            new_name = base_name + std::to_string(i);
            bool name_exists = false;

            for (const auto gameObject : game_object_list)
            {
                if (gameObject->Get_ID() == new_name)
                {
                    name_exists = true;
                    break;
                }
            }
            if (!name_exists)
            {
                break;
            }

            i++;
        }

        Game_Objects::Instantiate(Prefabs::Get_Prefab("EMPTY"), new_name);
        Update_Hierarchy();
    }

    void Create_Prefab(const Assets::Prefabs::Prefab& _prefab)
    {
        Game_Objects::Instantiate(_prefab, _prefab.prefab_ID);
        Update_Hierarchy();
    }

    void Draw_Node(GameObject* _object)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
        if (_object == selected_object)
        {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)_object->Get_ID().c_str(), flags, "%s", _object->Get_ID().c_str());

        if (ImGui::IsItemClicked())
        {
            selected_object = _object;
        }

        if (selected_object == _object && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_F2)))
        {
            ImGui::OpenPopup("Rename GameObject");
        }
        if (ImGui::BeginPopup("Rename GameObject"))
        {
            static char new_name[32] = "";
            if (ImGui::InputText("New Name", new_name, IM_ARRAYSIZE(new_name), ImGuiInputTextFlags_EnterReturnsTrue))
            {
                _object->Set_ID(new_name);
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (node_open)
        {
            ImGui::TreePop();
        }
    }

    void Hierarchy()
    {
        // Update hierarchy if needed
        // Update_Hierarchy(); // Uncomment when changing scenes in SceneManager

        // Button to add a new GameObject
        if (ImGui::Button("Add GameObject"))
        {
            Create_Empty();
        }

        // Accept drop payload for creating GameObjects from prefabs
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_PREFAB"))
            {
                // Retrieve the prefab ID from the payload
                const char* prefabID = static_cast<const char*>(payload->Data);
                auto& prefabs = Assets::Prefabs::Get_Prefabs();
                auto it = prefabs.find(prefabID);
                if (it != prefabs.end())
                {
                    const auto& prefab = it->second;
                    Create_Prefab(prefab); // Function to instantiate prefab in hierarchy
                }
            }
            ImGui::EndDragDropTarget(); // End the drag-and-drop target
        }

        // Check if the selected GameObject should be deleted
        if (selected_object && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
        {
            Game_Objects::Delete_Game_Object(selected_object);
            Update_Hierarchy();
            selected_object = nullptr;
        }

        // Iterate and draw each GameObject node, allowing for reordering
        for (int i = 0; i < game_object_list.size(); ++i)
        {
            GameObject* currentObject = game_object_list[i];
            Draw_Node(currentObject);

            // Begin drag-and-drop reordering logic here
            if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
            {
                float dragY = ImGui::GetMouseDragDelta(0).y;
                int targetIndex = (dragY < 0.f) ? i - 1 : i + 1;

                // Ensure the drag is within bounds and exceeds a threshold
                if (targetIndex >= 0 && targetIndex < game_object_list.size() &&
                    std::abs(dragY) > ImGui::GetTextLineHeightWithSpacing())
                {
                    std::swap(game_object_list[i], game_object_list[targetIndex]);
                    ImGui::ResetMouseDragDelta();  // Reset drag state after swap
                }
            }
        }
    }
}