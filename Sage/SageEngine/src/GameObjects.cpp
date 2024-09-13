#include "GameObjects.hpp"
#include <unordered_map>
#include <memory>
#include <iostream>

std::unordered_map<unsigned int, GameObject> g_game_objects;
unsigned int g_go_counter{};

namespace Game_Objects
{
	void Init()
	{
		for (auto & _g : g_game_objects)
		{
			_g.second.Init();
		}
	}

	void Update()
	{
		for (auto& _g : g_game_objects)
		{
			_g.second.Update();
		}
	}

	void Exit()
	{
		for (auto& _g : g_game_objects)
		{
			_g.second.Exit();
		}
		g_game_objects.clear();
	}

	void Add_Game_Object(GameObject const& _game_object)
	{
		//g_go_counter++;
		//g_game_objects[g_go_counter] = _game_object;
	}

	std::unordered_map<unsigned int, GameObject>& Get_Game_Objects()
	{
		return g_game_objects;
	}

	void Clear_Game_Objects()
	{
		g_game_objects.clear();
	}
}

GameObject::GameObject(){}

void GameObject::Init()
{	
	for (auto& _c : components)
	{
		_c->Init();
	}
	std::cout << "GameObject::Init() Successful" << "\n";
}

void GameObject::Update()
{
	if (!components.empty())
	{
		for (const auto& _c : components)
		{
			_c->Update();
		}
	}
}

void GameObject::Exit()
{
	if (!components.empty())
	{
		for (const auto& _c : components)
		{
			_c->Exit();
		}
	}
}

void GameObject::Add_Component(std::unique_ptr<Component> _c, ComponentType _type)
{
	components.push_back(std::move(_c));
}

std::unique_ptr<Component>& GameObject::Get_Component(ComponentType _type)
{
	for (auto& c : components)
	{
		if ((*c).Get_Component_Type() == _type)
		{
			return c;
		}
	}
}