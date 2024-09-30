/* Start Header ************************************************************************/
/*!
\file		Physics.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		20 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to call physics functions.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Physics.hpp"

#include <iostream>

#include "SageTimer.hpp"

Physics::Physics(): velocity(), curr_velocity(), gravity(), mass() {}
Physics::Physics(ToastBox::Vec2 _velocity) : velocity{ _velocity } ,gravity() {}

void Physics::Init(GameObject* _parent)
{
	Component::Init(_parent);
	is_static = true;
	gravity = 9.8f;
}
void Physics::Update()
{

	if (!is_static)
	{
		// Simulate gravity
		curr_velocity.y -= gravity * SageTimer::delta_time;
	}
	
}
void Physics::Exit() {}
ComponentType Physics::Get_Component_Type() { return PHYSICS; }
void Physics::set_static(bool _is_static)
{
	is_static = _is_static;
}

ToastBox::Vec2& Physics::Get_Velocity()
{
	return curr_velocity;
}
