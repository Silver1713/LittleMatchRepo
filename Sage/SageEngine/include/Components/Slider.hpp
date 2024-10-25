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

class Slider : public Component
{
private:
	Transform* transform{ nullptr };
	UITransform* ui_transform{ nullptr };
	Sprite2D* sprite{ nullptr };
	Image* image{ nullptr };

	float cur_value{};
	float min_value{};
	float max_value{};

public:

	Slider();

	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		This function process any inputs the slider might have
	*******************************************************************************/
	void Input() override;

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
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;
};