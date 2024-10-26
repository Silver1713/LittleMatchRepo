/* Start Header ************************************************************************/
/*!
\file		Audio.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class Audio that overrides the virtual functions of the
			base class Component to do Audio specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Audio.hpp"

/*!*****************************************************************************
  \brief
	Initializes the component and assigns the parent to the gameobject that
	created this component. Provides a space if any audio components need to
	be initialized per gameobject

  \param _parent
	the gameobject creating this component
*******************************************************************************/
void Audio::Init(GameObject* _parent)
{
	Component::Init(_parent);
}

/*!*****************************************************************************
  \brief
	Updates any audio this component uses
*******************************************************************************/
void Audio::Update()
{
	if (!is_enabled) { return; }
}
/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Audio::Exit()
{

}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Audio::Get_Component_Type() { return AUDIO; }