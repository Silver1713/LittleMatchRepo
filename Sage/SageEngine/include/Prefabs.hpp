#pragma once
#include "AssetLoader.hpp"
#include "GameObjects.hpp"

namespace Prefabs
{
	void Init();
	Assets::Prefabs::Prefab const& Get_Prefab(std::string _ID);
}
