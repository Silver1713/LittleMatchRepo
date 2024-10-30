/* Start Header ************************************************************************/
/*!
\file		RigidBody.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		20 September 2024
\brief		Contains the derived class Physics that overrides the virtual functions of the
			base class Component to call physics functions.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"
#include "GameObjects.hpp"

#include <iostream>

#include "SageTimer.hpp"

RigidBody::RigidBody() {}
RigidBody::RigidBody(ToastBox::Vec2 _velocity) : velocity{ _velocity } {}

void RigidBody::Init(GameObject* _parent)
{
	Component::Init(_parent);
	transform = static_cast<Transform*>(Get_Parent()->Get_Component<Transform>());
	//curr_velocity = velocity * (float)SageTimer::delta_time;
}

void RigidBody::Update()
{	
	if (!is_enabled) { return; }
	float dt = (float)SageTimer::delta_time;
	if (enable_gravity)
	{
		ApplyGravity(dt);
	}
	transform->Translate({ curr_velocity.x * dt,curr_velocity.y * dt,0.f });
}

void RigidBody::Exit() {}

ComponentType RigidBody::Get_Component_Type() { return RIGIDBODY; }

void RigidBody::Set_Gravity_Disable(bool _is_static)
{
	if (!enable_gravity) curr_velocity  = {velocity.x,velocity.y};
	enable_gravity = !_is_static;
}

ToastBox::Vec2 const& RigidBody::Get_Velocity() const
{
	return velocity;
}

ToastBox::Vec2& RigidBody::Get_Velocity()
{
	return velocity;
}

ToastBox::Vec2& RigidBody::Get_Current_Velocity()
{
	return curr_velocity;
}

void RigidBody::ApplyGravity(float _delta_time)
{
	// Adjust the current velocity by gravity over time
	curr_velocity += gravity * _delta_time; // Apply gravity to the vertical velocity
}

void RigidBody::UpdateVelocity(float _delta_time) 
{
	std::cout << "HI";

	(void)_delta_time;
}

void RigidBody::AddForce(ToastBox::Vec2 force, ForceMode mode)
{
	if (mode == ForceMode::Force)
	{
		curr_velocity += (force /mass) * static_cast<float>(SageTimer::delta_time);
	}
	else if (mode == ForceMode::Impulse)
	{
		curr_velocity += force / mass;
	}
}

// Return Gravity bool flag
bool RigidBody::Gravity_Flag() const
{
	return enable_gravity;
}

// Return Gravity bool flag
bool RigidBody::Gravity_Flag()
{
	return enable_gravity;
}

// Setter Gravity Bool Flag
void RigidBody::Set_Gravity_Flag(bool flag)
{
	enable_gravity = flag;
}

float RigidBody::Get_Mass() const
{
	return mass;
}

void RigidBody::Apply_Mass(float new_mass)
{
	mass = new_mass;
}

ToastBox::Vec2 const& RigidBody::Get_Gravity() const
{
	return gravity;
}

void RigidBody::Apply_New_Gravity(ToastBox::Vec2 new_gravity)
{
	gravity = new_gravity;
}

void RigidBody::Set_Mass(float _mass)
{
	mass = _mass;
}

void RigidBody::Set_Gravity(ToastBox::Vec2 _gravity)
{
	gravity = _gravity;
}

void RigidBody::Set_Current_Velocity(const ToastBox::Vec2& newVelocity)
{
	curr_velocity = newVelocity;
}

float RigidBody::Get_Restitution() const 
{ 
	return restitution; 
}

void RigidBody::Set_Restitution(float _restitution)
{ 
	restitution = _restitution; 
}

float RigidBody::Get_Friction() const
{ 
	return friction; 
}

void RigidBody::Set_Friction(float _friction)
{ 
	friction = _friction; 
}


