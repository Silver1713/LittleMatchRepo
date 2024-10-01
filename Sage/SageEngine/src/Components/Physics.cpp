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
#include "Components/Transform.hpp"

#include <iostream>

#include "SageTimer.hpp"

Physics::Physics() : velocity(), curr_velocity(), gravity(9.8f), mass(1.0f), enable_gravity(true) {}
Physics::Physics(ToastBox::Vec2 _velocity) : velocity{ _velocity }, curr_velocity(), gravity(9.8f), mass(1.0f), enable_gravity(true) {}

void Physics::Init(GameObject* _parent)
{
	Component::Init(_parent);
	curr_velocity = velocity * (float)SageTimer::delta_time;
}

void Physics::Update()
{

	if (enable_gravity)
	{
		ApplyGravity((float)SageTimer::delta_time);
	}
	
}

void Physics::Exit() {}

ComponentType Physics::Get_Component_Type() { return PHYSICS; }

void Physics::set_gravity_disable(bool _is_static)
{
	if (!enable_gravity) curr_velocity  = {velocity.x,velocity.y};
	enable_gravity = !_is_static;
}
	
ToastBox::Vec2& Physics::Get_Velocity()
{
	return curr_velocity;
}

void Physics::ApplyGravity(float _delta_time)
{
	// Adjust the current velocity by gravity over time
	curr_velocity.y -= gravity * (float)SageTimer::delta_time; // Apply gravity to the vertical velocity

	(void)_delta_time;
}

void Physics::UpdateVelocity(float _delta_time) 
{
	std::cout << "HI";

	(void)_delta_time;
}
