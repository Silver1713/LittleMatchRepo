/* Start Header ************************************************************************/
/*!
\file		Button.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		11 September 2024
\brief		Contains the derived class Button that overrides the virtual functions of the
			base class Component to do button specific tasks including event detection.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "GameObjects.hpp"
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/UITransform.hpp"
#include "Components/Slider.hpp"

#include "KeyInputs.h"

//default functions available to all buttons
//changing animation state/params
#include "Components/Animator.hpp"
//changing scenes
#include "SceneManager.hpp"

Slider::Slider()
{

}

/*!*****************************************************************************
  \brief
	This function initializes the component along with any Slider specific
	members that need initializing

  \param _parent
	the gameobject that is the parent to this component
*******************************************************************************/
void Slider::Init(GameObject* _parent)
{
	Component::Init(_parent);
	transform = static_cast<Transform*>(parent->Get_Component<Transform>());
	ui_transform = static_cast<UITransform*>(parent->Get_Component<UITransform>());
	sprite = static_cast<Sprite2D*>(parent->Get_Component<Sprite2D>());
	image = static_cast<Image*>(parent->Get_Component<Image>());	
}

/*!*****************************************************************************
  \brief
	This function process any inputs the button might have
*******************************************************************************/
void Slider::Input()
{
}

/*!*****************************************************************************
  \brief
	Updates the Button transforms to match its transform component
*******************************************************************************/
void Slider::Update()
{
}

/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Slider::Exit()
{

}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Slider::Get_Component_Type() { return SLIDER; }