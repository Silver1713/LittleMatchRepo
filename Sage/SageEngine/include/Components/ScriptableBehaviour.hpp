#pragma once
#include "Components/Components.hpp"
class ScriptableBehaviour : public Component
{
protected:
	GameObject* parent;
public:

	void Init(GameObject* _parent = nullptr);
	void Update() override = 0;
	void Exit() override = 0;

	ComponentType Get_Component_Type() override;
};