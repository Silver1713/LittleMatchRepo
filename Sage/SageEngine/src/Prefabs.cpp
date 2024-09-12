#include "GameObjects.hpp"
#include "Prefabs.hpp"
#include "AssetLoader.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

std::unordered_map<std::string, std::vector<std::unique_ptr<Component>>> runtime_prefabs;
//std::unordered_map<std::string, std::vector<Component>> runtime_prefabs;
std::unordered_map<std::string, Assets::Prefabs::Prefab> prefabs;

void Init()
{
	prefabs = Assets::Prefabs::Get_Prefabs();
	
	//converting prefabs into components
	for (std::pair<std::string,Assets::Prefabs::Prefab> p : prefabs)
	{
		std::vector<std::unique_ptr<Component>> vc;

		vc.push_back(std::make_unique<Transform>(p.second.positions,p.second.rotations));

		if (p.second.collision_data != "Nil")
		{		
			vc.push_back(std::make_unique<Collision2D>());
		}

		if (p.second.audio_data != "Nil")
		{
			vc.push_back(std::make_unique<Audio>());
		}

		//runtime_prefabs[p.first] = vc;
	}
}

Test_GO::Test_GO() : GameObject(runtime_prefabs["TEST_GO"])
{
	
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
