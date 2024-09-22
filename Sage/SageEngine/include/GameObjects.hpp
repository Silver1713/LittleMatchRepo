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
	unsigned int iD{};
	bool is_enabled{true};

public:
	GameObject();
	GameObject(Assets::Prefabs::Prefab& _p);
	GameObject(unsigned int const& _iD);

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Exit();

	void Set_ID(unsigned int const& _iD);
	unsigned int const Get_ID();

	bool const& Is_Enabled() const;
	void Enable();
	void Disable();

	void Add_Component(std::unique_ptr<Component> _c);
	std::unique_ptr<Component>* Get_Component(ComponentType _component);
};

namespace Game_Objects
{
	void Init();
	void Update();
	void Draw();
	void Exit();

	void Add_Game_Object(GameObject* _g);
	std::unordered_map<unsigned int, GameObject*>& Get_Game_Objects();
	void Clear_Game_Objects();
}