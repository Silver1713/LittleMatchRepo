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

namespace Buttons
{	
	/*!*****************************************************************************
	  \brief
		Gets the function from the map of button functions
	*******************************************************************************/
	void(*Get_Button_Function(std::string const& _key))(GameObject*);

	/*!*****************************************************************************
	  \brief
		Default behaviour of button updating its status when event is triggered
	  \param _caller
		the caller
	*******************************************************************************/
	void Default_Button_Update(GameObject* _caller);

	/*!*****************************************************************************
	  \brief
		Default behaviour of button updating its status when clicked
	  \param _caller
		the caller
	*******************************************************************************/
	void Default_Click(GameObject* _caller);

	/*!*****************************************************************************
	  \brief
		Function to go to a specific scene
	  \param _caller
		the caller
	*******************************************************************************/
	void Go_To_Splash_Screen(GameObject* _caller);
	void Go_To_Main_Menu(GameObject* _caller);	
	void Go_To_Level_1(GameObject* _caller);
	void Exit_Game(GameObject* _caller);
}

class Button : public Component
{
private:
	typedef void(*Function_Ptr)(GameObject*);
	Transform* transform{ nullptr };
	UITransform* ui_transform{ nullptr };
	Sprite2D* sprite{ nullptr };
	Image* image{ nullptr };
	bool is_clicked{ false };
	bool is_hovered{ false };

	ToastBox::Vec2 mouse_pos{};
	ToastBox::Vec2 top_right{};
	ToastBox::Vec2 bottom_left{};

	Function_Ptr on_click{ nullptr };
	Function_Ptr on_click_hold{ nullptr };
	Function_Ptr on_click_release{ nullptr };
	Function_Ptr on_hover_enter{ nullptr };
	Function_Ptr on_hover{ nullptr };
	Function_Ptr on_hover_exit{ nullptr };

public:
	ToastBox::Vec4 initial_colour{};
	ToastBox::Vec3 initial_scale{};

	/*!*****************************************************************************
	  \brief
		Default constructor for Button
	*******************************************************************************/
	Button();

	/*!*****************************************************************************
	  \brief
		Constructor for Button that creates the Button that triggers functions
		that has a signature like "void Name(GameObject* _caller)" based on events that happen to the
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
	Button(Function_Ptr _on_click, Function_Ptr _on_click_hold, Function_Ptr _on_click_release, Function_Ptr _on_hover_enter, Function_Ptr _on_hover, Function_Ptr _on_hover_exit);

	/*!*****************************************************************************
	  \brief
		Constructor for Button that creates the Button that triggers functions
		that has a signature like "void Name(GameObject* _caller)" based on events that happen to the
		button. Instead, this constructor takes the string that represents each function pointer to
		be initialized with
	  \param _on_click
		key of the function that triggers on click
	  \param _on_click_hold
		key of the function that triggers on held click
	  \param _on_click_release
		key of the function that triggers on released click
	  \param _on_hover_enter
		key of the function that triggers on entering hover state
	  \param _on_hover
		key of the function that triggers on hover
	  \param _on_hover_exit
		key of the function that triggers on hover exit
	*******************************************************************************/
	Button(std::string const& _on_click, std::string const& _on_click_hold, std::string const& _on_click_release, std::string const& _on_hover_enter, std::string const& _on_hover, std::string const& _on_hover_exit);

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
		This function process any inputs the button might have
	*******************************************************************************/
	void Input() override;

	/*!*****************************************************************************
	  \brief
		Updates the Button transforms to match its transform component
	*******************************************************************************/
	void Update() override;

	/*!*****************************************************************************
	  \brief
		Checks if mouse is within bounds of the button
	  \return
		if mouse is within bounds
	*******************************************************************************/
	bool const Within_Bounds() const;

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
	bool const Is_Clicked() const;

	/*!*****************************************************************************
	  \brief
		Returns whether the button is being moused over
	  \return
		whether the button is being moused over
	*******************************************************************************/
	bool const Is_Hovered() const;

	/*!*****************************************************************************
	  \brief
		Sets the On_Click function to the provided parameter
	  \param _new_on_click
		the new function
	*******************************************************************************/
	void Set_On_Click(Function_Ptr _new_on_click);

	/*!*****************************************************************************
	  \brief
		Sets the On_Click_Hold function to the provided parameter
	  \param _new_on_click_hold
		the new function
	*******************************************************************************/
	void Set_On_Click_Hold(Function_Ptr _new_on_click_hold);

	/*!*****************************************************************************
	  \brief
		Sets the On_Click_Release function to the provided parameter
	  \param _new_on_click_release
		the new function
	*******************************************************************************/
	void Set_On_Click_Release(Function_Ptr _new_on_click_release);

	/*!*****************************************************************************
	  \brief
		Sets the On_Hover_Enter function to the provided parameter
	  \param _new_on_hover_enter
		the new function
	*******************************************************************************/
	void Set_On_Hover_Enter(Function_Ptr _new_on_hover_enter);

	/*!*****************************************************************************
	  \brief
		Sets the On_Hover function to the provided parameter
	  \param _new_on_hover
		the new function
	*******************************************************************************/
	void Set_On_Hover(Function_Ptr _new_on_hover);

	/*!*****************************************************************************
	  \brief
		Sets the On_Hover_Exit function to the provided parameter
	  \param _new_on_hover_exit
		the new function
	*******************************************************************************/
	void Set_On_Hover_Exit(Function_Ptr _new_on_hover_exit);


	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;
};