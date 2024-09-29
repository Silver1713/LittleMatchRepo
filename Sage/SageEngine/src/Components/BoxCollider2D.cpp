/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to do Collision specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/BoxCollider2D.hpp"

#include <iostream>
#include <ostream>

#include "GameObjects.hpp"

void BoxCollider2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
	Transform* transform = dynamic_cast<Transform*>(_parent->Get_Component(ComponentType::TRANSFORM));
	float const* scale = transform->Get_Scale();
	aabb.min_x = -scale[0] / 2;
	aabb.max_x = scale[0] / 2;
	aabb.min_y = -scale[1] / 2;
	aabb.max_y = scale[1] / 2;



}
void BoxCollider2D::Update()
{
	
}
void BoxCollider2D::Exit() {}
ComponentType BoxCollider2D::Get_Component_Type() { return BOXCOLLIDER2D; }