#pragma once
#include "../Components.hpp"

#include <string>
#include <initializer_list>

class Component;
class SageObject;

class BoxCollider2D : public Component
{
	void Init(GameObject* _parent) override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
};

