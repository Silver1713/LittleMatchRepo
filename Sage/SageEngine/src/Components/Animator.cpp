/* Start Header ************************************************************************/
/*!
\file		Animator.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		11 September 2024
\brief		Contains the derived class Animator that overrides the virtual functions of the
			base class Component to do animator specific tasks. Times itself to pass the
			sprites to the gameobject's rendering component to simulate an animation
			based on flags provided by the animation set

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "GameObjects.hpp"
#include "Components/Animator.hpp"
#include "SageObjectManager.hpp"

#include <iostream>

#include "SageTimer.hpp"

/*!*****************************************************************************
  \brief
	Default constructor for Animator
*******************************************************************************/
Animator::Animator() {}
/*!*****************************************************************************
  \brief
	Constructor for Animator that initializes the animation set based on the
	provided ID

  \param _animation_set_ID
	What animation the sprite will use
*******************************************************************************/
Animator::Animator(std::string const& _animation_set_ID) : animation_set{Assets::Animation_Set::Get_Animation_Set(_animation_set_ID)} {}

/*!*****************************************************************************
  \brief
	This function initializes the component along with any Animator specific
	members that need initializing

  \param _parent
	the gameobject that created this component
*******************************************************************************/
void Animator::Init(GameObject* _parent)
{
	Component::Init(_parent);
	//will use whichever is not nullptr
	sprite = static_cast<Sprite2D*>(parent->Get_Component<Sprite2D>());
	image = static_cast<Image*>(parent->Get_Component<Image>());
	
	if (sprite)
	{
		obj = sprite->Get_Object();
	}
	else
	{
		obj = image->Get_Object();
	}
}

/*!*****************************************************************************
  \brief
	Updates the Animator's internal logic to give the correct sprite to the
	Image or Sprite2D to be drawn
*******************************************************************************/
void Animator::Update()
{
	internal_timer += (float)SageTimer::delta_time;
	std::string cur_animation_key{};


	//if (internal_timer > animation_set.animations[animation_set.animation_IDs].frame_time)
	//{
	//}
}

/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Animator::Exit() {}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Animator::Get_Component_Type() { return ANIMATOR; }

/*!*****************************************************************************
  \brief
	Sets the flag _flag to bool _b for the purpose of animator conditionals

  \param _param
	name of the flag

  \param _b
	the bool to set the flag to
*******************************************************************************/
void Animator::Set_Parameter(std::string const& _param, bool _b)
{
	/*if (animation_set.flags.find(_flag) != animation_set.flags.end())
	{
		animation_set.flags[_flag] = _b;
	}*/
}