#include "GameObjects.hpp"
#include "Prefabs.hpp"
#include "AssetLoader.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

std::unordered_map<std::string, std::vector<std::unique_ptr<Component>>> runtime_prefabs;
std::unordered_map<std::string, Assets::Prefabs::Prefab> prefabs;

namespace Prefabs
{
	void Init()
	{
		prefabs = Assets::Prefabs::Get_Prefabs();
	}

	GameObject Create_Copy(Assets::Prefabs::Prefab _p)
	{
		GameObject g;
		g.Add_Component(std::make_unique<Transform>(_p.positions, _p.rotations), TRANSFORM);
		return g;
	}
}

Test_GO::Test_GO() : GameObject(Prefabs::Create_Copy(prefabs["TEST_GO"]))
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
