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
#include "Components/Button.hpp"

/*!*****************************************************************************
  \brief
	Default constructor for Button
*******************************************************************************/
Button::Button(){}

/*!*****************************************************************************
  \brief
	This function initializes the component along with any Button specific
	members that need initializing

  \param _parent
	the gameobject that is the parent to this component
*******************************************************************************/
void Button::Init(GameObject* _parent)
{
	Component::Init(_parent);
	transform = static_cast<Transform*>(parent->Get_Component<Transform>());
	ui_transform = static_cast<UITransform*>(parent->Get_Component<UITransform>());

	//TODO: C# BINDINGS
}

/*!*****************************************************************************
  \brief
	Updates the Button transforms to match its transform component
*******************************************************************************/
void Button::Update()
{

}

/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Button::Exit()
{

}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being clicked
*******************************************************************************/
void Button::On_Click()
{
	is_clicked = true;
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being clicked and also every frame
	the button is being held down
*******************************************************************************/
void Button::On_Click_Hold()
{

}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being no longer clicked
*******************************************************************************/
void Button::On_Click_Release()
{
	is_clicked = false;
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being moused over
*******************************************************************************/
void Button::On_Hover_Enter() 
{
	is_hovered = true;
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being moused over and every frame the
	button remains moused over
*******************************************************************************/
void Button::On_Hover()
{

}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being no longer moused over
*******************************************************************************/
void Button::On_Hover_Exit()
{
	is_hovered = false;
}

/*!*****************************************************************************
  \brief
	Returns whether the button is being clicked
  \return
	whether the button is being clicked
*******************************************************************************/
bool const Button::Is_Clicked()
{
	return is_clicked;
}

/*!*****************************************************************************
  \brief
	Returns whether the button is being moused over
  \return
	whether the button is being moused over
*******************************************************************************/
bool const Button::Is_Hovered()
{
	return is_hovered;
}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Button::Get_Component_Type() { return BUTTON; }