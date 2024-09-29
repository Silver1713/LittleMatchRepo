/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to do Collision specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/BoxCollider2D.hpp"

/*!*****************************************************************************
  \brief
	This function initializes the component along with any BoxCollider specific
	members that need initializing

  \param _parent
	the gameobject that created this component
*******************************************************************************/
void BoxCollider2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
}

/*!*****************************************************************************
  \brief
	Space for calls to collision implementation
*******************************************************************************/
void BoxCollider2D::Update() {}

/*!*****************************************************************************
  \brief
	Frees and unload any members that needs it
*******************************************************************************/
void BoxCollider2D::Exit() {}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType BoxCollider2D::Get_Component_Type() { return BOXCOLLIDER2D; }