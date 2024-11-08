/* Start Header ************************************************************************/
/*!
\file		GameObjects.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		Contains the declarations of functions that defines the gameobject class, along
			with all of its member functions.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "AssetLoader.hpp"
#include "Components/Components.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

//The Vessel that holds the pointers to its components and its identifiers
class GameObject
{
protected:
	std::vector<std::unique_ptr<Component>> components;
	std::string identifier{};
	bool is_enabled{true};
	unsigned int z_order{};
public:
	/*!*****************************************************************************
	  \brief
		Default constructor for GameObject
	*******************************************************************************/
	GameObject();

	/*!*****************************************************************************
	  \brief
		Constructor for GameObject that takes in a prefab to copy from along with
		what it should be named via its identifier

	  \param _p
		The prefab to copy from

	  \param _identifier
		What this instance should be called

	  \param _z_order
		The z-order of the object
	*******************************************************************************/
	GameObject(Assets::Prefabs::Prefab const& _p, std::string const& _identifier, unsigned int _z_order = 0);

	/*!*****************************************************************************
	  \brief
		Initializes the gameobject
	*******************************************************************************/
	void Init();
	/*!*****************************************************************************
	  \brief
		Updates the gameobject
	*******************************************************************************/
	void Update();
	/*!*****************************************************************************
	  \brief
		Draws the gameobject
	*******************************************************************************/
	void Draw();
	/*!*****************************************************************************
	  \brief
		Frees and Unloads members of the gameobject if necessary
	*******************************************************************************/
	void Exit();

	/*!*****************************************************************************
	  \brief
		Gets the identifier of this instance of a gameobject
	  \return
		Returns the string that is the identifier
	*******************************************************************************/
	std::string const& Get_ID();

	/*!*****************************************************************************
	  \brief
		Gets the z_order of this instance of a gameobject
	  \return
		Returns the z_order
	*******************************************************************************/
	unsigned int const& Get_Z_Order() const;

	/*!*****************************************************************************
	  \brief
		Returns whether the object is enabled
	  \return
		Whether the object is enabled
	*******************************************************************************/
	bool const& Is_Enabled() const;
	/*!*****************************************************************************
	  \brief
		Enables the gameobject
	*******************************************************************************/
	void Enable();
	/*!*****************************************************************************
	  \brief
		Disables the gameobject
	*******************************************************************************/
	void Disable();

	/*!*****************************************************************************
	  \brief
		Adds component to the gameobject
	  \param _c
		Component to be added
	*******************************************************************************/
	void Add_Component(std::unique_ptr<Component> _c);

	/*!*****************************************************************************
	  \brief
		Adds component to the gameobject
	  \param _component
		Component to be added
	  \return
	    pointer to the component
	*******************************************************************************/
	Component* Get_Component(ComponentType _component);

	template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
	T* Get_Component();
	

};

// The central gameobject manager that iterates through all active gameobjects
namespace Game_Objects
{
	/*!*****************************************************************************
	  \brief
		Initializes all components of all gameobjects
	*******************************************************************************/
	void Init();
	/*!*****************************************************************************
	  \brief
		Updates all components of all gameobjects
	*******************************************************************************/
	void Update();
	/*!*****************************************************************************
	  \brief
		Draws all components of all gameobjects
	*******************************************************************************/
	void Draw();
	/*!*****************************************************************************
	  \brief
		Clears all gameobjects
	*******************************************************************************/
	void Exit();

	/*!*****************************************************************************
	  \brief
		Gets a reference to the map of all gameobjects
	  \return
	    A reference to the map of all gameobjects
	*******************************************************************************/
	std::unordered_map<std::string, std::unique_ptr<GameObject>>& Get_Game_Objects();
	/*!*****************************************************************************
	  \brief
		Gets the pointer to the specific gameobject
	  \param _identifier
		The identifier to look for
	  \return
		A reference to the map of all gameobjects
	*******************************************************************************/
	GameObject* Get_Game_Object(std::string const& _identifier);
	/*!*****************************************************************************
	  \brief
		Instantiates a new gameobject based on a specified prefab and given a
		specific identifier
	  \param _p
		The prefab to copy from
	  \param _identifier
		The identifier of the newly create gameobject
	  \param _z_order
		The _z_order of the newly create gameobject
	  \return
		A pointer to the created gameobject
	*******************************************************************************/
	GameObject* Instantiate(Assets::Prefabs::Prefab const& _p, std::string const& _identifer, unsigned int _z_order = 0);

	/*!*****************************************************************************
	  \brief
		Clears the map of gameobjects
	*******************************************************************************/
	void Clear_Game_Objects();
}


template <typename T, typename>
T* GameObject::Get_Component()
{
	for (auto& _c : components)
	{
		T* t = dynamic_cast<T*>(_c.get());
		if (t)
		{
			return t;
		}
	}
	return nullptr;
}