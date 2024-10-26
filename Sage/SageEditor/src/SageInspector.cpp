#include "imgui.h"
#include "GameObjects.hpp"
#include <stdio.h>

namespace SageComponent
{
    
    std::vector<std::unique_ptr<Component>> Component_List;
    //typedef enum {
    //    COMPONENT,
    //    TRANSFORM,
    //    UITRANSFORM,
    //    SPRITE2D,
    //    IMAGE,
    //    RENDERER,
    //    ANIMATOR,
    //    BOXCOLLIDER2D,
    //    PHYSICS,
    //    AUDIO,
    //    BEHAVIOUR,
    //    BUTTON,
    //    NUM_OF_TYPES_OF_COMPONENTS
    //} ComponentType;
    // Pseudo test
    std::vector<const char*> componentNames = { "COMPONENT", "TRANSFORM", "UITRANSFORM", "SPRITE2D", "IMAGE", "RENDERER", "ANIMATOR", "BOXCOLLIDER2D"
    , "PHYSICS", "AUDIO", "BEHAVIOUR", "BUTTON", "NUM_OF_TYPES_OF_COMPONENTS"};

    void DrawTransformComponent(float* position, float* rotation, float* scale) {
        if (ImGui::CollapsingHeader("Transform")) {
            ImGui::InputFloat3("Position", position);
            ImGui::InputFloat3("Rotation", rotation);
            ImGui::InputFloat3("Scale", scale);
        }
    }

    void DrawSprite2DComponent(int* spriteID) {
        if (ImGui::CollapsingHeader("Sprite2D")) {
            ImGui::InputInt("Sprite ID", spriteID);
            // Add more fields specific to the Sprite2D component
        }
    }

    void DrawRendererComponent(float* color) {
        if (ImGui::CollapsingHeader("Renderer")) {
            ImGui::ColorEdit3("Color", color);
            // Add more fields specific to the Renderer component
        }
    }

    void ShowInspector() {
        
        //ImGui::Button("Add Component");

        for (auto& gameobject : Game_Objects::Get_Game_Objects()) {
            for (auto& component : gameobject.second.get()->Get_Component_List())
            {
                switch (component.get()->Get_Component_Type())
                {
                case TRANSFORM:
                    if (ImGui::BeginTable("transform_table_width", 3, ImGuiTableFlags_Borders)) {
                        ImGui::TableSetupColumn("X");
                        ImGui::TableSetupColumn("Y");
                        ImGui::TableSetupColumn("Z");
                    }
                    break;
                case COMPONENT:
                    break;
                case UITRANSFORM:
                    break;
                case SPRITE2D:
                    break;
                case IMAGE:
                    break;
                case RENDERER:
                    break;
                case ANIMATOR:
                    break;
                case BOXCOLLIDER2D:
                    break;
                case PHYSICS:
                    break;
                case AUDIO:
                    break;
                case BEHAVIOUR:
                    break;
                case BUTTON:
                    break;
                case NUM_OF_TYPES_OF_COMPONENTS:
                    break;
                }
            }
        }

        /*if (ImGui::Button("Add Component")) {
            ImGui::OpenPopup("Add Component Popup");
        }

        if (ImGui::BeginPopup("Add Component Popup")) {
            for (size_t i = 0; i < componentNames.size(); ++i) {
                if (ImGui::Selectable(componentNames[i])) {
                    ImGui::Text("Thanks for clicking me!");
                }
            }
            ImGui::EndPopup;
        }*/
        
        //void AddComponentToEntity(Entity & entity, ComponentType componentType) {
        //    switch (componentType) {
        //    case ComponentType::Transform:
        //        entity.AddComponent<TransformComponent>();
        //        break;
        //    case ComponentType::Mesh:
        //        entity.AddComponent<MeshComponent>();
        //        break;
        //    case ComponentType::Physics:
        //        entity.AddComponent<PhysicsComponent>();
        //        break;
        //        // Add other components as needed
        //    }
        //}
    }


    //void Inspector()
    //{
    //    // Right side: draw properties
    //    ImGui::BeginGroup();
    //    if (TreeNode* node = selected_node)
    //    {
    //        //This is how renaming works on the Inspector that is supposed to change in the Hierarchy.
    //        if (ImGui::InputText("###name", node->Name, IM_ARRAYSIZE(node->Name), ImGuiInputTextFlags_EnterReturnsTrue))
    //        {
    //            /*RenamingDoc = doc;
    //            RenamingStarted = true;*/
    //        }

    //        ImGui::Separator();
    //        if (ImGui::BeginTable("##properties", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
    //        {
    //            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
    //            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 2.0f); // Default twice larger
    //            if (node->HasData)
    //            {
    //                // In a typical application, the structure description would be derived from a data-driven system.
    //                // - We try to mimic this with our ExampleMemberInfo structure and the ExampleTreeNodeMemberInfos[] array.
    //                // - Limits and some details are hard-coded to simplify the demo.
    //                for (const ComponentInfo& field_desc : component_infos)
    //                {
    //                    ImGui::TableNextRow();
    //                    ImGui::PushID(field_desc.Name);
    //                    ImGui::TableNextColumn();
    //                    ImGui::AlignTextToFramePadding();
    //                    ImGui::TextUnformatted(field_desc.Name);
    //                    ImGui::TableNextColumn();
    //                    void* field_ptr = (void*)(((unsigned char*)node) + field_desc.Offset);
    //                    switch (field_desc.DataType)
    //                    {
    //                    case ImGuiDataType_Bool:
    //                    {
    //                        IM_ASSERT(field_desc.DataCount == 1);
    //                        ImGui::Checkbox("##Editor", (bool*)field_ptr);
    //                        break;
    //                    }
    //                    case ImGuiDataType_S32:
    //                    {
    //                        int v_min = INT_MIN, v_max = INT_MAX;
    //                        ImGui::SetNextItemWidth(-FLT_MIN);
    //                        ImGui::DragScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, 1.0f, &v_min, &v_max);
    //                        break;
    //                    }
    //                    case ImGuiDataType_Float:
    //                    {
    //                        float v_min = 0.0f, v_max = 1.0f;
    //                        ImGui::SetNextItemWidth(-FLT_MIN);
    //                        ImGui::SliderScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, &v_min, &v_max);
    //                        break;
    //                    }
    //                    }
    //                    ImGui::PopID();
    //                }
    //            }
    //            ImGui::EndTable();
    //        }
    //    }
    //    ImGui::EndGroup();
    //}

	void ComponentButtons() {
		//if (I)
	}
}