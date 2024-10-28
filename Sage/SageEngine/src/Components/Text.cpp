/* Start Header ************************************************************************/
/*!
\file		Text.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		27 October 2024
\brief		Contains the derived class Text that overrides the virtual functions of the
			base class Component to do Text specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Text.hpp"

/*!*****************************************************************************
  \brief
	Initializes the component and assigns the parent to the gameobject that
	created this component. Provides a space if any audio components need to
	be initialized per gameobject

  \param _parent
	the gameobject creating this component
*******************************************************************************/
void Text::Init(GameObject* _parent)
{
	Component::Init(_parent);
}

/*!*****************************************************************************
  \brief
	Updates any audio this component uses
*******************************************************************************/
void Text::Update()
{
	if (!is_enabled) { return; }
}
/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Text::Exit()
{

}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Text::Get_Component_Type() { return AUDIO; }