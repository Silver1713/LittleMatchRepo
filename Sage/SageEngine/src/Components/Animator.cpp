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
		states[s.name] = s;
	}

	for (auto const& p : animation_set.parameters)
	{
		param_values[p.name] = p.value;
	}

	for (auto& t : animation_set.transitions)
	{
		for (auto& c : t.conditions)
		{
			conditions[c.parameter] = c.value;

			if (c.type == "equals")
			{
				c.comparator = [](float a, float b) {return (a == b); };
			}
			else if (c.type == "not_equals")
			{
				c.comparator = [](float a, float b) {return (a != b); };
			}
			else if (c.type == "greater_than")
			{
				c.comparator = [](float a, float b) {return (a > b); };
			}
			else if (c.type == "less_than")
			{
				c.comparator = [](float a, float b) {return (a < b); };
			}
			else if (c.type == "greater_than_or_equals_to")
			{
				c.comparator = [](float a, float b) {return (a >= b); };
			}
			else if (c.type == "less_than_or_equals_to")
			{
				c.comparator = [](float a, float b) {return (a <= b); };
			}
			else 
			{
				c.comparator = [](float a, float b) {return (a == b); };
			}			
		}
	}
	
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
	for (auto& t : animation_set.transitions)
	{
		if (t.to_state == current_state.name)
		{
			continue;
		}

		if (t.from_state == current_state.name || t.from_state == "any")
		{
			bool pass{ true };
			for (auto& c : t.conditions)
			{
				if (!(c.comparator(param_values[c.parameter], c.value)))
				{
					pass = false;
				}				
			}
			if (pass)
			{
				Switch_State(states[t.to_state]);
			}			
		}
	}

	internal_timer += ((float)SageTimer::delta_time * current_state.speed_multiplier);

	if (internal_timer > current_state.animation.frame_time)
	{
		Go_To_Next_Frame();
		internal_timer = 0.f;
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
	current_frame = current_frame + 1;
	
	if (current_state.looping && (current_frame >= current_state.animation.num_frames))
	{
		current_frame = 0;
	}
	else if (!current_state.looping && (current_frame >= current_state.animation.num_frames))
	{
		current_frame = current_state.animation.num_frames - 1;
	}

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
	Sets the flag _flag to bool _b for the purpose of animator conditionals. For
	true/false, 1.f is true, 0.f is false

  \param _param
	name of the flag

  \param _new_value
	the new value of the flag
*******************************************************************************/
void Animator::Set_Parameter(std::string const& _param, float const _new_value)
{
	if (param_values.find(_param) != param_values.end())
	{
		param_values[_param] = _new_value;
	}	
}

/*!*****************************************************************************
  \brief
	Sets all parameters to 0.f
*******************************************************************************/
void Animator::Reset_Parameters()
{
	for (auto& p : param_values)
	{
		p.second = 0.f;
	}
}