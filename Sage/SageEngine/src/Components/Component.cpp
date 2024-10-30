/* Start Header ************************************************************************/
/*!
\file		Component.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the class Component that declares the base class that is to be polymorphed
			into the various types of components as defined by ComponentType depending on the
			need of a gameobject.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Component.hpp"
#include "GameObjects.hpp"
#include "SageEngine.hpp"
#include "AssetLoader.hpp"

#include <iostream>
#include <initializer_list>

#pragma region Component
/*!*****************************************************************************
  \brief
	Initializes the component and assigns the parent to the gameobject that
	created this component

  \param _parent
	the gameobject creating this component
*******************************************************************************/
void Component::Init(GameObject* _parent)
{
	parent = _parent;
}

/*!*****************************************************************************
  \brief
	to be overriden by the Input function of specialized components
	that this component will polymorph into
*******************************************************************************/
void Component::Input() {}

/*!*****************************************************************************
  \brief
	to be overriden by the Update function of specialized components
	that this component will polymorph into
*******************************************************************************/
void Component::Update() {}
/*!*****************************************************************************
  \brief
	to be overriden by the Draw function of specialized components
	that this component will polymorph into
*******************************************************************************/
void Component::Draw() {}
/*!*****************************************************************************
  \brief
	to be overriden by the Exit function of specialized components
	that this component will polymorph into
*******************************************************************************/
void Component::Exit() {}
/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Component::Get_Component_Type() { return COMPONENT; }

/*!*****************************************************************************
  \brief
	Returns the parent of this component

  \return
	the parent of this component
*******************************************************************************/
GameObject* Component::Get_Parent() { return parent; }

/*!*****************************************************************************
  \brief
	Changes the parent of this component

  \param _parent
	the new parent gameobject
*******************************************************************************/
void Component::Set_Parent(GameObject* const _parent)
{
	parent = _parent;
}

/*!*****************************************************************************
  \brief
	Enable or disable the component

  \param _is_enabled
	enabled or disabled
*******************************************************************************/
void Component::Set_Enabled(bool const _is_enabled)
{
	is_enabled = _is_enabled;
}

/*!*****************************************************************************
  \brief
	Gets the active state of the component

  \return
	whether is enabled or disabled
*******************************************************************************/
bool const Component::Get_Enabled() const
{
	return is_enabled;
}