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

#include "KeyInputs.h"

/*!*****************************************************************************
  \brief
	Default constructor for Button
*******************************************************************************/
Button::Button() : on_click{ Default_Click }, on_hover_enter{ Default_Button_Update }, on_hover{ Default_Button_Update }, on_hover_exit{ Default_Button_Update } {}

/*!*****************************************************************************
  \brief
	Constructor for Button that creates the Button that triggers functions
	that has a signature like "void name()" based on events that happen to the
	button
  \param _on_click
	function that triggers on click
  \param _on_click_hold
	function that triggers on held click
  \param _on_click_release
	function that triggers on released click
  \param _on_hover_enter
	function that triggers on entering hover state
  \param _on_hover
	function that triggers on hover
  \param _on_hover_exit
	function that triggers on hover exit
*******************************************************************************/
Button::Button(Function_Ptr _on_click, Function_Ptr _on_click_hold, Function_Ptr _on_click_release, Function_Ptr _on_hover_enter, Function_Ptr _on_hover, Function_Ptr _on_hover_exit)
	: on_click{ _on_click }, on_click_hold{ _on_click_hold }, on_click_release{ _on_click_release }, on_hover_enter{ _on_hover_enter }, on_hover{ _on_hover }, on_hover_exit{ _on_hover_exit }
{}

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
	sprite = static_cast<Sprite2D*>(parent->Get_Component<Sprite2D>());
	image = static_cast<Image*>(parent->Get_Component<Image>());	

	mouse_pos.x = static_cast<float>(SAGEInputHandler::Get_Mouse_X());
	mouse_pos.y = static_cast<float>(SAGEInputHandler::Get_Mouse_Y());
	
	ToastBox::Vec3 pos;
	ToastBox::Vec3 scale;
	if (transform)
	{
		pos = transform->Get_Position();
		scale = transform->Get_Scale();
		initial_scale = scale;
	}
	
	if (ui_transform)
	{
		pos = ui_transform->Get_Position();
		scale = ui_transform->Get_Scale();
		initial_scale = scale;
	}

	if (sprite)
	{
		initial_colour = sprite->Get_Colour();
	}
	if (image)
	{
		initial_colour = image->Get_Colour();
	}


	top_right.x = pos.x + (scale.x / 2.f);
	top_right.y = pos.y + (scale.y / 2.f);
	bottom_left.x = pos.x - (scale.x / 2.f);
	bottom_left.y = pos.y - (scale.y / 2.f);

	//TODO: C# BINDINGS
}

/*!*****************************************************************************
  \brief
	This function process any inputs the button might have
*******************************************************************************/
void Button::Input()
{
	if (Within_Bounds())
	{
		if (!is_hovered)
		{
			On_Hover_Enter();
		}
		else 
		{
			On_Hover();
		}

		if (SAGEInputHandler::Get_Mouse_Clicked(SAGE_MOUSE_BUTTON_LEFT))
		{
			On_Click();
		}

		if (SAGEInputHandler::Get_Mouse(SAGE_MOUSE_BUTTON_LEFT) || SAGEInputHandler::Get_Mouse_Clicked(SAGE_MOUSE_BUTTON_LEFT))
		{
			On_Click_Hold();
		}
		else 
		{
			On_Click_Release();
		}
	}
	else
	{
		if (is_hovered)
		{
			On_Hover_Exit();
		}
	}
}

/*!*****************************************************************************
  \brief
	Updates the Button transforms to match its transform component
*******************************************************************************/
void Button::Update()
{
	mouse_pos.x = static_cast<float>(SAGEInputHandler::Get_Mouse_X());
	mouse_pos.y = static_cast<float>(SAGEInputHandler::Get_Mouse_Y());
}

/*!*****************************************************************************
  \brief
	Checks if mouse is within bounds of the button
  \return
	if mouse is within bounds
*******************************************************************************/
bool Button::Within_Bounds()
{
	if ((mouse_pos.x >= bottom_left.x) && (mouse_pos.y >= bottom_left.y))
	{
		if ((mouse_pos.x <= top_right.x) && (mouse_pos.y <= top_right.y))
		{
			return true;
		}
	}
	return false;
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
	if (on_click)
	{
		on_click(Get_Parent());
	}
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being clicked and also every frame
	the button is being held down
*******************************************************************************/
void Button::On_Click_Hold()
{
	if (on_click_hold)
	{
		on_click_hold(Get_Parent());
	}	
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being no longer clicked
*******************************************************************************/
void Button::On_Click_Release()
{
	is_clicked = false;
	if (on_click_release)
	{
		on_click_release(Get_Parent());
	}	
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being moused over
*******************************************************************************/
void Button::On_Hover_Enter() 
{
	is_hovered = true;
	if (on_hover_enter)
	{
		on_hover_enter(Get_Parent());
	}
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being moused over and every frame the
	button remains moused over
*******************************************************************************/
void Button::On_Hover()
{
	if (on_hover)
	{
		on_hover(Get_Parent());
	}
}

/*!*****************************************************************************
  \brief
	Triggers during first frame of button being no longer moused over
*******************************************************************************/
void Button::On_Hover_Exit()
{
	is_hovered = false;
	if (on_hover_exit)
	{
		on_hover_exit(Get_Parent());
	}
}

/*!*****************************************************************************
  \brief
	Returns whether the button is being clicked
  \return
	whether the button is being clicked
*******************************************************************************/
bool const Button::Is_Clicked() const
{
	return is_clicked;
}

/*!*****************************************************************************
  \brief
	Returns whether the button is being moused over
  \return
	whether the button is being moused over
*******************************************************************************/
bool const Button::Is_Hovered() const
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

/*!*****************************************************************************
  \brief
	Default behaviour of button updating its status when event is triggered
  \param _caller
	the caller
*******************************************************************************/
void Default_Button_Update(GameObject* _caller)
{
	Sprite2D* sprite = _caller->Get_Component<Sprite2D>();
	Button* button = _caller->Get_Component<Button>();
	Image* image = _caller->Get_Component<Image>();
	if (button)
	{
		if (button->Is_Hovered())
		{
			if (sprite)
			{
				sprite->Set_Transparency(0.75f);
			}
			else if (image)
			{
				image->Set_Transparency(0.75f);
			}			
		}
		else
		{
			if (sprite)
			{
				sprite->Set_Transparency(1.f);
			}
			else if (image)
			{
				image->Set_Transparency(1.f);
			}
		}
	}
}

/*!*****************************************************************************
  \brief
	Default behaviour of button updating its status when clicked
  \param _caller
	the caller
*******************************************************************************/
void Default_Click(GameObject* _caller)
{
	Sprite2D* sprite = _caller->Get_Component<Sprite2D>();
	Button* button = _caller->Get_Component<Button>();
	Image* image = _caller->Get_Component<Image>();
	if (button->Is_Clicked())
	{
		if (sprite)
		{
			sprite->Set_Transparency(0.2f);
		}
		else if (image)
		{
			image->Set_Transparency(0.2f);
		}
	}
}