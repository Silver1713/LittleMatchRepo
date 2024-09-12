#include "GameObject.hpp"
#include <unordered_map>

std::unordered_map<int, GameObject> g_gameobjects;

namespace Game_Objects {
	void Init()
	{
		for (std::pair<int,GameObject> g : g_gameobjects)
		{
			g.second.Init();
		}
	}

	void Update()
	{
		for (std::pair<int, GameObject> g : g_gameobjects)
		{
			g.second.Update();
		}
	}

	void Exit()
	{
		for (std::pair<int, GameObject> g : g_gameobjects)
		{
			g.second.Exit();
		}
		g_gameobjects.clear();
	}
}

void GameObject::Init()
{
	if (!components.empty())
	{
		for (Component c : components)
		{
			c.Init();
		}
	}
}

void GameObject::Update()
{
	if (!components.empty())
	{
		for (Component c : components)
		{
			c.Update();
		}
	}
}

void GameObject::Exit()
{
	if (!components.empty())
	{
		for (Component c : components)
		{
			c.Exit();
		}
	}
}