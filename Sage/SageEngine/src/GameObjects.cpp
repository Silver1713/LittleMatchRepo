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
		for (std::pair<unsigned int,GameObject> _g : g_game_objects)
		{
			_g.second.Init();
		}
	}

	void Update()
	{
		for (std::pair<unsigned int, GameObject> _g : g_game_objects)
		{
			_g.second.Update();
		}
	}

	void Exit()
	{
		for (std::pair<unsigned int, GameObject> _g : g_game_objects)
		{
			_g.second.Exit();
		}
		g_game_objects.clear();
	}

	void Add_Game_Object(GameObject const& _game_object)
	{
		g_go_counter++;
		g_game_objects[g_go_counter] = _game_object;
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

GameObject::GameObject() {}

GameObject::GameObject(std::vector<std::unique_ptr<Component>> const& _components)
{
	components = _components;
}


void GameObject::Init()
{	
	if (!components.empty())
	{
		for (const auto& _c : components)
		{
			_c->Init();
		}
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

void GameObject::Add_Component(std::unique_ptr<Component> _component, ComponentType _type)
{
	if (components.size() != NUM_OF_TYPES_OF_COMPONENTS)
	{
		components.resize(NUM_OF_TYPES_OF_COMPONENTS);
	}

	//components[_type] = _component;
}

void GameObject::Add_Component(ComponentType _component)
{
	if (components.size() != NUM_OF_TYPES_OF_COMPONENTS)
	{
		components.resize(NUM_OF_TYPES_OF_COMPONENTS);
	}

	switch (_component)
	{
	case TRANSFORM:
		//components[TRANSFORM] = Transform();
		break;

	case SPRITE2D:
		//components[SPRITE2D] = Sprite2D();
		break;

	case COLLISION2D:
		//components[COLLISION2D] = Collision2D();
		break;

	case AUDIO:
		//components[AUDIO] = Audio();
		break;

	default:
		break;
	}
}

std::unique_ptr<Component> GameObject::Get_Component(ComponentType _type)
{
	switch (_type)
	{
	case TRANSFORM:
		break;

	case SPRITE2D:
		break;

	case COLLISION2D:
		break;

	case AUDIO:
		break;

	default:
		break;
	}
}