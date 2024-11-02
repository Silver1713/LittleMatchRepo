#include "imgui.h"
#include "GameObjects.hpp"
#include <stdio.h>

namespace Sage_Inspector 
{
	inline std::vector<std::string> texture_list;

	void Show_Transform_Component(Transform* _transform_component);

	void Show_UITransform_Component(UITransform* _ui_transform);

	void Show_RigidBody_Component(RigidBody* _rigid_body);

	void Show_Box_Collider2D_Component(BoxCollider2D* _box_collider2D);

	void Show_Image_Component(Image* _image);

	void Show_Sprite2D_Component(Sprite2D* _sprited2D);

	void Show_Inspector(GameObject* _game_object);
}