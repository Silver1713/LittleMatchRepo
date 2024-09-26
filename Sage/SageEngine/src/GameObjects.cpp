/* Start Header ************************************************************************/
/*!
\file		GameObjects.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the definitions of functions that handles the individual gameobjects
			and includes the handler of the map of gameobjects which is pointed to by everywhere
			that uses gameobjects. Also contains the gameobject constructor which setup itself
			based on the prefab that is passed into.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "GameObjects.hpp"
#include "Prefabs.hpp"
#include "Components/Components.hpp"
#include "SageObjectManager.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

namespace Game_Objects
{
	static std::unordered_map<std::string, std::unique_ptr<GameObject>> g_game_objects;

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

	std::unique_ptr<GameObject>* Add_Game_Object(std::unique_ptr<GameObject> _g, std::string const& _identifier)
	{
		if (!_g)
		{
			return nullptr;
		}

		g_game_objects[_identifier] = std::move(_g);
		return &g_game_objects[_identifier];
	}

	std::unordered_map<std::string, std::unique_ptr<GameObject>>& Get_Game_Objects()
	{
		return g_game_objects;
	}

	GameObject* Get_Game_Object(std::string const& _identifier)
	{
		return g_game_objects[_identifier].get();
	}

	GameObject* Instantiate(Assets::Prefabs::Prefab const& _p, std::string const& _identifier)
	{
		return (Add_Game_Object(std::make_unique<GameObject>(_p,_identifier), _identifier))->get();
	}

	void Clear_Game_Objects()
	{
		SageObjectManager::DestroyAllObjects();
		g_game_objects.clear();
	}
}

GameObject::GameObject(){}
GameObject::GameObject(Assets::Prefabs::Prefab const& _p, std::string const& _identifier) : identifier{_identifier}
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
		Add_Component(std::make_unique<BoxCollider2D>());
	}
	if (!(_p.audio_data == "Nil"))
	{
		Add_Component(std::make_unique<Audio>());
	}

	Init();
}

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

std::string const& GameObject::Get_ID()
{
	return identifier;
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

Component* GameObject::Get_Component(ComponentType _type)
{
	for (auto& c : components)
	{
		if (c->Get_Component_Type() == _type)
		{
			return c.get();
		}
	}
	return nullptr;
}