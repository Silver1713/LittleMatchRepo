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
#pragma once
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/UITransform.hpp"
#include "Components/Sprite2D.hpp"
#include "Components/Image.hpp"
#include <vector>

namespace Sliders
{
	void(*Get_Slider_Function(std::string const& _key))(GameObject*);

	void Demo_Init(GameObject* _caller);
	void Demo_Update(GameObject* _caller);
}

class Slider : public Component
{
private:
	typedef void(*Function_Ptr)(GameObject*);

	UITransform* ui_transform{ nullptr };
	Image* image{ nullptr };

	GameObject* fill_gameobject{ nullptr };
	Image* fill_image{ nullptr };

	GameObject* background_gameobject{ nullptr };
	Image* background_image{ nullptr };

	GameObject* frame_gameobject{ nullptr };
	Image* frame_image{ nullptr };

	float cur_value{};
	float min_value{};
	float max_value{};

	ToastBox::Vec2 anchor_modifier{};
	ToastBox::Vec3 cur_value_scale{};
	
	Function_Ptr init{ nullptr };
	Function_Ptr update{ nullptr };

public:

	/*!*****************************************************************************
	  \brief
		Default constructor for Slider
	*******************************************************************************/
	Slider();

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
	*******************************************************************************/
	Slider(GameObject* _fill, GameObject* _bg, GameObject* _frame, std::string const& _init = "", std::string const& _update = "");

	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any Slider specific
		members that need initializing

	  \param _parent
		the gameobject that is the parent to this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Updates the Slider transforms to match its transform component
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
		Various self-explanatory functions to get or set slider data
	*******************************************************************************/
	void Set_Max(float const _new_max);
	float const Get_Max() const;

	void Set_Min(float const _new_min);
	float const Get_Min() const;

	void Set_Value(float const _new_val);
	void Add_Value(float const _add_val);
	float const Get_Value() const;

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;
};