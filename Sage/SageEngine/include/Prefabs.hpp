#pragma once
#include "AssetLoader.hpp"
#include "GameObjects.hpp"

namespace Prefabs
{
	void Init();
	GameObject Create_Copy(Assets::Prefabs::Prefab& _p);
}


class Red : public GameObject
{
public:
	Red();
	void Init() override;
	void Update() override;
	void Exit() override;
};

class Green : public GameObject
{
public:
	Green();
	void Init() override;
	void Update() override;
	void Exit() override;
};

class Blue : public GameObject
{
public:
	Blue();
	void Init() override;
	void Update() override;
	void Exit() override;
};