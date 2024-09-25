/* Start Header ************************************************************************/
/*!
\file		GameObjects.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the declarations of functions that defines the gameobject class, along
			with all of its member functions.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
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
	std::string identifier{};
	bool is_enabled{true};

public:
	GameObject();
	GameObject(Assets::Prefabs::Prefab const& _p, std::string const& _identifier);

	void Init();
	void Update();
	void Draw();
	void Exit();

	std::string const& Get_ID();

	bool const& Is_Enabled() const;
	void Enable();
	void Disable();

	void Add_Component(std::unique_ptr<Component> _c);
	Component* Get_Component(ComponentType _component);
};

namespace Game_Objects
{
	void Init();
	void Update();
	void Draw();
	void Exit();

	std::unordered_map<std::string, std::unique_ptr<GameObject>>& Get_Game_Objects();
	GameObject* Get_Game_Object(std::string const& _identifier);
	GameObject* Instantiate(Assets::Prefabs::Prefab const& _p, std::string const& _identifer);
	void Clear_Game_Objects();
}