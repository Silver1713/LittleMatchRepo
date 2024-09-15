#include "GameObjects.hpp"
#include <unordered_map>
#include <memory>
#include <iostream>

std::unordered_map<unsigned int, GameObject*> g_game_objects;
unsigned int g_go_counter{};

namespace Game_Objects
{
	void Init()
	{
		for (auto& _g : g_game_objects)
		{
			if (_g.second)
			{
				_g.second->Init();
			}
			std::cout << "GameObject::Init() number " << _g.first << " is successful" << "\n";
		}
	}

	void Update()
	{
		for (auto& _g : g_game_objects)
		{
			if (_g.second)
			{
				_g.second->Update();
			}
		}
	}

	void Exit()
	{
		for (auto& _g : g_game_objects)
		{
			if (_g.second)
			{
				_g.second->Exit();
			}
		}
		Clear_Game_Objects();
	}

	void Add_Game_Object(GameObject* _g)
	{
		if (!_g)
		{
			return;
		}

		_g->Set_ID(g_go_counter);
		g_go_counter++;
		g_game_objects[g_go_counter] = _g;
	}

	std::unordered_map<unsigned int, GameObject*>& Get_Game_Objects()
	{
		return g_game_objects;
	}

	void Clear_Game_Objects()
	{
		g_game_objects.clear();
		g_go_counter = 0;
	}
}

GameObject::GameObject(){}
GameObject::GameObject(unsigned int _iD) : GameObject()
{
	iD = _iD;
};

void GameObject::Init()
{	
	if (components.empty())
	{
		return;
	}

	for (auto& _c : components)
	{
		_c->Init(this);
	}
}

void GameObject::Update()
{
	if (components.empty())
	{
		return;
	}

	for (const auto& _c : components)
	{
		_c->Update();
	}
}

void GameObject::Draw()
{
	if (components.empty())
	{
		return;
	}

	for (const auto& _c : components)
	{
		_c->Draw();
	}
}

void GameObject::Exit()
{
	if (components.empty())
	{
		return;
	}

	for (const auto& _c : components)
	{
		_c->Exit();
	}
}

void GameObject::Set_ID(unsigned int _iD)
{
	iD = _iD;
}

unsigned int const GameObject::Get_ID()
{
	return iD;
}

void GameObject::Add_Component(std::unique_ptr<Component> _c)
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

	static std::unique_ptr<Component> a{};
	return a;
}