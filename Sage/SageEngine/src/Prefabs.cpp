#include "GameObjects.hpp"
#include "Prefabs.hpp"
#include "AssetLoader.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <iostream>

std::unordered_map<std::string, Assets::Prefabs::Prefab> prefabs;
static bool is_initialized{ false };

namespace Prefabs
{
	void Init()
	{
		if (is_initialized)
		{
			return;
		}
		prefabs = Assets::Prefabs::Get_Prefabs();
		is_initialized = true;
	}
}

White::White() : GameObject(prefabs["WHITE"])
{
	Init();
}

void White::Init()
{
	GameObject::Init();
}
void White::Update()
{

}
void White::Exit()
{

}

Red::Red() : GameObject(prefabs["RED"])
{
	Init();
}

void Red::Init()
{
	GameObject::Init();
}
void Red::Update()
{

}
void Red::Exit()
{

}

Green::Green() : GameObject(prefabs["GREEN"])
{
	Init();
}

void Green::Init()
{
	GameObject::Init();
}
void Green::Update()
{

}
void Green::Exit()
{

}

Blue::Blue() : GameObject(prefabs["BLUE"])
{
	Init();
}

void Blue::Init()
{
	GameObject::Init();
}
void Blue::Update()
{

}
void Blue::Exit()
{

}
