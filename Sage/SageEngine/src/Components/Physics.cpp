/* Start Header ************************************************************************/
/*!
\file		Component.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the class Component that declares the base class that is to be polymorphed
			into the various types of components as defined by ComponentType depending on the
			need of a gameobject.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Physics.hpp"

Physics::Physics() {}
Physics::Physics(float _velocity) : velocity{ _velocity } {}

void Physics::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void Physics::Update() {}
void Physics::Exit() {}
ComponentType Physics::Get_Component_Type() { return PHYSICS; }
