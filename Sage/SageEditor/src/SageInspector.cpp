#include "imgui.h"
#include "GameObjects.hpp"
#include <stdio.h>

namespace Sage_Inspector
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
    /*std::vector<const char*> componentNames = { "COMPONENT", "TRANSFORM", "UITRANSFORM", "SPRITE2D", "IMAGE", "RENDERER", "ANIMATOR", "BOXCOLLIDER2D"
    , "PHYSICS", "AUDIO", "BEHAVIOUR", "BUTTON", "NUM_OF_TYPES_OF_COMPONENTS"};*/

    void Show_Transform_Component(Transform* _transform_component) {
        if (ImGui::BeginTable("transform_table_width", 4, ImGuiTableFlags_Borders))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Transform");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("X");
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("Y");
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("Z");

            // Position Row
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Position");
            ImGui::TableSetColumnIndex(1);
            float pos_x = _transform_component->Get_Position().x;
            if (ImGui::InputFloat("##PositionX", &pos_x))
            {
            	_transform_component->Get_Position().x = pos_x;
            }
            ImGui::TableSetColumnIndex(2);
            float pos_y = _transform_component->Get_Position().y;
            if (ImGui::InputFloat("##PositionY", &pos_y))
            {
                _transform_component->Get_Position().y = pos_y;
            }
            ImGui::TableSetColumnIndex(3);
            float pos_z = _transform_component->Get_Position().z;
            if (ImGui::InputFloat("##PositionZ", &pos_z))
            {
                _transform_component->Get_Position().z = pos_z;
            }

            // Rotation Row
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Rotation");
            ImGui::TableSetColumnIndex(1);
        	float rot_x = _transform_component->Get_Rotation().x;
            if (ImGui::InputFloat("##RotationX", &rot_x))
            {
                _transform_component->Get_Rotation().x = rot_x;
            }
            ImGui::TableSetColumnIndex(2);
            float rot_y = _transform_component->Get_Rotation().y;
            if (ImGui::InputFloat("##PositionY", &rot_y))
            {
                _transform_component->Get_Rotation().y = rot_y;
            }
            ImGui::TableSetColumnIndex(3);
            float rot_z = _transform_component->Get_Rotation().z;
            if (ImGui::InputFloat("##PositionZ", &rot_z))
            {
                _transform_component->Get_Rotation().z = rot_z;
            }

            // Scale Row
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Scale");
            ImGui::TableSetColumnIndex(1);
            float scale_x = _transform_component->Get_Scale().x;
            if (ImGui::InputFloat("##ScaleX", &scale_x))
            {
                _transform_component->Get_Scale().x = scale_x;
            }
            ImGui::TableSetColumnIndex(2);
            float scale_y = _transform_component->Get_Scale().y;
            if (ImGui::InputFloat("##ScaleY", &scale_y))
            {
                _transform_component->Get_Scale().y = scale_y;
            }
            ImGui::TableSetColumnIndex(3);
            float scale_z = _transform_component->Get_Scale().z;
            if (ImGui::InputFloat("##ScaleZ", &scale_z))
            {
                _transform_component->Get_Scale().z = scale_z;
            }
            ImGui::EndTable();
            //transform_component->Get_Position().x
        }
    }

    void Show_UITransform_Component(UITransform* _ui_transform) {
        if (ImGui::BeginTable("uitransform_table", 4, ImGuiTableFlags_Borders))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("UI Transform");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("X");
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("Y");
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("Z");

            // Position Row
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Position");
            ImGui::TableSetColumnIndex(1);
            float pos_x = _ui_transform->Get_Position().x;
            if (ImGui::InputFloat("##UIPositionX", &pos_x))
            {
                _ui_transform->Get_Position().x = pos_x;
            }
            ImGui::TableSetColumnIndex(2);
            float pos_y = _ui_transform->Get_Position().y;
            if (ImGui::InputFloat("##UIPositionY", &pos_y))
            {
                _ui_transform->Get_Position().y = pos_y;
            }
            ImGui::TableSetColumnIndex(3);
            float pos_z = _ui_transform->Get_Position().z;
            if (ImGui::InputFloat("##UIPositionZ", &pos_z))
            {
                _ui_transform->Get_Position().z = pos_z;
            }

            // Rotation Row
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Rotation");
            ImGui::TableSetColumnIndex(1);
            float rot_x = _ui_transform->Get_Rotation().x;
            if (ImGui::InputFloat("##UIRotationX", &rot_x))
            {
                _ui_transform->Get_Rotation().x = rot_x;
            }
            ImGui::TableSetColumnIndex(2);
            float rot_y = _ui_transform->Get_Rotation().y;
            if (ImGui::InputFloat("##UIRotationY", &rot_y))
            {
                _ui_transform->Get_Rotation().y = rot_y;
            }
            ImGui::TableSetColumnIndex(3);
            float rot_z = _ui_transform->Get_Rotation().z;
            if (ImGui::InputFloat("##UIRotationZ", &rot_z))
            {
                _ui_transform->Get_Position().z = rot_z;
            }

            // Scale Row
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Scale");
            ImGui::TableSetColumnIndex(1);
            float scale_x = _ui_transform->Get_Scale().x;
            if (ImGui::InputFloat("##UIScaleX", &scale_x))
            {
                _ui_transform->Get_Scale().x = scale_x;
            }
            ImGui::TableSetColumnIndex(2);
            float scale_y = _ui_transform->Get_Scale().y;
            if (ImGui::InputFloat("##UIScaleY", &scale_y))
            {
                _ui_transform->Get_Scale().y = scale_y;
            }
            ImGui::TableSetColumnIndex(3);
            float scale_z = _ui_transform->Get_Scale().z;
            if (ImGui::InputFloat("##UIScaleZ", &scale_z))
            {
            	_ui_transform->Get_Scale().z = scale_z;
            }
        }
    }

    void Show_RigidBody_Component(RigidBody* _rigid_body)
    {
	    if (ImGui::BeginTable("velocity_table", 3, ImGuiTableFlags_Borders))
	    {
		    // Velocity Row
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Velocity");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("X");
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("Y");

            // Velocity X/Y
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Velocity");
            ImGui::TableSetColumnIndex(1);
            float velocity_x = _rigid_body->Get_Velocity().x;
            if (ImGui::InputFloat("##VelocityX", &velocity_x))
            {
                _rigid_body->Get_Velocity().x = velocity_x;
            }
            ImGui::TableSetColumnIndex(2);
            float velocity_y = _rigid_body->Get_Velocity().y;
            if (ImGui::InputFloat("##VelocityY", &velocity_y))
            {
                _rigid_body->Get_Velocity().y = velocity_y;
            }
            ImGui::EndTable;
	    }

        ImGui::Separator();
        ImGui::Text("Enable Gravity");
        static bool gravity_flag = _rigid_body->Gravity_Flag();
        ImGui::Checkbox("##Gravity", &gravity_flag);
        _rigid_body->Set_Gravity_Flag(gravity_flag);
        ImGui::Text("Gravity");
        float gravity_val = _rigid_body->Get_Gravity();
        _rigid_body->Apply_New_Gravity(gravity_val);
        ImGui::Separator();

        ImGui::Text("Mass");
        float mass = _rigid_body->Get_Mass();
        if (ImGui::InputFloat("#Mass", &mass))
        {
            _rigid_body->Apply_Mass(mass);
        }
    }

    void Show_Box_Collider2D_Component(BoxCollider2D* _box_collider2D)
    {
	    
    }
    //void DrawRendererComponent(Sprite2D* _sprite_2d) {
    //    if (ImGui::CollapsingHeader("Renderer")) {
    //        ImGui::ColorEdit3("Color", color);
    //         //Add more fields specific to the Renderer component
    //    }
    //}

    //void DrawRendererComponent(float* color) {
    //    if (ImGui::CollapsingHeader("Renderer")) {
    //        ImGui::ColorEdit3("Color", color);
    //        // Add more fields specific to the Renderer component
    //    }
    //}

    void ShowInspector() {
        
        //ImGui::Button("Add Component");

        for (auto& gameobject : Game_Objects::Get_Game_Objects()) {
            for (auto& component : gameobject.second.get()->Get_Component_List())
            {
                switch (component.get()->Get_Component_Type())
                {
                case TRANSFORM:
                    Show_Transform_Component(dynamic_cast<Transform*>(component.get()));
                    break;
                case COMPONENT:
                    break;
                case UITRANSFORM:
                    Show_UITransform_Component(dynamic_cast<UITransform*>(component.get()));
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
                case RIGIDBODY:
                    Show_RigidBody_Component(dynamic_cast<RigidBody*>(component.get()));
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