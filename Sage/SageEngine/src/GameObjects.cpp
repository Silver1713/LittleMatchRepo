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

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "GameObjects.hpp"
#include "Components/Components.hpp"
#include "SageObjectManager.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

#include "BindingSystem.hpp"
#include "SageSystemManager.hpp"
#include "Components/RigidBody.hpp"
#include "Systems/SageScripting.hpp"

namespace Game_Objects
{
	const unsigned int max_z_orders{3};
	static std::unordered_map<std::string, std::unique_ptr<GameObject>> g_game_objects;

	static std::vector<std::unique_ptr<GameObject>*> screen_space_game_objects;
	static std::vector<std::unique_ptr<GameObject>*> world_space_game_objects;

	static SageScriptSystem* script_system{ nullptr };

	/*!*****************************************************************************
	  \brief
		Initializes all components of all gameobjects
	*******************************************************************************/
	void Init()
	{
		script_system = SageSystemManager::Get_System<SageScriptSystem>();
		for (auto& _g : g_game_objects)
		{
			if (_g.second)
			{				
				_g.second->Init();
				BindingSystem::Init_Batch(_g.second.get());
			}
		}
	}
	/*!*****************************************************************************
	  \brief
		Updates all components of all gameobjects
	*******************************************************************************/
	void Update()
	{

		for (auto& _g : g_game_objects)
		{
			if (_g.second)
			{
				_g.second->Input();
				_g.second->Update();
			}
		}
	}

	/*!*****************************************************************************
	  \brief
		Draws all components of all gameobjects
	*******************************************************************************/
	void Draw()
	{
		//std::cout << "Drawing\n";
		SageRenderer::Clear_Color({ 1,1,1,1 });

		for (unsigned int current_z{}; current_z <= max_z_orders; ++current_z)
		{
			for (auto& go : world_space_game_objects)
			{
				if (go->get()->Get_Z_Order() == current_z)
				{
					go->get()->Draw();
				}
			}			
		}

		for (unsigned int current_z{}; current_z <= max_z_orders; ++current_z)
		{
			for (auto& go : screen_space_game_objects)
			{
				if (go->get()->Get_Z_Order() == current_z)
				{
					go->get()->Draw();
				}
			}
		}

	}

	/*!*****************************************************************************
	  \brief
		Clears all gameobjects
	*******************************************************************************/
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

	/*!*****************************************************************************
	  \brief
		Adds the gameobject the map of gameobjects

	  \param _g
		the gameobject to add

	  \param _identifier
		the name of the gameobject

	  \return
		the pointer to the gameobject after it is added to the map
	*******************************************************************************/
	std::unique_ptr<GameObject>* Add_Game_Object(std::unique_ptr<GameObject> _g, std::string const& _identifier)
	{
		if (!_g)
		{
			return nullptr;
		}

		g_game_objects[_identifier] = std::move(_g);
		if (g_game_objects[_identifier].get()->Get_Component<UITransform>())
		{
			screen_space_game_objects.push_back(&g_game_objects[_identifier]);
		}
		else 
		{
			world_space_game_objects.push_back(&g_game_objects[_identifier]);
		}
		return &g_game_objects[_identifier];
	}

	/*!*****************************************************************************
	  \brief
		Gets a reference to the map of all gameobjects
	  \return
		A reference to the map of all gameobjects
	*******************************************************************************/
	std::unordered_map<std::string, std::unique_ptr<GameObject>>& Get_Game_Objects()
	{
		return g_game_objects;
	}

	/*!*****************************************************************************
	  \brief
		Gets the pointer to the specific gameobject
	  \param _identifier
		The identifier to look for
	  \return
		A reference to the map of all gameobjects
	*******************************************************************************/
	GameObject* Get_Game_Object(std::string const& _identifier)
	{
		return g_game_objects[_identifier].get();
	}

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
	GameObject* Instantiate(Assets::Prefabs::Prefab const& _p, std::string const& _identifier, unsigned int _z_order)
	{
		return (Add_Game_Object(std::make_unique<GameObject>(_p,_identifier,_z_order), _identifier))->get();
	}

