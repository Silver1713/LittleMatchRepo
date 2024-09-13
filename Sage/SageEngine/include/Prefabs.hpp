#pragma once
#include "AssetLoader.hpp"
#include "GameObjects.hpp"

namespace Prefabs
{
	void Init();
	GameObject Create_Copy(Assets::Prefabs::Prefab& _p);
}


class Test_GO : public GameObject
{
public:
	Test_GO();
	void Init() override;
	void Update() override;
	void Exit() override;
};

class Test_GO_2 : public GameObject
{
public:
	Test_GO_2();
	void Init() override;
	void Update() override;
	void Exit() override;
};