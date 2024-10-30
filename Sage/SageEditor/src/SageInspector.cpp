#include "SageInspector.hpp"

#include <iostream>

#include "SageUIEditor.hpp"

namespace Sage_Inspector
{

    void Show_Transform_Component(Transform* _transform_component) {
		bool changed = false;
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
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
					changed = true;
                    _transform_component->Get_Position().x = pos_x;
                }
                ImGui::TableSetColumnIndex(2);
                float pos_y = _transform_component->Get_Position().y;
                if (ImGui::InputFloat("##PositionY", &pos_y))
                {
					changed = true;
                    _transform_component->Get_Position().y = pos_y;
                }
                ImGui::TableSetColumnIndex(3);
                float pos_z = _transform_component->Get_Position().z;
                if (ImGui::InputFloat("##PositionZ", &pos_z))
                {
					changed = true;
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
					changed = true;
                    _transform_component->Get_Rotation().x = rot_x;
                }
                ImGui::TableSetColumnIndex(2);
                float rot_y = _transform_component->Get_Rotation().y;
                if (ImGui::InputFloat("##RotationY", &rot_y))
                {
					changed = true;
                    _transform_component->Get_Rotation().y = rot_y;
                }
                ImGui::TableSetColumnIndex(3);
                float rot_z = _transform_component->Get_Rotation().z;
                if (ImGui::InputFloat("##ROTATIONZ", &rot_z))
                {
					changed = true;
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
					changed = true;
                    _transform_component->Get_Scale().x = scale_x;
                }
                ImGui::TableSetColumnIndex(2);
                float scale_y = _transform_component->Get_Scale().y;
                if (ImGui::InputFloat("##ScaleY", &scale_y))
                {
					changed = true;
                    _transform_component->Get_Scale().y = scale_y;
                }
                ImGui::TableSetColumnIndex(3);
                float scale_z = _transform_component->Get_Scale().z;
                if (ImGui::InputFloat("##ScaleZ", &scale_z))
                {
					changed = true;
                    _transform_component->Get_Scale().z = scale_z;
                }
                ImGui::EndTable();
                //transform_component->Get_Position().x

