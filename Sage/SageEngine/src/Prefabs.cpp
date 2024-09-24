#include "GameObjects.hpp"
#include "Prefabs.hpp"
#include "AssetLoader.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <iostream>

static std::unordered_map<std::string, Assets::Prefabs::Prefab> prefabs;

namespace Prefabs
{	
	static bool is_initialized{ false };

	void Init()
	{
		if (is_initialized)
		{
			return;
		}
		prefabs = Assets::Prefabs::Get_Prefabs();
		is_initialized = true;
	}

	Assets::Prefabs::Prefab const& Get_Prefab(std::string _ID)
	{
		if (!is_initialized)
		{
			Init();
		}
		return prefabs[_ID];
	}
}