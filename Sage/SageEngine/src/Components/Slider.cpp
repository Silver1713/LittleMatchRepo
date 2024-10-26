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
#include "SageHelper.hpp"
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/UITransform.hpp"
#include "Components/Slider.hpp"

#include "KeyInputs.h"

#include <iostream>

namespace Sliders
{
	std::unordered_map<std::string, void(*)(GameObject*)> slider_functions =
	{
		{"Demo_Init", Demo_Init},
		{"Demo_Update", Demo_Update},
	};

	/*!*****************************************************************************
	  \brief
		Gets the function from the map of button functions
	*******************************************************************************/
	void(*Get_Slider_Function(std::string const& _key))(GameObject*)
	{
		if (slider_functions.find(_key) != slider_functions.end())
		{
			return slider_functions[_key];
		}
		else
		{
			return nullptr;
		}
	}

	void Demo_Init(GameObject* _caller)
	{
		Slider* s = _caller->Get_Component<Slider>();
		if (s)
		{
			s->Set_Max(10.f);
			s->Set_Min(0.f);
			s->Set_Value(0.0f);
		}
	}
	void Demo_Update(GameObject* _caller)
	{
		Slider* s = _caller->Get_Component<Slider>();
		if (s)
		{
			float cur_value{ s->Get_Value() };
			static float direction{ 1.f };
			if (cur_value >= s->Get_Max())
			{
				direction = -1.f;
			}
			else if (cur_value < s->Get_Min())
			{
				direction = 1.f;
			}
			s->Add_Value(static_cast<float>(SageHelper::delta_time) * direction);
		}
	}
}

/*!*****************************************************************************
  \brief
	Default constructor for Slider
*******************************************************************************/
Slider::Slider() {}

/*!*****************************************************************************
  \brief
	Constructor for Slider that assigns that is the children gameobjects that is
	the fill, bg and border

  \param _fill
	the fill gameobject

  \param _bg
	the background gameobject

  \param _border
	the border gameobject

  \param _init
	the string that is the key of the function that is mapped in slider functions

  \param _update
	the string that is the key of the function that is mapped in slider functions
*******************************************************************************/
Slider::Slider(GameObject* _frame, GameObject* _fill, GameObject* _bg, std::string const& _init, std::string const& _update) : frame_gameobject{ _frame }, fill_gameobject{ _fill }, background_gameobject{ _bg }, init{ Sliders::Get_Slider_Function(_init) }, update{ Sliders::Get_Slider_Function(_update) }
{}

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
	ui_transform = static_cast<UITransform*>(parent->Get_Component<UITransform>());
	image = static_cast<Image*>(parent->Get_Component<Image>());

	if (fill_gameobject)
	{
		fill_image = static_cast<Image*>(fill_gameobject->Get_Component<Image>());
	}
	if (background_gameobject)
	{
		background_image = static_cast<Image*>(background_gameobject->Get_Component<Image>());
	}
	if (frame_gameobject)
	{
		frame_image = static_cast<Image*>(frame_gameobject->Get_Component<Image>());
	}

	fill_gameobject->Set_Position(_parent->Get_Position());
	background_gameobject->Set_Position(_parent->Get_Position());
	frame_gameobject->Set_Position(_parent->Get_Position());

	if (init)
	{
		init(parent);
	}
}

/*!*****************************************************************************
  \brief
	Updates the Button transforms to match its transform component
*******************************************************************************/
void Slider::Update() 
{
	if (!is_enabled) { return; }
	if (update)
	{
		update(parent);
	}

	UITransform* ut = fill_gameobject->Get_Component<UITransform>();
	UITransform* ut_frame = frame_gameobject->Get_Component<UITransform>();

	float bar_width{ ut_frame->Get_Scale().x };
	float scale_x{ (cur_value/max_value) * bar_width};

	ToastBox::Vec3 _new_scale{ scale_x,ut_frame->Get_Scale().y,ut_frame->Get_Scale().z };
	ut->Set_Scale(_new_scale);

	float left_point{ ut_frame->Get_Position().x - (ut_frame->Get_Scale().x / 2.f) };
	float smaller_left_point{ ut->Get_Position().x - (ut->Get_Scale().x / 2.f) };
	float pos_x{ (ut->Get_Position().x) + (left_point - smaller_left_point) };

	ToastBox::Vec3 _new_pos{ pos_x,ui_transform->Get_Position().y,ui_transform->Get_Position().z };
	ut->Set_Position(_new_pos);
}

/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Slider::Exit() {}

/*!*****************************************************************************
  \brief
	Various self-explanatory functions to get or set slider data
*******************************************************************************/
void Slider::Set_Max(float const _new_max)
{
	max_value = _new_max;
}

float const Slider::Get_Max() const
{
	return max_value;
}

void Slider::Set_Min(float const _new_min)
{
	min_value = _new_min;
}

float const Slider::Get_Min() const
{
	return min_value;
}

void Slider::Set_Value(float const _new_val)
{
	cur_value = _new_val;
}

void Slider::Add_Value(float const _add_val)
{
	cur_value += _add_val;
}

float const Slider::Get_Value() const
{
	return cur_value;
}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Slider::Get_Component_Type() { return SLIDER; }