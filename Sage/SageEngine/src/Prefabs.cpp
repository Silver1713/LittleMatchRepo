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

	GameObject Create_Copy(Assets::Prefabs::Prefab& _p)
	{
		GameObject g;
		g.Add_Component(std::make_unique<Transform>(_p.positions, _p.rotations, _p.scale));
		if (!(_p.sprite_texture_ID == "Nil"))
		{
			g.Add_Component(std::make_unique<Sprite2D>(_p.sprite_texture_ID, _p.colour));
		}
		if (!(_p.collision_data == "Nil"))
		{
			g.Add_Component(std::make_unique<Collision2D>());
		}
		if (!(_p.audio_data == "Nil"))
		{
			g.Add_Component(std::make_unique<Audio>());
		}
		return g;
	}
}

Red::Red() : GameObject(Prefabs::Create_Copy(prefabs["RED"]))
{
	Game_Objects::Add_Game_Object(std::move(this));
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

Green::Green() : GameObject(Prefabs::Create_Copy(prefabs["GREEN"]))
{
	Game_Objects::Add_Game_Object(std::move(this));
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

Blue::Blue() : GameObject(Prefabs::Create_Copy(prefabs["BLUE"]))
{
	Game_Objects::Add_Game_Object(std::move(this));
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
