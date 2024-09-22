#pragma once
#include "Components.hpp"

class Audio : public Component
{
	void Init(GameObject* _parent) override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
};