	/*!*****************************************************************************
	  \brief
		Clears the map of gameobjects
	*******************************************************************************/
	void Clear_Game_Objects()
	{
		SageObjectManager::Destroy_All_Objects();
		g_game_objects.clear();
		world_space_game_objects.clear();
		screen_space_game_objects.clear();
	}
}

/*!*****************************************************************************
  \brief
	Default constructor for GameObject
*******************************************************************************/
GameObject::GameObject(){}
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
GameObject::GameObject(Assets::Prefabs::Prefab const& _p, std::string const& _identifier, unsigned int _z_order) : identifier{_identifier}, z_order{_z_order}
{
	if (_p.transform_type == "Screen")
	{
		Add_Component(std::make_unique<UITransform>(_p.positions, _p.rotations, _p.scale));
		Add_Component(std::make_unique<Image>(_p.sprite_texture_ID, _p.colour, _p.object_shape));
	}
	else
	{
		Add_Component(std::make_unique<Transform>(_p.positions, _p.rotations, _p.scale));
		Add_Component(std::make_unique<Sprite2D>(_p.sprite_texture_ID, _p.colour, _p.object_shape));		
	}
	if (_p.has_collider)
	{
		Add_Component(std::make_unique<BoxCollider2D>());
	}
	if (_p.has_physics)
	{
		Add_Component(std::make_unique<RigidBody>(ToastBox::Vec2{ _p.velocity.x ,_p.velocity.y }));
	}
	if (_p.has_animator)
	{
		Add_Component(std::make_unique<Animator>(_p.animation_set_ID));
	}
	if (_p.is_button)
	{
		Add_Component(std::make_unique<Button>(_p.on_click,_p.on_click_hold,_p.on_click_release,_p.on_hover_enter,_p.on_hover,_p.on_hover_exit));
	}
	if (_p.is_slider)
	{
		Add_Component(std::make_unique<Slider>(
			Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab(_p.slider_children_ID.at("Frame")), _identifier + "_Frame", _z_order),
			Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab(_p.slider_children_ID.at("Fill")), _identifier + "_Fill", _z_order),
			Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab(_p.slider_children_ID.at("BG")), _identifier + "_BG", _z_order),
			_p.slider_init,
			_p.slider_update));
	}

	if (_p.has_behaviour)
	{
		Add_Component(std::make_unique<Behaviour>());
		Behaviour* b = Get_Component<Behaviour>();
		b->Init(this);
		for (unsigned int i{}; i < _p.num_behaviour; ++i)
		{
			b->Add_Instance(_p.cs_class_name[i], _p.cs_namespace[i]);
		}
	}

	//Generates children if it has any
	if (_p.has_children)
	{
		for (unsigned int i{}; i < _p.num_children; ++i)
		{
			GameObject* p = Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab(_p.children_IDs[i]), _identifier + "_Child_" + std::to_string(i), z_order);
			if (p)
			{
				p->Set_Position(Get_Position());
			}
			Add_Child(p);
		}
	}

	Init();
}


/*!*****************************************************************************
  \brief
	Initializes the gameobject
*******************************************************************************/
void GameObject::Init()
{
	if (components.empty())
	{
		return;
	}

	for (auto& _c : components)
	{
		_c->Init(this);

		if (_c->Get_Component_Type() == ComponentType::BEHAVIOUR)
		{
			std::cout << "Behaviour Component Added\n";
		}
	}


}

/*!*****************************************************************************
  \brief
	Updates the inputs to the gameobject
*******************************************************************************/
void GameObject::Input()
{
	if (components.empty() || (!is_enabled))
	{
		return;
	}

	for (const auto& _c : components)
	{
		_c->Input();
	}
}

/*!*****************************************************************************
  \brief
	Updates the gameobject
*******************************************************************************/
void GameObject::Update()
{
	if (components.empty() || (!is_enabled))
	{
		return;
	}

	for (const auto& _c : components)
	{
		if (_c->Get_Component_Type() == ComponentType::BEHAVIOUR)
		{
			Game_Objects::script_system->Update_Entity(this);
			continue;
		}
		_c->Update();
	}
}

/*!*****************************************************************************
  \brief
	Draws the gameobject
*******************************************************************************/
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

/*!*****************************************************************************
  \brief
	Frees and Unloads members of the gameobject if necessary
*******************************************************************************/
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

