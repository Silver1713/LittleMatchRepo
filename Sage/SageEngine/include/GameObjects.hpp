#pragma once
#include "Components.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

class GameObject
{
protected:
	std::vector<std::unique_ptr<Component>> components;

public:
	GameObject();

	virtual void Init();
	virtual void Update();
	virtual void Exit();

	void Add_Component(std::unique_ptr<Component> _c, ComponentType _type);
	std::unique_ptr<Component>& Get_Component(ComponentType _component);
};

namespace Game_Objects
{
	void Init();
	void Update();
	void Exit();

	void Add_Game_Object(GameObject const& _game_object);
	std::unordered_map<unsigned int, GameObject>& Get_Game_Objects();
	void Clear_Game_Objects();
}