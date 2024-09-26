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
#include "Components/Component.hpp"
#include "GameObjects.hpp"
#include "SageEngine.hpp"
#include "AssetLoader.hpp"

#include <iostream>
#include <initializer_list>

#pragma region Component
void Component::Init(GameObject* _parent)
{
	parent = _parent;
}
void Component::Update() {}
void Component::Draw() {}
void Component::Exit() {}
ComponentType Component::Get_Component_Type() { return COMPONENT; }

GameObject* Component::Get_Parent() const { return parent; }
void Component::Set_Parent(GameObject* const _parent)
{
	parent = _parent;
}