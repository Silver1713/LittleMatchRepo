#include "SageHierarchy.hpp"
#include <iostream>
#include "../../SageEngine/src/GameObjects.cpp"

namespace SageHierarchy
{
    // Definition of the list of GameObjects.
    std::vector<GameObject*> game_object_list;
    extern GameObject* selected_object = nullptr;

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
        //Update_Hierarchy(); need to call this in scene manager change scene

        if (ImGui::Button("Add GameObject"))
        {
            Create_Empty();
        }

        // Check for deletion
        if (selected_object && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
        {
            Game_Objects::Delete_Game_Object(selected_object);
            selected_object = nullptr;
        }

        // Iterate and draw each GameObject node, allowing for reordering via drag-and-drop
        for (int i = 0; i < game_object_list.size(); ++i)
        {
            GameObject* currentObject = game_object_list[i];
            Draw_Node(currentObject);

            // Begin drag-and-drop reordering
            if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
            {
                float dragY = ImGui::GetMouseDragDelta(0).y;
                int targetIndex = (dragY < 0.f) ? i - 1 : i + 1; // Set target index based on drag direction

                // Only proceed if within bounds and drag distance exceeds threshold
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