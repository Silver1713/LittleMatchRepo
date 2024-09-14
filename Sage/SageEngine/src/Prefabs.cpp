#include "GameObjects.hpp"
#include "Prefabs.hpp"
#include "AssetLoader.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <iostream>

std::unordered_map<std::string, Assets::Prefabs::Prefab> prefabs;

namespace Prefabs
{
	void Init()
	{
		prefabs = Assets::Prefabs::Get_Prefabs();
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

Test_GO::Test_GO() : GameObject(Prefabs::Create_Copy(prefabs["TEST_GO"])) 
{
	Game_Objects::Add_Game_Object(this);
}

void Test_GO::Init()
{
	GameObject::Init();
}
void Test_GO::Update()
{

}
void Test_GO::Exit()
{

}

Test_GO_2::Test_GO_2() : GameObject(Prefabs::Create_Copy(prefabs["TEST_GO_2"]))
{
	Game_Objects::Add_Game_Object(this);
}

void Test_GO_2::Init()
{
	GameObject::Init();
}
void Test_GO_2::Update()
{

}
void Test_GO_2::Exit()
{

}
