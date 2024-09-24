#pragma once
#include "AssetLoader.hpp"
#include "Components/Components.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

class GameObject
{
protected:
	std::vector<std::unique_ptr<Component>> components;
	std::string identifier{};
	bool is_enabled{true};

public:
	GameObject();
	GameObject(Assets::Prefabs::Prefab const& _p, std::string const& _identifier);

	void Init();
	void Update();
	void Draw();
	void Exit();

	std::string const& Get_ID();

	bool const& Is_Enabled() const;
	void Enable();
	void Disable();

	void Add_Component(std::unique_ptr<Component> _c);
	Component* Get_Component(ComponentType _component);
};

namespace Game_Objects
{
	void Init();
	void Update();
	void Draw();
	void Exit();

	std::unordered_map<std::string, std::unique_ptr<GameObject>>& Get_Game_Objects();
	GameObject* Get_Game_Object(std::string const& _identifier);
	GameObject* Instantiate(Assets::Prefabs::Prefab const& _p, std::string const& _identifer);
	void Clear_Game_Objects();
}