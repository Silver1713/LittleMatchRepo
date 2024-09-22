#pragma once
#include "AssetLoader.hpp"
#include "GameObjects.hpp"

namespace Prefabs
{
	void Init();
	Assets::Prefabs::Prefab const& Get_Prefab(std::string _ID);
}

//class White : public GameObject
//{
//public:
//	White();
//	void Init() override;
//	void Update() override;
//	void Exit() override;
//};
//
//class Red : public GameObject
//{
//public:
//	Red();
//	void Init() override;
//	void Update() override;
//	void Exit() override;
//};
//
//class Green : public GameObject
//{
//public:
//	Green();
//	void Init() override;
//	void Update() override;
//	void Exit() override;
//};
//
//class Blue : public GameObject
//{
//public:
//	Blue();
//	void Init() override;
//	void Update() override;
//	void Exit() override;
//};