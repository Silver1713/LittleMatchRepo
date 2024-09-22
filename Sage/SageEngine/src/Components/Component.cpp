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

GameObject* Component::Get_Parent() { return parent; }
void Component::Set_Parent(GameObject* const _parent)
{
	parent = _parent;
}