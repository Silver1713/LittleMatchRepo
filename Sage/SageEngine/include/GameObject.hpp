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

	void Add_Component(component_type _component);
	void Get_Component(component_type _component);
};

class Knight1 : public GameObject
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
};