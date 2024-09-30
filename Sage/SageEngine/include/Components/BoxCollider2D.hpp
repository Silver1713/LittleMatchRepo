/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to do Collision specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"

class BoxCollider2D : public Component
{
	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any BoxCollider specific
		members that need initializing

	  \param _parent
		the gameobject that created this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Space for calls to collision implementation
	*******************************************************************************/
	void Update() override;

	/*!*****************************************************************************
	  \brief
		Frees and unload any members that needs it
	*******************************************************************************/
	void Exit() override;

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;
};