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

//The Vessel that holds the pointers to its components and its identifiers
class GameObject
{
protected:
	std::vector<std::unique_ptr<Component>> components;
	std::unordered_map<std::string,GameObject*> children;
	GameObject* parent{ nullptr };
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
		Updates the inputs to the gameobject
	*******************************************************************************/
	void Input();
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

	//[HALIS]
	void Set_ID(std::string const& _id);

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
		Remove component from the gameobject
	  \param _c
		Component to be added
	*******************************************************************************/
	void Remove_Component(ComponentType _c);

	/*!*****************************************************************************
	  \brief
		Clears all gameobjects
	  \return
		Returns the vector of components that the gameobject posseses
	*******************************************************************************/
	std::vector<std::unique_ptr<Component>>& Get_Component_List();

	/*!*****************************************************************************
	  \brief
		Gets the component of the specified type T belonging to the gameobject
	  \return
	    pointer to the component or nullptr if not found
	*******************************************************************************/
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
	T* Get_Component();

	/*!*****************************************************************************
	  \brief
		Check if the game object has a particular component
	  \return
		bool true if it has a component otherwise bool false
	*******************************************************************************/
	bool Has_Component(const std::shared_ptr<GameObject>& _game_object, ComponentType _component_type) const;

	/*!*****************************************************************************
	  \brief
		Sets the parent
	  \param _new_parent
		pointer to the new parent gameobject
	*******************************************************************************/
	void Set_Parent(GameObject* const _new_parent);

	/*!*****************************************************************************
	  \brief
		Gets the parent
	  \return
		pointer to the parent gameobject
	*******************************************************************************/
	GameObject* Get_Parent();

	/*!*****************************************************************************
	  \brief
		Gets the position of the transform of the gameobject
	  \return
		Vector 3 to the position of the gameobject
	*******************************************************************************/
	ToastBox::Vec3 const Get_Position();

	/*!*****************************************************************************
	  \brief
		Sets the position of the transform of the gameobject
	  \param
		Vector 3 to the position of the gameobject
	*******************************************************************************/
	void Set_Position(ToastBox::Vec3 const& _new_pos);

	/*!*****************************************************************************
	  \brief
		Adds a gameobject to be a child to this gameobject
	  \param _new_child
		the gameobject to add
	*******************************************************************************/
	void Add_Child(GameObject* const _new_child);

	/*!*****************************************************************************
	  \brief
		Removes a child from the map of children gameobjects of this gameobject
	  \param _identifier
		the name of the child that is to be removed
	*******************************************************************************/
	void Remove_Child(std::string const& _identifier);

	/*!*****************************************************************************
	  \brief
		Gets the child with the given name
	  \param _identifier
		the name of the child that is to be gotten
	  \return
		the poitner to the gameobject if it exists, nullptr if not
	*******************************************************************************/
	GameObject* Get_Child(std::string const& _identifier);


	std::vector<std::unique_ptr<Component>>& Get_Components();
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
		Updates game object list
	*******************************************************************************/
	void Update_Game_Object_List();

	//[HALIS]
	void Delete_Game_Object(GameObject* _object);

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

/*!*****************************************************************************
  \brief
	Gets the component of the specified type T belonging to the gameobject
  \return
	pointer to the component or nullptr if not found
*******************************************************************************/
template <typename T, typename>
T* GameObject::Get_Component()
{	
	if (components.size() != 0)
	{
		for (auto& _c : components)
		{
			T* t = dynamic_cast<T*>(_c.get());
			if (t)
			{
				return t;
			}
		}
		
	}
	return nullptr;
	
}

/*!*****************************************************************************
  \brief
	Check if the game object has a particular component
  \return
	bool true if it has a component otherwise bool false
*******************************************************************************/
//bool GameObject::Has_Component(const std::shared_ptr<GameObject>& _game_object, ComponentType _component_type) const
//{
//	for (const auto& component : components)
//	{
//		if (component->Get_Component_Type() == _component_type)
//		{
//			return true;
//		}
//	}
//	return false;
//}



