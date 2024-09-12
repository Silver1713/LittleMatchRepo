#include "GameObject.hpp"
#include <unordered_map>

#include <iostream>

std::unordered_map<unsigned int, GameObject> g_gameobjects;

namespace Game_Objects {
	void Init()
	{
		for (std::pair<unsigned int,GameObject> _g : g_gameobjects)
		{
			_g.second.Init();
		}
	}

	void Update()
	{
		for (std::pair<unsigned int, GameObject> _g : g_gameobjects)
		{
			_g.second.Update();
		}
	}

	void Exit()
	{
		for (std::pair<unsigned int, GameObject> _g : g_gameobjects)
		{
			_g.second.Exit();
		}
		g_gameobjects.clear();
	}
}

GameObject::GameObject()
{

}

GameObject::GameObject(std::vector<Component> _comps)
{
	for (Component _comp : _comps)
	{
	}
}

void GameObject::Init()
{	
	if (!components.empty())
	{
		for (Component _c : components)
		{
			_c.Init();
		}
	}

	std::cout << "GameObject::Init() Successful" << "\n";
}

void GameObject::Update()
{
	if (!components.empty())
	{
		for (Component _c : components)
		{
			_c.Update();
		}
	}
}

void GameObject::Exit()
{
	if (!components.empty())
	{
		for (Component _c : components)
		{
			_c.Exit();
		}
	}
}

void GameObject::Add_Component(Component const& _component, ComponentType _componentType)
{
	if (components.size() != NUM_OF_TYPES_OF_COMPONENTS)
	{
		components.resize(NUM_OF_TYPES_OF_COMPONENTS);
	}

	components[_componentType] = _component;
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
		components[TRANSFORM] = Transform();
		break;

	case SPRITE2D:
		components[SPRITE2D] = Sprite2D();
		break;

	case COLLISION2D:
		components[COLLISION2D] = Collision2D();
		break;

	case AUDIO:
		components[AUDIO] = Audio();
		break;

	default:
		break;
	}
}

Component& GameObject::Get_Component(ComponentType _type)
{
	return components[_type];
}