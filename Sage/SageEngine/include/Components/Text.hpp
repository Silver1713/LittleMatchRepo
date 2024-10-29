/* Start Header ************************************************************************/
/*!
\file		Text.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		27 October 2024
\brief		Contains the derived class Text that overrides the virtual functions of the
			base class Component to do Text specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Component.hpp"

//Derived component class audio
class Text : public Component
{
	/*!*****************************************************************************
	  \brief
		Initializes the component and assigns the parent to the gameobject that
		created this component. Provides a space if any audio components need to
		be initialized per gameobject

	  \param _parent
		the gameobject creating this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Updates any audio this component uses
	*******************************************************************************/
	void Update() override;

	/*!*****************************************************************************
	  \brief
		Provides a space if there is any unloading or freeing may be required
		per component
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