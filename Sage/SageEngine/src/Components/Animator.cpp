/* Start Header ************************************************************************/
/*!
\file		Animator.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		13 October 2024
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
	
	for (auto const& s : animation_set.states)
	{
		if (s.is_starting_state)
		{
			current_state = s;
		}
	}	

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
	internal_timer += ((float)SageTimer::delta_time * current_state.speed_multiplier);
	std::string cur_animation_key{};


	if (internal_timer > current_state.animation.frame_time)
	{
		Go_To_Next_Frame();
	}
}

/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Animator::Exit() {}

/*!*****************************************************************************
  \brief
	Transitions into a different state

  \param _new_state
	name of the new state to transition into
*******************************************************************************/
void Animator::Switch_State(Assets::Animation_Set::State const& _new_state)
{
	current_state = _new_state;
}

/*!*****************************************************************************
  \brief
	Gets the next frame in the current state's animation
*******************************************************************************/
void Animator::Go_To_Next_Frame()
{
	current_frame = (current_frame + 1) > current_state.animation.num_frames ? 0 : (current_frame + 1);

	if (obj)
	{
		(*obj)->Attach_Texture(&Assets::Textures::Get_Texture(current_state.animation.parent_texture_ID + '_' + std::to_string(current_frame)));
	}
}

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