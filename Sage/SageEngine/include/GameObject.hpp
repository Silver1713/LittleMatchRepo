#pragma once
#include "Components.hpp"
#include <vector>

class GameObject
{
protected:
	std::vector<Component> components;

public:
	GameObject();
	GameObject(std::vector<Component>_components);

	virtual void Init();
	virtual void Update();
	virtual void Exit();

	void Add_Component(ComponentType _component);
	void Add_Component(Component const& _component, ComponentType _componentType);
	Component& Get_Component(ComponentType _component);
};

class Knight1 : public GameObject
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
};