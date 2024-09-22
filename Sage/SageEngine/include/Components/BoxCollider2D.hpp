#pragma once
#include "Components/Component.hpp"

class BoxCollider2D : public Component
{
	void Init(GameObject* _parent) override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
};