                if (changed)
                {
					Sprite2D* sprite = _transform_component->Get_Parent()->Get_Component<Sprite2D>();
					if (sprite)
					{
						sprite->Update();
					}
                }
            }
        }
		ImGui::Separator();
    }

    void Show_UITransform_Component(UITransform* _ui_transform) {
		bool changed = false;
    	if (ImGui::CollapsingHeader("UI Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
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
					changed = true;
                    _ui_transform->Get_Position().x = pos_x;
                }
                ImGui::TableSetColumnIndex(2);
                float pos_y = _ui_transform->Get_Position().y;
                if (ImGui::InputFloat("##UIPositionY", &pos_y))
                {
					changed = true;
                    _ui_transform->Get_Position().y = pos_y;
                }
                ImGui::TableSetColumnIndex(3);
                float pos_z = _ui_transform->Get_Position().z;
                if (ImGui::InputFloat("##UIPositionZ", &pos_z))
                {
					changed = true;
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
					changed = true;
                    _ui_transform->Get_Rotation().x = rot_x;
                }
                ImGui::TableSetColumnIndex(2);
                float rot_y = _ui_transform->Get_Rotation().y;
                if (ImGui::InputFloat("##UIRotationY", &rot_y))
                {
					changed = true;
                    _ui_transform->Get_Rotation().y = rot_y;
                }
                ImGui::TableSetColumnIndex(3);
                float rot_z = _ui_transform->Get_Rotation().z;
                if (ImGui::InputFloat("##UIRotationZ", &rot_z))
                {
					changed = true;
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
					changed = true;
                    _ui_transform->Get_Scale().x = scale_x;
                }
                ImGui::TableSetColumnIndex(2);
                float scale_y = _ui_transform->Get_Scale().y;
                if (ImGui::InputFloat("##UIScaleY", &scale_y))
                {
                    changed = true;
                    _ui_transform->Get_Scale().y = scale_y;
                }
                ImGui::TableSetColumnIndex(3);
                float scale_z = _ui_transform->Get_Scale().z;
                if (ImGui::InputFloat("##UIScaleZ", &scale_z))
                {
                    changed = true;
                    _ui_transform->Get_Scale().z = scale_z;
                }
                ImGui::EndTable();


                if (changed)
                {
                    Image* sprite = _ui_transform->Get_Parent()->Get_Component<Image>();
                    if (sprite)
                    {
                        sprite->Update();
                    }
                }
            }
        }
		ImGui::Separator();
    }

    void Show_RigidBody_Component(RigidBody* _rigid_body)
    {
        if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::BeginTable("velocity_table", 3, ImGuiTableFlags_Borders))
            {
                // Velocity Row
                ImGui::TableNextRow();
                //ImGui::Text("Velocity");
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
                ImGui::EndTable();
            }

            ImGui::Separator();
            ImGui::Text("Enable Gravity");
            static bool gravity_flag = _rigid_body->Gravity_Flag();
            ImGui::Checkbox("##Enable Gravity", &gravity_flag);
            _rigid_body->Set_Gravity_Flag(gravity_flag);
            ImGui::Text("Gravity");
            ToastBox::Vec2 gravity_val = _rigid_body->Get_Gravity();
            SageUIEditor::IMGUI_Elements::IMGUI_Vector2 elmn{ &gravity_val.x };
            if (elmn.onChanged)
            {
                _rigid_body->Apply_New_Gravity(gravity_val);
            }

            ImGui::Separator();

            ImGui::Text("Mass");
            float mass = _rigid_body->Get_Mass();
            if (ImGui::InputFloat("##Mass", &mass))
            {
                _rigid_body->Apply_Mass(mass);
            }
        }
        ImGui::Separator();
    }

    void Show_Box_Collider2D_Component(BoxCollider2D* _box_collider2D)
    {
        if (ImGui::CollapsingHeader("BoxCollider2D", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("Enable Debug Mode");
            static bool debug_flag = _box_collider2D->Get_Debug();
            ImGui::Checkbox("##Enable Debug", &debug_flag);
            _box_collider2D->Set_Debug(debug_flag);
        }
		ImGui::Separator();
    }

    void Show_Image_Component(Image* _image)
    {
        ImGui::Text("Image Component");
        ImGui::Text("Texture ID");
        char texture_id_buffer[128];
        strncpy(texture_id_buffer, _image->Get_Texture_ID().c_str(), sizeof(texture_id_buffer));
        if (ImGui::InputText("##Texture ID", texture_id_buffer, sizeof(texture_id_buffer)))
        {
            _image->Set_Texture_ID(std::string(texture_id_buffer));
        }
        
        // Object dropdown box
        ImGui::Text("Object Shape");
        std::vector<std::string> shapes = { "Rect", "Circle" };
        static int current_shape_index = 0;
        for (int i = 0; i < shapes.size(); ++i)
        {
	        if (_image->Get_Shape() == shapes[i])
	        {
                current_shape_index = i;
                break;
	        }
        }
        if (ImGui::Combo("##ObjectShape", &current_shape_index, [](void* data, int idx, const char** out_text) {
            const std::vector<std::string>* shapes = static_cast<const std::vector<std::string>*>(data);
            *out_text = shapes->at(idx).c_str();
            return true;
            }, static_cast<void*>(&shapes), shapes.size())) {
            _image->Set_Shape(shapes[current_shape_index]);
        }
        ImGui::Separator();

        // Color picker for images
        ImGui::Text("Color");
        float color[4] = { _image->Get_Colour().x, _image->Get_Colour().y, _image->Get_Colour().z, _image->Get_Colour().a };
        if (ImGui::ColorEdit4("##Color", color))
        {
            _image->Set_Colour({color[0], color[1], color[2], color[3]});
        }
    }
     
    void Show_Sprite2D_Component(Sprite2D* _sprite2D)
    {
        ImGui::Text("Image Component");
        ImGui::Text("Texture ID: %s", _sprite2D->Get_Texture_ID().c_str());
        ImGui::SameLine();
        if (ImGui::Button("Open"))
        {
            ImGui::OpenPopup("Select Texture");
        }

        if (ImGui::BeginPopup("Select Texture"))
        {
            for (const auto& texture_id : texture_list)
            {
	            if (ImGui::Selectable(texture_id.c_str()))
	            {
                    //std::cout << "%s" << texture_id << std::endl;
                    _sprite2D->Set_Texture_ID(texture_id);
	            }
            }
            ImGui::EndPopup();
        }

        /*char texture_id_buffer[128];
        strncpy(texture_id_buffer, _sprited2D->Get_Texture_ID().c_str(), sizeof(texture_id_buffer));
        if (ImGui::InputText("##Texture ID", texture_id_buffer, sizeof(texture_id_buffer)))
        {
            _sprited2D->Set_Texture_ID(std::string(texture_id_buffer));
        }*/

        if (ImGui::CollapsingHeader("Sprite2D", ImGuiTreeNodeFlags_DefaultOpen)) {
            // Object dropdown box
            ImGui::Text("Object Shape");
            std::vector<std::string> shapes = { "Rect", "Circle" };
            static int current_shape_index = 0;
            for (int i = 0; i < shapes.size(); ++i)
            {
                if (_sprite2D->Get_Shape() == shapes[i])
                {
                    current_shape_index = i;
                    break;
                }
            }
            if (ImGui::Combo("##ObjectShape", &current_shape_index, [](void* data, int idx, const char** out_text) {
                const std::vector<std::string>* shapes = static_cast<const std::vector<std::string>*>(data);
                *out_text = shapes->at(idx).c_str();
                return true;
            }, static_cast<void*>(&shapes), shapes.size())) {
                _sprite2D->Set_Shape(shapes[current_shape_index]);
            }
            ImGui::Separator();

            // Color picker for images
            ImGui::Text("Color");
            float color[4] = { _sprite2D->Get_Colour().x, _sprite2D->Get_Colour().y, _sprite2D->Get_Colour().z, _sprite2D->Get_Colour().a };
            if (ImGui::ColorEdit4("##Color", color))
            {
                _sprite2D->Set_Colour({ color[0], color[1], color[2], color[3] });
            }
        }
		ImGui::Separator();
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

    void ShowInspector(GameObject* _game_object) {
        
        //ImGui::Button("Add Component");

        for (auto& component : _game_object->Get_Component_List())
        {
            switch (component.get()->Get_Component_Type())
            {
            case COMPONENT:
                break;
            case TRANSFORM:
                Show_Transform_Component(dynamic_cast<Transform*>(component.get()));
                break;
            case UITRANSFORM:
                Show_UITransform_Component(dynamic_cast<UITransform*>(component.get()));
                break;
            case SPRITE2D:
                Show_Sprite2D_Component(dynamic_cast<Sprite2D*>(component.get()));
                break;
            case IMAGE:
                Show_Image_Component(dynamic_cast<Image*>(component.get()));
                break;
            case RENDERER:
                // Not touch
                break;
            case ANIMATOR:
                // Not touch
                break;
            case BOXCOLLIDER2D:
                Show_Box_Collider2D_Component(dynamic_cast<BoxCollider2D*>(component.get()));
                break;
            case RIGIDBODY:
                Show_RigidBody_Component(dynamic_cast<RigidBody*>(component.get()));
                break;
            case AUDIO:
                // Not touch
                break;
            case BEHAVIOUR:
                // Not touch
                break;
            case BUTTON:
                // Not touch
                break;
            case NUM_OF_TYPES_OF_COMPONENTS:
                // Not touch
                break;
            default:
                break;
            }
        }
    }

}
