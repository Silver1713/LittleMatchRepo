#pragma once
#include "GameObjects.hpp"

class Test_GO : public GameObject
{
public:
	Test_GO();
	void Init() override;
	void Update() override;
	void Exit() override;
};