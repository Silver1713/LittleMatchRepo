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

Physics::Physics() {}
Physics::Physics(float _velocity) : velocity{ _velocity } {}

void Physics::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void Physics::Update() {}
void Physics::Exit() {}
ComponentType Physics::Get_Component_Type() { return PHYSICS; }
