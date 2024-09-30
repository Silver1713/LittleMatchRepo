/* Start Header ************************************************************************/
/*!
\file		Physics.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		20 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to call physics functions.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Physics.hpp"
#include "Components/Transform.hpp"

#include <iostream>

#include "SageTimer.hpp"

Physics::Physics() : velocity(), curr_velocity(), gravity(9.8f), mass(1.0f), is_static(true) {}
Physics::Physics(ToastBox::Vec2 _velocity) : velocity{ _velocity }, curr_velocity(), gravity(9.8f), mass(1.0f), is_static(true) {}

void Physics::Init(GameObject* _parent)
{
	Component::Init(_parent);
}

void Physics::Update()
{

	if (!is_static)
	{
		ApplyGravity(SageTimer::delta_time);
	}
}

void Physics::Exit() {}

ComponentType Physics::Get_Component_Type() { return PHYSICS; }

void Physics::set_static(bool _is_static)
{
	if (is_static) curr_velocity  = {};
	is_static = _is_static;
}

ToastBox::Vec2& Physics::Get_Velocity()
{
	return curr_velocity;
}

void Physics::ApplyGravity(float delta_time)
{
	// Adjust the current velocity by gravity over time
	curr_velocity.y -= gravity * SageTimer::delta_time; // Apply gravity to the vertical velocity
}

void Physics::UpdateVelocity(float delta_time) 
{

}
