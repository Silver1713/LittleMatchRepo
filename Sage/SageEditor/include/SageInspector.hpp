#include "imgui.h"
#include "GameObjects.hpp"
#include <stdio.h>

namespace Sage_Inspector 
{
	void Show_Transform_Component(Transform* _transform_component);

	void Show_UITransform_Component(UITransform* _ui_transform);

	void Show_RigidBody_Component(RigidBody* _rigid_body);

	void Show_Box_Collider2D_Component(BoxCollider2D* _box_collider2D);

	void ShowInspector(GameObject* _game_object);
}