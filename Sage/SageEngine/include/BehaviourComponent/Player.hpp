#pragma once

#include "Components/ScriptableBehaviour.hpp"

class Player : public ScriptableBehaviour
{
	void Init(GameObject* _parent = nullptr) override;
	void Update() override;
	void Exit() override;
};
