/* Start Header ************************************************************************/
/*!
\file		Physics.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		20 September 2024
\brief		Contains the derived class Physics that overrides the virtual functions of the
			base class Component to call physics functions.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Physics.hpp"
#include "Components/Transform.hpp"
#include "GameObjects.hpp"

#include <iostream>

#include "SageTimer.hpp"

Physics::Physics() {}
Physics::Physics(ToastBox::Vec2 _velocity) : velocity{ _velocity } {}

void Physics::Init(GameObject* _parent)
{
	Component::Init(_parent);
	transform = static_cast<Transform*>(Get_Parent()->Get_Component<Transform>());
	curr_velocity = velocity * (float)SageTimer::delta_time;
}

void Physics::Update()
{	
	float dt = (float)SageTimer::delta_time;
	if (enable_gravity)
	{
		ApplyGravity(dt);
	}
	transform->Translate({ curr_velocity.x * dt,curr_velocity.y * dt,0.f });
}

void Physics::Exit() {}

ComponentType Physics::Get_Component_Type() { return PHYSICS; }

void Physics::Set_Gravity_Disable(bool _is_static)
{
	if (!enable_gravity) curr_velocity  = {velocity.x,velocity.y};
	enable_gravity = !_is_static;
}

ToastBox::Vec2 const& Physics::Get_Velocity()
{
	return velocity;
}

ToastBox::Vec2& Physics::Get_Current_Velocity()
{
	return curr_velocity;
}

void Physics::ApplyGravity(float _delta_time)
{
	// Adjust the current velocity by gravity over time
	curr_velocity.y -= gravity * _delta_time; // Apply gravity to the vertical velocity
}

void Physics::UpdateVelocity(float _delta_time) 
{
	std::cout << "HI";

	(void)_delta_time;
}
