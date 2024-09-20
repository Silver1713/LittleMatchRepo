#include "GameObjects.hpp"
#include "SageObjectManager.hpp"
#include "Prefabs.hpp"
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

	void Draw()
	{
		for (auto& _g : g_game_objects)
		{
			if (_g.second)
			{
				_g.second->Draw();
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
		g_game_objects[g_go_counter] = std::move(_g);
	}

	std::unordered_map<unsigned int, GameObject*>& Get_Game_Objects()
	{
		return g_game_objects;
	}

	void Clear_Game_Objects()
	{
		SageObjectManager::DestroyAllObjects();
		g_game_objects.clear();		
		g_go_counter = 0;
	}
}

GameObject::GameObject(){}
GameObject::GameObject(Assets::Prefabs::Prefab& _p)
{
	Add_Component(std::make_unique<Transform>(_p.positions, _p.rotations, _p.scale));
	if (!(_p.sprite_texture_ID == "Nil"))
	{
		Add_Component(std::make_unique<Sprite2D>(_p.sprite_texture_ID, _p.colour));
	}
	else
	{
		Add_Component(std::make_unique<Sprite2D>("", _p.colour));
	}
	if (!(_p.collision_data == "Nil"))
	{
		Add_Component(std::make_unique<Collision2D>());
	}
	if (!(_p.audio_data == "Nil"))
	{
		Add_Component(std::make_unique<Audio>());
	}
}
GameObject::GameObject(unsigned int const& _iD) : GameObject()
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
	if (components.empty() || (!is_enabled))
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
	if (components.empty() || (!is_enabled))
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

void GameObject::Set_ID(unsigned int const& _iD)
{
	iD = _iD;
}

unsigned int const GameObject::Get_ID()
{
	return iD;
}

bool const& GameObject::Is_Enabled() const
{
	return is_enabled;
}
void GameObject::Enable()
{
	is_enabled = true;
}
void GameObject::Disable()
{
	is_enabled = false;
}

void GameObject::Add_Component(std::unique_ptr<Component> _c)
{
	components.push_back(std::move(_c));
}

std::unique_ptr<Component>* GameObject::Get_Component(ComponentType _type)
{
	for (auto& c : components)
	{
		if (c->Get_Component_Type() == _type)
		{
			return &c;
		}
	}
	return nullptr;
}