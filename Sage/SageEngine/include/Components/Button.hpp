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
#include <vector>

class Button : public Component
{
private:
	Transform* transform{ nullptr };
	UITransform* ui_transform{ nullptr };
	bool is_clicked{ false };
	bool is_hovered{ false };

	

public:

	/*!*****************************************************************************
	  \brief
		Default constructor for Button
	*******************************************************************************/
	Button();

	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any Button specific
		members that need initializing

	  \param _parent
		the gameobject that is the parent to this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Updates the Button transforms to match its transform component
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
		Triggers during first frame of button being clicked
	*******************************************************************************/
	void On_Click();

	/*!*****************************************************************************
	  \brief
		Triggers during first frame of button being clicked and also every frame
		the button is being held down
	*******************************************************************************/
	void On_Click_Hold();

	/*!*****************************************************************************
	  \brief
		Triggers during first frame of button being no longer clicked
	*******************************************************************************/
	void On_Click_Release();

	/*!*****************************************************************************
	  \brief
		Triggers during first frame of button being moused over
	*******************************************************************************/
	void On_Hover_Enter();

	/*!*****************************************************************************
	  \brief
		Triggers during first frame of button being moused over and every frame the
		button remains moused over
	*******************************************************************************/
	void On_Hover();

	/*!*****************************************************************************
	  \brief
		Triggers during first frame of button being no longer moused over
	*******************************************************************************/
	void On_Hover_Exit();

	/*!*****************************************************************************
	  \brief
		Returns whether the button is being clicked
	  \return
		whether the button is being clicked
	*******************************************************************************/
	bool const Is_Clicked();

	/*!*****************************************************************************
	  \brief
		Returns whether the button is being moused over
	  \return
		whether the button is being moused over
	*******************************************************************************/
	bool const Is_Hovered();

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;
};