/*!*****************************************************************************
  \brief
	Gets the identifier of this instance of a gameobject
  \return
	Returns the string that is the identifier
*******************************************************************************/
std::string const& GameObject::Get_ID()
{
	return identifier;
}

/*!*****************************************************************************
  \brief
	Gets the z_order of this instance of a gameobject
  \return
	Returns the z_order
*******************************************************************************/
unsigned int const& GameObject::Get_Z_Order() const
{
	return z_order;
}

/*!*****************************************************************************
  \brief
	Returns whether the object is enabled
  \return
	Whether the object is enabled
*******************************************************************************/
bool const& GameObject::Is_Enabled() const
{
	return is_enabled;
}
/*!*****************************************************************************
  \brief
	Enables the gameobject
*******************************************************************************/
void GameObject::Enable()
{
	is_enabled = true;
}
/*!*****************************************************************************
  \brief
	Disables the gameobject
*******************************************************************************/
void GameObject::Disable()
{
	is_enabled = false;
}

/*!*****************************************************************************
  \brief
	Adds component to the gameobject
  \param _c
	Component to be added
*******************************************************************************/
void GameObject::Add_Component(std::unique_ptr<Component> _c)
{
	components.push_back(std::move(_c));
}

/*!*****************************************************************************
  \brief
	Clears all gameobjects
  \return
	Returns the vector of components that the gameobject posseses
*******************************************************************************/
std::vector<std::unique_ptr<Component>>& GameObject::Get_Component_List()
{
	return components;
}

/*!*****************************************************************************
  \brief
	Sets the parent
  \param _new_parent
	pointer to the new parent gameobject
*******************************************************************************/
void GameObject::Set_Parent(GameObject* const _new_parent)
{
	parent = _new_parent;
}

/*!*****************************************************************************
  \brief
	Gets the parent
  \return
	pointer to the parent gameobject
*******************************************************************************/
GameObject* GameObject::Get_Parent()
{
	return parent;
}

/*!*****************************************************************************
  \brief
	Gets the position of the transform of the gameobject
  \return
	Vector 3 to the position of the gameobject
*******************************************************************************/
ToastBox::Vec3 const GameObject::Get_Position()
{
	Transform* t = Get_Component<Transform>();
	UITransform* ut = Get_Component<UITransform>();
	if (t)
	{
		return t->Get_Position();
	}
	else if (ut)
	{
		return ut->Get_Position();
	}
	return ToastBox::Vec3();
}

/*!*****************************************************************************
  \brief
	Sets the position of the transform of the gameobject
  \param
	Vector 3 to the position of the gameobject
*******************************************************************************/
void GameObject::Set_Position(ToastBox::Vec3 const& _new_pos)
{
	Transform* t = Get_Component<Transform>();
	UITransform* ut = Get_Component<UITransform>();
	if (t)
	{
		t->Set_Position(_new_pos);
	}
	else if (ut)
	{
		ut->Set_Position(_new_pos);
	}
}

/*!*****************************************************************************
  \brief
	Adds a gameobject to be a child to this gameobject
  \param _new_child
	the gameobject to add
*******************************************************************************/
void GameObject::Add_Child(GameObject* const _new_child)
{
	_new_child->Set_Parent(this);
	children[_new_child->Get_ID()] = _new_child;
}

/*!*****************************************************************************
  \brief
	Removes a child from the map of children gameobjects of this gameobject
  \param _identifier
	the name of the child that is to be removed
*******************************************************************************/
void GameObject::Remove_Child(std::string const& _identifier)
{
	if (children.find(_identifier) != children.end())
	{
		children.erase(_identifier);
	}
}

/*!*****************************************************************************
  \brief
	Gets the child with the given name
  \param _identifier
	the name of the child that is to be gotten
  \return
	the poitner to the gameobject if it exists, nullptr if not
*******************************************************************************/
GameObject* GameObject::Get_Child(std::string const& _identifier)
{
	if (children.find(_identifier) != children.end())
	{
		return children[_identifier];
	}
	return nullptr;
}

std::vector<std::unique_ptr<Component>>& GameObject::Get_Components()
{
	return components;
}
